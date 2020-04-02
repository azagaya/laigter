#include "about_dialog.h"
#include "ui_about_dialog.h"

#include <QDesktopServices>

AboutDialog::AboutDialog(QWidget *parent)
    : QWidget(parent), ui(new Ui::AboutDialog)
{
  ui->setupUi(this);
  ui->version_label->setText("Version: " +
                             QCoreApplication::applicationVersion());
}

AboutDialog::~AboutDialog() { delete ui; }

void AboutDialog::on_pushButton_clicked()
{
  QDesktopServices::openUrl(QUrl("https://azagaya.itch.io/laigter"));
}

void AboutDialog::on_pushButton_2_clicked()
{
  QDesktopServices::openUrl(QUrl("https://twitter.com/AzagayaVj"));
}

void AboutDialog::on_pushButton_3_clicked()
{
  QDesktopServices::openUrl(QUrl("https://patreon.com/azagaya"));
}

void AboutDialog::on_pushButton_4_clicked()
{
  QDesktopServices::openUrl(QUrl("https://ko-fi.com/azagayavj"));
}

void AboutDialog::on_pushButton_5_clicked()
{
  QDesktopServices::openUrl(QUrl("https://github.com/azagaya/laigter"));
}
