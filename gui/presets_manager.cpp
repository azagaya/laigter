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

#include "presets_manager.h"
#include "ui_presets_manager.h"

#include <QDebug>
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <QStandardPaths>

static QString presetCodes[30] = {"EnhanceHeight ",
                                  "EnhanceSoft ",
                                  "BumpHeight ",
                                  "BumpDistance",
                                  "BumpSoft ",
                                  "BumpCut ",
                                  "Tile ",
                                  "InvertX ",
                                  "InvertY ",
                                  "ParallaxType",
                                  "BinaryThreshold ",
                                  "BinaryFocus ",
                                  "ParallaxSoft ",
                                  "BinaryMinHeight ",
                                  "BinaryErodeDilate ",
                                  "HeightMapBrightness ",
                                  "HeightMapContrast ",
                                  "InvertParallax ",
                                  "SpecularBlur ",
                                  "SpecularBright ",
                                  "SpecularContrast ",
                                  "SpecularThresh ",
                                  "SpecularInvert ",
                                  "OcclusionBlur ",
                                  "OcclusionBright ",
                                  "OcclusionInvert ",
                                  "OcclusionThresh ",
                                  "OcclusionContrast ",
                                  "OcclusionDistance ",
                                  "OcclusionDistanceMode "};

PresetsManager::PresetsManager(ProcessorSettings settings,
                               QList<ImageProcessor *> *processorList,
                               QWidget *parent)
    : QDialog(parent), ui(new Ui::PresetsManager), mSettings(settings),
      mProcessorList(processorList)
{
  ui->setupUi(this);
#ifndef PORTABLE
  presetsPath =
      QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) +
      "/presets/";
  presetsDir = QDir(presetsPath);
#else
  presetsPath = "./presets/";
  presetsDir = QDir(presetsPath);
#endif
  update_presets();
  foreach (ImageProcessor *p, *mProcessorList)
  {
    ui->listWidgetTextures->addItem(new QListWidgetItem(
        QIcon(QPixmap::fromImage(p->get_neighbour(1, 1))), p->get_name()));
  }

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
  currentValues[16] = QString::number(*mSettings.parallax_contrast * 1000);
  currentValues[17] = QString::number(*mSettings.parallax_invert);
  currentValues[18] = QString::number(*mSettings.specular_blur);
  currentValues[19] = QString::number(*mSettings.specular_bright);
  currentValues[20] = QString::number(*mSettings.specular_contrast * 1000);
  currentValues[21] = QString::number(*mSettings.specular_thresh);
  currentValues[22] = *mSettings.specular_invert ? "1" : "0";
  currentValues[23] = QString::number(*mSettings.occlusion_blur);
  currentValues[24] = QString::number(*mSettings.occlusion_bright);
  currentValues[25] = *mSettings.occlusion_invert ? "1" : "0";
  currentValues[26] = QString::number(*mSettings.occlusion_thresh);
  currentValues[27] = QString::number(*mSettings.occlusion_contrast * 1000);
  currentValues[28] = QString::number(*mSettings.occlusion_distance);
  currentValues[29] = *mSettings.occlusion_distance_mode ? "1" : "0";

  lightList.clear();
  foreach (LightSource *light, *(mSettings.lightList))
  {
    LightSource *l = new LightSource();
    l->copy_settings(light);
    lightList.append(l);
  }

  ui->listWidgetTextures->setSelectionMode(
      QAbstractItemView::ExtendedSelection);
  ui->treeWidget->setColumnHidden(1, true);
}

PresetsManager::~PresetsManager() { delete ui; }

void PresetsManager::update_presets()
{
  ui->comboBoxPreset->clear();
  foreach (QString file, scan_presets())
    ui->comboBoxPreset->addItem(file);
}

QStringList PresetsManager::scan_presets()
{
  return presetsDir.entryList(QDir::Files);
}

