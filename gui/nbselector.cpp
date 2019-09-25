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

#include "nbselector.h"
#include "ui_nbselector.h"
#include <QFileDialog>
#include <QMessageBox>

NBSelector::NBSelector(ImageProcessor *processor, QWidget *parent)
    : QDialog(parent), ui(new Ui::NBSelector), processor(processor) {
  ui->setupUi(this);
  get_neighbours();
}

NBSelector::~NBSelector() { delete ui; }

void NBSelector::get_neighbours() {
  QImage image = processor->get_neighbour(0, 0);
  ui->NUL->setIcon(QIcon(QPixmap::fromImage(image)));
  image = processor->get_neighbour(0, 1);
  ui->NUM->setIcon(QIcon(QPixmap::fromImage(image)));
  image = processor->get_neighbour(0, 2);
  ui->NUR->setIcon(QIcon(QPixmap::fromImage(image)));
  image = processor->get_neighbour(1, 0);
  ui->NML->setIcon(QIcon(QPixmap::fromImage(image)));
  image = processor->get_neighbour(1, 1);
  ui->NMM->setIcon(QIcon(QPixmap::fromImage(image)));
  image = processor->get_neighbour(1, 2);
  ui->NMR->setIcon(QIcon(QPixmap::fromImage(image)));
  image = processor->get_neighbour(2, 0);
  ui->NBL->setIcon(QIcon(QPixmap::fromImage(image)));
  image = processor->get_neighbour(2, 1);
  ui->NBM->setIcon(QIcon(QPixmap::fromImage(image)));
  image = processor->get_neighbour(2, 2);
  ui->NBR->setIcon(QIcon(QPixmap::fromImage(image)));
}

void NBSelector::on_pushButtonResetNeighbours_clicked() {
  processor->reset_neighbours();
  get_neighbours();
}

void NBSelector::on_NUL_clicked() {
  QString fileName = QFileDialog::getOpenFileName(
      this, tr("Open Image"), "", tr("Image Files (*.png *.jpg *.bmp *.tga)"));
  if (fileName != nullptr) {
    bool success;
    QImage image = il->loadImage(fileName, &success);
    image = image.convertToFormat(QImage::Format_RGBA8888);
    processor->set_neighbour_image(fileName, image, 0, 0);
    get_neighbours();
    processor->calculate();
  }
}

void NBSelector::on_NUM_clicked() {
  QString fileName = QFileDialog::getOpenFileName(
      this, tr("Open Image"), "", tr("Image Files (*.png *.jpg *.bmp *.tga)"));
  if (fileName != nullptr) {
    bool success;
    QImage image = il->loadImage(fileName, &success);
    image = image.convertToFormat(QImage::Format_RGBA8888);
    processor->set_neighbour_image(fileName, image, 0, 1);
    get_neighbours();
    processor->calculate();
  }
}

void NBSelector::on_NUR_clicked() {
  QString fileName = QFileDialog::getOpenFileName(
      this, tr("Open Image"), "", tr("Image Files (*.png *.jpg *.bmp *.tga)"));
  if (fileName != nullptr) {
    bool success;
    QImage image = il->loadImage(fileName, &success);
    image = image.convertToFormat(QImage::Format_RGBA8888);
    processor->set_neighbour_image(fileName, image, 0, 2);
    get_neighbours();
    processor->calculate();
  }
}

void NBSelector::on_NML_clicked() {
  QString fileName = QFileDialog::getOpenFileName(
      this, tr("Open Image"), "", tr("Image Files (*.png *.jpg *.bmp *.tga)"));
  if (fileName != nullptr) {
    bool success;
    QImage image = il->loadImage(fileName, &success);
    image = image.convertToFormat(QImage::Format_RGBA8888);
    processor->set_neighbour_image(fileName, image, 1, 0);
    get_neighbours();
    processor->calculate();
  }
}

void NBSelector::on_NMM_clicked() {
  QString fileName = QFileDialog::getOpenFileName(
      this, tr("Open Image"), "", tr("Image Files (*.png *.jpg *.bmp *.tga)"));
  if (fileName != nullptr) {
    bool success;
    QImage image = il->loadImage(fileName, &success);
    image = image.convertToFormat(QImage::Format_RGBA8888);
    processor->set_neighbour_image(fileName, image, 1, 1);
    get_neighbours();
    processor->calculate();
  }
}

void NBSelector::on_NMR_clicked() {
  QString fileName = QFileDialog::getOpenFileName(
      this, tr("Open Image"), "", tr("Image Files (*.png *.jpg *.bmp *.tga)"));
  if (fileName != nullptr) {
    bool success;
    QImage image = il->loadImage(fileName, &success);
    image = image.convertToFormat(QImage::Format_RGBA8888);
    processor->set_neighbour_image(fileName, image, 1, 2);
    get_neighbours();
    processor->calculate();
  }
}

void NBSelector::on_NBL_clicked() {
  QString fileName = QFileDialog::getOpenFileName(
      this, tr("Open Image"), "", tr("Image Files (*.png *.jpg *.bmp *.tga)"));
  if (fileName != nullptr) {
    bool success;
    QImage image = il->loadImage(fileName, &success);
    image = image.convertToFormat(QImage::Format_RGBA8888);
    processor->set_neighbour_image(fileName, image, 2, 0);
    get_neighbours();
    processor->calculate();
  }
}

void NBSelector::on_NBM_clicked() {
  QString fileName = QFileDialog::getOpenFileName(
      this, tr("Open Image"), "", tr("Image Files (*.png *.jpg *.bmp *.tga)"));
  if (fileName != nullptr) {
    bool success;
    QImage image = il->loadImage(fileName, &success);
    image = image.convertToFormat(QImage::Format_RGBA8888);
    processor->set_neighbour_image(fileName, image, 2, 1);
    get_neighbours();
    processor->calculate();
  }
}

void NBSelector::on_NBR_clicked() {
  QString fileName = QFileDialog::getOpenFileName(
      this, tr("Open Image"), "", tr("Image Files (*.png *.jpg *.bmp *.tga)"));
  if (fileName != nullptr) {
    bool success;
    QImage image = il->loadImage(fileName, &success);
    image = image.convertToFormat(QImage::Format_RGBA8888);
    processor->set_neighbour_image(fileName, image, 2, 2);
    get_neighbours();
    processor->calculate();
  }
}

void NBSelector::on_pushButton_clicked() {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      processor->empty_neighbour(i, j);
    }
  }
  processor->calculate();
  get_neighbours();
}
