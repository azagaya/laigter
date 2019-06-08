#include "presetsmanager.h"
#include "ui_presetsmanager.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QStandardPaths>
#include <QDir>
#include <QDebug>

static QString presetCodes[19] = {"EnhanceHeight ", "EnhanceSoft ", "BumpHeight ",
                                  "BumpDistance", "BumpSoft ", "BumpCut ", "Tile ", "InvertX ",
                                  "InvertY ", "ParallaxType", "BinaryThreshold ",
                                  "BinaryFocus ", "ParallaxSoft ", "BinaryMinHeight ",
                                  "BinaryErodeDilate ", "HeightMapBrightness ",
                                  "HeightMapContrast ", "InvertParallax "};

PresetsManager::PresetsManager(ProcessorSettings settings, QList <ImageProcessor*> *processorList, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PresetsManager),
    mSettings(settings),
    mProcessorList(processorList)
{
    ui->setupUi(this);

#ifndef PORTABLE
    presetsPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)+"/presets/";
    presetsDir = QDir(presetsPath);
#else
    presetsPath = "./presets/";
    presetsDir = QDir(presetsPath);
#endif

    update_presets();
    foreach(ImageProcessor *p, *mProcessorList){
        ui->listWidgetTextures->addItem(new QListWidgetItem(QIcon(QPixmap::fromImage(p->get_neighbour(1,1))),p->get_name()));
    }
    connect(ui->checkBoxAllPresets,SIGNAL(stateChanged(int)),this,SLOT(control_checkbox_state_changed(int)));

    currentValues[0] = QString::number(*mSettings.normal_depth);
    currentValues[1] = QString::number(*mSettings.normal_blur_radius);
    currentValues[2] = QString::number(*mSettings.normal_bisel_depth);
    currentValues[3] = QString::number(*mSettings.normal_bisel_distance);
    currentValues[4] = QString::number(*mSettings.normal_bisel_blur_radius);
    currentValues[5] = *mSettings.normal_bisel_soft ? "1" : "0";
    currentValues[6] = *mSettings.tileable ? "1" : "0";
    currentValues[7] = *mSettings.normalInvertX == -1 ? "1" : "0";
    currentValues[8] = *mSettings.normalInvertY == -1 ? "1" : "0";
    currentValues[9] = QString::number((int)*mSettings.parallax_type);
    currentValues[10] = QString::number(*mSettings.parallax_max);
    currentValues[11] = QString::number(*mSettings.parallax_focus);
    currentValues[12] = QString::number(*mSettings.parallax_soft);
    currentValues[13] = QString::number(*mSettings.parallax_min);
    currentValues[14] = QString::number(*mSettings.parallax_erode_dilate);
    currentValues[15] = QString::number(*mSettings.parallax_brightness);
    currentValues[16] = QString::number(*mSettings.parallax_contrast*1000);
    currentValues[17] = QString::number(*mSettings.parallax_invert);

    ui->listWidgetTextures->setSelectionMode(QAbstractItemView::ExtendedSelection);
}

void PresetsManager::update_presets(){
    ui->comboBoxPreset->clear();
    foreach(QString file, scan_presets()){
        ui->comboBoxPreset->addItem(file);
    }
}

QStringList PresetsManager::scan_presets(){
    return presetsDir.entryList(QDir::Files);
}

PresetsManager::~PresetsManager()
{
    delete ui;
}

void PresetsManager::on_pushButtonSavePreset_clicked()
{
    QMessageBox msg;
    QString presetName = ui->lineEditPresetName->text();
    if (presetName == ""){
        msg.setText(tr("Debe ingresar un nombre para el preset!"));
        msg.exec();
        return;
    }

    QFile preset(presetsPath + presetName);
    if (preset.exists()){
        msg.setText(tr("Ya existe un preset con ese nombre!"));
        msg.exec();
        return;
    }

    if (preset.open(QIODevice::WriteOnly)){

        QTextStream in(&preset);
        in << "[Laigter Preset]";
        for (int i=0; i < ui->listWidgetControls->count(); i++){
            if(ui->listWidgetControls->item(i)->checkState() == Qt::Checked){
                in << "\n" << presetCodes[i] << "\t" << currentValues[i];
            }
        }

        preset.close();
        update_presets();
    }
}

void PresetsManager::control_checkbox_state_changed(int state){
    for (int i=0; i< ui->listWidgetControls->count(); i++){
        ui->listWidgetControls->item(i)->setCheckState((Qt::CheckState)state);
    }
}

void PresetsManager::on_listWidgetControls_itemChanged(QListWidgetItem *item)
{
    bool checked = item->checkState() == Qt::Checked ? true : false;
    disconnect(ui->checkBoxAllPresets,SIGNAL(stateChanged(int)),this,SLOT(control_checkbox_state_changed(int)));
    if (!checked){
        ui->checkBoxAllPresets->setChecked(false);

    } else {
        for (int i=0; i < ui->listWidgetControls->count(); i++){
            checked &= ui->listWidgetControls->item(i)->checkState() == Qt::Checked;
            if (!checked)
                break;
        }
        ui->checkBoxAllPresets->setChecked(checked);
    }
    connect(ui->checkBoxAllPresets,SIGNAL(stateChanged(int)),this,SLOT(control_checkbox_state_changed(int)));
}

