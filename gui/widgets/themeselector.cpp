#include "themeselector.h"
#include "ui_themeselector.h"
#include <QFile>
#include <QtDebug>

ThemeSelector::ThemeSelector(QWidget *parent) : QWidget(parent),
                                                ui(new Ui::ThemeSelector)
{
  ui->setupUi(this);
}

ThemeSelector::~ThemeSelector()
{
  delete ui;
}

void ThemeSelector::on_listWidget_itemClicked(QListWidgetItem *item)
{
  QString theme = item->text() + " Laigter";
  QString style = theme;
  style = style.replace(" ", "_").toLower() + ".qss";
  // Setting style
  QFile stylesheet_file(":/styles/" + style);
  stylesheet_file.open(QFile::ReadOnly);
  QString stylesheet = QLatin1String(stylesheet_file.readAll());
  qApp->setStyleSheet(stylesheet);

  /* Set Icon Path */
  QIcon::setFallbackSearchPaths(QIcon::fallbackSearchPaths() << ":icons");
  QIcon::setThemeName(theme);
}
