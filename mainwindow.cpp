#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "src/openglwidget.h"

#include <QFileDialog>
#include <QDebug>
#include <QThread>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_raw_scene = new QGraphicsScene(this);
    connect(&processor,SIGNAL(processed(QImage, ProcessedImage)),this,SLOT(update_scene(QImage, ProcessedImage)));
    connect(ui->normalDepthSlider,SIGNAL(valueChanged(int)),&processor,SLOT(set_normal_depth(int)));
    connect(ui->normalBlurSlider,SIGNAL(valueChanged(int)),&processor,SLOT(set_normal_blur_radius(int)));
    connect(ui->normalBevelSlider,SIGNAL(valueChanged(int)),&processor,SLOT(set_normal_bisel_depth(int)));
    connect(ui->normalBiselDistanceSlider,SIGNAL(valueChanged(int)),&processor,SLOT(set_normal_bisel_distance(int)));
    connect(ui->normalBiselBlurSlider,SIGNAL(valueChanged(int)),&processor,SLOT(set_normal_bisel_blur_radius(int)));
    connect(ui->biselSoftRadio,SIGNAL(toggled(bool)),&processor,SLOT(set_normal_bisel_soft(bool)));
    connect(ui->normalInvertX,SIGNAL(toggled(bool)),&processor,SLOT(set_normal_invert_x(bool)));
    connect(ui->normalInvertY,SIGNAL(toggled(bool)),&processor,SLOT(set_normal_invert_y(bool)));
    connect(ui->openGLPreviewWidget,SIGNAL(initialized()),this,SLOT(openGL_initialized()));

//    QThread *processing_trhead = new QThread();

//    processor.moveToThread(processing_trhead);
//    processing_trhead->start(QThread::HighPriority);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update_scene(QImage image, ProcessedImage type){
    QPixmap pixmap = QPixmap::fromImage(image);
    switch (type) {

    case ProcessedImage::Raw:
        ui->openGLPreviewWidget->setImage(image);

        break;
    case ProcessedImage::Normal:
        normal = image;
        ui->openGLPreviewWidget->setNormalMap(image);
        if (ui->radioButtonNormal->isChecked())
            ui->openGLPreviewWidget->setImage(image);
        break;

    }
    ui->openGLPreviewWidget->update();
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open Image"), "/home/pablo",
                                                    tr("Image Files (*.png *.jpg *.bmp)"));
    image = QImage(fileName);
    if (fileName != nullptr){
        processor.loadImage(fileName);
        if (ui->radioButtonRaw->isChecked()){
            on_radioButtonRaw_toggled(true);
        } else if (ui->radioButtonNormal->isChecked()){
            on_radioButtonNormal_toggled(true);
        } else {
            on_radioButtonPreview_toggled(true);
        }
    }
}

void MainWindow::on_actionFitZoom_triggered()
{
    ui->openGLPreviewWidget->fitZoom();

}

void MainWindow::on_actionZoom_100_triggered()
{
    ui->openGLPreviewWidget->resetZoom();
}

void MainWindow::on_actionZoomIn_triggered()
{
    ui->openGLPreviewWidget->setZoom(1.1*ui->openGLPreviewWidget->getZoom());
}

void MainWindow::on_actionZoomOut_triggered()
{
    ui->openGLPreviewWidget->setZoom(0.9*ui->openGLPreviewWidget->getZoom());
}

void MainWindow::on_actionExport_triggered()
{

}

void MainWindow::on_radioButtonRaw_toggled(bool checked)
{
    if (checked){
        ui->openGLPreviewWidget->setLight(false);
        update_scene(image,ProcessedImage::Raw);
    }
}

void MainWindow::on_radioButtonNormal_toggled(bool checked)
{
    if (checked){
        ui->openGLPreviewWidget->setLight(false);
        update_scene(normal,ProcessedImage::Raw);
    }
}

void MainWindow::on_radioButtonPreview_toggled(bool checked)
{
    if (checked){
        ui->openGLPreviewWidget->setLight(true);
        update_scene(image,ProcessedImage::Raw);
    }
}

void MainWindow::openGL_initialized(){
    ui->radioButtonRaw->toggle();
}
