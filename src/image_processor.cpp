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

#include "image_processor.h"

#include <cmath>

#include <QApplication>
#include <QDebug>
#include <QtConcurrent/QtConcurrent>

using namespace cimg_library;

ImageProcessor::ImageProcessor(QObject *parent) : QObject(parent)
{
  position = offset = QVector2D(0, 0);
  zoom = 1.0;
  selected = false;
  normal_bisel_depth = 100;
  normal_bisel_distance = 60;
  normal_depth = 250;
  normal_blur_radius = 6;
  normal_bisel_blur_radius = 10;
  gradient_end = 1;
  normal_bisel_soft = true;
  normalInvertX = normalInvertY = normalInvertZ = 1;
  tileable = false;
  tileX = false;
  tileY = false;
  busy = false;
  parallax_max = 140;
  parallax_min = 0;
  parallax_invert = false;
  parallax_focus = 2;
  parallax_soft = 3;
  parallax_quantization = 1;
  parallax_type = ParallaxType::Binary;
  parallax_brightness = 0;
  parallax_contrast = 1;
  parallax_erode_dilate = 1;
  specular_blur = 3;
  specular_bright = 0;
  specular_contrast = 1;
  specular_thresh = 127;
  specular_invert = false;
  occlusion_blur = 3;
  occlusion_bright = 16;
  occlusion_contrast = 1;
  occlusion_thresh = 1;
  occlusion_invert = false;
  occlusion_distance_mode = true;
  occlusion_distance = 10;
  settings.tileable = &tileable;
  settings.gradient_end = &gradient_end;
  settings.parallax_max = &parallax_max;
  settings.parallax_min = &parallax_min;
  settings.parallax_soft = &parallax_soft;
  settings.parallax_type = &parallax_type;
  settings.parallax_focus = &parallax_focus;
  settings.parallax_invert = &parallax_invert;
  settings.parallax_contrast = &parallax_contrast;
  settings.parallax_brightness = &parallax_brightness;
  settings.parallax_erode_dilate = &parallax_erode_dilate;
  settings.parallax_quantization = &parallax_quantization;
  settings.normal_depth = &normal_depth;
  settings.normalInvertX = &normalInvertX;
  settings.normalInvertY = &normalInvertY;
  settings.normalInvertZ = &normalInvertZ;
  settings.normal_bisel_soft = &normal_bisel_soft;
  settings.normal_bisel_depth = &normal_bisel_depth;
  settings.normal_blur_radius = &normal_blur_radius;
  settings.normal_bisel_distance = &normal_bisel_distance;
  settings.normal_bisel_blur_radius = &normal_bisel_blur_radius;
  settings.specular_blur = &specular_blur;
  settings.specular_bright = &specular_bright;
  settings.specular_invert = &specular_invert;
  settings.specular_thresh = &specular_thresh;
  settings.specular_contrast = &specular_contrast;
  settings.occlusion_blur = &occlusion_blur;
  settings.occlusion_bright = &occlusion_bright;
  settings.occlusion_invert = &occlusion_invert;
  settings.occlusion_thresh = &occlusion_thresh;
  settings.occlusion_contrast = &occlusion_contrast;
  settings.occlusion_distance = &occlusion_distance;
  settings.occlusion_distance_mode = &occlusion_distance_mode;
  settings.lightList = &lightList;
  is_parallax = false;
  connected = false;
  customSpecularMap = false;
  customHeightMap = false;
  active = true;
  normal_counter = parallax_counter = specular_counter = occlussion_counter =  0;

  connect(&animation, SIGNAL(timeout()), this, SLOT(next_frame()));
  connect(&recalculate_timer, SIGNAL(timeout()), this, SLOT(recalculate()));

  animation.setInterval(80);
  animation.setSingleShot(false);
  animation.start();

  recalculate_timer.setInterval(100);
  recalculate_timer.setSingleShot(false);
  recalculate_timer.start();

}

ImageProcessor::~ImageProcessor()
{
  active = false;
  while (normal_counter > 0)
    QThread::msleep(10);
  while (parallax_counter > 0)
    QThread::msleep(10);
  while (specular_counter > 0)
    QThread::msleep(10);
  while (occlussion_counter > 0)
    QThread::msleep(10);
}

int ImageProcessor::loadImage(QString fileName, QImage image)
{
  m_fileName = fileName;
  QFileInfo info(fileName);
  m_absolute_path = info.absolutePath();
  texture = image;
  Sprite s;
  s.set_image(TextureTypes::Diffuse, image);
  s.set_image(TextureTypes::Heightmap, image);
  s.set_image(TextureTypes::SpecularBase, image);
  s.set_image(TextureTypes::OcclussionBase, image);
  QImage n(3 * image.size(), QImage::Format_RGBA8888_Premultiplied);
  n.fill(0);
  s.set_image(TextureTypes::Neighbours, n);
  n = QImage(image.width(), image.height(),
             QImage::Format_RGBA8888_Premultiplied);
  n.fill(0);
  s.set_image(TextureTypes::NormalOverlay, n);
  s.set_image(TextureTypes::HeightmapOverlay, n);
  s.set_image(TextureTypes::SpecularOverlay, n);
  s.set_image(TextureTypes::ParallaxOverlay, n);
  s.set_image(TextureTypes::OcclussionOverlay, n);
  s.fileName = fileName;
  frames.append(s);
  set_current_frame_id(frames.count() - 1);
  get_normal_overlay();

  if (!customHeightMap)
  {
    fill_neighbours(fileName, image);
  }

  return 0;
}

