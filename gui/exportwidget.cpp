#include "exportwidget.h"
#include "ui_exportwidget.h"

ExportWidget::ExportWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExportWidget)
{
    ui->setupUi(this);
}

ExportWidget::~ExportWidget()
{
    delete ui;
}
