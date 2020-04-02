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

#ifndef NBSELECTOR_H
#define NBSELECTOR_H

#include "src/image_loader.h"
#include "src/image_processor.h"

#include <QDialog>

namespace Ui {
class NBSelector;
}

class NBSelector : public QDialog {
  Q_OBJECT

private:
  Ui::NBSelector *ui;
  ImageProcessor *processor;
  ImageLoader *il;

public:
  explicit NBSelector(ImageProcessor *processor, QWidget *parent = nullptr);
  ~NBSelector();

private slots:
  void on_pushButtonResetNeighbours_clicked();
  void get_neighbours();
  void on_NUL_clicked();
  void on_NUM_clicked();
  void on_NUR_clicked();
  void on_NML_clicked();
  void on_NMM_clicked();
  void on_NMR_clicked();
  void on_NBL_clicked();
  void on_NBM_clicked();
  void on_NBR_clicked();
  void on_pushButton_clicked();
};

#endif // NBSELECTOR_H