void ImageProcessor::set_current_heightmap(int id)
{
  Sprite *current_frame = &frames[id];
  if (tileable)
    current_frame->get_image(TextureTypes::Neighbours, &heightmap);
  else
    current_frame->get_image(TextureTypes::Heightmap, &heightmap);

  current_heightmap = QImage2CImg(heightmap.convertToFormat(QImage::Format_RGBA8888));
  m_gray = QImage2CImg(heightmap.convertToFormat(QImage::Format_Grayscale8));
}

void ImageProcessor::calculate()
{
  set_current_heightmap(current_frame_id);
  calculate_distance();
  calculate_heightmap();
  generate_normal_map();
  calculate_parallax();
  calculate_specular();
  calculate_occlusion();
}

void ImageProcessor::recalculate(){
  if (normal_counter > 0)
  {
    QtConcurrent::run(this, &ImageProcessor::generate_normal_map, true, true,
                      false, QRect(0, 0, 0, 0));
    normal_counter = 0;
  }
  if (specular_counter > 0)
  {
    QtConcurrent::run(this, &ImageProcessor::calculate_specular);
    specular_counter = 0;
  }
  if (parallax_counter > 0)
  {
    QtConcurrent::run(this, &ImageProcessor::calculate_parallax);
    parallax_counter = 0;
  }
  if (occlussion_counter > 0)
  {
    QtConcurrent::run(this, &ImageProcessor::calculate_occlusion);
    occlussion_counter = 0;
  }
}

void ImageProcessor::calculate_parallax()
{
  if (!parallax_mutex.tryLock())
  {
    parallax_counter = 1;
    return;
  }
  int frame = current_frame_id;

  for (int i = 0; i < frames.count(); i++)
  {
    set_current_frame_id(i);
    QImage ovi = get_parallax_overlay();

    CImg<float> ov(QImage2CImg(ovi));
    CImg<float> alpha = ov.get_channel(3)/255.0;

    current_parallax = modify_parallax();

    if (tileable )
    {

      QSize s = current_frame->size();
      current_parallax.crop(s.width(), s.height(), 2*s.width()-1, 2*s.height()-1);
    }

    current_parallax = (current_parallax.mul(1.0-alpha)+ov.get_channel(0)).cut(0.0,255.0);

    parallax_ready.lock();
    frames[i].set_image(TextureTypes::Parallax, CImg2QImage(current_parallax));

    parallax_ready.unlock();
  }

  set_current_frame_id(frame);
  processed();
  parallax_mutex.unlock();
}

void ImageProcessor::calculate_specular()
{
  if (!specular_mutex.tryLock())
  {
    specular_counter = 1;
    return;
  }
  int frame = current_frame_id;

  for (int i = 0; i < frames.count(); i++)
  {
    set_current_frame_id(i);
    current_specular = modify_specular();
    QImage ovi = get_specular_overlay();

    CImg<float> ov(QImage2CImg(ovi));
    CImg<float> alpha = ov.get_channel(3)/255.0;

    if (tileable)
    {
      QSize s = current_frame->size();
      current_specular.crop(s.width(), s.height(), 2*s.width()-1, 2*s.height()-1);
    }

    current_specular = (current_specular.mul(1.0-alpha)+ov.get_channel(0)).cut(0.0,255.0);

    specular_ready.lock();
    frames[i].set_image(TextureTypes::Specular, CImg2QImage(current_specular));
    specular_ready.unlock();
  }

  set_current_frame_id(frame);
  processed();
  specular_mutex.unlock();
}

void ImageProcessor::calculate_occlusion()
{
  if (!occlusion_mutex.tryLock())
  {
    occlussion_counter = 1;
    return;
  }
  int frame = current_frame_id;

  for (int i = 0; i < frames.count(); i++)
  {
    set_current_frame_id(i);
    current_occlusion = modify_occlusion();
    QImage ovi = get_occlusion_overlay();

    CImg<float> ov(QImage2CImg(ovi));
    CImg<float> alpha = ov.get_channel(3)/255.0;

    /* TODO IMPORTANT make occlussion tileable */
    QSize s = current_frame->size();
    if (tileable)
    {
      current_occlusion.crop(s.width(),s.height(),2*s.width()-1, 2*s.height()-1);
    }

    current_occlusion = (current_occlusion.mul(1.0-alpha)+ov.get_channel(0)).cut(0.0,255.0);
    occlussion_ready.lock();
    frames[i].set_image(TextureTypes::Occlussion, CImg2QImage(current_occlusion));
    occlussion_ready.unlock();
  }

  set_current_frame_id(frame);
  processed();
  occlusion_mutex.unlock();
}

void ImageProcessor::calculate_heightmap()
{
  /* Implement this ? */
}

int ImageProcessor::fill_neighbours(QString fileName, QImage image)
{
  QImage neighbours;
  current_frame->get_image(TextureTypes::Neighbours, &neighbours);
  QSize s = current_frame->size();
  image = image.scaled(s);

  for (int x = 0; x < 3; x++)
  {
    for (int y = 0; y < 3; y++)
      set_neighbour_image(fileName, image, x, y);
  }
  calculate();

  return 0;
}

void ImageProcessor::reset_neighbours()
{
  QImage diffuse;
  current_frame->get_image(TextureTypes::Diffuse, &diffuse);
  fill_neighbours(current_frame->fileName, diffuse);
}

int ImageProcessor::empty_neighbour(int x, int y)
{
  QImage image(current_frame->size(), QImage::Format_RGBA64_Premultiplied);
  image.fill(0);
  set_neighbour_image("", image, x, y);

  return 0;
}

