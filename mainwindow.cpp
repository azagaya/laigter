#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "src/openglwidget.h"
#include "src/graphicsview.h"

#include <QFileDialog>
#include <QDebug>
#include <QThread>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_raw_scene = new QGraphicsScene(this);
    m_normal_scene = new QGraphicsScene(this);


    connect(&processor,SIGNAL(processed(QImage, ProcessedImage)),this,SLOT(update_scene(QImage, ProcessedImage)));
    connect(ui->normalDepthSlider,SIGNAL(valueChanged(int)),&processor,SLOT(set_normal_depth(int)));
    connect(ui->normalBlurSlider,SIGNAL(valueChanged(int)),&processor,SLOT(set_normal_blur_radius(int)));
    connect(ui->normalBevelSlider,SIGNAL(valueChanged(int)),&processor,SLOT(set_normal_bisel_depth(int)));
    connect(ui->normalBiselDistanceSlider,SIGNAL(valueChanged(int)),&processor,SLOT(set_normal_bisel_distance(int)));
    connect(ui->normalBiselBlurSlider,SIGNAL(valueChanged(int)),&processor,SLOT(set_normal_bisel_blur_radius(int)));
    connect(ui->biselSoftRadio,SIGNAL(toggled(bool)),&processor,SLOT(set_normal_bisel_soft(bool)));
    connect(ui->normalInvertX,SIGNAL(toggled(bool)),&processor,SLOT(set_normal_invert_x(bool)));
    connect(ui->normalInvertY,SIGNAL(toggled(bool)),&processor,SLOT(set_normal_invert_y(bool)));

    connect(ui->graphicsViewRaw,SIGNAL(zoomed_in(double,double)),ui->graphicsViewNormal,SLOT(zoom_in(double,double)));
    connect(ui->graphicsViewNormal,SIGNAL(zoomed_in(double,double)),ui->graphicsViewRaw,SLOT(zoom_in(double,double)));

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
        m_raw_scene->clear();
        ui->graphicsViewRaw->setSceneRect(pixmap.rect());
        m_raw_scene->addPixmap(pixmap);
        ui->graphicsViewRaw->setScene(m_raw_scene);

        ui->openGLPreviewWidget->setImage(image);
        ui->openGLPreviewWidget->update();

        break;
    case ProcessedImage::Normal:
        m_normal_scene->clear();
        ui->graphicsViewNormal->setSceneRect(pixmap.rect());
        m_normal_scene->addPixmap(pixmap);
        ui->graphicsViewNormal->setScene(m_normal_scene);

        ui->openGLPreviewWidget->setNormalMap(image);
        break;

    }
    ui->openGLPreviewWidget->update();
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open Image"), "/home/pablo",
                                                    tr("Image Files (*.png *.jpg *.bmp)"));
    if (fileName != nullptr){
        update_scene(QImage(fileName),ProcessedImage::Raw);
        processor.loadImage(fileName);
    }
}

void MainWindow::on_actionFitZoom_triggered()
{
    ui->graphicsViewRaw->fitInView(ui->graphicsViewRaw->sceneRect(),Qt::KeepAspectRatio);
    ui->graphicsViewNormal->fitInView(ui->graphicsViewNormal->sceneRect(),Qt::KeepAspectRatio);
    ui->openGLPreviewWidget->fitZoom();

}

void MainWindow::on_actionZoom_100_triggered()
{
    ui->graphicsViewRaw->resetTransform();
    ui->graphicsViewNormal->resetTransform();
    ui->openGLPreviewWidget->resetZoom();
}

void MainWindow::on_actionZoomIn_triggered()
{
    ui->graphicsViewRaw->scale(1.01,1.01);
    ui->graphicsViewNormal->scale(1.01,1.01);
    ui->openGLPreviewWidget->setZoom(1.1*ui->openGLPreviewWidget->getZoom());
}

void MainWindow::on_actionZoomOut_triggered()
{
    ui->graphicsViewRaw->scale(0.99,0.99);
    ui->graphicsViewNormal->scale(0.99,0.99);
    ui->openGLPreviewWidget->setZoom(0.9*ui->openGLPreviewWidget->getZoom());
}

void MainWindow::on_actionExport_triggered()
{

}
