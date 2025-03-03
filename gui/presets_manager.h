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

#ifndef PRESETSMANAGER_H
#define PRESETSMANAGER_H

#include "src/image_processor.h"
#include "src/light_source.h"

#include <QDialog>
#include <QDir>
#include <QList>
#include <QListWidgetItem>

namespace Ui
{
typedef QString preset_codes_array[34];
class PresetsManager;
} // namespace Ui

class PresetsManager : public QDialog
{
  Q_OBJECT

private:
  Ui::PresetsManager *ui;
  ProcessorSettings mSettings, loadedSettings;
  QList<ImageProcessor *> *mProcessorList;
  QString presetsPath;
  QDir presetsDir;
  QString currentValues[34];
  QList<LightSource *> lightList;

public:
  explicit PresetsManager(ProcessorSettings settings,
                          QList<ImageProcessor *> *processorList,
                          QWidget *parent = nullptr);
  ~PresetsManager();
  static Ui::preset_codes_array &get_preset_codes();
  static void applyPresetSettings(QByteArray &setting, ImageProcessor &p);
  static void applyPresets(QString &preset, ImageProcessor &p);
  static void applyPresetsString(QString preset, ImageProcessor *p);
  static void SaveAllPresets(ImageProcessor *p, QString path);

private slots:
  QStringList scan_presets();
  void on_pushButtonSavePreset_clicked();
  void update_presets();
  void on_pushButtonDeletePreset_clicked();
  void on_pushButtonAplyPreset_clicked();
  void on_pushButtonExportPreset_clicked();
  void on_pushButtonImportPreset_clicked();

signals:
  void settingAplied();
};

#endif // PRESETSMANAGER_H