int ImageProcessor::set_neighbour_image(QString fileName, QImage image, int x,
                                        int y)
{
  QImage neighbours;
  current_frame->get_image(TextureTypes::Neighbours, &neighbours);
  QSize s = current_frame->size();
  current_frame->neighbours_paths[x][y] = fileName;
  int aleft = x * s.width();
  int atop = y * s.height();
  QRect r(aleft, atop, s.width(), s.height());
  QPainter p(&neighbours);
  p.setCompositionMode(QPainter::CompositionMode_Source);
  p.drawImage(r, image);
  current_frame->set_image(TextureTypes::Neighbours, neighbours);

  return 0;
}

QImage ImageProcessor::get_neighbour(int x, int y)
{
  QImage neighbours;
  current_frame->get_image(TextureTypes::Neighbours, &neighbours);
  QSize s = current_frame->size();
  x *= s.width();
  y *= s.height();
  QRect r(x, y, s.width(), s.height());
  QImage p = neighbours.copy(r);

  return p;
}

QString ImageProcessor::get_specular_path()
{
  return current_frame->specularPath;
}

QString ImageProcessor::get_heightmap_path()
{
  return current_frame->heightmapPath;
}

int ImageProcessor::loadSpecularMap(QString fileName, QImage specular)
{
  if (fileName == m_fileName)
  {
    current_frame->specularPath = "";
    customSpecularMap = false;
  }
  else
  {
    current_frame->specularPath = fileName;
    customSpecularMap = true;
  }

  QSize s = current_frame->size();
  specular = specular.scaled(s.width(), s.height());
  current_frame->set_image(TextureTypes::SpecularBase, specular);
  calculate();

  return 0;
}

int ImageProcessor::loadHeightMap(QString fileName, QImage height)
{
  if (fileName == m_fileName)
  {
    current_frame->heightmapPath = "";
    customHeightMap = false;
  }
  else
  {
    current_frame->heightmapPath = fileName;
    customHeightMap = true;
  }

  QSize s = current_frame->size();
  height = height.scaled(s.width(), s.height());
  current_frame->set_image(TextureTypes::Heightmap, height);
  calculate();

  return 0;
}

void ImageProcessor::set_name(QString name) { m_name = name; }

QString ImageProcessor::get_name() { return m_name; }

void ImageProcessor::calculate_gradient() {}

void ImageProcessor::calculate_distance()
{

  m_distance = QImage2CImg(heightmap.convertToFormat(QImage::Format_RGBA8888));
  m_distance.channel(3).threshold(0.1)*255.0f;
  cimg_for_borderXY(m_distance,x,y,1) m_distance(x,y) = 0.0;
  m_distance.distance(0.0f);

  m_distance*=1;
}

void ImageProcessor::set_normal_invert_x(bool invert)
{
  normalInvertX = -invert * 2 + 1;
  QtConcurrent::run(this, &ImageProcessor::generate_normal_map, true, true,
                    false, QRect(0, 0, 0, 0));
}

void ImageProcessor::set_normal_invert_y(bool invert)
{
  normalInvertY = -invert * 2 + 1;
  QtConcurrent::run(this, &ImageProcessor::generate_normal_map, true, true,
                    false, QRect(0, 0, 0, 0));
}

void ImageProcessor::set_normal_invert_z(bool invert)
{
  normalInvertZ = -invert * 2 + 1;
  QtConcurrent::run(this, &ImageProcessor::generate_normal_map, true, true,
                    false, QRect(0, 0, 0, 0));
}

void ImageProcessor::set_normal_depth(int depth)
{
  normal_depth = depth;
  QtConcurrent::run(this, &ImageProcessor::generate_normal_map, true, false,
                    false, QRect(0, 0, 0, 0));
}

void ImageProcessor::set_normal_bisel_soft(bool soft)
{
  normal_bisel_soft = soft;
  QtConcurrent::run(this, &ImageProcessor::generate_normal_map, false, true,
                    true, QRect(0, 0, 0, 0));
}

void ImageProcessor::set_normal_blur_radius(int radius)
{
  normal_blur_radius = radius;
  QtConcurrent::run(this, &ImageProcessor::generate_normal_map, true, false,
                    false, QRect(0, 0, 0, 0));
}

void ImageProcessor::set_normal_bisel_depth(int depth)
{
  normal_bisel_depth = depth;
  QtConcurrent::run(this, &ImageProcessor::generate_normal_map, false, true,
                    false, QRect(0, 0, 0, 0));
}

void ImageProcessor::set_normal_bisel_distance(int distance)
{
  normal_bisel_distance = distance;
  QtConcurrent::run(this, &ImageProcessor::generate_normal_map, false, true,
                    true, QRect(0, 0, 0, 0));
}

void ImageProcessor::set_tileable(bool t)
{
  tileable = t;
  update_tileable = true;
  QtConcurrent::run(this, &ImageProcessor::generate_normal_map, true, true,
                    true, QRect(0, 0, 0, 0));
}

bool ImageProcessor::get_tileable() { return tileable; }

CImg<float> ImageProcessor::modify_distance()
{
  CImg<float> dist(m_distance);

  if (normal_bisel_distance != 0)
  {
    dist *= 255.0/normal_bisel_distance;
  }
  else
  {
    dist.threshold(0.1f)*255.0;
  }

  dist.cut(0,255);
  if (normal_bisel_soft)
  {
    dist = (1.0 - (dist/255.0 - 1).pow(2)).sqrt()*255.0;
  }
  return dist;
}

