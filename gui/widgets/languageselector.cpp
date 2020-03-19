#include "languageselector.h"
#include "ui_languageselector.h"

LanguageSelector::LanguageSelector(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LanguageSelector)
{
  ui->setupUi(this);
}

LanguageSelector::~LanguageSelector()
{
  delete ui;
}