void PresetsManager::on_pushButtonSavePreset_clicked()
{
  QMessageBox msg;
  QString presetName = ui->lineEditPresetName->text();
  if (presetName == "")
  {
    msg.setText(tr("You must input a name for the preset!"));
    msg.exec();
    return;
  }

  QFile preset(presetsPath + presetName);
  if (preset.exists())
  {
    msg.setText(tr("There is already a preset with that name!"));
    msg.exec();
    return;
  }

  if (preset.open(QIODevice::WriteOnly))
  {
    QTextStream in(&preset);
    in << "[Laigter Preset]";
    bool saveLights = false;
    QTreeWidgetItemIterator it(ui->treeWidget);
    while (*it)
    {
      if ((*it)->checkState(0) == Qt::Checked)
      {
        QString code = (*it)->text(1);
        if ((*it)->text(0) == tr("Lights"))
          saveLights = true;
        else if (code != "")
        {
          int i = (*it)->text(1).toInt();
          in << "\n"
             << presetCodes[i] << "\t" << currentValues[i];
        }
      }
      ++it;
    }

    if (saveLights)
    {
      foreach (LightSource *light, lightList)
      {
        QColor diffuseColor = light->get_diffuse_color();
        QColor specularColor = light->get_specular_color();
        QVector3D position = light->get_light_position();
        in << "\nLightSource\n";
        in << "DiffuseColor \t" << diffuseColor.red() << "\t"
           << diffuseColor.green() << "\t" << diffuseColor.blue()
           << "\n";
        in << "DiffuseIntensity \t" << light->get_diffuse_intensity()
           << "\n";
        in << "SpecularColor \t" << specularColor.red() << "\t"
           << specularColor.green() << "\t" << specularColor.blue()
           << "\n";
        in << "SpecularScatter \t" << light->get_specular_scatter()
           << "\n";
        in << "SpecularIntensity \t" << light->get_specular_intesity()
           << "\n";
        in << "Position \t" << position.x() << "\t" << position.y()
           << "\t" << position.z() << "\t";
      }
    }
    preset.close();
    update_presets();
  }
}

void PresetsManager::on_pushButtonDeletePreset_clicked()
{
  QString current_preset = ui->comboBoxPreset->currentText();
  QFile::remove(presetsPath + current_preset);
  update_presets();
}

