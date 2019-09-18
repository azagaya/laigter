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
#include "gui/aboutdialog.h"

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

    QColor c;
    c.setRgbF(0.0,1.0,0.7);
    currentColor = c;
    currentAmbientcolor = QColor("white");
    currentSpecColor = c;
    c.setRgbF(0.2,0.2,0.3);
    currentBackgroundColor = c;
    currentSpecBaseColor = c;

    QPixmap pixmap(100,100);
    pixmap.fill(currentColor);
    ui->pushButtonColor->setIcon(QIcon(pixmap));
    pixmap.fill(currentAmbientcolor);
    ui->pushButtonAmbientColor->setIcon(QIcon(pixmap));
    pixmap.fill(currentBackgroundColor);
    ui->pushButtonBackgroundColor->setIcon(QIcon(pixmap));

    ui->listWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->listWidget, SIGNAL(customContextMenuRequested(const QPoint &)),
            SLOT(showContextMenuForListWidget(const QPoint &)));
//    connect(ui->checkBoxMosaicoX, SIGNAL(toggled(bool)),ui->openGLPreviewWidget,SLOT(setTileX(bool)));
//    connect(ui->checkBoxMosaicoY, SIGNAL(toggled(bool)),ui->openGLPreviewWidget,SLOT(setTileY(bool)));
    connect(ui->sliderParallax,SIGNAL(valueChanged(int)),ui->openGLPreviewWidget,SLOT(setParallaxHeight(int)));
    connect(ui->checkBoxPixelated,SIGNAL(toggled(bool)),ui->openGLPreviewWidget,SLOT(setPixelated(bool)));

    connect(ui->openGLPreviewWidget,SIGNAL(selectedLightChanged(LightSource *)), this,SLOT(selectedLightChanged(LightSource*)));
    connect(ui->openGLPreviewWidget,SIGNAL(stopAddingLight()),this,SLOT(stopAddingLight()));

    tabifyDockWidget(ui->normalDockWidget, ui->specularDockWidget);
    tabifyDockWidget(ui->normalDockWidget, ui->parallaxDockWidget);
    tabifyDockWidget(ui->normalDockWidget, ui->occlusionDockWidget);

    tabifyDockWidget(ui->dockWidgetTextures, ui->dockWidgetExport);

    ui->dockWidgetTextures->raise();

    ui->normalDockWidget->raise();

    ui->parallaxQuantizationSlider->setVisible(false);
    ui->labelQuantization->setVisible(false);

    ui->sliderParallaxBright->setVisible(false);
    ui->sliderParallaxContrast->setVisible(false);

    ui->labelBrightness->setVisible(false);
    ui->labelContrast->setVisible(false);

    setAcceptDrops(true);

    ui->listWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);

    connect(ui->openGLPreviewWidget,SIGNAL(processor_selected(ImageProcessor*,bool)),
            this,SLOT(processor_selected(ImageProcessor*,bool)));

    connect(ui->openGLPreviewWidget,SIGNAL(initialized()),this,SLOT(openGL_initialized()));
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
        QListWidgetItem *item =  ui->listWidget->selectedItems().at(0);
        for (int i=0; i<processorList.count(); i++){
            if (processorList.at(i)->get_name() == item->text()){
                processorList.at(i)->deleteLater();
                processorList.removeAt(i);
                break;
            }
        }
        delete item;
        if (processorList.count() == 0){
            ui->openGLPreviewWidget->clear_processor_list();
            processor_selected(sample_processor,true);
            ui->openGLPreviewWidget->add_processor(sample_processor);
        }
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

void MainWindow::update_scene(){
    ui->openGLPreviewWidget->need_to_update = true;
}

void MainWindow::on_actionOpen_triggered()
{
    QStringList fileNames = QFileDialog::getOpenFileNames(this,
                                                          tr("Abrir Imagen"), "",
                                                          tr("Archivos de Imagen (*.png *.jpg *.bmp *.tga)"));
    open_files(fileNames);
}

