/*
 * Laigter: an automatic map generator for lighting effects.
 * Copyright (C) 2019  Pablo Ivan Fonovich
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 * Contact: azagaya.games@gmail.com
 */

#include "win_install.h"

#include <QCheckBox>
#include <QCoreApplication>
#include <QDesktopServices>
#include <QDialog>
#include <QDialogButtonBox>
#include <QDir>
#include <QDirIterator>
#include <QFileDialog>
#include <QFileInfo>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QProcess>
#include <QPushButton>
#include <QRadioButton>
#include <QSettings>
#include <QStandardPaths>
#include <QTextBrowser>
#include <QTextStream>
#include <QUrl>
#include <QVBoxLayout>

#include <shlobj.h>

namespace
{
const QString project_id = "Laigter.Project";

struct Options
{
  bool install = true;
  QString path;
  bool shortcut = true;
  bool desktop_shortcut = true;
  bool association = true;
  bool uninstall_entry = true;

  int extras() const
  {
    return (shortcut ? WinInstall::Shortcut : 0) |
           (desktop_shortcut ? WinInstall::DesktopShortcut : 0) |
           (association ? WinInstall::Association : 0) |
           (uninstall_entry ? WinInstall::UninstallEntry : 0);
  }
};

/* Everything the install writes goes either in the user hive or, when we had to
 * elevate, in the machine one */
QString hive(bool machine)
{
  return machine ? "HKEY_LOCAL_MACHINE" : "HKEY_CURRENT_USER";
}

QString uninstall_key(bool machine)
{
  return hive(machine) +
         "\\Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\Laigter";
}

/* Where laigter is installed, kept apart from the uninstall entry because that
 * one is optional and this is what a later setup uses to offer an update */
QString laigter_key(bool machine)
{
  return hive(machine) + "\\Software\\Azagaya\\Laigter";
}

QString classes_key(bool machine) { return hive(machine) + "\\Software\\Classes"; }

QString app_dir() { return QCoreApplication::applicationDirPath(); }

QString portable_marker() { return app_dir() + "/portable.txt"; }

QString installed_marker() { return app_dir() + "/installed.txt"; }

QString shortcut_file(bool machine)
{
  if (!machine)
  {
    return QStandardPaths::writableLocation(QStandardPaths::ApplicationsLocation) +
           "/Laigter.lnk";
  }

  QString data = qEnvironmentVariable("ProgramData", "C:/ProgramData");
  return data + "/Microsoft/Windows/Start Menu/Programs/Laigter.lnk";
}

/* The public desktop when we installed for everyone, ours otherwise */
QString desktop_shortcut_file(bool machine)
{
  if (!machine)
  {
    return QStandardPaths::writableLocation(QStandardPaths::DesktopLocation) +
           "/Laigter.lnk";
  }

  QString shared = qEnvironmentVariable("PUBLIC", "C:/Users/Public");
  return shared + "/Desktop/Laigter.lnk";
}

QString recorded_install()
{
  foreach (bool machine, QList<bool>() << false << true)
  {
    QSettings ours(laigter_key(machine), QSettings::NativeFormat);
    QString dir = ours.value("InstallLocation").toString();
    if (!dir.isEmpty())
      return dir;

    QSettings key(uninstall_key(machine), QSettings::NativeFormat);
    dir = key.value("InstallLocation").toString();
    if (!dir.isEmpty())
      return dir;
  }

  return QString();
}

bool same_dir(QString a, QString b)
{
  if (a.isEmpty() || b.isEmpty())
    return false;

  a = QDir::cleanPath(QDir(a).absolutePath());
  b = QDir::cleanPath(QDir(b).absolutePath());
  return a.compare(b, Qt::CaseInsensitive) == 0;
}

/* Can we create this folder, or does it need admin rights */
bool is_writable(const QString &dir)
{
  QString existing = QDir::cleanPath(QDir(dir).absolutePath());
  while (!existing.isEmpty() && !QDir(existing).exists())
  {
    QString up = QFileInfo(existing).absolutePath();
    if (up == existing)
      break;
    existing = up;
  }

  QFile probe(existing + "/.laigter-write-test");
  if (!probe.open(QIODevice::WriteOnly))
    return false;

  probe.close();
  probe.remove();
  return true;
}

/* Runs ourselves again through the uac prompt and waits for it to finish */
bool run_elevated(const QString &arguments, int *exit_code)
{
  QString exe = QDir::toNativeSeparators(QCoreApplication::applicationFilePath());

  SHELLEXECUTEINFOW info;
  memset(&info, 0, sizeof(info));
  info.cbSize = sizeof(info);
  info.fMask = SEE_MASK_NOCLOSEPROCESS;
  info.lpVerb = L"runas";
  info.lpFile = reinterpret_cast<LPCWSTR>(exe.utf16());
  info.lpParameters = reinterpret_cast<LPCWSTR>(arguments.utf16());
  info.nShow = SW_SHOWNORMAL;

  if (!ShellExecuteExW(&info))
    return false; /* usually the user said no to the prompt */

  WaitForSingleObject(info.hProcess, INFINITE);

  DWORD code = 1;
  GetExitCodeProcess(info.hProcess, &code);
  CloseHandle(info.hProcess);

  if (exit_code)
    *exit_code = int(code);

  return true;
}

bool write_marker(const QString &path, const QString &text)
{
  QFile marker(path);
  if (!marker.open(QIODevice::WriteOnly))
    return false;

  QTextStream(&marker) << text << "\n";
  marker.close();
  return true;
}

bool copy_dir(const QString &from, const QString &to)
{
  QDir source(from);
  if (!QDir().mkpath(to))
    return false;

  QDirIterator it(from, QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot,
                  QDirIterator::Subdirectories);
  while (it.hasNext())
  {
    it.next();
    QString target = to + "/" + source.relativeFilePath(it.filePath());

    if (it.fileInfo().isDir())
    {
      if (!QDir().mkpath(target))
        return false;
      continue;
    }

    /* Overwrite, we could be updating an older install */
    QFile::remove(target);
    if (!QFile::copy(it.filePath(), target))
      return false;
  }

  return true;
}

/* A folder cannot delete itself while we run from it, so leave a script behind
 * that waits for us to quit and then removes the folder and itself */
void schedule_removal(const QString &dir, const QString &script_name)
{
  QString script_path = QDir::tempPath() + "/" + script_name;
  QFile script(script_path);
  if (!script.open(QIODevice::WriteOnly))
    return;

  QTextStream out(&script);
  out << "@echo off\r\n"
      << "ping 127.0.0.1 -n 4 > nul\r\n"
      << "rmdir /s /q \"" << QDir::toNativeSeparators(dir) << "\"\r\n"
      << "del \"%~f0\"\r\n";
  script.close();

  QProcess::startDetached("cmd.exe", QStringList() << "/c" << script_path);
}

/* Copies laigter and sets up whatever the user allowed. machine means we are
 * the elevated copy, so everything goes to the machine wide places */
bool do_install(const QString &dir, int extras, bool machine, QWidget *parent)
{
  if (!copy_dir(app_dir(), dir))
  {
    QMessageBox::warning(parent, QObject::tr("Laigter"),
                         QObject::tr("Could not copy Laigter to %1").arg(dir));
    return false;
  }

  QString exe = QDir::toNativeSeparators(dir + "/laigter.exe");

  QFile::remove(dir + "/portable.txt");
  write_marker(dir + "/installed.txt", QObject::tr("Installed by Laigter"));

  QSettings ours(laigter_key(machine), QSettings::NativeFormat);
  ours.setValue("InstallLocation", QDir::toNativeSeparators(dir));

  if (extras & WinInstall::Association)
  {
    QSettings classes(classes_key(machine), QSettings::NativeFormat);
    classes.setValue(".laigter/Default", project_id);
    classes.setValue(project_id + "/Default", QObject::tr("Laigter Project"));
    classes.setValue(project_id + "/DefaultIcon/Default", exe + ",0");
    classes.setValue(project_id + "/shell/open/command/Default",
                     "\"" + exe + "\" \"%1\"");

    SHChangeNotify(SHCNE_ASSOCCHANGED, SHCNF_IDLIST, nullptr, nullptr);
  }

  if (extras & WinInstall::UninstallEntry)
  {
    QSettings key(uninstall_key(machine), QSettings::NativeFormat);
    key.setValue("DisplayName", "Laigter");
    key.setValue("DisplayVersion", QCoreApplication::applicationVersion());
    key.setValue("DisplayIcon", exe);
    key.setValue("Publisher", "Azagaya");
    key.setValue("InstallLocation", QDir::toNativeSeparators(dir));
    key.setValue("UninstallString", "\"" + exe + "\" --uninstall");
    key.setValue("NoModify", 1);
    key.setValue("NoRepair", 1);
  }

  if (extras & WinInstall::Shortcut)
  {
    QFile::remove(shortcut_file(machine));
    QFile::link(exe, shortcut_file(machine));
  }

  if (extras & WinInstall::DesktopShortcut)
  {
    QFile::remove(desktop_shortcut_file(machine));
    QFile::link(exe, desktop_shortcut_file(machine));
  }

  return true;
}

/* Where to put laigter, and what it may touch outside its own folder */
bool ask(QWidget *parent, const QString &setup_dir, Options &options)
{
  QString existing = recorded_install();
  /* Under the user, so the usual install needs no admin rights. Browsing to
   * program files still works, it just goes through the uac prompt */
  QString fresh_install =
      qEnvironmentVariable("LOCALAPPDATA",
                           QStandardPaths::writableLocation(QStandardPaths::GenericConfigLocation)) +
      "/Programs/Laigter";
  QString portable_default =
      (setup_dir.isEmpty() ? QDir::currentPath() : setup_dir) + "/Laigter";

  QDialog dialog(parent);
  dialog.setWindowTitle(QObject::tr("Laigter"));

  QRadioButton *install = new QRadioButton(QObject::tr("Install"));
  QRadioButton *portable = new QRadioButton(QObject::tr("Portable, keep everything in one folder"));
  install->setChecked(true);

  QRadioButton *update_existing = new QRadioButton(
      QObject::tr("Update the installation in %1").arg(QDir::toNativeSeparators(existing)));
  QRadioButton *new_install = new QRadioButton(QObject::tr("Install in another folder"));
  update_existing->setChecked(true);
  update_existing->setVisible(!existing.isEmpty());
  new_install->setVisible(!existing.isEmpty());

  QLineEdit *location = new QLineEdit;
  QPushButton *browse = new QPushButton(QObject::tr("Browse..."));
  QLabel *admin_note = new QLabel;

  QCheckBox *shortcut = new QCheckBox(QObject::tr("Create a start menu shortcut"));
  QCheckBox *desktop_shortcut = new QCheckBox(QObject::tr("Create a desktop shortcut"));
  QCheckBox *association = new QCheckBox(QObject::tr("Open .laigter projects with Laigter"));
  QCheckBox *uninstall_entry = new QCheckBox(QObject::tr("Show Laigter in add or remove programs"));
  shortcut->setChecked(true);
  desktop_shortcut->setChecked(true);
  association->setChecked(true);
  uninstall_entry->setChecked(true);

  QGroupBox *extras = new QGroupBox(QObject::tr("While installing"));
  QVBoxLayout *extras_layout = new QVBoxLayout(extras);
  extras_layout->addWidget(update_existing);
  extras_layout->addWidget(new_install);
  extras_layout->addWidget(shortcut);
  extras_layout->addWidget(desktop_shortcut);
  extras_layout->addWidget(association);
  extras_layout->addWidget(uninstall_entry);

  /* Folders like program files need admin rights, so say it before continuing */
  auto check_path = [=]() {
    bool needs_admin = install->isChecked() && !is_writable(location->text());
    admin_note->setText(needs_admin
                            ? QObject::tr("Windows will ask for administrator "
                                          "rights to install here")
                            : QString());
  };

  auto refresh = [=]() {
    bool updating = install->isChecked() && !existing.isEmpty() &&
                    update_existing->isChecked();
    extras->setEnabled(install->isChecked());
    location->setReadOnly(updating);
    browse->setEnabled(!updating);

    if (updating)
      location->setText(QDir::toNativeSeparators(existing));
    else if (install->isChecked())
      location->setText(QDir::toNativeSeparators(fresh_install));
    else
      location->setText(QDir::toNativeSeparators(portable_default));

    check_path();
  };

  QObject::connect(install, &QRadioButton::toggled, &dialog, refresh);
  QObject::connect(update_existing, &QRadioButton::toggled, &dialog, refresh);
  QObject::connect(location, &QLineEdit::textChanged, &dialog, check_path);
  QObject::connect(browse, &QPushButton::clicked, &dialog, [&dialog, location]() {
    QString start = QFileInfo(location->text()).absolutePath();
    QString chosen = QFileDialog::getExistingDirectory(
        &dialog, QObject::tr("Where to put Laigter"), start);
    if (!chosen.isEmpty())
      location->setText(QDir::toNativeSeparators(chosen + "/Laigter"));
  });

  QHBoxLayout *location_layout = new QHBoxLayout;
  location_layout->addWidget(location);
  location_layout->addWidget(browse);

  QTextBrowser *license = new QTextBrowser;
  QFile license_file(":/LICENSE");
  if (license_file.open(QIODevice::ReadOnly))
    license->setPlainText(QString::fromUtf8(license_file.readAll()));

  QDialogButtonBox *buttons =
      new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
  buttons->button(QDialogButtonBox::Ok)->setText(QObject::tr("Continue"));
  QObject::connect(buttons, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
  QObject::connect(buttons, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

  QVBoxLayout *layout = new QVBoxLayout(&dialog);
  layout->addWidget(new QLabel(QObject::tr("How do you want to use Laigter?")));
  layout->addWidget(install);
  layout->addWidget(portable);
  layout->addWidget(extras);
  layout->addWidget(new QLabel(QObject::tr("Folder:")));
  layout->addLayout(location_layout);
  layout->addWidget(admin_note);
  layout->addWidget(new QLabel(QObject::tr("Laigter is free software, released under the GPL v3:")));
  layout->addWidget(license);
  layout->addWidget(buttons);

  dialog.resize(580, 640);
  refresh();

  if (dialog.exec() != QDialog::Accepted)
    return false;

  options.install = install->isChecked();
  options.path = QDir::fromNativeSeparators(location->text()).trimmed();
  options.shortcut = shortcut->isChecked();
  options.desktop_shortcut = desktop_shortcut->isChecked();
  options.association = association->isChecked();
  options.uninstall_entry = uninstall_entry->isChecked();
  return !options.path.isEmpty();
}
} // namespace

WinInstall::Mode WinInstall::current_mode()
{
  if (QFileInfo::exists(portable_marker()))
    return Mode::Portable;

  if (QFileInfo::exists(installed_marker()))
    return Mode::Installed;

  /* The marker is gone but we still know this folder */
  if (same_dir(recorded_install(), app_dir()))
    return Mode::Installed;

  return Mode::FirstRun;
}

bool WinInstall::first_run(QWidget *parent, const QString &setup_dir)
{
  Options options;
  if (!ask(parent, setup_dir, options))
    return false; /* cancelled, run this once from the temporary folder */

  if (options.install)
  {
    if (is_writable(options.path))
    {
      if (!do_install(options.path, options.extras(), false, parent))
        return false;
    }
    else
    {
      /* Program files and the like. Our elevated copy does the work and we
       * start laigter afterwards, so the app itself does not run as admin */
      QString arguments = QString("--install-to \"%1\" --install-extras %2")
                              .arg(QDir::toNativeSeparators(options.path))
                              .arg(options.extras());
      int result = 1;
      if (!run_elevated(arguments, &result))
      {
        QMessageBox::warning(parent, QObject::tr("Laigter"),
                             QObject::tr("Laigter was not installed, "
                                         "administrator rights were refused."));
        return false;
      }
      if (result != 0)
      {
        QMessageBox::warning(parent, QObject::tr("Laigter"),
                             QObject::tr("Could not install Laigter in %1").arg(options.path));
        return false;
      }
    }
  }
  else
  {
    if (!copy_dir(app_dir(), options.path))
    {
      QMessageBox::warning(parent, QObject::tr("Laigter"),
                           QObject::tr("Could not copy Laigter to %1").arg(options.path));
      return false;
    }

    write_marker(options.path + "/portable.txt",
                 QObject::tr("Laigter runs portable while this file is here"));

    /* Nothing points at a portable copy, so at least say where it went */
    QMessageBox where(parent);
    where.setWindowTitle(QObject::tr("Laigter"));
    where.setText(QObject::tr("Laigter lives in %1")
                      .arg(QDir::toNativeSeparators(options.path)));
    where.setInformativeText(QObject::tr("Start it from there next time, or "
                                         "move that folder wherever you want."));
    QPushButton *open = where.addButton(QObject::tr("Open folder"), QMessageBox::ActionRole);
    where.addButton(QMessageBox::Ok);
    where.exec();

    if (where.clickedButton() == open)
      QDesktopServices::openUrl(QUrl::fromLocalFile(options.path));
  }

  return QProcess::startDetached(options.path + "/laigter.exe", QStringList());
}

bool WinInstall::install_for_all_users(const QString &dir, int extras)
{
  return do_install(dir, extras, true, nullptr);
}

bool WinInstall::uninstall(QWidget *parent, bool confirmed)
{
  QString dir = app_dir();

  if (!confirmed &&
      QMessageBox::question(parent, QObject::tr("Laigter"),
                            QObject::tr("Remove Laigter from %1?").arg(dir)) !=
          QMessageBox::Yes)
    return false;

  /* Installed somewhere only admins can write, so let an elevated copy do it */
  if (!is_writable(dir))
  {
    int result = 1;
    if (!run_elevated("--uninstall --confirmed", &result) || result != 0)
    {
      QMessageBox::warning(parent, QObject::tr("Laigter"),
                           QObject::tr("Laigter was not removed."));
      return false;
    }
    return true;
  }

  /* Whatever of these the install wrote, in either hive. Removing what is not
   * there does nothing */
  foreach (bool machine, QList<bool>() << false << true)
  {
    QSettings classes(classes_key(machine), QSettings::NativeFormat);
    classes.remove(".laigter");
    classes.remove(project_id);

    QSettings key(uninstall_key(machine), QSettings::NativeFormat);
    key.remove("");

    QSettings ours(laigter_key(machine), QSettings::NativeFormat);
    ours.remove("");

    QFile::remove(shortcut_file(machine));
    QFile::remove(desktop_shortcut_file(machine));
  }

  SHChangeNotify(SHCNE_ASSOCCHANGED, SHCNF_IDLIST, nullptr, nullptr);

  schedule_removal(dir, "laigter-uninstall.bat");

  return true;
}
