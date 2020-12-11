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

#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include "src/light_source.h"
#include "src/sprite.h"

#include <QBrush>
#include <QFuture>
#include <QImage>
#include <QList>
#include <QMutex>
#include <QObject>
#include <QPainter>
#include <QPixmap>
#include <QSemaphore>
#include <QTimer>
#include <QVector2D>

#define cimg_display 0
#include "thirdparty/CImg.h"

enum class ProcessedImage
{
  Raw,
  Normal,
  Parallax,
  Specular,
  Occlusion
};

enum class ParallaxType
{
  Binary,
  HeightMap,
  Quantization,
  Intervals
};

class Request
{
public:
  bool needed = false;
  ProcessedImage type;
  QVector<int> params;
  QRect rect = QRect(0, 0, 0, 0);
};

class Animation
{
public:
  Animation(QString name)
  {
    this->name = name;
  }
  int idx = 0;
  QString name;
  QVector<int> frames_id;
  int getFrame(int idx)
  {

    if (idx >= frames_id.size())
    {
      idx = frames_id.size() - 1;
    }
    else if (idx < 0)
    {
      idx = 0;
    }

    this->idx = idx;
    return frames_id[idx];
  }
  QString getName()
  {
    return name;
  }
};

class ProcessorSettings
{
public:
  ParallaxType *parallax_type;
  QList<LightSource *> *lightList;
  bool *normal_bisel_soft, *tileable, *parallax_invert;
  bool *occlusion_distance_mode;
  bool *occlusion_invert;
  bool *specular_invert;
  char *gradient_end;
  double *occlusion_contrast;
  double *parallax_contrast;
  double *specular_contrast;
  int *normalInvertX, *normalInvertY, *normalInvertZ;
  int *normal_bisel_blur_radius;
  int *normal_bisel_depth;
  int *normal_bisel_distance;
  int *normal_blur_radius;
  int *normal_depth;
  int *occlusion_blur;
  int *occlusion_bright;
  int *occlusion_distance;
  int *occlusion_thresh;
  int *parallax_brightness;
  int *parallax_erode_dilate;
  int *parallax_focus;
  int *parallax_max;
  int *parallax_min;
  int *parallax_quantization;
  int *parallax_soft;
  int *specular_blur;
  int *specular_bright;
  int *specular_thresh;

public:
  ProcessorSettings &operator=(ProcessorSettings other);
};

class ImageProcessor : public QObject
{
  Q_OBJECT

public:
  QImage heightOverlay = QImage(0, 0, QImage::Format_RGBA8888);
  QImage heightmap;
  QImage last_normal;
  QImage normalOverlay = QImage(0, 0, QImage::Format_RGBA8888);
  QImage occlussion, last_occlussion;
  QImage occlussionOverlay = QImage(0, 0, QImage::Format_RGBA8888);
  QImage parallax, last_parallax;
  QImage parallaxOverlay = QImage(0, 0, QImage::Format_RGBA8888);
  QImage specular, last_specular;
  QImage specularOverlay = QImage(0, 0, QImage::Format_RGBA8888);
  QImage specular_base;
  QImage texture, last_texture;
  QImage textureOverlay = QImage(0, 0, QImage::Format_RGBA8888);
  QMutex heightmap_overlay_mutex;
  QMutex normal_overlay_mutex;
  QMutex occlussion_overlay_mutex;
  QMutex parallax_overlay_mutex;
  QMutex specular_overlay_mutex;
  QMutex texture_overlay_mutex;
  QString m_fileName, m_absolute_path;
  QTimer animation, recalculate_timer;
  Sprite sprite;
  QString frame_mode = "Sheet";
  bool busy, active;
  bool updated = false;

  int normal_counter, parallax_counter, specular_counter, occlussion_counter;

  QRect rect_requested = QRect(0, 0, 0, 0);

  QVector<QVector<float>> vertices;

  float current_vertices[20] = {
      -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, // bot left
      1.0f, -1.0f, 0.0f, 1.0f, 1.0f,  // bot right
      -1.0f, 1.0f, 0.0f, 0.0f, 0.0f,  // top left
      1.0f, 1.0f, 0.0f, 1.0f, 0.0f,   // top right

      //1.0f/2, 1.0f/2, 0.0f, 1.0f/2, 0.0f,   // top right
  };

