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
  frameList = ui->tab->findChild<QListWidget *>("listWidget");
}

NBSelector::~NBSelector() { delete ui; }

void NBSelector::setProcessor(ImageProcessor *processor)
{
  this->disconnect();
  this->processor = processor;
  connect(processor, SIGNAL(processed()), this, SLOT(get_neighbours()));

  for (int i = 0; i < frameList->count(); i++)
  {
    QListWidgetItem *item = frameList->takeItem(i);
    delete item;
  }

  foreach (int frame, processor->current_animation->frames_id)
  {
    QListWidgetItem *item = new QListWidgetItem;
    item->setData(Qt::UserRole, frame);
    QPixmap icon = QPixmap::fromImage(processor->getFrameImage(frame));
    item->setIcon(icon);
    frameList->addItem(item);
  }

  get_neighbours();
}

void NBSelector::get_neighbours()
{
  QImage image = processor->get_neighbour(0, 0);
  ui->NUL->setIcon(QIcon(QPixmap::fromImage(image)));
  image = processor->get_neighbour(1, 0);
  ui->NUM->setIcon(QIcon(QPixmap::fromImage(image)));
  image = processor->get_neighbour(2, 0);
  ui->NUR->setIcon(QIcon(QPixmap::fromImage(image)));
  image = processor->get_neighbour(0, 1);
  ui->NML->setIcon(QIcon(QPixmap::fromImage(image)));
  image = processor->get_neighbour(1, 1);
  ui->NMM->setIcon(QIcon(QPixmap::fromImage(image)));
  image = processor->get_neighbour(2, 1);
  ui->NMR->setIcon(QIcon(QPixmap::fromImage(image)));
  image = processor->get_neighbour(0, 2);
  ui->NBL->setIcon(QIcon(QPixmap::fromImage(image)));
  image = processor->get_neighbour(1, 2);
  ui->NBM->setIcon(QIcon(QPixmap::fromImage(image)));
  image = processor->get_neighbour(2, 2);
  ui->NBR->setIcon(QIcon(QPixmap::fromImage(image)));
}

void NBSelector::on_pushButtonResetNeighbours_clicked()
{
  processor->reset_neighbours();
  get_neighbours();
}

void NBSelector::setNeighbor(int x, int y)
{
  if (frameList->selectedItems().size() <= 0)
    return;

  QImage image = processor->getFrameImage(frameList->currentItem()->data(Qt::UserRole).toInt());

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