void PresetsManager::on_pushButtonDeletePreset_clicked()
{
    QString current_preset = ui->comboBoxPreset->currentText();
    QFile::remove(presetsPath+current_preset);
    update_presets();
}

void PresetsManager::on_pushButtonAplyPreset_clicked()
{
    QMessageBox msg;

    QString preset = ui->comboBoxPreset->currentText();
    QFile selected_preset(presetsPath+preset);
    if(!selected_preset.open(QIODevice::ReadOnly)){
        msg.setText(tr("No se pudo abrir el preset especificado."));
        msg.exec();
        return;
    }
    QByteArray settings = selected_preset.readAll();
    QList<QByteArray> settings_list = settings.split('\n');
    if (settings_list[0] != "[Laigter Preset]"){
        msg.setText(tr("Archivo con formato incorrecto."));
        msg.exec();
        return;
    }

    ui->groupBox->setEnabled(false);
    ui->groupBox_2->setEnabled(false);

    settings_list.removeAt(0);

    QStringList processorList;
    foreach(QListWidgetItem *item, ui->listWidgetTextures->selectedItems()){
        processorList.append(item->text());
    }
    foreach(ImageProcessor *p, *mProcessorList){
        if (!processorList.contains(p->get_name()))
            continue;

        ui->labelMessage->setText(tr("Aplicando ")+ preset + tr(" a ") + p->get_name() + "...");
        QApplication::processEvents();
        for (int i=0; i< settings_list.count(); i++){
            QByteArray setting = settings_list.at(i);
            QList<QByteArray> aux = setting.split('\t');
            if (aux[0] == presetCodes[0]){
                p->set_normal_depth(aux[1].toInt());
            }else if (aux[0] == presetCodes[1]){
                p->set_normal_blur_radius(aux[1].toInt());
            }else if (aux[0] == presetCodes[2]){
                p->set_normal_bisel_depth(aux[1].toInt());
            }else if (aux[0] == presetCodes[3]){
                p->set_normal_bisel_distance(aux[1].toInt());
            }else if (aux[0] == presetCodes[4]){
                p->set_normal_bisel_blur_radius(aux[1].toInt());
            }else if (aux[0] == presetCodes[5]){
                p->set_normal_bisel_soft((bool)aux[1].toInt());
            }else if (aux[0] == presetCodes[6]){
                p->set_tileable((bool)aux[1].toInt());
            }else if (aux[0] == presetCodes[7]){
                p->set_normal_invert_x((bool)aux[1].toInt());
            }else if (aux[0] == presetCodes[8]){
                p->set_normal_invert_y((bool)aux[1].toInt());
            }else if (aux[0] == presetCodes[9]){
                p->set_parallax_type((ParallaxType)aux[1].toInt());
            }else if (aux[0] == presetCodes[10]){
                p->set_parallax_thresh(aux[1].toInt());
            }else if (aux[0] == presetCodes[11]){
                p->set_parallax_focus(aux[1].toInt());
            }else if (aux[0] == presetCodes[12]){
                p->set_parallax_soft(aux[1].toInt());
            }else if (aux[0] == presetCodes[13]){
                p->set_parallax_min(aux[1].toInt());
            }else if (aux[0] == presetCodes[14]){
                p->set_parallax_erode_dilate(aux[1].toInt());
            }else if (aux[0] == presetCodes[15]){
                p->set_parallax_brightness(aux[1].toInt());
            }else if (aux[0] == presetCodes[16]){
                p->set_parallax_contrast(aux[1].toInt());
            }else if (aux[0] == presetCodes[17]){
                p->set_parallax_invert((bool)aux[1].toInt());
            }
        }
    }

    ui->groupBox->setEnabled(true);
    ui->groupBox_2->setEnabled(true);
    ui->labelMessage->setText("");
    settingAplied();
}

void PresetsManager::on_pushButtonExportPreset_clicked()
{
    QString path = QFileDialog::getExistingDirectory();
    if (path != nullptr){
        QString preset = ui->comboBoxPreset->currentText();
        QFile selected_preset(presetsPath+preset);
        if(selected_preset.open(QIODevice::ReadOnly)){
            selected_preset.copy(path+"/"+preset);
        }
    }
}

void PresetsManager::on_pushButtonImportPreset_clicked()
{
    QString path = QFileDialog::getOpenFileName();
    if (path != nullptr){
        QFile preset(path);
        QFileInfo info(preset);
        QString name = info.baseName();
        QFile existing_preset(presetsPath+name);
        if (!existing_preset.exists()){
            if (preset.open(QIODevice::ReadOnly)){
                QByteArray firstLine = preset.readLine();
                if (firstLine == "[Laigter Preset]\n"){
                    preset.copy(presetsPath+name);
                }
                else{
                    QMessageBox msg;
                    msg.setText(tr("Formato de preset incorrecto."));
                    msg.exec();
                }
            }
        }
        else{
            QMessageBox msg;
            msg.setText(tr("Ya existe un preset con ese nombre."));
            msg.exec();
        }
    }
    update_presets();
}