CImg<float> ImageProcessor::modify_occlusion()
{
  QMutexLocker locker(&heightmap_mutex);
  set_current_heightmap(current_frame_id);

  CImg<float> occ(QImage2CImg(heightmap.convertToFormat(QImage::Format_Grayscale8)));

  if (occlusion_invert)
  {
    occ = 255.0f - occ;
  }

  if (occlusion_distance_mode)
  {
    occ.threshold(occlusion_thresh)*255.0;

    if (occlusion_distance != 0)
    {
      occ.distance(0.0);
      occ *= 255.0/occlusion_distance;
    }
    occ.cut(0,255);
    occ = (1.0 - (occ/255.0 - 1).pow(2)).sqrt()*255.0;

  }

  occ = occlusion_contrast*occ + occlusion_thresh*(1-occlusion_contrast);
  occ += occlusion_bright;
  occ.cut(0,255);
  occ = occ.blur(occlusion_blur);

  return occ;
}

CImg<float> ImageProcessor::modify_parallax()
{
  QMutexLocker locker(&heightmap_mutex);
  set_current_heightmap(current_frame_id);

  CImg<float> par(QImage2CImg(heightmap.convertToFormat(QImage::Format_Grayscale8)));
  CImg<float> dist = modify_distance();
  switch (parallax_type)
  {
    case ParallaxType::Binary:
    {
      par.blur(parallax_focus);
      par.threshold(parallax_max).normalize(0,255);
      par -= parallax_min;

      if (!parallax_invert)
      {
        par = 255.0 - par;
      }

      if (parallax_erode_dilate > 0)
      {
        par.dilate(parallax_erode_dilate,parallax_erode_dilate);
      }
      else
      {
        par.erode(-parallax_erode_dilate,-parallax_erode_dilate);
      }

      par.blur(parallax_soft);
      break;
    }
    case ParallaxType::HeightMap:
    {
      par = (par+dist-1)/2.0+0.5;
      par = parallax_contrast*par + parallax_max*(1-parallax_contrast);
      par += parallax_brightness;
      par.blur(parallax_soft);
      if (parallax_invert)
      {
        par = 255.0 - par;
      }
      break;
    }
    case ParallaxType::Intervals:
    {
      break;
    }
    case ParallaxType::Quantization:
    {
      //TODO: Important, check if i can do it now with CImg
      break;
    }
  }
  par.cut(0,255);
  return par;
}

CImg<float> ImageProcessor::modify_specular()
{
  current_frame->get_image(TextureTypes::SpecularBase, &specular);
  specular = specular.convertToFormat(QImage::Format_Grayscale8);
  CImg<uchar> img = QImage2CImg(specular);
  CImg<float> img_float(img);
  img_float = specular_contrast*img_float + specular_thresh*(1-specular_contrast);
  img_float += specular_bright;
  img_float.cut(0,255);

  img_float.blur(specular_blur);

  if (specular_invert)
  {
    img_float = 255.0 - img_float;
  }

  return img_float;
}

void ImageProcessor::set_normal_bisel_blur_radius(int radius)
{
  normal_bisel_blur_radius = radius;
  QtConcurrent::run(this, &ImageProcessor::generate_normal_map, false, true,
                    false, QRect(0, 0, 0, 0));
}

