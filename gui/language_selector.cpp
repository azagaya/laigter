#include "language_selector.h"
#include "ui_language_selector.h"

#include <QDebug>
#include <QFile>
#include <QStandardPaths>
#include <QStringConverter>

LanguageSelector::LanguageSelector(QWidget *parent)
    : QDialog(parent), ui(new Ui::LanguageSelector)
{
  ui->setupUi(this);
  QFile f(":/translations/languages.txt");
  if (f.open(QIODevice::ReadOnly))
  {
    QTextStream in(&f);
    in.setEncoding(QStringConverter::Utf8);
    while (!in.atEnd())
    {
      QStringList line = in.readLine().split("\t");
      if (line.count() >= 3)
      {
        icon_path = line[1];
        icon = QPixmap::fromImage(
            QImage(":/translations/flags/" + icon_path));
        QListWidgetItem *item =
            new QListWidgetItem(QIcon(icon), line[0]);
        item->setData(Qt::UserRole, line[1] + "\t" + line[2]);
        ui->listWidget->addItem(item);
      }
    }
    f.close();
  }
}

LanguageSelector::~LanguageSelector() { delete ui; }

void LanguageSelector::on_listWidget_itemSelectionChanged()
{
  QStringList locale = ui->listWidget->currentItem()->data(Qt::UserRole).toString().split("\t");
  QString lang = ui->listWidget->currentItem()->text();
  icon = QPixmap::fromImage(QImage(":/translations/flags/" + locale[0]));

  qApp->removeTranslator(translator);
  translator->load(":/translations/laigter_" + locale[1]);
  qApp->installTranslator(translator);
  QString current_language =
      QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) +
      "/lang";
  QFile l(current_language);

  if (l.open(QIODevice::ReadWrite | QFile::Truncate))
  {
    QString data(lang + "\t" + locale[0] + "\t" + locale[1]);
    l.write(data.toUtf8());
  }
}

void LanguageSelector::on_pushButton_clicked() { close(); }