void MainWindow::add_processor(ImageProcessor *p){

    processorList.append(p);
    processor = p;
    on_comboBoxView_currentIndexChanged(ui->comboBoxView->currentIndex());
    ui->listWidget->addItem(new QListWidgetItem(QIcon(QPixmap::fromImage(*p->get_texture())),p->get_name()));
    ui->listWidget->setCurrentRow(ui->listWidget->count()-1);
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
            ImageProcessor *p = new ImageProcessor();
            p->copy_settings(processor->get_settings());

            p->loadImage(fileName, auximage);
            //p->set_light_list(*(ui->openGLPreviewWidget->get_current_light_list_ptr()));
            add_processor(p);
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
    QString aux;

    QImage n;
    QString suffix;
    QFileInfo info;
    QString message = "";

    info = QFileInfo(fileName);
    suffix = info.completeSuffix();

    if (suffix == "") suffix = "png";

    if (ui->checkBoxExportNormal->isChecked()){
        aux = info.absoluteFilePath().remove("."+suffix)+"_n."+suffix;
        n = *processor->get_normal();
        n.save(aux);
        message += tr("Se exportó el mapa normal.\n");
    }
    if (ui->checkBoxExportParallax->isChecked()){
        aux = info.absoluteFilePath().remove("."+suffix)+"_p."+suffix;
        n = *processor->get_parallax();
        n.save(aux);
        message += tr("Se exportó el mapa de paralaje.\n");
    }
    if (ui->checkBoxExportSpecular->isChecked()){
        aux = info.absoluteFilePath().remove("."+suffix)+"_s."+suffix;
        n = *processor->get_specular();
        n.save(aux);
        message += tr("Se exportó el mapa especular.\n");
    }
    if (ui->checkBoxExportOcclusion->isChecked()){
        fileName = info.absoluteFilePath().remove("."+suffix)+"_o."+suffix;
        n = *processor->get_occlusion();
        n.save(fileName);
        message += tr("Se exportó el mapa de oclusión.\n");
    }
    if (message != ""){
        QMessageBox msgBox;
        msgBox.setText(message);
        msgBox.exec();
    }

}


void MainWindow::openGL_initialized(){
    QString tmpImage = ":/images/sample.png";
    bool success;

    processor_selected(processor,false);
    processor->loadImage(tmpImage,il.loadImage(tmpImage, &success));
    ui->openGLPreviewWidget->add_processor(processor);
    ui->openGLPreviewWidget->loadTextures();

    update_scene();

    processor_selected(processor,true);
    processor->set_light_list(*(ui->openGLPreviewWidget->get_current_light_list_ptr()));
    ui->openGLPreviewWidget->set_current_light_list(processor->get_light_list_ptr());

}

void MainWindow::on_pushButtonColor_clicked()
{
    QColorDialog *cd = new QColorDialog(currentColor);
    connect(cd,SIGNAL(currentColorChanged(const QColor&)),this,SLOT(set_light_color(const QColor&)));
    cd->exec();
    disconnect(cd,SIGNAL(currentColorChanged(const QColor&)),this,SLOT(set_light_color(const QColor&)));
    delete cd;
}

