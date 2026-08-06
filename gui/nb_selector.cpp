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

#include "nb_selector.h"
#include "ui_nb_selector.h"

#include <QFileDialog>
#include <QJsonArray>
#include <QJsonDocument>
#include <QListWidgetItem>
#include <QMessageBox>
#include <QStandardPaths>
#include <QTimer>
#include <QtConcurrent/QtConcurrent>

NBSelector::NBSelector(QDialog *parent)
    : QDialog(parent), ui(new Ui::NBSelector)
{
  ui->setupUi(this);
  frameList = ui->framesTab->findChild<QListWidget *>("listWidget");
  imagesList = ui->imagesTab->findChild<QListWidget *>("listWidgetImages");
  ui->listWidget->setIconSize(QSize(100, 100));
  ui->listWidgetImages->setIconSize(QSize(100,100));

#ifndef PORTABLE
  presetsPath =
      QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) +
      "/tile_presets/";
#else
  presetsPath = "./tile_presets/";
#endif
  presetsDir = QDir(presetsPath);
  /* Editable to name new presets, but only add them when saved */
  ui->presetComboBox->setInsertPolicy(QComboBox::NoInsert);
  update_presets();
}

NBSelector::~NBSelector() { delete ui; }

void NBSelector::setProcessor(ImageProcessor *processor)
{
  /* Only the previous processor, disconnecting everything also kills the
   * connections other windows made to us */
  if (this->processor)
    disconnect(this->processor, SIGNAL(processed()), this, SLOT(get_neighbours()));

  this->processor = processor;
  connect(processor, SIGNAL(processed()), this, SLOT(get_neighbours()));

  /* We dont know which preset this sprite is using, if any */
  ui->presetComboBox->setCurrentIndex(0);

  update_frame_list();
  get_neighbours();
}

void NBSelector::update_frame_list()
{
  while (frameList->count() > 0)
  {
    QListWidgetItem *item = frameList->takeItem(0);
    delete item;
  }
  QSize s(processor->texture.width() / processor->getHFrames(), processor->texture.height() / processor->getVFrames());
  QImage empty(s, processor->texture.format());
  empty.fill(Qt::transparent);

  foreach (int frame, processor->current_animation->frames_id)
  {
    QImage image = processor->getFrameImage(frame);
    if (image == empty)
      continue;
    QListWidgetItem *item = new QListWidgetItem;
    item->setData(Qt::UserRole, frame);
    QPixmap icon = QPixmap::fromImage(image);
    item->setIcon(icon);
    frameList->addItem(item);
  }

  QListWidgetItem *item = new QListWidgetItem;
  item->setData(Qt::UserRole, -1);
  QPixmap icon = QPixmap::fromImage(processor->getFrameImage(-1));
  item->setIcon(icon);
  frameList->addItem(item);
}

void NBSelector::get_neighbours()
{

  QSize s = ui->NUL->size();

  ui->NUL->setIconSize(s);
  ui->NUM->setIconSize(s);
  ui->NUR->setIconSize(s);
  ui->NML->setIconSize(s);
  ui->NMM->setIconSize(s);
  ui->NMR->setIconSize(s);
  ui->NBL->setIconSize(s);
  ui->NBM->setIconSize(s);
  ui->NBR->setIconSize(s);

  QImage image = processor->get_neighbour(0, 0);
  ui->NUL->setIcon(QIcon(QPixmap::fromImage(image).scaled(s.width(), s.height(), Qt::KeepAspectRatio)));
  image = processor->get_neighbour(1, 0);
  ui->NUM->setIcon(QIcon(QPixmap::fromImage(image).scaled(s.width(), s.height(), Qt::KeepAspectRatio)));
  image = processor->get_neighbour(2, 0);
  ui->NUR->setIcon(QIcon(QPixmap::fromImage(image).scaled(s.width(), s.height(), Qt::KeepAspectRatio)));
  image = processor->get_neighbour(0, 1);
  ui->NML->setIcon(QIcon(QPixmap::fromImage(image).scaled(s.width(), s.height(), Qt::KeepAspectRatio)));
  image = processor->get_neighbour(1, 1);
  ui->NMM->setIcon(QIcon(QPixmap::fromImage(image).scaled(s.width(), s.height(), Qt::KeepAspectRatio)));
  image = processor->get_neighbour(2, 1);
  ui->NMR->setIcon(QIcon(QPixmap::fromImage(image).scaled(s.width(), s.height(), Qt::KeepAspectRatio)));
  image = processor->get_neighbour(0, 2);
  ui->NBL->setIcon(QIcon(QPixmap::fromImage(image).scaled(s.width(), s.height(), Qt::KeepAspectRatio)));
  image = processor->get_neighbour(1, 2);
  ui->NBM->setIcon(QIcon(QPixmap::fromImage(image).scaled(s.width(), s.height(), Qt::KeepAspectRatio)));
  image = processor->get_neighbour(2, 2);
  ui->NBR->setIcon(QIcon(QPixmap::fromImage(image).scaled(s.width(), s.height(), Qt::KeepAspectRatio)));
}