void ImageProcessor::generate_normal_map(bool updateEnhance, bool updateBump, bool updateDistance, QRect rect)
{

  if (!normal_mutex.tryLock()){
    normal_counter = 1;
    return;
  }

  QMutexLocker hlocker(&heightmap_mutex);

  /* Calculate rects to update */
  QList<QRect> rlist;
  bool diagonal = true;

  // Adjust for 1px blur
  rect.adjust(0, 0, 1, 1);
  rect.moveTo(WrapCoordinate(rect.left(), texture.width()) - 1,
              WrapCoordinate(rect.top(), texture.height()) - 1);
  rlist.append(rect.intersected(texture.rect()));

  if (rect.right() > texture.rect().right() && tileX)
    rlist.prepend(
        QRect(0, rect.top(), WrapCoordinate(rect.right(), texture.width()), rect.height())
            .intersected(texture.rect()));
  else
    diagonal = false;

  if (rect.bottom() > texture.rect().bottom() && tileY)
    rlist.append(QRect(rect.left(), 0, rect.width(),
                       WrapCoordinate(rect.bottom(), texture.height()))
                     .intersected(texture.rect()));
  else
    diagonal = false;

  if (diagonal)
    rlist.append(QRect(0, 0, WrapCoordinate(rect.right(), texture.width()),
                       WrapCoordinate(rect.bottom(), texture.height()))
                     .intersected(texture.rect()));

  rlist.removeAll(QRect(0, 0, 0, 0));
  if (rlist.count() == 0)
    rlist.append(QRect(0, 0, 0, 0));


    QImage heightOverlay = get_heightmap_overlay();
    CImg<float> heightOv = QImage2CImg(heightOverlay);
    heightOv = heightOv.mul(heightOv.get_channel(3)/255.0);
    for (int i = 0; i < rlist.count(); i++)
    {
      m_height_ov =  calculate_normal(heightOv.channel(0), 5000, 0, rlist.at(i));
    }

  if (updateEnhance)
    enhance_requested=1;
  if (updateBump)
    bump_requested=1;
  if (updateDistance)
    distance_requested=1;

  for (int i = 0; i < frames.count(); i++)
  {
    if (update_tileable || frames.count() > 1 )
    {
      set_current_heightmap(i);
      calculate_heightmap();
      calculate_distance();
    }

    if (update_tileable)
    {
      update_tileable = false;
      distance_requested = true;
    }

    if (enhance_requested || frames.count() > 1 )
    {
      for (int i = 0; i < rlist.count(); i++)
      {
        m_emboss_normal = calculate_normal(m_gray*10.0, normal_depth, normal_blur_radius);
      }
    }

    if (distance_requested || frames.count() > 1)
    {
      new_distance = modify_distance();
    }

    if (bump_requested || frames.count() > 1 )
    {
      for (int i = 0; i < rlist.count(); i++)
      {
        m_distance_normal = calculate_normal(new_distance, normal_bisel_depth * normal_bisel_distance, normal_bisel_blur_radius);
      }
    }

    if (m_normal.width() == 0 || m_normal.height() == 0)
    {
      m_normal = m_emboss_normal;
    }

    foreach (QRect rect, rlist)
    {
      int xmin = 0, xmax = texture.width() - 1;
      int ymin = 0, ymax = texture.height() - 1;

      if (rect != QRect(0, 0, 0, 0))
      {
        rect.getCoords(&xmin, &ymin, &xmax, &ymax);
      }
      for (int x = xmin; x <= xmax; ++x)
      {
        for (int y = ymin; y <= ymax; ++y)
        {
          float nr, ng, nb, norm, r, g, b, a;
          QColor ov = normalOverlay.pixelColor(x,y);
          r = ov.redF()*2-1;
          g = ov.greenF()*2-1;
          b = ov.blueF()*2-1;
          a = ov.alphaF();
          nr = m_emboss_normal(x,y,0,0) * 3 / 2.0 + m_distance_normal(x,y,0,0) * 3 / 2.0 + m_height_ov(x,y,0,0);
          ng = m_emboss_normal(x,y,0,1) * 3 / 2.0 + m_distance_normal(x,y,0,1) * 3 / 2.0 + m_height_ov(x,y,0,1);
          nb = m_emboss_normal(x,y,0,2) * 3 / 2.0 + m_distance_normal(x,y,0,2) * 3 / 2.0 + m_height_ov(x,y,0,2);

          nr = nr*(1-a)+(r)*a;
          ng = ng*(1-a)+(g)*a;
          nb = nb*(1-a)+(b)*a;
          norm = sqrtf(nr*nr + ng*ng + nb*nb);

          m_normal(x,y,0,0) = 255.0*(nr/norm*0.5+0.5);
          m_normal(x,y,0,1) = 255.0*(ng/norm*0.5+0.5);
          m_normal(x,y,0,2) = 255.0*(nb/norm*0.5+0.5);

          //          if (!active)
          //          {
          //            normal_mutex.unlock();
          //            return;
          //          }
        }
      }
    }
    normal_ready.lock();
    frames[i].set_image(TextureTypes::Normal, CImg2QImage(m_normal));
    normal_ready.unlock();

  }

  if (enhance_requested)
    enhance_requested--;

  if (distance_requested)
    distance_requested--;

  if (bump_requested)
    bump_requested--;

  processed();
  normal_mutex.unlock();
}

CImg<float> ImageProcessor::calculate_normal(CImg<float> in, int depth, int blur_radius, QRect r)
{
  QSize s = current_frame->size();
  float dx, dy;

  CImg<float> img(in);

  if (img.width() == s.width() * 3)
  {
    img.blur(blur_radius/3.0,true,true);
  }
  else
  {
    img.resize(-300,-300,-100,-100,0,2);
    img.blur(blur_radius/3.0);
    img.crop(s.width(),s.height(),2*s.width()-1, 2*s.height()-1);
  }
  int xs, xe, ys, ye;
  if (r == QRect(0, 0, 0, 0))
  {
    xs = 0;
    xe = img.width() - 1;
    ys = 0;
    ye = img.height() - 1;
  }
  else
  {
    xs = r.left();
    xe = r.right();
    ys = r.top();
    ye = r.bottom();
  }

  CImg<float> normals(img.width(),img.height(),1,3);

  img /= 255.0;

  for (int x = xs; x <= xe; ++x)
  {
    for (int y = ys; y <= ye; ++y)
    {
      if (current_heightmap(x,y,0,3) == 0.0)
      {
        normals(x,y,0,0) = 0;
        normals(x,y,0,1) = 0;
        normals(x,y,0,2) = 1;
        continue;
      }

      if (x == 0)
      {
        dx = -3 * img(x, y) + 4 * img(x + 1, y) - img(x + 2, y);
      }
      else if (x == img.width() - 1)
      {
        dx = 3 * img(x, y) - 4 * img(x - 1, y) + img(x - 2, y);
      }
      else
      {
        dx = -img(x - 1, y) + img(x + 1, y);
      }

      if (y == 0)
      {
        dy = -3 * img(x, y) + 4 * img(x, y + 1) - img(x, y + 2);
      }
      else if (y == img.height() - 1)
      {
        dy = 3 * img(x, y) - 4 * img(x, y - 1) + img(x, y - 2);
      }
      else
      {
        dy = -img(x, y - 1) + img(x, y + 1);
      }

      normals(x, y, 0, 0) = -dx * (depth / 100.0) * normalInvertX;
      normals(x, y, 0, 1) = dy * (depth / 100.0) * normalInvertY;
      normals(x, y, 0, 2) = 1.0;
    }
  }
  //  normals *= 255.0;
  if (tileable)
  {
    normals.crop(s.width(),s.height(),2*s.width()-1, 2*s.height()-1);
  }
  return normals;
}

void ImageProcessor::copy_settings(ProcessorSettings s) { settings = s; }

ProcessorSettings ImageProcessor::get_settings() { return settings; }

int ImageProcessor::get_normal_depth() { return normal_depth; }

int ImageProcessor::get_normal_blur_radius() { return normal_blur_radius; }

bool ImageProcessor::get_normal_bisel_soft() { return normal_bisel_soft; }

