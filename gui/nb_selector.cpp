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
#include <QListWidgetItem>
#include <QMessageBox>
#include <QtConcurrent/QtConcurrent>

NBSelector::NBSelector(QDialog *parent)
    : QDialog(parent), ui(new Ui::NBSelector)
{
  ui->setupUi(this);
  frameList = ui->framesTab->findChild<QListWidget *>("listWidget");
  imagesList = ui->imagesTab->findChild<QListWidget *>("listWidgetImages");
  ui->listWidget->setIconSize(QSize(100, 100));
  ui->listWidgetImages->setIconSize(QSize(100,100));
}

NBSelector::~NBSelector() { delete ui; }

void NBSelector::setProcessor(ImageProcessor *processor)
{
  this->disconnect();
  this->processor = processor;
  connect(processor, SIGNAL(processed()), this, SLOT(get_neighbours()));

  qDebug() << 0;
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

  qDebug() << 2;
  QListWidgetItem *item = new QListWidgetItem;
  item->setData(Qt::UserRole, -1);
  QPixmap icon = QPixmap::fromImage(processor->getFrameImage(-1));
  item->setIcon(icon);
  frameList->addItem(item);
  get_neighbours();
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

    image = processor->getFrameImage(frameList->currentItem()->data(Qt::UserRole).toInt());
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

void NBSelector::on_pushButton_clicked()
{
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
      processor->empty_neighbour(i, j);
  }
  processor->calculate();
  get_neighbours();
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