void MainWindow::set_light_color(const QColor &color){
    if (color.isValid()){
        currentColor = color;
        QPixmap pixmap(100,100);
        pixmap.fill(color);
        ui->pushButtonColor->setIcon(QIcon(pixmap));
        ui->openGLPreviewWidget->setLightColor(color);
        ui->openGLPreviewWidget->setSpecColor(color);
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
    QColorDialog *cd = new QColorDialog(currentColor);
    connect(cd,SIGNAL(currentColorChanged(const QColor&)),this,SLOT(set_ambient_color(const QColor&)));
    cd->exec();
    disconnect(cd,SIGNAL(currentColorChanged(const QColor&)),this,SLOT(set_ambient_color(const QColor&)));
    delete cd;
}

void MainWindow::set_ambient_color(const QColor & color){
    if (color.isValid()){
        currentAmbientcolor = color;
        QPixmap pixmap(100,100);
        pixmap.fill(color);
        ui->pushButtonAmbientColor->setIcon(QIcon(pixmap));
        ui->openGLPreviewWidget->setAmbientColor(color);
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
    connect(p,SIGNAL(processed()),this,SLOT(update_scene()));
    connect(ui->normalDepthSlider,SIGNAL(valueChanged(int)),p,SLOT(set_normal_depth(int)));
    connect(ui->normalBlurSlider,SIGNAL(valueChanged(int)),p,SLOT(set_normal_blur_radius(int)));
    connect(ui->normalBevelSlider,SIGNAL(valueChanged(int)),p,SLOT(set_normal_bisel_depth(int)));
    connect(ui->normalBiselDistanceSlider,SIGNAL(valueChanged(int)),p,SLOT(set_normal_bisel_distance(int)));
    connect(ui->normalBiselBlurSlider,SIGNAL(valueChanged(int)),p,SLOT(set_normal_bisel_blur_radius(int)));
    connect(ui->biselSoftRadio,SIGNAL(toggled(bool)),p,SLOT(set_normal_bisel_soft(bool)));
    connect(ui->normalInvertX,SIGNAL(toggled(bool)),p,SLOT(set_normal_invert_x(bool)));
    connect(ui->normalInvertY,SIGNAL(toggled(bool)),p,SLOT(set_normal_invert_y(bool)));
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

    connect(ui->checkBoxMosaicoX,SIGNAL(toggled(bool)),p,SLOT(set_tile_x(bool)));
    connect(ui->checkBoxMosaicoY,SIGNAL(toggled(bool)),p,SLOT(set_tile_y(bool)));
    connect(ui->checkBoxParallax,SIGNAL(toggled(bool)),p,SLOT(set_is_parallax(bool)));

    p->set_connected(true);
}

void MainWindow::disconnect_processor(ImageProcessor *p){
    disconnect(p,SIGNAL(processed()),this,SLOT(update_scene()));
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

    disconnect(ui->sliderOcclusionSoft,SIGNAL(valueChanged(int)),p,SLOT(set_occlusion_blur(int)));
    disconnect(ui->sliderOcclusionBright,SIGNAL(valueChanged(int)),p,SLOT(set_occlusion_bright(int)));
    disconnect(ui->sliderOcclusionContrast,SIGNAL(valueChanged(int)),p,SLOT(set_occlusion_contrast(int)));
    disconnect(ui->sliderOcclusionThresh,SIGNAL(valueChanged(int)),p,SLOT(set_occlusion_thresh(int)));
    disconnect(ui->checkBoxOcclusionInvert,SIGNAL(toggled(bool)),p,SLOT(set_occlusion_invert(bool)));
    disconnect(ui->checkBoxOcclusionDistance,SIGNAL(toggled(bool)),p,SLOT(set_occlusion_distance_mode(bool)));
    disconnect(ui->sliderOcclusionDistance,SIGNAL(valueChanged(int)),p,SLOT(set_occlusion_distance(int)));

    disconnect(ui->checkBoxMosaicoX,SIGNAL(toggled(bool)),p,SLOT(set_tile_x(bool)));
    disconnect(ui->checkBoxMosaicoY,SIGNAL(toggled(bool)),p,SLOT(set_tile_y(bool)));
    disconnect(ui->checkBoxParallax,SIGNAL(toggled(bool)),p,SLOT(set_is_parallax(bool)));
    p->set_connected(false);
}

void MainWindow::on_listWidget_itemSelectionChanged()
{
    ImageProcessor *p = nullptr;
    if (ui->listWidget->count() == 0){
      processor_selected(sample_processor,true);
    } else if (ui->listWidget->selectedItems().count() > 0){
        processor_selected(sample_processor,false);
        ui->openGLPreviewWidget->clear_processor_list();
        foreach(QListWidgetItem *item, ui->listWidget->selectedItems()){
            for(int i = 0; i < processorList.count(); i++){
                if (processorList.at(i)->get_name() == item->text()){
                    p = processorList.at(i);
                    ui->openGLPreviewWidget->add_processor(p);
                    processor_selected(p,true);
                }
            }
        }
    }
    else {
        ui->listWidget->setCurrentRow(0);
    }

    ui->openGLPreviewWidget->need_to_update = true;
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
            n = *p->get_normal();
            info = QFileInfo(p->get_name());
            suffix = info.completeSuffix();
            name = info.absoluteFilePath().remove("."+suffix)+"_n."+suffix;
            n.save(name);
        }
        message += tr("Se exportaron todos los mapas normales.\n");
    }
    if (ui->checkBoxExportParallax->isChecked()){
        foreach (ImageProcessor *p, processorList){
            n = *p->get_parallax();
            info = QFileInfo(p->get_name());
            suffix = info.completeSuffix();
            name = info.absoluteFilePath().remove("."+suffix)+"_p."+suffix;
            n.save(name);
        }
        message += tr("Se exportaron todos los mapas de paralaje.\n");
    }
    if (ui->checkBoxExportSpecular->isChecked()){
        foreach (ImageProcessor *p, processorList){
            n = *p->get_specular();
            info = QFileInfo(p->get_name());
            suffix = info.completeSuffix();
            name = info.absoluteFilePath().remove("."+suffix)+"_s."+suffix;
            n.save(name);
        }
        message += tr("Se exportaron todos los mapas especulares.\n");
    }
    if (ui->checkBoxExportOcclusion->isChecked()){
        foreach (ImageProcessor *p, processorList){
            n = *p->get_occlusion();
            info = QFileInfo(p->get_name());
            suffix = info.completeSuffix();
            name = info.absoluteFilePath().remove("."+suffix)+"_o."+suffix;
            n.save(name);
        }
        message += tr("Se exportaron todos los mapas de oclusión.\n");
    }
    if (message != ""){
        QMessageBox msgBox;
        msgBox.setText(message);
        msgBox.exec();
    }
}

