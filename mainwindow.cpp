#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "src/openglwidget.h"

#include <QFileDialog>
#include <QColorDialog>
#include <QDebug>
#include <QtConcurrent/QtConcurrent>
#include <QDesktopServices>
#include <QStandardPaths>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    processor = new ImageProcessor();
    currentColor = QVector3D(0.0,1.0,0.7);
    currentAmbientcolor = QVector3D(1.0,1.0,1.0);
    QPixmap pixmap(100,100);
    pixmap.fill(QColor(currentColor.x()*255,currentColor.y()*255,currentColor.z()*255));
    ui->pushButtonColor->setIcon(QIcon(pixmap));
    pixmap.fill(QColor(currentAmbientcolor.x()*255,currentAmbientcolor.y()*255,currentAmbientcolor.z()*255));
    ui->pushButtonAmbientColor->setIcon(QIcon(pixmap));
    m_raw_scene = new QGraphicsScene(this);

    ui->dockWidget->setFeatures(QDockWidget::DockWidgetMovable);
    ui->dockWidget_2->setFeatures(QDockWidget::DockWidgetMovable);


//    processingThread = new QThread();
//    processor->moveToThread(processingThread);
//    processingThread->start();

    connect(processor,SIGNAL(processed(QImage, ProcessedImage)),this,SLOT(update_scene(QImage, ProcessedImage)));
    connect(ui->normalDepthSlider,SIGNAL(valueChanged(int)),processor,SLOT(set_normal_depth(int)));
    connect(ui->normalBlurSlider,SIGNAL(valueChanged(int)),processor,SLOT(set_normal_blur_radius(int)));
    connect(ui->normalBevelSlider,SIGNAL(valueChanged(int)),processor,SLOT(set_normal_bisel_depth(int)));
    connect(ui->normalBiselDistanceSlider,SIGNAL(valueChanged(int)),processor,SLOT(set_normal_bisel_distance(int)));
    connect(ui->normalBiselBlurSlider,SIGNAL(valueChanged(int)),processor,SLOT(set_normal_bisel_blur_radius(int)));
    connect(ui->biselSoftRadio,SIGNAL(toggled(bool)),processor,SLOT(set_normal_bisel_soft(bool)));
    connect(ui->normalInvertX,SIGNAL(toggled(bool)),processor,SLOT(set_normal_invert_x(bool)));
    connect(ui->normalInvertY,SIGNAL(toggled(bool)),processor,SLOT(set_normal_invert_y(bool)));
    connect(ui->openGLPreviewWidget,SIGNAL(initialized()),this,SLOT(openGL_initialized()));


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
                                                    tr("Abrir Imagen"), "",
                                                    tr("Archivos de Imagen (*.png *.jpg *.bmp)"));

    if (fileName != nullptr){
        image = QImage(fileName);
        processor->loadImage(fileName);
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
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Guardar Imagen"), "",
                                                    tr("Archivos de Imagen (*.png *.jpg *.bmp)"));

    if (fileName != nullptr){
        normal.save(fileName);
    }

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

void MainWindow::on_pushButtonColor_clicked()
{
    QColor color = QColorDialog::getColor(QColor(currentColor.x()*255,currentColor.y()*255,currentColor.z()*255));
    if (color.isValid()){
        currentColor = QVector3D(color.redF(),color.greenF(),color.blueF());
        QPixmap pixmap(100,100);
        pixmap.fill(color);
        ui->pushButtonColor->setIcon(QIcon(pixmap));
        ui->openGLPreviewWidget->setLightColor(currentColor);
    }
}

void MainWindow::on_horizontalSliderDiffHeight_valueChanged(int value)
{
    ui->openGLPreviewWidget->setLightHeight(value/100.0);
}

void MainWindow::on_horizontalSliderDiffLight_valueChanged(int value)
{
    ui->openGLPreviewWidget->setLightIntensity(value/100.0);
}

void MainWindow::on_horizontalSliderAmbientLight_valueChanged(int value)
{
    ui->openGLPreviewWidget->setAmbientIntensity(value/100.0);
}


void MainWindow::on_pushButtonAmbientColor_clicked()
{
    QColor color = QColorDialog::getColor(QColor(currentAmbientcolor.x()*255,currentAmbientcolor.y()*255,currentAmbientcolor.z()*255));
    if (color.isValid()){
        currentAmbientcolor = QVector3D(color.redF(),color.greenF(),color.blueF());
        QPixmap pixmap(100,100);
        pixmap.fill(color);
        ui->pushButtonAmbientColor->setIcon(QIcon(pixmap));
        ui->openGLPreviewWidget->setAmbientColor(currentAmbientcolor);
    }
}

void MainWindow::on_actionLicencia_triggered()
{
    QDesktopServices::openUrl(QUrl("license.html"));
}

void MainWindow::on_actionReconocimientos_triggered()
{
    QDesktopServices::openUrl(QUrl("acknowledgements.html"));
}

