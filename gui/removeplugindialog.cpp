#include "removeplugindialog.h"
#include "ui_removeplugindialog.h"

#include <QStandardPaths>
#include <QDir>

RemovePluginDialog::RemovePluginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RemovePluginDialog)
{
  ui->setupUi(this);
  ui->listWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
}

RemovePluginDialog::~RemovePluginDialog()
{
  delete ui;
}

void RemovePluginDialog::setPluginList(QStringList plugin_list){
  ui->listWidget->addItems(plugin_list);
}

void RemovePluginDialog::on_buttonBox_accepted()
{
  QString appData =
    QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
  QDir dir(appData);
  dir.cd("plugins");
  foreach (QListWidgetItem *plugin_name, ui->listWidget->selectedItems()) {
    QFile plugin(dir.filePath(plugin_name->text()));
    plugin.remove();
  }
}
