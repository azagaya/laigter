#ifndef PRESETSMANAGER_H
#define PRESETSMANAGER_H

#include <QDialog>
#include <QList>
#include <QListWidgetItem>
#include <QDir>
#include "src/imageprocessor.h"

namespace Ui {
class PresetsManager;
}

class PresetsManager : public QDialog
{
    Q_OBJECT

public:
    explicit PresetsManager(ProcessorSettings settings, QList <ImageProcessor *> *processorList, QWidget *parent = nullptr);
    ~PresetsManager();

signals:
    void settingAplied();

private slots:
    void on_pushButtonSavePreset_clicked();
    void update_presets();
    QStringList scan_presets();

//    void control_checkbox_state_changed(int state);

//    void on_listWidgetControls_itemChanged(QListWidgetItem *item);

    void on_pushButtonDeletePreset_clicked();

    void on_pushButtonAplyPreset_clicked();

    void on_pushButtonExportPreset_clicked();

    void on_pushButtonImportPreset_clicked();

private:
    Ui::PresetsManager *ui;
    ProcessorSettings mSettings, loadedSettings;
    QList <ImageProcessor *> *mProcessorList;
    QString presetsPath;
    QDir presetsDir;
    QString currentValues[23];
};

#endif // PRESETSMANAGER_H