void NBSelector::on_pushButtonResetNeighbours_clicked()
{
  processor->reset_neighbours();
  get_neighbours();
}

void NBSelector::setNeighbor(int x, int y)
{
  QImage image;
  if (ui->tabWidget->currentIndex() == 0)
  {
    if (frameList->selectedItems().size() <= 0)
      return;

    int frame = frameList->currentItem()->data(Qt::UserRole).toInt();
    image = processor->getFrameImage(frame);
    /* Remember the id, the texture only keeps the pixels */
    processor->set_tile_neighbour_id(processor->get_current_frame_id(), x, y,
                                     frame);
  }
  else if (ui->tabWidget->currentIndex() == 1)
  {
    if (imagesList->selectedItems().size() <= 0)
      return;
    QString filename = imagesList->currentItem()->data(Qt::UserRole).toString();
    bool success;
    image = il->loadImage(filename, &success);
    image = image.convertToFormat(QImage::Format_RGBA8888);
  }

  processor->set_neighbour_image(image, x, y);
  get_neighbours();
  processor->set_tileable(true);
}

void NBSelector::on_NUL_clicked()
{
  setNeighbor(0, 0);
}

void NBSelector::on_NUM_clicked()
{
  setNeighbor(1, 0);
}

void NBSelector::on_NUR_clicked()
{
  setNeighbor(2, 0);
}

void NBSelector::on_NML_clicked()
{
  setNeighbor(0, 1);
}

void NBSelector::on_NMM_clicked()
{
  setNeighbor(1, 1);
}

void NBSelector::on_NMR_clicked()
{
  setNeighbor(2, 1);
}

void NBSelector::on_NBL_clicked()
{
  setNeighbor(0, 2);
}

void NBSelector::on_NBM_clicked()
{
  setNeighbor(1, 2);
}

void NBSelector::on_NBR_clicked()
{
  setNeighbor(2, 2);
}

void NBSelector::on_pushButtonResetNeighbours_pressed()
{
  processor->reset_neighbours();
  get_neighbours();
  processor->set_tileable(true);
}

void NBSelector::on_addImagePushButton_pressed()
{
  QString fileName = QFileDialog::getOpenFileName(
      this, tr("Open Image"), "",
      tr("Image Files (*.png *.jpg *.bmp *.tga)"));
  if (fileName != nullptr)
  {
    bool success;
    QImage image = il->loadImage(fileName, &success);
    image = image.convertToFormat(QImage::Format_RGBA8888);
    QListWidgetItem *item = new QListWidgetItem;
    item->setIcon(QPixmap::fromImage(image));
    item->setData(Qt::UserRole, fileName);
    imagesList->addItem(item);
  }
}

void NBSelector::update_presets()
{
  ui->presetComboBox->clear();
  /* Empty entry, for sprites with no preset applied */
  ui->presetComboBox->addItem("");
  if (presetsDir.exists())
    ui->presetComboBox->addItems(presetsDir.entryList(QDir::Files));
}

void NBSelector::on_savePresetButton_clicked()
{
  QString presetName = ui->presetComboBox->currentText().trimmed();
  QMessageBox msg(this);

  if (presetName == "")
  {
    msg.setText(tr("You must input a name for the preset!"));
    msg.exec();
    return;
  }

  QHash<int, QVector<int>> neighbours = processor->get_tile_neighbours();
  if (neighbours.isEmpty())
  {
    msg.setText(tr("There are no neighbour tiles to save!"));
    msg.exec();
    return;
  }

  if (!presetsDir.exists())
    presetsDir.mkpath(presetsPath);

  QFile preset(presetsPath + presetName);
  if (preset.exists())
  {
    if (QMessageBox::question(this, tr("Overwrite preset"),
                              tr("There is already a preset with that name. "
                                 "Do you want to overwrite it?")) !=
        QMessageBox::Yes)
      return;
  }

  QJsonObject tiles;
  QHash<int, QVector<int>>::const_iterator it;
  for (it = neighbours.constBegin(); it != neighbours.constEnd(); it++)
  {
    QJsonArray slot_ids;
    foreach (int frame, it.value())
      slot_ids.append(frame);

    tiles[QString::number(it.key())] = slot_ids;
  }

  QJsonObject json;
  json["h_frames"] = processor->getHFrames();
  json["v_frames"] = processor->getVFrames();
  json["tile_width"] = processor->texture.width() / processor->getHFrames();
  json["tile_height"] = processor->texture.height() / processor->getVFrames();
  json["neighbours"] = tiles;

  if (!preset.open(QIODevice::WriteOnly))
  {
    msg.setText(tr("Could not write the preset!"));
    msg.exec();
    return;
  }

  preset.write(QJsonDocument(json).toJson());
  preset.close();

  update_presets();
  ui->presetComboBox->setCurrentText(presetName);
}