void MainWindow::on_pushButtonBackgroundColor_clicked()
{
    QColorDialog *cd = new QColorDialog(currentColor);
    connect(cd,SIGNAL(currentColorChanged(const QColor&)),this,SLOT(set_background_color(const QColor&)));
    cd->exec();
    disconnect(cd,SIGNAL(currentColorChanged(const QColor&)),this,SLOT(set_background_color(const QColor&)));
    delete cd;
}

void MainWindow::set_background_color(const QColor& color){
    if (color.isValid()){
        currentBackgroundColor = color;
        QPixmap pixmap(100,100);
        pixmap.fill(color);
        ui->pushButtonBackgroundColor->setIcon(QIcon(pixmap));
        ui->openGLPreviewWidget->setBackgroundColor(color);
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    NBSelector *nb = new NBSelector(processor);
    nb->exec();
}


void MainWindow::on_comboBox_currentIndexChanged(int index)
{

    ParallaxType ptype = static_cast<ParallaxType>(index);
    foreach(ImageProcessor * processor, processorList){
        if (processor->get_selected() && processor->get_connected())
            processor->set_parallax_type(ptype);
    }

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
                n = *p->get_normal();
                info = QFileInfo(p->get_name());
                suffix = info.completeSuffix();
                name = path + "/" + info.baseName() + "_n." + suffix;
                int i=1;
                while (QFileInfo::exists(name))
                    name = path + "/" + info.baseName() + "(" + QString::number(++i) + ")" + "_n." + suffix;
                n.save(name);
            }
            message += tr("Se exportaron todos los mapas normales.\n");
        }
        if (ui->checkBoxExportParallax->isChecked()){
            foreach (ImageProcessor *p, processorList){
                n = *p->get_parallax();
                info = QFileInfo(p->get_name());
                suffix = info.completeSuffix();
                name = path + "/" + info.baseName() + "_p." + suffix;
                int i=1;
                while (QFileInfo::exists(name))
                    name = path + "/" + info.baseName() + "(" + QString::number(++i) + ")" + "_p." + suffix;
                n.save(name);
            }
            message += tr("Se exportaron todos los mapas de paralaje.\n");
        }
        if (ui->checkBoxExportSpecular->isChecked()){
            foreach (ImageProcessor *p, processorList){
                n = *p->get_specular();
                info = QFileInfo(p->get_name());
                suffix = info.completeSuffix();
                name = path + "/" + info.baseName() + "_s." + suffix;
                int i=1;
                while (QFileInfo::exists(name))
                    name = path + "/" + info.baseName() + "(" + QString::number(++i) + ")" + "_s." + suffix;
                n.save(name);
            }
            message += tr("Se exportaron todos los mapas especulares.\n");
        }
        if (ui->checkBoxExportOcclusion->isChecked()){
            foreach (ImageProcessor *p, processorList){
                n = *p->get_occlusion();
                info = QFileInfo(p->get_name());
                suffix = info.completeSuffix();
                name = path + "/" + info.baseName() + "_o." + suffix;
                int i=1;
                while (QFileInfo::exists(name))
                    name = path + "/" + info.baseName() + "(" + QString::number(++i) + ")" + "_o." + suffix;
                n.save(name);
            }
            message += tr("Se exportaron todos los mapas de oclusión.\n");
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
    switch (index){
    case ViewMode::Texture:
        ui->openGLPreviewWidget->set_view_mode(Texture);
        break;
    case ViewMode::NormalMap:
        ui->openGLPreviewWidget->set_view_mode(NormalMap);
        break;
    case ViewMode::SpecularMap:
        ui->openGLPreviewWidget->set_view_mode(SpecularMap);
        break;
    case ViewMode::ParallaxMap:
        ui->openGLPreviewWidget->set_view_mode(ParallaxMap);
        break;
    case ViewMode::OcclusionMap:
        ui->openGLPreviewWidget->set_view_mode(OcclusionMap);
        break;
    case ViewMode::Preview:
        ui->openGLPreviewWidget->setLight(true);
        ui->openGLPreviewWidget->set_view_mode(Preview);
        break;
    }
}

