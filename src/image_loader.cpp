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

#include "image_loader.h"

#include <QFileInfo>
#include <QImageReader>
#include <fstream>

ImageLoader::ImageLoader(QObject *parent) : QObject(parent) {}

QList<QImage> ImageLoader::loadImages(QString fileName)
{
  QList<QImage> image_list;
  QImageReader reader(fileName);
  for (int i = 0; i < reader.imageCount(); i++)
  {
    reader.jumpToImage(i);
    image_list.append(reader.read());
  }
  return image_list;
}

QImage ImageLoader::loadImage(QString fileName, bool *success)
{
  QFileInfo info(fileName);
  QImage image;
  QString suffix = info.completeSuffix();
  *success = true;

  if (suffix == "tga")
  {
    bool loaded;
    QByteArray ba = fileName.toLocal8Bit();
    const char *c_str2 = ba.data();
    image = loadTga(c_str2, &loaded);
    *success = loaded;
  }
  else
  {
    QImageReader reader(fileName);
    image = QImage(fileName);
  }
  if (image.isNull())
    *success = false;

  return image;
}

QImage ImageLoader::loadTga(const char *filePath, bool *success)
{
  QImage img;
  if (!img.load(filePath))
  {
    // open the file
    std::fstream fsPicture(filePath, std::ios::in | std::ios::binary);

    if (!fsPicture.is_open())
    {
      img = QImage(1, 1, QImage::Format_RGB32);
      img.fill(Qt::red);
      *success = false;
      return img;
    }

    // some variables
    std::vector<std::uint8_t> *vui8Pixels;
    std::uint32_t ui32BpP;
    std::uint32_t ui32Width;
    std::uint32_t ui32Height;

    // read in the header
    std::uint8_t ui8x18Header[19] = {0};
    fsPicture.read(reinterpret_cast<char *>(&ui8x18Header),
                   sizeof(ui8x18Header) - 1);

    // get variables
    vui8Pixels = new std::vector<std::uint8_t>;
    bool bCompressed;
    std::uint32_t ui32IDLength;
    std::uint32_t ui32PicType;
    std::uint32_t ui32PaletteLength;
    std::uint32_t ui32Size;

    // extract all information from header
    ui32IDLength = ui8x18Header[0];
    ui32PicType = ui8x18Header[2];
    ui32PaletteLength = ui8x18Header[6] * 0x100 + ui8x18Header[5];
    ui32Width = ui8x18Header[13] * 0x100 + ui8x18Header[12];
    ui32Height = ui8x18Header[15] * 0x100 + ui8x18Header[14];
    ui32BpP = ui8x18Header[16];

    // calculate some more information
    ui32Size = ui32Width * ui32Height * ui32BpP / 8;
    bCompressed = ui32PicType == 9 || ui32PicType == 10;
    vui8Pixels->resize(ui32Size);

    // jump to the data block
    fsPicture.seekg(ui32IDLength + ui32PaletteLength, std::ios_base::cur);

    if (ui32PicType == 2 && (ui32BpP == 24 || ui32BpP == 32))
      fsPicture.read(reinterpret_cast<char *>(vui8Pixels->data()),
                     ui32Size);
    // else if compressed 24 or 32 bit
    else if (ui32PicType == 10 &&
             (ui32BpP == 24 || ui32BpP == 32)) // compressed
    {
      std::uint8_t tempChunkHeader;
      std::uint8_t tempData[5];
      unsigned int tempByteIndex = 0;

      do
      {
        fsPicture.read(reinterpret_cast<char *>(&tempChunkHeader),
                       sizeof(tempChunkHeader));

        if (tempChunkHeader >> 7) // repeat count
        {
          // just use the first 7 bits
          tempChunkHeader = (uint8_t(tempChunkHeader << 1) >> 1);
          fsPicture.read(reinterpret_cast<char *>(&tempData),
                         ui32BpP / 8);

          for (int i = 0; i <= tempChunkHeader; i++)
          {
            vui8Pixels->at(tempByteIndex++) = tempData[0];
            vui8Pixels->at(tempByteIndex++) = tempData[1];
            vui8Pixels->at(tempByteIndex++) = tempData[2];
            if (ui32BpP == 32)
              vui8Pixels->at(tempByteIndex++) = tempData[3];
          }
        }
        else // data count
        {
          // just use the first 7 bits
          tempChunkHeader = (uint8_t(tempChunkHeader << 1) >> 1);

          for (int i = 0; i <= tempChunkHeader; i++)
          {
            fsPicture.read(reinterpret_cast<char *>(&tempData),
                           ui32BpP / 8);
            vui8Pixels->at(tempByteIndex++) = tempData[0];
            vui8Pixels->at(tempByteIndex++) = tempData[1];
            vui8Pixels->at(tempByteIndex++) = tempData[2];
            if (ui32BpP == 32)
              vui8Pixels->at(tempByteIndex++) = tempData[3];
          }
        }
      } while (tempByteIndex < ui32Size);
    }
    else
    {
      fsPicture.close();
      img = QImage(1, 1, QImage::Format_RGB32);
      img.fill(Qt::red);
      *success = false;
      return img;
    }

    fsPicture.close();
    img = QImage(ui32Width, ui32Height, QImage::Format_RGBA8888);
    int pixelSize = ui32BpP == 32 ? 4 : 3;
    // TODO: write direct into img

    for (unsigned int x = 0; x < ui32Width; x++)
    {
      for (unsigned int y = 0; y < ui32Height; y++)
      {
        int vala = pixelSize == 4
                       ? vui8Pixels->at(y * ui32Width * pixelSize +
                                        x * pixelSize + 3)
                       : 255;
        int valr = vui8Pixels->at(y * ui32Width * pixelSize +
                                  x * pixelSize + 2);
        int valg = vui8Pixels->at(y * ui32Width * pixelSize +
                                  x * pixelSize + 1);
        int valb =
            vui8Pixels->at(y * ui32Width * pixelSize + x * pixelSize);
        QColor value(valr, valg, valb, vala);
        img.setPixelColor(x, y, value);
      }
    }
    img = img.mirrored();
  }

  *success = true;
  return img;
}

QSize ImageLoader::maxImagesSize(QList<QImage> image_list)
{
  QSize s(0, 0);
  foreach (QImage image, image_list)
  {
    if (s.width() < image.size().width())
    {
      s.setWidth(image.size().width());
    }
    if (s.height() < image.size().height())
    {
      s.setHeight(image.size().height());
    }
  }
  return s;
}