  QList<Animation> animation_list;
  Animation *current_animation = nullptr;

private:
  ParallaxType parallax_type;
  ProcessorSettings settings;
  QBrush normal_brush;
  QFuture<void> normal_future;
  QList<LightSource *> lightList;
  QMutex normal_mutex, parallax_mutex, specular_mutex, occlusion_mutex, heightmap_mutex,
      normal_ready, specular_ready, parallax_ready, occlussion_ready;
  QPainter normal_painter;
  QString m_name, m_heightmapPath, m_specularPath;
  QVector3D offset;
  QVector3D position;
  int selected_frame = 0;
  bool customHeightMap, customSpecularMap;
  bool normal_bisel_soft, tileable, update_tileable = false, parallax_invert;
  bool occlusion_distance_mode;
  bool occlusion_invert;
  bool selected, tileX, tileY, is_parallax, connected;
  bool specular_invert;
  char gradient_end;
  bool useNormalAlpha = false;
  bool useParallaxAlpha = false;
  bool useSpecularAlpha = false;
  bool useOcclusionAlpha = false;
  cimg_library::CImg<float> current_heightmap;
  cimg_library::CImg<float> current_occlusion;
  cimg_library::CImg<float> current_parallax;
  cimg_library::CImg<float> current_specular;
  cimg_library::CImg<float> m_distance;
  cimg_library::CImg<float> new_distance;
  cimg_library::CImg<float> m_distance_normal;
  cimg_library::CImg<float> m_emboss_normal;
  cimg_library::CImg<float> m_normal;
  cimg_library::CImg<float> m_gray;
  cimg_library::CImg<float> m_height_ov, aux_height_ov;

  double occlusion_contrast;
  double parallax_contrast;
  double specular_contrast;
  float rotation = 0;
  float sx, sy;
  float zoom;
  int current_frame_id = 0;
  bool enhance_requested = false, bump_requested = false, distance_requested = false;
  int normalInvertX, normalInvertY, normalInvertZ;
  int normal_bisel_blur_radius;
  int normal_bisel_depth;
  int normal_bisel_distance;
  int normal_blur_radius;
  int normal_depth;
  int occlusion_blur;
  int occlusion_bright;
  int occlusion_distance;
  int occlusion_thresh;
  int parallax_brightness;
  int parallax_erode_dilate;
  int parallax_focus;
  int parallax_max;
  int parallax_min;
  int parallax_quantization;
  int parallax_soft;
  int specular_blur;
  int specular_bright;
  int specular_thresh;

  int h_frames = 1, v_frames = 1;

public:
  explicit ImageProcessor(QObject *parent = nullptr);
  ~ImageProcessor();
  QImage *get_normal();
  QImage *get_occlusion();
  QImage *get_parallax();
  QImage *get_specular();
  QImage *get_texture();
  QImage get_distance_map();
  QImage get_heightmap();
  QString get_heightmap_path();
  QString get_name();
  QString get_specular_path();
  cimg_library::CImg<float> modify_distance();
  cimg_library::CImg<float> modify_occlusion();
  cimg_library::CImg<float> modify_parallax();
  cimg_library::CImg<float> modify_specular();
  int loadHeightMap(QString fileName, QImage height);
  int loadImage(QString fileName, QImage image, QString basePath = "");
  int loadSpecularMap(QString fileName, QImage specular);
  void calculate_distance();
  void calculate_gradient();
  void calculate_heightmap();
  void calculate_texture();
  cimg_library::CImg<float> calculate_normal(cimg_library::CImg<float> in, int depth, int blur_radius, QRect r = QRect(0, 0, 0, 0));
  void generate_normal_map(bool updateEnhance = true, bool updateBump = true,
                           bool updateDistance = true,
                           QRect rect = QRect(0, 0, 0, 0));
  void set_name(QString name);
  QImage get_normal_overlay();
  QImage get_texture_overlay();
  QImage get_heightmap_overlay();
  QImage get_occlusion_overlay();
  QImage get_parallax_overlay();
  QImage get_specular_overlay();
  void calculate();
  void calculate_occlusion();
  void calculate_parallax();
  void calculate_specular();
  void set_heightmap_overlay(QImage ho);
  void set_normal_overlay(QImage no);
  void set_occlussion_overlay(QImage oo);
  void set_parallax_overlay(QImage po);
  void set_specular_overlay(QImage so);
  void set_texture_overlay(QImage to);
  int WrapCoordinate(int coord, int interval);
  QImage CImg2QImage(cimg_library::CImg<uchar> in);
  cimg_library::CImg<uchar> QImage2CImg(QImage in);

  int get_frame_count();
  int get_frame_at_point(QPoint point);
  Animation *getAnimation(QString name);
  QStringList getAnimationNames();
  void removeAnimation(QString name);
  void setCurrentAnimation(QString name);
  QString getCurrentAnimationName();
  QString current_animation_name = "Default";
  Animation *getCurrentAnimation();
  void setFrameMode(QString mode);
  QString getFrameMode();
  QImage getFrameImage(int frame);
  QImage getFrameImage(int x, int y);
  QRect getFrameRect(int frame);
  QRect getFrameRect(int x, int y);

