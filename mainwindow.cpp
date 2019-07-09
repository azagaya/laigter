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

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "src/openglwidget.h"
#include "gui/nbselector.h"
#include "gui/presetsmanager.h"

#include <QFileDialog>
#include <QColorDialog>
#include <QMenu>
#include <QDebug>
#include <QtConcurrent/QtConcurrent>
#include <QDesktopServices>
#include <QStandardPaths>
#include <QMessageBox>
#include <QListWidgetItem>
#include <QMimeData>
#include <QDragEnterEvent>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    sample_processor = new ImageProcessor();

    processor = sample_processor;
    currentColor = QVector3D(0.0,1.0,0.7);
    currentAmbientcolor = QVector3D(1.0,1.0,1.0);
    currentBackgroundColor = QVector3D(0.2, 0.2, 0.3);
    currentSpecColor = QVector3D(0.0,1.0,0.7);
    currentSpecBaseColor = QVector3D(0,0,0);

    bool success;
    image = il.loadImage(":/images/sample.png",&success);

    QPixmap pixmap(100,100);
    pixmap.fill(QColor(currentColor.x()*255,currentColor.y()*255,currentColor.z()*255));
    ui->pushButtonColor->setIcon(QIcon(pixmap));
    ui->pushButtonColorSpec->setIcon(QIcon(pixmap));
    pixmap.fill(QColor(currentAmbientcolor.x()*255,currentAmbientcolor.y()*255,currentAmbientcolor.z()*255));
    ui->pushButtonAmbientColor->setIcon(QIcon(pixmap));
    pixmap.fill(QColor(currentBackgroundColor.x()*255,currentBackgroundColor.y()*255,currentBackgroundColor.z()*255));
    ui->pushButtonBackgroundColor->setIcon(QIcon(pixmap));

    m_raw_scene = new QGraphicsScene(this);

    //    ui->normalDockWidget->setFeatures(QDockWidget::DockWidgetMovable);
    //    ui->dockWidget_2->setFeatures(QDockWidget::DockWidgetMovable);

    connect_processor(processor);


    //    processingThread = new QThread();
    //    processor->moveToThread(processingThread);
    //    processingThread->start();

    ui->listWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->listWidget, SIGNAL(customContextMenuRequested(const QPoint &)),
            SLOT(showContextMenuForListWidget(const QPoint &)));
    connect(ui->checkBoxMosaicoX, SIGNAL(toggled(bool)),ui->openGLPreviewWidget,SLOT(setTileX(bool)));
    connect(ui->checkBoxMosaicoY, SIGNAL(toggled(bool)),ui->openGLPreviewWidget,SLOT(setTileY(bool)));
    connect(ui->sliderParallax,SIGNAL(valueChanged(int)),ui->openGLPreviewWidget,SLOT(setParallaxHeight(int)));
    connect(ui->checkBoxPixelated,SIGNAL(toggled(bool)),ui->openGLPreviewWidget,SLOT(setPixelated(bool)));

    tabifyDockWidget(ui->normalDockWidget, ui->specularDockWidget);
    tabifyDockWidget(ui->normalDockWidget, ui->parallaxDockWidget);
    tabifyDockWidget(ui->normalDockWidget, ui->occlusionDockWidget);

    ui->normalDockWidget->raise();

    ui->parallaxQuantizationSlider->setVisible(false);
    ui->labelQuantization->setVisible(false);

    ui->sliderParallaxBright->setVisible(false);
    ui->sliderParallaxContrast->setVisible(false);

    ui->labelBrightness->setVisible(false);
    ui->labelContrast->setVisible(false);

    setAcceptDrops(true);

}