int ImageProcessor::get_normal_bisel_depth() { return normal_bisel_depth; }

int ImageProcessor::get_normal_bisel_distance()
{
  return normal_bisel_distance;
}

int ImageProcessor::get_normal_bisel_blur_radius()
{
  return normal_bisel_blur_radius;
}

int ImageProcessor::get_normal_invert_x() { return normalInvertX; }

int ImageProcessor::get_normal_invert_y() { return normalInvertY; }

QImage *ImageProcessor::get_texture() { return &texture; }

QImage *ImageProcessor::get_normal()
{
  current_frame->get_image(TextureTypes::Normal, &last_normal);
  return &last_normal;
}

QImage *ImageProcessor::get_parallax()
{
  current_frame->get_image(TextureTypes::Parallax, &last_parallax);
  return &last_parallax;
}

QImage *ImageProcessor::get_specular()
{
  current_frame->get_image(TextureTypes::Specular, &last_specular);
  return &last_specular;
}

QImage *ImageProcessor::get_occlusion()
{
  current_frame->get_image(TextureTypes::Occlussion, &last_occlussion);
  return &last_occlussion;
}

QImage *ImageProcessor::get_texture_overlay()
{
  current_frame->get_image(TextureTypes::TextureOverlay, &textureOverlay);
  return &textureOverlay;
}

void ImageProcessor::set_texture_overlay(QImage to)
{
  current_frame->set_image(TextureTypes::TextureOverlay, to);
}

QImage ImageProcessor::get_normal_overlay()
{
  current_frame->get_image(TextureTypes::NormalOverlay, &normalOverlay);
  return normalOverlay;
}

void ImageProcessor::set_normal_overlay(QImage no)
{
  current_frame->set_image(TextureTypes::NormalOverlay, no);
  normal_mutex.lock();
  get_normal_overlay();
  normal_mutex.unlock();
}

QImage ImageProcessor::get_parallax_overlay()
{
  current_frame->get_image(TextureTypes::ParallaxOverlay, &parallaxOverlay);
  return parallaxOverlay;
}

void ImageProcessor::set_parallax_overlay(QImage po)
{
  current_frame->set_image(TextureTypes::ParallaxOverlay, po);
}

QImage ImageProcessor::get_specular_overlay()
{
  current_frame->get_image(TextureTypes::SpecularOverlay, &specularOverlay);
  return specularOverlay;
}

void ImageProcessor::set_specular_overlay(QImage so)
{
  current_frame->set_image(TextureTypes::SpecularOverlay, so);
}

QImage ImageProcessor::get_heightmap_overlay()
{
  current_frame->get_image(TextureTypes::HeightmapOverlay, &heightOverlay);
  return heightOverlay;
}

void ImageProcessor::set_heightmap_overlay(QImage ho)
{
  current_frame->set_image(TextureTypes::HeightmapOverlay, ho);
}

QImage ImageProcessor::get_occlusion_overlay()
{
  current_frame->get_image(TextureTypes::OcclussionOverlay,
                           &occlussionOverlay);
  return occlussionOverlay;
}

void ImageProcessor::set_occlussion_overlay(QImage oo)
{
  current_frame->set_image(TextureTypes::OcclussionOverlay, oo);
}

bool ImageProcessor::get_parallax_invert() { return parallax_invert; }

void ImageProcessor::set_parallax_invert(bool invert)
{
  parallax_invert = invert;
  QtConcurrent::run(this, &ImageProcessor::calculate_parallax);
}

void ImageProcessor::set_parallax_focus(int focus)
{
  parallax_focus = focus;
  QtConcurrent::run(this, &ImageProcessor::calculate_parallax);
}

int ImageProcessor::get_parallax_focus() { return parallax_focus; }

void ImageProcessor::set_parallax_soft(int soft)
{
  parallax_soft = soft;
  QtConcurrent::run(this, &ImageProcessor::calculate_parallax);
}

int ImageProcessor::get_parallax_soft() { return parallax_soft; }

int ImageProcessor::get_parallax_thresh() { return parallax_max; }

void ImageProcessor::set_parallax_thresh(int thresh)
{
  parallax_max = thresh;
  QtConcurrent::run(this, &ImageProcessor::calculate_parallax);
}

int ImageProcessor::get_parallax_min() { return parallax_min; }

void ImageProcessor::set_parallax_min(int min)
{
  parallax_min = min;
  QtConcurrent::run(this, &ImageProcessor::calculate_parallax);
}

ParallaxType ImageProcessor::get_parallax_type() { return parallax_type; }

void ImageProcessor::set_parallax_type(ParallaxType ptype)
{
  parallax_type = ptype;
  QtConcurrent::run(this, &ImageProcessor::calculate_parallax);
}

int ImageProcessor::get_parallax_quantization()
{
  return parallax_quantization;
}

void ImageProcessor::set_parallax_quantization(int q)
{
  parallax_quantization = q;
  QtConcurrent::run(this, &ImageProcessor::calculate_parallax);
}

void ImageProcessor::set_parallax_erode_dilate(int value)
{
  parallax_erode_dilate = value;
  QtConcurrent::run(this, &ImageProcessor::calculate_parallax);
}

int ImageProcessor::get_parallax_erode_dilate()
{
  return parallax_erode_dilate;
}

void ImageProcessor::set_parallax_contrast(int contrast)
{
  parallax_contrast = contrast / 1000.0;
  QtConcurrent::run(this, &ImageProcessor::calculate_parallax);
}

double ImageProcessor::get_parallax_contrast() { return parallax_contrast; }

void ImageProcessor::set_parallax_brightness(int brightness)
{
  parallax_brightness = brightness;
  QtConcurrent::run(this, &ImageProcessor::calculate_parallax);
}

