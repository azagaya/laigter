#include "presetsmanager.h"
#include "ui_presetsmanager.h"
#include <QMessageBox>
#include <QStandardPaths>
#include <QDir>
#include <QDebug>

PresetsManager::PresetsManager(ProcessorSettings settings, QList <ImageProcessor*> *processorList, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PresetsManager),
    mSettings(settings),
    mProcessorList(processorList)
{
    ui->setupUi(this);
    foreach(QString file, scan_presets()){
        ui->comboBoxPreset->addItem(file);
    }
    foreach(ImageProcessor *p, *mProcessorList){
        ui->listWidgetTextures->addItem(new QListWidgetItem(QIcon(QPixmap::fromImage(p->get_neighbour(1,1))),p->get_name()));

    }
}

QStringList PresetsManager::scan_presets(){

#ifndef PORTABLE
    QString presetsPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)+"/presets/";
    QDir presetsDir(presetsPath);
#else
    QString presetsPath = "./presets/";
    QDir presetsDir(presetsPath);
#endif

    return presetsDir.entryList(QDir::Files);
}

PresetsManager::~PresetsManager()
{
    delete ui;
}

void PresetsManager::on_pushButtonSavePreset_clicked()
{
    QMessageBox msg;
    if (ui->lineEditPresetName->text() == ""){
        msg.setText(tr("Debe ingresar un nombre para el preset!"));
        msg.exec();
        return;
    }

#ifndef PORTABLE
    QString presetsPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)+"/presets/";
    QFile preset(presetsPath+ui->lineEditPresetName->text());
    if (preset.exists()){
        msg.setText(tr("Ya existe un preset con ese nombre!"));
        msg.exec();
        return;
    }

#else
    QString presetsPath = "./presets/";
    QFile preset(presetsPath+ui->lineEditPresetName->text());
    if (preset.exists()){
        msg.setText(tr("Ya existe un preset con ese nombre!"));
        msg.exec();
        return;
    }
#endif

    if (preset.open(QIODevice::WriteOnly)){

    }
    preset.close();
}