void MainWindow::on_actionExportPreview_triggered()
{
    int current_view = ui->comboBoxView->currentIndex();
    ui->comboBoxView->setCurrentIndex(ViewMode::Preview);
    QImage preview(ui->openGLPreviewWidget->get_preview());
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Guardar Imagen"), "",
                                                    tr("Archivos de Imagen (*.png *.jpg *.bmp)"));

    QMessageBox msgBox;
    if(preview.save(fileName)){
        msgBox.setText("Se exportó la vista previa.");
    }else{
        msgBox.setText("No se pudo exportar la vista previa.");
    }
    msgBox.exec();
    ui->comboBoxView->setCurrentIndex(current_view);
}

void MainWindow::on_actionAbout_triggered()
{
    AboutDialog *ad = new AboutDialog;
    ad->show();
}


void MainWindow::on_actionAdd_Light_triggered(bool checked)
{
    ui->openGLPreviewWidget->set_add_light(checked);
}

void MainWindow::selectedLightChanged(LightSource *light){
    ui->horizontalSliderDiffLight->setValue(light->get_diffuse_intensity()*100);
    ui->horizontalSliderSpec->setValue(light->get_specular_intesity()*100);
    ui->horizontalSliderSpecScatter->setValue(light->get_specular_scatter());
    ui->horizontalSliderDiffHeight->setValue(light->get_height()*100);

    QPixmap pixmap(100,100);
    currentColor = light->get_diffuse_color();
    pixmap.fill(currentColor);
    ui->pushButtonColor->setIcon(QIcon(pixmap));

}

void MainWindow::stopAddingLight(){
    ui->actionAdd_Light->setChecked(false);
    on_actionAdd_Light_triggered(false);
}

void MainWindow::on_checkBoxLightsPerTexture_toggled(bool checked)
{
    if (!checked){
        ui->openGLPreviewWidget->set_current_light_list(sample_processor->get_light_list_ptr());
    }else{
        ui->openGLPreviewWidget->set_current_light_list(processor->get_light_list_ptr());
    }
}

void MainWindow::selectedProcessorsChanged(QList<ImageProcessor *> list){
    selectedProcessors = list;
    foreach(ImageProcessor * p, processorList){
        disconnect_processor(p);
    }
    foreach(ImageProcessor* p, selectedProcessors){
        connect_processor(p);
    }
}

void MainWindow::processor_selected(ImageProcessor* processor, bool selected){

    foreach(ImageProcessor *p, processorList){
        disconnect_processor(p);
    }
    processor->set_selected(selected);
    if(selected){
        ui->openGLPreviewWidget->processor = processor;
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

        ui->sliderOcclusionSoft->setValue(processor->get_occlusion_blur());
        ui->sliderOcclusionBright->setValue(processor->get_occlusion_bright());
        ui->sliderOcclusionThresh->setValue(processor->get_occlusion_trhesh());
        ui->sliderOcclusionContrast->setValue(static_cast<int>(processor->get_occlusion_contrast()*1000));
        ui->sliderOcclusionDistance->setValue(processor->get_occlusion_distance());
        ui->checkBoxOcclusionInvert->setChecked(processor->get_occlusion_invert());
        ui->checkBoxOcclusionDistance->setChecked(processor->get_occlusion_distance_mode());
        this->processor = processor;

        ui->checkBoxMosaicoX->setChecked(processor->get_tile_x());
        ui->checkBoxMosaicoY->setChecked(processor->get_tile_y());


    }
    if (ui->listWidget->selectedItems().count() == 1){
        foreach (ImageProcessor *p, processorList){
            if (p->get_name() == ui->listWidget->selectedItems().at(0)->text()){
                p->set_selected(true);
            }
        }
    }
    foreach(ImageProcessor *p, processorList){
        if (p->get_selected()) connect_processor(p);
    }
    if (sample_processor->get_selected()) connect_processor(sample_processor);

}