int ImageProcessor::get_parallax_brightness() { return parallax_brightness; }

void ImageProcessor::set_specular_blur(int blur)
{
  specular_blur = blur;
  QtConcurrent::run(this, &ImageProcessor::calculate_specular);
}

int ImageProcessor::get_specular_blur() { return specular_blur; }

void ImageProcessor::set_specular_bright(int bright)
{
  specular_bright = bright;
  QtConcurrent::run(this, &ImageProcessor::calculate_specular);
}

int ImageProcessor::get_specular_bright() { return specular_bright; }

void ImageProcessor::set_specular_invert(bool invert)
{
  specular_invert = invert;
  QtConcurrent::run(this, &ImageProcessor::calculate_specular);
}

bool ImageProcessor::get_specular_invert() { return specular_invert; }

void ImageProcessor::set_specular_thresh(int thresh)
{
  specular_thresh = thresh;
  QtConcurrent::run(this, &ImageProcessor::calculate_specular);
}

int ImageProcessor::get_specular_trhesh() { return specular_thresh; }

void ImageProcessor::set_specular_contrast(int contrast)
{
  specular_contrast = contrast / 1000.0;
  QtConcurrent::run(this, &ImageProcessor::calculate_specular);
}

double ImageProcessor::get_specular_contrast() { return specular_contrast; }

void ImageProcessor::set_occlusion_blur(int blur)
{
  occlusion_blur = blur;
  QtConcurrent::run(this, &ImageProcessor::calculate_occlusion);
}

int ImageProcessor::get_occlusion_blur() { return occlusion_blur; }

void ImageProcessor::set_occlusion_bright(int bright)
{
  occlusion_bright = bright;
  QtConcurrent::run(this, &ImageProcessor::calculate_occlusion);
}

int ImageProcessor::get_occlusion_bright() { return occlusion_bright; }

void ImageProcessor::set_occlusion_invert(bool invert)
{
  occlusion_invert = invert;
  QtConcurrent::run(this, &ImageProcessor::calculate_occlusion);
}

bool ImageProcessor::get_occlusion_invert() { return occlusion_invert; }

void ImageProcessor::set_occlusion_thresh(int thresh)
{
  occlusion_thresh = thresh;
  QtConcurrent::run(this, &ImageProcessor::calculate_occlusion);
}

int ImageProcessor::get_occlusion_trhesh() { return occlusion_thresh; }

void ImageProcessor::set_occlusion_contrast(int contrast)
{
  occlusion_contrast = contrast / 1000.0;
  QtConcurrent::run(this, &ImageProcessor::calculate_occlusion);
}

double ImageProcessor::get_occlusion_contrast() { return occlusion_contrast; }

void ImageProcessor::set_occlusion_distance_mode(bool distance_mode)
{
  occlusion_distance_mode = distance_mode;
  QtConcurrent::run(this, &ImageProcessor::calculate_occlusion);
}

bool ImageProcessor::get_occlusion_distance_mode()
{
  return occlusion_distance_mode;
}

void ImageProcessor::set_occlusion_distance(int distance)
{
  occlusion_distance = distance;
  QtConcurrent::run(this, &ImageProcessor::calculate_occlusion);
}

int ImageProcessor::get_occlusion_distance() { return occlusion_distance; }

ProcessorSettings &ProcessorSettings::operator=(ProcessorSettings other)
{
  *tileable = *(other.tileable);
  *gradient_end = *(other.gradient_end);
  *parallax_max = *(other.parallax_max);
  *parallax_min = *(other.parallax_min);
  *parallax_soft = *(other.parallax_soft);
  *parallax_type = *(other.parallax_type);
  *parallax_focus = *(other.parallax_focus);
  *parallax_invert = *(other.parallax_invert);
  *parallax_contrast = *(other.parallax_contrast);
  *parallax_brightness = *(other.parallax_brightness);
  *parallax_erode_dilate = *(other.parallax_erode_dilate);
  *parallax_quantization = *(other.parallax_quantization);
  *normal_depth = *(other.normal_depth);
  *normalInvertX = *(other.normalInvertX);
  *normalInvertY = *(other.normalInvertY);
  *normalInvertZ = *(other.normalInvertZ);
  *normal_bisel_soft = *(other.normal_bisel_soft);
  *normal_bisel_depth = *(other.normal_bisel_depth);
  *normal_blur_radius = *(other.normal_blur_radius);
  *normal_bisel_distance = *(other.normal_bisel_distance);
  *normal_bisel_blur_radius = *(other.normal_bisel_blur_radius);
  *specular_blur = *(other.specular_blur);
  *specular_bright = *(other.specular_bright);
  *specular_invert = *(other.specular_invert);
  *specular_thresh = *(other.specular_thresh);
  *specular_contrast = *(other.specular_contrast);
  *occlusion_blur = *(other.occlusion_blur);
  *occlusion_bright = *(other.occlusion_bright);
  *occlusion_invert = *(other.occlusion_invert);
  *occlusion_thresh = *(other.occlusion_thresh);
  *occlusion_contrast = *(other.occlusion_contrast);
  *occlusion_distance = *(other.occlusion_distance);
  *occlusion_distance_mode = *(other.occlusion_distance_mode);

  lightList->clear();
  foreach (LightSource *light, *(other.lightList))
  {
    LightSource *l = new LightSource();
    l->copy_settings(light);
    lightList->append(l);
  }

  return *this;
}

QImage ImageProcessor::get_heightmap()
{
  /* TODO Implement this */
}

QImage ImageProcessor::get_distance_map()
{
  /* Implement this ? */
}