void PresetsManager::on_pushButtonAplyPreset_clicked()
{
  QMessageBox msg;
  QString preset = ui->comboBoxPreset->currentText();
  QFile selected_preset(presetsPath + preset);
  if (!selected_preset.open(QIODevice::ReadOnly))
  {
    msg.setText(tr("Cannot open the specified preset."));
    msg.exec();
    return;
  }
  QByteArray settings = selected_preset.readAll();
  QList<QByteArray> settings_list = settings.split('\n');
  if (settings_list[0] != "[Laigter Preset]")
  {
    msg.setText(tr("Incorrect format."));
    msg.exec();
    return;
  }

  ui->groupBox->setEnabled(false);
  ui->groupBox_2->setEnabled(false);

  settings_list.removeAt(0);

  QStringList processorList;
  foreach (QListWidgetItem *item, ui->listWidgetTextures->selectedItems())
    processorList.append(item->text());

  foreach (ImageProcessor *p, *mProcessorList)
  {
    if (!processorList.contains(p->get_name()))
      continue;

    if (settings.contains("LightSource"))
      p->get_light_list_ptr()->clear();

    ui->labelMessage->setText(tr("Applying ") + preset + tr(" to ") +
                              p->get_name() + "...");
    QApplication::processEvents();
    for (int i = 0; i < settings_list.count(); i++)
    {
      QByteArray setting = settings_list.at(i);
      applyPresetSettings(setting, *p);
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
  if (path != nullptr)
  {
    QString preset = ui->comboBoxPreset->currentText();
    QFile selected_preset(presetsPath + preset);
    if (selected_preset.open(QIODevice::ReadOnly))
      selected_preset.copy(path + "/" + preset);
  }
}

void PresetsManager::on_pushButtonImportPreset_clicked()
{
  QString path = QFileDialog::getOpenFileName();
  if (path != nullptr)
  {
    QFile preset(path);
    QFileInfo info(preset);
    QString name = info.baseName();
    QFile existing_preset(presetsPath + name);
    if (!existing_preset.exists())
    {
      if (preset.open(QIODevice::ReadOnly))
      {
        QByteArray firstLine = preset.readLine();
        if (firstLine == "[Laigter Preset]\n")
          preset.copy(presetsPath + name);
        else
        {
          QMessageBox msg;
          msg.setText(tr("Incorrect format."));
          msg.exec();
        }
      }
    }
    else
    {
      QMessageBox msg;
      msg.setText(tr("There is already a preset with that name."));
      msg.exec();
    }
  }
  update_presets();
}

Ui::preset_codes_array &PresetsManager::get_preset_codes()
{
  return presetCodes;
}

void PresetsManager::applyPresetSettings(QByteArray &setting, ImageProcessor &p)
{
  Ui::preset_codes_array &presetCodes = PresetsManager::get_preset_codes();
  QList<QByteArray> aux = setting.split('\t');
  if (aux[0] == presetCodes[0])
    p.set_normal_depth(aux[1].toInt());
  else if (aux[0] == presetCodes[1])
    p.set_normal_blur_radius(aux[1].toInt());
  else if (aux[0] == presetCodes[2])
    p.set_normal_bisel_depth(aux[1].toInt());
  else if (aux[0] == presetCodes[3])
    p.set_normal_bisel_distance(aux[1].toInt());
  else if (aux[0] == presetCodes[4])
    p.set_normal_bisel_blur_radius(aux[1].toInt());
  else if (aux[0] == presetCodes[5])
    p.set_normal_bisel_soft((bool)aux[1].toInt());
  else if (aux[0] == presetCodes[6])
    p.set_tileable((bool)aux[1].toInt());
  else if (aux[0] == presetCodes[7])
    p.set_normal_invert_x((bool)aux[1].toInt());
  else if (aux[0] == presetCodes[8])
    p.set_normal_invert_y((bool)aux[1].toInt());
  else if (aux[0] == presetCodes[9])
    p.set_parallax_type((ParallaxType)aux[1].toInt());
  else if (aux[0] == presetCodes[10])
    p.set_parallax_thresh(aux[1].toInt());
  else if (aux[0] == presetCodes[11])
    p.set_parallax_focus(aux[1].toInt());
  else if (aux[0] == presetCodes[12])
    p.set_parallax_soft(aux[1].toInt());
  else if (aux[0] == presetCodes[13])
    p.set_parallax_min(aux[1].toInt());
  else if (aux[0] == presetCodes[14])
    p.set_parallax_erode_dilate(aux[1].toInt());
  else if (aux[0] == presetCodes[15])
    p.set_parallax_brightness(aux[1].toInt());
  else if (aux[0] == presetCodes[16])
    p.set_parallax_contrast(aux[1].toInt());
  else if (aux[0] == presetCodes[17])
    p.set_parallax_invert((bool)aux[1].toInt());
  else if (aux[0] == presetCodes[18])
    p.set_specular_blur(aux[1].toInt());
  else if (aux[0] == presetCodes[19])
    p.set_specular_bright(aux[1].toInt());
  else if (aux[0] == presetCodes[20])
    p.set_specular_contrast(aux[1].toInt());
  else if (aux[0] == presetCodes[21])
    p.set_specular_thresh(aux[1].toInt());
  else if (aux[0] == presetCodes[22])
    p.set_specular_invert((bool)aux[1].toInt());
  else if (aux[0] == presetCodes[23])
    p.set_occlusion_blur(aux[1].toInt());
  else if (aux[0] == presetCodes[24])
    p.set_occlusion_bright(aux[1].toInt());
  else if (aux[0] == presetCodes[25])
    p.set_occlusion_invert((bool)aux[1].toInt());
  else if (aux[0] == presetCodes[26])
    p.set_occlusion_thresh(aux[1].toInt());
  else if (aux[0] == presetCodes[27])
    p.set_occlusion_contrast(aux[1].toInt());
  else if (aux[0] == presetCodes[28])
    p.set_occlusion_distance(aux[1].toInt());
  else if (aux[0] == presetCodes[29])
    p.set_occlusion_distance_mode((bool)aux[1].toInt());
  else if (aux[0] == "LightSource")
  {
    QList<LightSource *> *pLightList = p.get_light_list_ptr();
    LightSource *light = new LightSource;
    pLightList->append(light);
  }
  else if (aux[0] == "DiffuseColor ")
  {
    QList<LightSource *> *pLightList = p.get_light_list_ptr();
    pLightList->last()->set_diffuse_color(
        QColor(aux[1].toInt(), aux[2].toInt(), aux[3].toInt()));
  }
  else if (aux[0] == "DiffuseIntensity ")
  {
    QList<LightSource *> *pLightList = p.get_light_list_ptr();
    pLightList->last()->set_diffuse_intensity(aux[1].toFloat());
  }
  else if (aux[0] == "SpecularColor ")
  {
    QList<LightSource *> *pLightList = p.get_light_list_ptr();
    pLightList->last()->set_specular_color(
        QColor(aux[1].toInt(), aux[2].toInt(), aux[3].toInt()));
  }
  else if (aux[0] == "SpecularScatter ")
  {
    QList<LightSource *> *pLightList = p.get_light_list_ptr();
    pLightList->last()->set_specular_scatter(aux[1].toInt());
  }
  else if (aux[0] == "SpecularIntensity ")
  {
    QList<LightSource *> *pLightList = p.get_light_list_ptr();
    pLightList->last()->set_specular_intensity(aux[1].toFloat());
  }
  else if (aux[0] == "Position ")
  {
    QList<LightSource *> *pLightList = p.get_light_list_ptr();
    pLightList->last()->set_light_position(
        QVector3D(aux[1].toFloat(), aux[2].toFloat(), aux[3].toFloat()));
  }
}

void PresetsManager::applyPresets(QString &preset, ImageProcessor &p)
{
  QFile selected_preset(preset);
  if (!selected_preset.open(QIODevice::ReadOnly))
    return;

  QByteArray settings = selected_preset.readAll();
  if (settings.contains("LightSource"))
    p.get_light_list_ptr()->clear();

  QList<QByteArray> settings_list = settings.split('\n');
  for (int i = 0; i < settings_list.count(); i++)
  {
    QByteArray setting = settings_list.at(i);
    applyPresetSettings(setting, p);
  }
}

void PresetsManager::SaveAllPresets(ImageProcessor *p, QString path)
{
  QString currentValues[30];

  QList<LightSource *> pLightList;
  pLightList.clear();


  ProcessorSettings settings = p->get_settings();
  foreach (LightSource *light, *(settings.lightList))
  {
    LightSource *l = new LightSource();
    l->copy_settings(light);
    pLightList.append(l);
  }

  currentValues[0] = QString::number(*settings.normal_depth);
  currentValues[1] = QString::number(*settings.normal_blur_radius);
  currentValues[2] = QString::number(*settings.normal_bisel_depth);
  currentValues[3] = QString::number(*settings.normal_bisel_distance);
  currentValues[4] = QString::number(*settings.normal_bisel_blur_radius);
  currentValues[5] = *settings.normal_bisel_soft ? "1" : "0";
  currentValues[6] = *settings.tileable ? "1" : "0";
  currentValues[7] = *settings.normalInvertX == -1 ? "1" : "0";
  currentValues[8] = *settings.normalInvertY == -1 ? "1" : "0";
  currentValues[9] = QString::number((int)*settings.parallax_type);
  currentValues[10] = QString::number(*settings.parallax_max);
  currentValues[11] = QString::number(*settings.parallax_focus);
  currentValues[12] = QString::number(*settings.parallax_soft);
  currentValues[13] = QString::number(*settings.parallax_min);
  currentValues[14] = QString::number(*settings.parallax_erode_dilate);
  currentValues[15] = QString::number(*settings.parallax_brightness);
  currentValues[16] = QString::number(*settings.parallax_contrast * 1000);
  currentValues[17] = QString::number(*settings.parallax_invert);
  currentValues[18] = QString::number(*settings.specular_blur);
  currentValues[19] = QString::number(*settings.specular_bright);
  currentValues[20] = QString::number(*settings.specular_contrast * 1000);
  currentValues[21] = QString::number(*settings.specular_thresh);
  currentValues[22] = *settings.specular_invert ? "1" : "0";
  currentValues[23] = QString::number(*settings.occlusion_blur);
  currentValues[24] = QString::number(*settings.occlusion_bright);
  currentValues[25] = *settings.occlusion_invert ? "1" : "0";
  currentValues[26] = QString::number(*settings.occlusion_thresh);
  currentValues[27] = QString::number(*settings.occlusion_contrast * 1000);
  currentValues[28] = QString::number(*settings.occlusion_distance);
  currentValues[29] = *settings.occlusion_distance_mode ? "1" : "0";

  QFile preset(path);

  if (preset.open(QIODevice::WriteOnly))
  {
    QTextStream in(&preset);
    in << "[Laigter Preset]";
    for (int i = 0; i < 30; i++)
    {
      in << "\n" << presetCodes[i] << "\t" << currentValues[i];
    }

    foreach (LightSource *light, pLightList)
    {
      QColor diffuseColor = light->get_diffuse_color();
      QColor specularColor = light->get_specular_color();
      QVector3D position = light->get_light_position();
      in << "\nLightSource\n";
      in << "DiffuseColor \t" << diffuseColor.red() << "\t"
         << diffuseColor.green() << "\t" << diffuseColor.blue()
         << "\n";
      in << "DiffuseIntensity \t" << light->get_diffuse_intensity()
         << "\n";
      in << "SpecularColor \t" << specularColor.red() << "\t"
         << specularColor.green() << "\t" << specularColor.blue()
         << "\n";
      in << "SpecularScatter \t" << light->get_specular_scatter()
         << "\n";
      in << "SpecularIntensity \t" << light->get_specular_intesity()
         << "\n";
      in << "Position \t" << position.x() << "\t" << position.y()
         << "\t" << position.z() << "\t";
    }

    preset.close();
  }

}
