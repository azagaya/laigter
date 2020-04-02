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

#ifndef IMAGELOADER_H
#define IMAGELOADER_H

#include <QImage>
#include <QObject>

class ImageLoader : public QObject {
  Q_OBJECT

public:
  explicit ImageLoader(QObject *parent = nullptr);
  QImage loadTga(const char *filePath, bool *success);
  QImage loadImage(QString fileName, bool *success);
};

#endif // IMAGELOADER_H