void NBSelector::on_deletePresetButton_clicked()
{
  QString presetName = ui->presetComboBox->currentText().trimmed();
  QFile preset(presetsPath + presetName);
  QMessageBox msg(this);

  if (presetName == "" || !preset.exists())
  {
    msg.setText(tr("There is no preset with that name!"));
    msg.exec();
    return;
  }

  if (QMessageBox::question(this, tr("Delete preset"),
                            tr("Do you want to delete the preset %1?")
                                .arg(presetName)) != QMessageBox::Yes)
    return;

  preset.remove();
  update_presets();
}

void NBSelector::on_presetComboBox_activated(int index)
{
  /* The empty entry means no preset, so there is nothing to apply */
  if (index == 0)
    return;

  /* Wait for the popup to close, it still has the grab and eats our dialogs */
  QString presetName = ui->presetComboBox->itemText(index);
  QTimer::singleShot(0, this, [this, presetName]() { load_preset(presetName); });
}

void NBSelector::load_preset(QString presetName)
{
  QFile preset(presetsPath + presetName);
  QMessageBox msg(this);

  if (!preset.open(QIODevice::ReadOnly))
  {
    msg.setText(tr("Could not read the preset!"));
    msg.exec();
    return;
  }

  QJsonDocument document = QJsonDocument::fromJson(preset.readAll());
  preset.close();

  if (!document.isObject())
  {
    msg.setText(tr("The preset is not valid!"));
    msg.exec();
    return;
  }

  apply_preset(document.object());
}

void NBSelector::apply_preset(QJsonObject preset)
{
  int h_frames = preset.value("h_frames").toInt();
  int v_frames = preset.value("v_frames").toInt();
  QMessageBox msg(this);

  if (h_frames <= 0 || v_frames <= 0)
  {
    msg.setText(tr("The preset is not valid!"));
    msg.exec();
    return;
  }

  /* The preset is for another arrangement, so split this tileset again */
  if (h_frames != processor->getHFrames() || v_frames != processor->getVFrames())
  {
    msg.setText(tr("This tileset will be changed to %1 by %2 tiles.")
                    .arg(h_frames)
                    .arg(v_frames));
    msg.exec();
    framesChanged(h_frames, v_frames, processor);
    update_frame_list();
  }

  QJsonObject tiles = preset.value("neighbours").toObject();
  int current_frame = processor->get_current_frame_id();

  foreach (QString key, tiles.keys())
  {
    int frame = key.toInt();
    QJsonArray slot_ids = tiles.value(key).toArray();

    /* set_neighbour_image works on the current frame */
    processor->set_current_frame_id(frame);

    for (int slot = 0; slot < slot_ids.count(); slot++)
    {
      int neighbour = slot_ids.at(slot).toInt(ImageProcessor::NeighbourUnset);
      if (neighbour == ImageProcessor::NeighbourUnset)
        continue;

      int x = slot % 3;
      int y = slot / 3;
      processor->set_neighbour_image(processor->getFrameImage(neighbour), x, y);
      processor->set_tile_neighbour_id(frame, x, y, neighbour);
    }
  }

  processor->set_current_frame_id(current_frame);
  processor->set_tileable(true);
  processor->calculate();
  get_neighbours();
}

void NBSelector::resizeEvent(QResizeEvent *event){
    Q_UNUSED(event);
    get_neighbours();
}

void NBSelector::on_horizontalSlider_valueChanged(int value)
{
    ui->listWidget->setIconSize(QSize(value, value));

    QSize s(processor->texture.width() / processor->getHFrames(), processor->texture.height() / processor->getVFrames());
    QImage empty(s, processor->texture.format());
    empty.fill(Qt::transparent);
    int i = 0;
    foreach (int frame, processor->current_animation->frames_id)
    {
      QImage image = processor->getFrameImage(frame);
      if (image == empty)
        continue;

      QListWidgetItem *item = ui->listWidget->item(i);
      QPixmap icon = QPixmap::fromImage(image.scaled(QSize(value,value)));
      item->setIcon(icon);
      i++;
    }
}