void MainWindow::showContextMenuForListWidget(const QPoint &pos){
    if (ui->listWidget->selectedItems().count() == 0)
        return;
    QMenu contextMenu(tr("Context menu"), ui->listWidget);
    contextMenu.addAction(new QAction(tr("Quitar"), ui->listWidget));
    contextMenu.addSeparator();
    contextMenu.addAction(new QAction(tr("Cargar mapa de altura")));
    contextMenu.addAction(new QAction(tr("Reiniciar mapa de altura")));
    contextMenu.addSeparator();
    contextMenu.addAction(new QAction(tr("Cargar mapa especular")));
    contextMenu.addAction(new QAction(tr("Reiniciar mapa especular")));

    connect(&contextMenu,SIGNAL(triggered(QAction*)),this,SLOT(list_menu_action_triggered(QAction*)));

    contextMenu.exec(ui->listWidget->mapToGlobal(pos));
    disconnect(&contextMenu,SIGNAL(triggered(QAction*)),this,SLOT(list_menu_action_triggered(QAction*)));
}

void MainWindow::list_menu_action_triggered(QAction *action){
    if (action->text() == tr("Quitar")){
        QListWidgetItem *item =  ui->listWidget->takeItem(ui->listWidget->currentRow());
        for (int i=0; i<processorList.count(); i++){
            if (processorList.at(i)->get_name() == item->text()){
                processorList.at(i)->deleteLater();
                processorList.removeAt(i);
                break;
            }
        }
        delete item;
    }
    else if (action->text() == tr("Cargar mapa de altura")){
        QString fileName = QFileDialog::getOpenFileName(this,
                                                        tr("Abrir Imagen"), "",
                                                        tr("Archivos de Imagen (*.png *.jpg *.bmp *.tga)"));

        if (fileName != nullptr){
            bool success;
            QImage height = il.loadImage(fileName, &success);
            if (!success) return;
            height = height.convertToFormat(QImage::Format_RGBA8888_Premultiplied);

            processor->loadHeightMap(fileName, height);
        }
    }
    else if (action->text() == tr("Reiniciar mapa de altura")){
        bool succes;
        QImage height = il.loadImage(processor->get_name(),&succes);
        height = height.convertToFormat(QImage::Format_RGBA8888_Premultiplied);
        processor->loadHeightMap(processor->get_name(),height);
    }
    else if (action->text() == tr("Cargar mapa especular")){
        QString fileName = QFileDialog::getOpenFileName(this,
                                                        tr("Abrir Imagen"), "",
                                                        tr("Archivos de Imagen (*.png *.jpg *.bmp *.tga)"));

        if (fileName != nullptr){
            bool success;
            QImage spec = il.loadImage(fileName, &success);
            if (!success) return;
            spec = spec.convertToFormat(QImage::Format_RGBA8888_Premultiplied);

            processor->loadSpecularMap(fileName, spec);
        }

    }
    else if (action->text() == tr("Reiniciar mapa especular")){
        bool succes;
        QImage specular = il.loadImage(processor->get_name(),&succes);
        specular = specular.convertToFormat(QImage::Format_RGBA8888_Premultiplied);
        processor->loadSpecularMap(processor->get_name(),specular);

    }

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
        if (ui->comboBoxView->currentIndex() == ViewMode::NormalMap  )
            ui->openGLPreviewWidget->setImage(image);
        break;
    case ProcessedImage::Parallax:
        parallax = image;
        ui->openGLPreviewWidget->setParallaxMap(parallax);
        if (ui->comboBoxView->currentIndex() == ViewMode::ParallaxMap)
            ui->openGLPreviewWidget->setImage(image);
        break;
    case ProcessedImage::Specular:
        specular = image;
        ui->openGLPreviewWidget->setSpecularMap(specular);
        if (ui->comboBoxView->currentIndex() == ViewMode::SpecularMap)
            ui->openGLPreviewWidget->setImage(image);
        break;
    case ProcessedImage::Occlusion:
        occlusion = image;
        ui->openGLPreviewWidget->setOcclusionMap(occlusion);
        if (ui->comboBoxView->currentIndex() == ViewMode::OcclusionMap)
            ui->openGLPreviewWidget->setImage(image);
        break;
    }
    ui->openGLPreviewWidget->update();
}