void ImageProcessor::set_light_list(QList<LightSource *> &list)
{
  lightList.clear();
  foreach (LightSource *light, list)
  {
    LightSource *l = new LightSource();
    l->copy_settings(light);
    lightList.append(l);
  }
}

QList<LightSource *> *ImageProcessor::get_light_list_ptr()
{
  return &lightList;
}

void ImageProcessor::set_position(QVector3D new_pos) {
  position = new_pos;
  positionChanged();
}

QVector3D *ImageProcessor::get_position() { return &position; }

void ImageProcessor::set_offset(QVector3D new_off) { offset = new_off; }

QVector3D *ImageProcessor::get_offset() { return &offset; }

void ImageProcessor::set_selected(bool s) { selected = s; }

bool ImageProcessor::get_selected() { return selected; }

void ImageProcessor::set_zoom(float new_zoom)
{
  zoom = new_zoom;
  processed();
}

float ImageProcessor::get_zoom() { return zoom; }

void ImageProcessor::set_sx(float new_sx) { sx = new_sx; }

float ImageProcessor::get_sx() { return sx; }

void ImageProcessor::set_sy(float new_sy) { sy = new_sy; }

float ImageProcessor::get_sy() { return sy; }

void ImageProcessor::set_tile_x(bool tx)
{
  tileX = tx;
  /* TODO remove this when properly handling tile feature */
  set_rotation(0);
  processed();
}

bool ImageProcessor::get_tile_x() { return tileX; }

void ImageProcessor::set_tile_y(bool ty)
{
  tileY = ty;
  /* TODO remove this when properly handling tile feature */
  set_rotation(0);
  processed();
}

bool ImageProcessor::get_tile_y() { return tileY; }

void ImageProcessor::set_is_parallax(bool p)
{
  is_parallax = p;
  processed();
}

bool ImageProcessor::get_is_parallax() { return is_parallax; }

void ImageProcessor::set_connected(bool c) { connected = c; }

bool ImageProcessor::get_connected() { return connected; }

void ImageProcessor::set_rotation(float r)
{
  rotation = r;
  processed();
}

float ImageProcessor::get_rotation() {
  return rotation;
}

int ImageProcessor::get_current_frame_id() {
  return current_frame_id;
}

void ImageProcessor::set_current_frame_id(int id)
{
  if (id >= frames.count())
    id = frames.count() - 1;
  else if (id < 0)
    id = 0;

  current_frame = &frames[id];
  current_frame_id = id;
  current_frame->get_image(TextureTypes::Diffuse, &texture);


  frameChanged(id);
  processed();

}

Sprite *ImageProcessor::get_current_frame()
{
  return current_frame;
}

void ImageProcessor::next_frame()
{
  if (frames.count() <= 1)
  {
    animation.stop();
    return;
  }

  if (normal_mutex.tryLock())
  {
    if (specular_mutex.tryLock())
    {
      if (parallax_mutex.tryLock())
      {
        if (occlusion_mutex.tryLock())
        {
          int id = (current_frame_id + 1) % frames.count();
          set_current_frame_id(id);
          occlusion_mutex.unlock();
        }
        parallax_mutex.unlock();
      }
      specular_mutex.unlock();
    }
    normal_mutex.unlock();
  }
}

void ImageProcessor::remove_frame(int id)
{
  frames.remove(id);
  set_current_frame_id(id);
}

void ImageProcessor::remove_current_frame() { remove_frame(current_frame_id); }

void ImageProcessor::setAnimationRate(int fps)
{
  animation.setInterval(1000.0/fps);
}

void ImageProcessor::playAnimation(bool play)
{
  play ? animation.start() : animation.stop();
}

int ImageProcessor::WrapCoordinate(int coord, int interval)
{
  coord %= interval;
  if (coord < 0){
    coord += interval;
  }
  return coord;
}

QImage ImageProcessor::CImg2QImage(CImg<uchar> in)
{
  int w = in.width(), h = in.height(), channels = in.spectrum();

  QImage::Format format;

  switch (channels) {
    case 1:
      format = QImage::Format_Grayscale8;
      break;
    case 3:
      format = QImage::Format_RGB888;
      break;
    case 4:
      format = QImage::Format_RGBA8888;
      break;
  }

  QImage out(w,h,format);

  for (int y = 0; y < h; y++)
  {
    unsigned char *dst = out.scanLine(y);
    for (int x = 0; x < w; x++)
    {
      for (int c = 0; c < channels; c++)
      {
        *dst = in(x,y,0,c);
        dst++;
      }
    }
  }
  //  in.permute_axes("cxyz");
  //  return QImage(in.data(), in.height(), in.depth(), format);

  return out;
}

CImg<uchar> ImageProcessor::QImage2CImg(QImage in)
{
  int channels;
  switch (in.format()) {
    case QImage::Format_RGBA8888:
    case QImage::Format_RGBA8888_Premultiplied:
      channels = 4;
      break;
    case QImage::Format_RGB888:
      channels = 3;
      break;
    case QImage::Format_Grayscale8:
      channels = 1;
      break;
    default:
      channels = 0;
  }

  int w = in.width(), h = in.height();

  //  CImg<uchar> srt(in.bits(), channels, w, h, 1);
  //  srt.permute_axes("yzcx");

  CImg<uchar> srt(w,h,1,channels);
  cimg_forY(srt,y)
  {
    unsigned char *src = in.scanLine(y);
    cimg_forX(srt,x)
    {
      for (int c = 0; c < channels; c++)
      {
        srt(x,y,0,c) = *src;
        src++;
      }
    }
  }
  return srt;
}
