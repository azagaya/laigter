#ifndef PRESETSMANAGER_H
#define PRESETSMANAGER_H

#include <QDialog>
#include <QList>
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
    void settingAplied(QStringList processorNames);

private slots:
    void on_pushButtonSavePreset_clicked();
    QStringList scan_presets();

private:
    Ui::PresetsManager *ui;
    ProcessorSettings mSettings;
    QList <ImageProcessor *> *mProcessorList;
};

#endif // PRESETSMANAGER_H