  int getHFrames();
  void setHFrames(int h);
  int getVFrames();
  void setVFrames(int v);

  void getFramePosition(int frame, int &x, int &y);
  void splitInFrames(int h_frames, int v_frames);

public slots:
  void playAnimation(bool play);
  void recalculate();
  void setAnimationRate(int fps);
  ParallaxType get_parallax_type();
  ProcessorSettings get_settings();
  QImage get_neighbour(int x, int y);
  QList<LightSource *> *get_light_list_ptr();
  QVector3D *get_offset();
  QVector3D *get_position();
  Sprite *get_current_frame();
  bool get_connected();
  bool get_is_parallax();
  bool get_normal_bisel_soft();
  bool get_occlusion_distance_mode();
  bool get_occlusion_invert();
  bool get_parallax_invert();
  bool get_selected();
  bool get_specular_invert();
  bool get_tile_x();
  bool get_tile_y();
  bool get_tileable();

  void set_use_normal_alpha(bool a);
  bool get_use_normal_alpha();
  void set_use_parallax_alpha(bool a);
  bool get_use_parallax_alpha();
  void set_use_specular_alpha(bool a);
  bool get_use_specular_alpha();
  void set_use_occlusion_alpha(bool a);
  bool get_use_occlusion_alpha();

  double get_occlusion_contrast();
  double get_parallax_contrast();
  double get_specular_contrast();
  float get_rotation();
  float get_sx();
  float get_sy();
  float get_zoom();
  int empty_neighbour(int x, int y);
  int fill_neighbours(QString fileName, QImage image);
  int get_current_frame_id();
  int get_normal_bisel_blur_radius();
  int get_normal_bisel_depth();
  int get_normal_bisel_distance();
  int get_normal_blur_radius();
  int get_normal_depth();
  int get_normal_invert_x();
  int get_normal_invert_y();
  int get_occlusion_blur();
  int get_occlusion_bright();
  int get_occlusion_distance();
  int get_occlusion_trhesh();
  int get_parallax_brightness();
  int get_parallax_erode_dilate();
  int get_parallax_focus();
  int get_parallax_min();
  int get_parallax_quantization();
  int get_parallax_soft();
  int get_parallax_thresh();
  int get_specular_blur();
  int get_specular_bright();
  int get_specular_trhesh();
  int set_neighbour_image(QString fileName, QImage image, int x, int y);
  int set_neighbour_image(QImage image, int x, int y);
  void copy_settings(ProcessorSettings s);
  void next_frame();
  void remove_current_frame();
  void remove_frame(int id);
  void reset_neighbours();
  void set_connected(bool c);
  void set_current_frame_id(int id);
  void set_current_heightmap();
  void set_is_parallax(bool p);
  void set_light_list(QList<LightSource *> &list);
  void set_normal_bisel_blur_radius(int radius);
  void set_normal_bisel_depth(int depth);
  void set_normal_bisel_distance(int distance);
  void set_normal_bisel_soft(bool soft);
  void set_normal_blur_radius(int radius);
  void set_normal_depth(int depth);
  void set_normal_invert_x(bool invert);
  void set_normal_invert_y(bool invert);
  void set_normal_invert_z(bool invert);
  void set_occlusion_blur(int blur);
  void set_occlusion_bright(int bright);
  void set_occlusion_contrast(int contrast);
  void set_occlusion_distance(int distance);
  void set_occlusion_distance_mode(bool distance_mode);
  void set_occlusion_invert(bool invert);
  void set_occlusion_thresh(int thresh);
  void set_offset(QVector3D new_off);
  void set_parallax_brightness(int brightness);
  void set_parallax_contrast(int contrast);
  void set_parallax_erode_dilate(int value);
  void set_parallax_focus(int focus);
  void set_parallax_invert(bool invert);
  void set_parallax_min(int min);
  void set_parallax_quantization(int q);
  void set_parallax_soft(int soft);
  void set_parallax_thresh(int thresh);
  void set_parallax_type(ParallaxType ptype);
  void set_position(QVector3D new_pos);
  void set_rotation(float r);
  void set_selected(bool s);
  void set_specular_blur(int blur);
  void set_specular_bright(int bright);
  void set_specular_contrast(int contrast);
  void set_specular_invert(bool invert);
  void set_specular_thresh(int thresh);
  void set_sx(float new_sx);
  void set_sy(float new_sy);
  void set_tile_x(bool tx);
  void set_tile_y(bool ty);
  void set_tileable(bool t);
  void set_zoom(float new_zoom);

signals:
  void processed();
  void positionChanged();
  void frameChanged(int index);
  void on_idle();
};

#endif // IMAGEPROCESSOR_H