void MainWindow::on_actionOpen_triggered()
{
    QStringList fileNames = QFileDialog::getOpenFileNames(this,
                                                          tr("Abrir Imagen"), "",
                                                          tr("Archivos de Imagen (*.png *.jpg *.bmp *.tga)"));
    open_files(fileNames);
}

void MainWindow::open_files(QStringList fileNames){
    QImage auximage;
    foreach (QString fileName, fileNames){
        if (fileName != nullptr){
            ImageLoader il;
            bool succes;
            auximage = il.loadImage(fileName,&succes);
            if (!succes || auximage.isNull()){
                QMessageBox msgBox;
                msgBox.setText(tr("No se puede abrir ")+fileName+".\n"+tr("Formato no soportado o incorrecto."));
                msgBox.exec();
                continue;
            }
            auximage = auximage.convertToFormat(QImage::Format_RGBA8888_Premultiplied);
            int i;
            for(i = 0; i < ui->listWidget->count(); i++){
                if (ui->listWidget->item(i)->text() == fileName){
                    QMessageBox msgBox;
                    msgBox.setText(tr("La imagen ya se encuentra abierta en laigter."));
                    msgBox.exec();
                    break;
                }
            }

            if (i != ui->listWidget->count()) continue;
            image = auximage;
            ImageProcessor *p = new ImageProcessor();
            processorList.append(p);
            p->copy_settings(processor->get_settings());
            disconnect_processor(processor);
            processor = p;
            connect_processor(processor);
            processor->loadImage(fileName, image);
            switch(ui->comboBoxView->currentIndex()){
            case ViewMode::Texture:

                break;

            }

            on_comboBoxView_currentIndexChanged(ui->comboBoxView->currentIndex());
            ui->listWidget->addItem(new QListWidgetItem(QIcon(QPixmap::fromImage(image)),processor->get_name()));
            ui->listWidget->setCurrentRow(ui->listWidget->count()-1);
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


void MainWindow::openGL_initialized(){
    on_comboBoxView_currentIndexChanged(0);
    QString tmpImage = QDir::temp().path()+"/sample.png";
    image.save(tmpImage);
    processor->loadImage(tmpImage,image);
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

void MainWindow::connect_processor(ImageProcessor *p){
    connect(p,SIGNAL(processed(QImage, ProcessedImage)),this,SLOT(update_scene(QImage, ProcessedImage)));
    connect(ui->normalDepthSlider,SIGNAL(valueChanged(int)),p,SLOT(set_normal_depth(int)));
    connect(ui->normalBlurSlider,SIGNAL(valueChanged(int)),p,SLOT(set_normal_blur_radius(int)));
    connect(ui->normalBevelSlider,SIGNAL(valueChanged(int)),p,SLOT(set_normal_bisel_depth(int)));
    connect(ui->normalBiselDistanceSlider,SIGNAL(valueChanged(int)),p,SLOT(set_normal_bisel_distance(int)));
    connect(ui->normalBiselBlurSlider,SIGNAL(valueChanged(int)),p,SLOT(set_normal_bisel_blur_radius(int)));
    connect(ui->biselSoftRadio,SIGNAL(toggled(bool)),p,SLOT(set_normal_bisel_soft(bool)));
    connect(ui->normalInvertX,SIGNAL(toggled(bool)),p,SLOT(set_normal_invert_x(bool)));
    connect(ui->normalInvertY,SIGNAL(toggled(bool)),p,SLOT(set_normal_invert_y(bool)));
    connect(ui->openGLPreviewWidget,SIGNAL(initialized()),this,SLOT(openGL_initialized()));
    connect(ui->checkBoxTileable,SIGNAL(toggled(bool)),p,SLOT(set_tileable(bool)));
    connect(ui->checkBoxParallaxInvert,SIGNAL(toggled(bool)),p,SLOT(set_parallax_invert(bool)));
    connect(ui->parallaxSoftSlider,SIGNAL(valueChanged(int)),p,SLOT(set_parallax_soft(int)));
    connect(ui->parallaxThreshSlider,SIGNAL(valueChanged(int)),p,SLOT(set_parallax_thresh(int)));
    connect(ui->parallaxFocusSlider,SIGNAL(valueChanged(int)),p,SLOT(set_parallax_focus(int)));
    connect(ui->parallaxMinHeight,SIGNAL(valueChanged(int)),p,SLOT(set_parallax_min(int)));
    connect(ui->parallaxQuantizationSlider,SIGNAL(valueChanged(int)),p,SLOT(set_parallax_quantization(int)));
    connect(ui->sliderParallaxErodeDilate,SIGNAL(valueChanged(int)),p,SLOT(set_parallax_erode_dilate(int)));
    connect(ui->sliderParallaxBright,SIGNAL(valueChanged(int)),p,SLOT(set_parallax_brightness(int)));
    connect(ui->sliderParallaxContrast,SIGNAL(valueChanged(int)),p,SLOT(set_parallax_contrast(int)));

    connect(ui->sliderSpecSoft,SIGNAL(valueChanged(int)),p,SLOT(set_specular_blur(int)));
    connect(ui->sliderSpecBright,SIGNAL(valueChanged(int)),p,SLOT(set_specular_bright(int)));
    connect(ui->sliderSpecContrast,SIGNAL(valueChanged(int)),p,SLOT(set_specular_contrast(int)));
    connect(ui->sliderSpecThresh,SIGNAL(valueChanged(int)),p,SLOT(set_specular_thresh(int)));
    connect(ui->checkBoxSpecInvert,SIGNAL(toggled(bool)),p,SLOT(set_specular_invert(bool)));

    connect(ui->sliderOcclusionSoft,SIGNAL(valueChanged(int)),p,SLOT(set_occlusion_blur(int)));
    connect(ui->sliderOcclusionBright,SIGNAL(valueChanged(int)),p,SLOT(set_occlusion_bright(int)));
    connect(ui->sliderOcclusionContrast,SIGNAL(valueChanged(int)),p,SLOT(set_occlusion_contrast(int)));
    connect(ui->sliderOcclusionThresh,SIGNAL(valueChanged(int)),p,SLOT(set_occlusion_thresh(int)));
    connect(ui->checkBoxOcclusionInvert,SIGNAL(toggled(bool)),p,SLOT(set_occlusion_invert(bool)));
    connect(ui->checkBoxOcclusionDistance,SIGNAL(toggled(bool)),p,SLOT(set_occlusion_distance_mode(bool)));
    connect(ui->sliderOcclusionDistance,SIGNAL(valueChanged(int)),p,SLOT(set_occlusion_distance(int)));
}

void MainWindow::disconnect_processor(ImageProcessor *p){
    disconnect(p,SIGNAL(processed(QImage, ProcessedImage)),this,SLOT(update_scene(QImage, ProcessedImage)));
    disconnect(ui->normalDepthSlider,SIGNAL(valueChanged(int)),p,SLOT(set_normal_depth(int)));
    disconnect(ui->normalBlurSlider,SIGNAL(valueChanged(int)),p,SLOT(set_normal_blur_radius(int)));
    disconnect(ui->normalBevelSlider,SIGNAL(valueChanged(int)),p,SLOT(set_normal_bisel_depth(int)));
    disconnect(ui->normalBiselDistanceSlider,SIGNAL(valueChanged(int)),p,SLOT(set_normal_bisel_distance(int)));
    disconnect(ui->normalBiselBlurSlider,SIGNAL(valueChanged(int)),p,SLOT(set_normal_bisel_blur_radius(int)));
    disconnect(ui->biselSoftRadio,SIGNAL(toggled(bool)),p,SLOT(set_normal_bisel_soft(bool)));
    disconnect(ui->normalInvertX,SIGNAL(toggled(bool)),p,SLOT(set_normal_invert_x(bool)));
    disconnect(ui->normalInvertY,SIGNAL(toggled(bool)),p,SLOT(set_normal_invert_y(bool)));
    disconnect(ui->openGLPreviewWidget,SIGNAL(initialized()),this,SLOT(openGL_initialized()));
    disconnect(ui->checkBoxTileable,SIGNAL(toggled(bool)),p,SLOT(set_tileable(bool)));
    disconnect(ui->checkBoxParallaxInvert,SIGNAL(toggled(bool)),p,SLOT(set_parallax_invert(bool)));
    disconnect(ui->parallaxSoftSlider,SIGNAL(valueChanged(int)),p,SLOT(set_parallax_soft(int)));
    disconnect(ui->parallaxThreshSlider,SIGNAL(valueChanged(int)),p,SLOT(set_parallax_thresh(int)));
    disconnect(ui->parallaxFocusSlider,SIGNAL(valueChanged(int)),p,SLOT(set_parallax_focus(int)));
    disconnect(ui->parallaxMinHeight,SIGNAL(valueChanged(int)),p,SLOT(set_parallax_min(int)));
    disconnect(ui->parallaxQuantizationSlider,SIGNAL(valueChanged(int)),p,SLOT(set_parallax_quantization(int)));
    disconnect(ui->sliderParallaxErodeDilate,SIGNAL(valueChanged(int)),p,SLOT(set_parallax_erode_dilate(int)));
    disconnect(ui->sliderParallaxBright,SIGNAL(valueChanged(int)),p,SLOT(set_parallax_brightness(int)));
    disconnect(ui->sliderParallaxContrast,SIGNAL(valueChanged(int)),p,SLOT(set_parallax_contrast(int)));

    disconnect(ui->sliderSpecSoft,SIGNAL(valueChanged(int)),p,SLOT(set_specular_blur(int)));
    disconnect(ui->sliderSpecBright,SIGNAL(valueChanged(int)),p,SLOT(set_specular_bright(int)));
    disconnect(ui->sliderSpecContrast,SIGNAL(valueChanged(int)),p,SLOT(set_specular_contrast(int)));
    disconnect(ui->sliderSpecThresh,SIGNAL(valueChanged(int)),p,SLOT(set_specular_thresh(int)));
    disconnect(ui->checkBoxSpecInvert,SIGNAL(toggled(bool)),p,SLOT(set_specular_invert(bool)));

}

void MainWindow::on_listWidget_itemSelectionChanged()
{
    if (ui->listWidget->selectedItems().count() > 0){
        QListWidgetItem *item = ui->listWidget->currentItem();
        for(int i = 0; i < processorList.count(); i++){
            if (processorList.at(i)->get_name() == item->text()){
                disconnect_processor(processor);
                processor = processorList.at(i);
                break;
            }
        }
    }
    else {
        processor= sample_processor;
    }

    ui->normalInvertX->setChecked(processor->get_normal_invert_x() == -1);
    ui->normalInvertY->setChecked(processor->get_normal_invert_y() == -1);
    ui->biselSoftRadio->setChecked(processor->get_normal_bisel_soft());
    ui->biselAbruptRadio->setChecked(!processor->get_normal_bisel_soft());
    ui->normalBlurSlider->setValue(processor->get_normal_blur_radius());
    ui->normalBevelSlider->setValue(processor->get_normal_bisel_depth());
    ui->normalDepthSlider->setValue(processor->get_normal_depth());
    ui->normalBiselBlurSlider->setValue(processor->get_normal_bisel_blur_radius());
    ui->normalBiselDistanceSlider->setValue(processor->get_normal_bisel_distance());
    ui->checkBoxTileable->setChecked(processor->get_tileable());

    ui->parallaxSoftSlider->setValue(processor->get_parallax_soft());
    ui->parallaxFocusSlider->setValue(processor->get_parallax_focus());
    ui->parallaxThreshSlider->setValue(processor->get_parallax_thresh());
    ui->checkBoxParallaxInvert->setChecked(processor->get_parallax_invert());
    ui->comboBox->setCurrentIndex(static_cast<int>(processor->get_parallax_type()));
    ui->parallaxMinHeight->setValue(processor->get_parallax_min());
    ui->parallaxQuantizationSlider->setValue(processor->get_parallax_quantization());
    ui->sliderParallaxBright->setValue(processor->get_parallax_brightness());
    ui->sliderParallaxContrast->setValue(static_cast<int>(processor->get_parallax_contrast()*1000));
    ui->sliderParallaxErodeDilate->setValue(processor->get_parallax_erode_dilate());

    ui->sliderSpecSoft->setValue(processor->get_specular_blur());
    ui->sliderSpecBright->setValue(processor->get_specular_bright());
    ui->sliderSpecThresh->setValue(processor->get_specular_trhesh());
    ui->sliderSpecContrast->setValue(static_cast<int>(processor->get_specular_contrast()*1000));
    ui->checkBoxSpecInvert->setChecked(processor->get_specular_invert());

    bool succes;
    image = il.loadImage(processor->get_name(), &succes);
    image = image.convertToFormat(QImage::Format_RGBA8888);

    processor->update();
    on_comboBoxView_currentIndexChanged(ui->comboBoxView->currentIndex());

//    update_scene(processor->get_normal(),ProcessedImage::Normal);
//    update_scene(processor->get_parallax(),ProcessedImage::Parallax);
//    update_scene(processor->get_specular(),ProcessedImage::Specular);
    connect_processor(processor);
}





void MainWindow::on_pushButton_clicked()
{
    QImage n;
    QString suffix;
    QString name;
    QFileInfo info;
    QString message = "";
    if (ui->checkBoxExportNormal->isChecked()){
        foreach (ImageProcessor *p, processorList){
            n = p->get_normal();
            info = QFileInfo(p->get_name());
            suffix = info.completeSuffix();
            name = info.absoluteFilePath().remove("."+suffix)+"_n."+suffix;
            n.save(name);
        }
        message += tr("Se exportaron todos los mapas normales. ");
    }
    if (ui->checkBoxExportParallax->isChecked()){
        foreach (ImageProcessor *p, processorList){
            n = p->get_parallax();
            info = QFileInfo(p->get_name());
            suffix = info.completeSuffix();
            name = info.absoluteFilePath().remove("."+suffix)+"_p."+suffix;
            n.save(name);
        }
        message += tr("Se exportaron todos los mapas de paralaje. ");
    }
    if (ui->checkBoxExportSpecular->isChecked()){
        foreach (ImageProcessor *p, processorList){
            n = p->get_specular();
            info = QFileInfo(p->get_name());
            suffix = info.completeSuffix();
            name = info.absoluteFilePath().remove("."+suffix)+"_s."+suffix;
            n.save(name);
        }
        message += tr("Se exportaron todos los mapas de especulares. ");
    }
    if (message != ""){
        QMessageBox msgBox;
        msgBox.setText(message);
        msgBox.exec();
    }
}

void MainWindow::on_pushButtonBackgroundColor_clicked()
{
    QColor color = QColorDialog::getColor(QColor(currentBackgroundColor.x()*255,currentBackgroundColor.y()*255,currentBackgroundColor.z()*255));
    if (color.isValid()){
        currentBackgroundColor = QVector3D(color.redF(),color.greenF(),color.blueF());
        QPixmap pixmap(100,100);
        pixmap.fill(color);
        ui->pushButtonBackgroundColor->setIcon(QIcon(pixmap));
        ui->openGLPreviewWidget->setBackgroundColor(currentBackgroundColor);
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    NBSelector *nb = new NBSelector(processor);
    nb->exec();
}



void MainWindow::on_checkBoxParallax_toggled(bool checked)
{
    ui->openGLPreviewWidget->setParallax(checked && ui->comboBoxView->currentIndex() == ViewMode::Preview);
}

void MainWindow::on_sliderParallax_sliderReleased()
{

}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{

    ParallaxType ptype = static_cast<ParallaxType>(index);
    processor->set_parallax_type(ptype);

    switch (ptype) {
    case ParallaxType::Binary:
        ui->parallaxMinHeight->setVisible(true);
        ui->parallaxSoftSlider->setVisible(true);
        ui->parallaxFocusSlider->setVisible(true);
        ui->parallaxThreshSlider->setVisible(true);
        ui->checkBoxParallaxInvert->setVisible(true);
        ui->parallaxQuantizationSlider->setVisible(false);
        ui->sliderParallaxErodeDilate->setVisible(true);
        ui->sliderParallaxBright->setVisible(false);
        ui->sliderParallaxContrast->setVisible(false);

        ui->labelErodeDilate->setVisible(true);
        ui->labelBrightness->setVisible(false);
        ui->labelContrast->setVisible(false);
        ui->labelThreshMin->setVisible(true);
        ui->labelThreshSoft->setVisible(true);
        ui->labelThreshFocus->setVisible(true);
        ui->labelThreshParallax->setVisible(true);
        ui->labelQuantization->setVisible(false);
        break;
    case ParallaxType::HeightMap:
        ui->parallaxMinHeight->setVisible(false);
        ui->parallaxSoftSlider->setVisible(true);
        ui->parallaxFocusSlider->setVisible(false);
        ui->parallaxThreshSlider->setVisible(false);
        ui->checkBoxParallaxInvert->setVisible(true);
        ui->parallaxQuantizationSlider->setVisible(false);

        ui->sliderParallaxErodeDilate->setVisible(false);
        ui->sliderParallaxBright->setVisible(true);
        ui->sliderParallaxContrast->setVisible(true);

        ui->labelErodeDilate->setVisible(false);
        ui->labelBrightness->setVisible(true);
        ui->labelContrast->setVisible(true);

        ui->labelThreshMin->setVisible(false);
        ui->labelThreshSoft->setVisible(true);
        ui->labelThreshFocus->setVisible(false);
        ui->labelThreshParallax->setVisible(false);
        ui->labelQuantization->setVisible(false);
        break;
    case ParallaxType::Quantization:
        ui->parallaxMinHeight->setVisible(true);
        ui->parallaxSoftSlider->setVisible(true);
        ui->parallaxFocusSlider->setVisible(true);
        ui->parallaxThreshSlider->setVisible(true);
        ui->checkBoxParallaxInvert->setVisible(true);
        ui->parallaxQuantizationSlider->setVisible(true);

        ui->sliderParallaxErodeDilate->setVisible(false);
        ui->sliderParallaxBright->setVisible(true);
        ui->sliderParallaxContrast->setVisible(true);

        ui->labelErodeDilate->setVisible(false);
        ui->labelBrightness->setVisible(true);
        ui->labelContrast->setVisible(true);

        ui->labelThreshMin->setVisible(true);
        ui->labelThreshSoft->setVisible(true);
        ui->labelThreshFocus->setVisible(true);
        ui->labelThreshParallax->setVisible(true);
        ui->labelQuantization->setVisible(true);
    }

}

void MainWindow::on_pushButtonExportTo_clicked()
{
    QImage n;
    QString suffix;
    QString name;
    QFileInfo info;
    QString message = "";
    QString path = QFileDialog::getExistingDirectory();
    if (path != nullptr){
        if (ui->checkBoxExportNormal->isChecked()){
            foreach (ImageProcessor *p, processorList){
                n = p->get_normal();
                info = QFileInfo(p->get_name());
                suffix = info.completeSuffix();
                name = path + "/" + info.baseName() + "_n." + suffix;
                int i=1;
                while (QFileInfo::exists(name))
                    name = path + "/" + info.baseName() + "(" + QString::number(++i) + ")" + "_n." + suffix;
                n.save(name);
            }
            message += tr("Se exportaron todos los mapas normales. ");
        }
        if (ui->checkBoxExportParallax->isChecked()){
            foreach (ImageProcessor *p, processorList){
                n = p->get_parallax();
                info = QFileInfo(p->get_name());
                suffix = info.completeSuffix();
                name = path + "/" + info.baseName() + "_p." + suffix;
                int i=1;
                while (QFileInfo::exists(name))
                    name = path + "/" + info.baseName() + "(" + QString::number(++i) + ")" + "_p." + suffix;
                n.save(name);
            }
            message += tr("Se exportaron todos los mapas de paralaje. ");
        }
        if (message != ""){
            QMessageBox msgBox;
            msgBox.setText(message);
            msgBox.exec();
        }
    }
}
void MainWindow::dragEnterEvent(QDragEnterEvent *e)
{
    if (e->mimeData()->hasUrls()) {
        e->acceptProposedAction();
    }
}
void MainWindow::dropEvent(QDropEvent *event){
    QStringList fileNames;
    QList<QUrl> urlList = event->mimeData()->urls();
    foreach(QUrl url, urlList){
        fileNames.append(url.toLocalFile());
    }
    open_files(fileNames);
}

void MainWindow::on_actionPresets_triggered()
{
    PresetsManager pm(processor->get_settings(), &processorList);
    connect(&pm, SIGNAL(settingAplied()),this,SLOT(on_listWidget_itemSelectionChanged()));
    pm.exec();
    disconnect(&pm, SIGNAL(settingAplied()),this,SLOT(on_listWidget_itemSelectionChanged()));
}


void MainWindow::on_pushButtonColorSpec_clicked()
{
    QColor color = QColorDialog::getColor(QColor(currentSpecColor.x()*255,currentSpecColor.y()*255,currentSpecColor.z()*255));
    if (color.isValid()){
        currentSpecColor = QVector3D(color.redF(),color.greenF(),color.blueF());
        QPixmap pixmap(100,100);
        pixmap.fill(color);
        ui->pushButtonColorSpec->setIcon(QIcon(pixmap));
        ui->openGLPreviewWidget->setSpecColor(currentSpecColor);
    }
}

void MainWindow::on_horizontalSliderSpec_valueChanged(int value)
{
    ui->openGLPreviewWidget->setSpecIntensity(static_cast<float>(value/100.0));
}

void MainWindow::on_horizontalSliderSpecScatter_valueChanged(int value)
{
    ui->openGLPreviewWidget->setSpecScatter(value);
}

void MainWindow::on_comboBoxView_currentIndexChanged(int index)
{

    ui->openGLPreviewWidget->setLight(false);
    ui->openGLPreviewWidget->setParallax(false);
    switch (index){
    case ViewMode::Texture:
        if (!image.isNull())
            update_scene(image,ProcessedImage::Raw);
        break;
    case ViewMode::NormalMap:
        if (!normal.isNull())
            update_scene(normal,ProcessedImage::Raw);
        break;
    case ViewMode::SpecularMap:
        if (!specular.isNull())
            update_scene(specular,ProcessedImage::Raw);
        break;
    case ViewMode::ParallaxMap:
        if (!parallax.isNull())
            update_scene(parallax,ProcessedImage::Raw);
        break;
    case ViewMode::OcclusionMap:
        if (!occlusion.isNull())
            update_scene(occlusion,ProcessedImage::Raw);
        break;
    case ViewMode::Preview:
        ui->openGLPreviewWidget->setLight(true);
        ui->openGLPreviewWidget->setParallax(ui->checkBoxParallax->isChecked());
        if (!image.isNull()){
            update_scene(normal,ProcessedImage::Normal);
            update_scene(image,ProcessedImage::Raw);
        }
        break;
    }
}
