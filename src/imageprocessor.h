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

#include <QImage>
#include <QList>
#include <QObject>

#include <QPixmap>
#include <QMutex>
#include <QPainter>
#include <QBrush>
#include <QFuture>
#include <QVector2D>
#include <QTimer>

#include "src/lightsource.h"
#include "src/sprite.h"

#include <opencv2/opencv.hpp>
#if CV_MAJOR_VERSION >= 4
#include <opencv2/imgproc/types_c.h>
#endif
#if defined(Q_OS_WIN)
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#endif



enum class ProcessedImage { Raw, Normal, Parallax, Specular, Occlusion };

enum class ParallaxType { Binary, HeightMap, Quantization, Intervals };

class ProcessorSettings {
  public:
  ProcessorSettings &operator=(ProcessorSettings other);
  int *parallax_min;
  int *parallax_max;
  int *parallax_focus;
  int *parallax_soft;
  int *parallax_quantization;
  int *parallax_brightness;
  double *parallax_contrast;
  int *parallax_erode_dilate;
  ParallaxType *parallax_type;

  int *specular_thresh;
  double *specular_contrast;
  int *specular_bright;
  int *specular_blur;
  bool *specular_invert;

  int *normal_depth;
  int *normal_bisel_depth;
  int *normal_bisel_distance;
  int *normal_blur_radius;
  int *normal_bisel_blur_radius;
  bool *normal_bisel_soft, *tileable, *parallax_invert;
  int *normalInvertX, *normalInvertY, *normalInvertZ;
  char *gradient_end;

  int *occlusion_thresh;
  double *occlusion_contrast;
  int *occlusion_bright;
  int *occlusion_blur;
  bool *occlusion_invert;
  bool *occlusion_distance_mode;
  int *occlusion_distance;

  QList<LightSource *> *lightList;
};

class ImageProcessor : public QObject {
  Q_OBJECT
  public:
  explicit ImageProcessor(QObject *parent = nullptr);
  ~ImageProcessor();
  int loadImage(QString fileName, QImage image);
  int loadHeightMap(QString fileName, QImage height);
  int loadSpecularMap(QString fileName, QImage specular);
  void generate_normal_map(bool updateEnhance = true, bool updateBump = true, bool updateDistance = true, QRect rect = QRect(0,0,0,0));
  void calculate_normal(cv::Mat mat, cv::Mat src, int depth, int blur_radius, QRect r = QRect(0,0,0,0));
  void calculate_gradient();
  void calculate_distance();
  void calculate_heightmap();
  cv::Mat modify_distance();
  cv::Mat modify_parallax();
  cv::Mat modify_specular();
  cv::Mat modify_occlusion();
  void set_name(QString name);
  QString get_name();
  QString get_specular_path();
  QString get_heightmap_path();
  bool busy, active;
  QString m_fileName;

  QImage *get_texture();
  QImage get_heightmap();
  QImage get_distance_map();
  QImage *get_normal();
  QImage *get_parallax();
  QImage *get_specular();
  QImage *get_occlusion();

  QImage texture;
  QImage last_normal;
  QImage parallax, last_parallax;
  QImage specular, last_specular;
  QImage occlussion, last_occlussion;

  QImage heightmap;
  QImage specular_base;

  QTimer animation;

  QRect normalRect = QRect(0,0,0,0);

  /* Images for Plugins */

  QImage textureOverlay = QImage(0,0,QImage::Format_RGBA8888);
  QImage normalOverlay = QImage(0,0,QImage::Format_RGBA8888);
  QImage parallaxOverlay = QImage(0,0,QImage::Format_RGBA8888);
  QImage specularOverlay = QImage(0,0,QImage::Format_RGBA8888);
  QImage occlussionOverlay = QImage(0,0,QImage::Format_RGBA8888);
  QImage heightOverlay = QImage(0,0,QImage::Format_RGBA8888);

  QMutex texture_overlay_mutex;
  QImage *get_texture_overlay();
  void set_texture_overlay(QImage to);

  QMutex normal_overlay_mutex;
  QImage get_normal_overlay();
  void set_normal_overlay(QImage no);

  QMutex parallax_overlay_mutex;
  QImage get_parallax_overlay();
  void set_parallax_overlay(QImage po);

  QMutex specular_overlay_mutex;
  QImage get_specular_overlay();
  void set_specular_overlay(QImage so);

  QMutex occlussion_overlay_mutex;
  QImage get_occlusion_overlay();
  void set_occlussion_overlay(QImage oo);

  QMutex heightmap_overlay_mutex;
  QImage get_heightmap_overlay();
  void set_heightmap_overlay(QImage ho);

  void calculate();
  void calculate_parallax();
  void calculate_specular();
  void calculate_occlusion();

  bool updated = false;


  QVector <Sprite> frames;

  signals:
  void processed();
  void on_idle();
  public slots:


  void next_frame();

  void set_current_frame_id(int id);
  int get_current_frame_id();

  void remove_frame(int id);
  void remove_current_frame();

  void copy_settings(ProcessorSettings s);
  void set_normal_depth(int depth);
  int get_normal_depth();
  void set_normal_blur_radius(int radius);
  int get_normal_blur_radius();
  void set_normal_bisel_depth(int depth);
  int get_normal_bisel_depth();
  void set_normal_bisel_distance(int distance);
  int get_normal_bisel_distance();
  void set_normal_bisel_blur_radius(int radius);
  int get_normal_bisel_blur_radius();
  void set_normal_bisel_soft(bool soft);
  bool get_normal_bisel_soft();
  void set_normal_invert_x(bool invert);
  int get_normal_invert_x();
  void set_normal_invert_y(bool invert);
  int get_normal_invert_y();
  void set_normal_invert_z(bool invert);
  bool get_tileable();
  void set_tileable(bool t);

  void set_parallax_invert(bool invert);
  bool get_parallax_invert();
  void set_parallax_focus(int focus);
  int get_parallax_focus();
  void set_parallax_soft(int soft);
  int get_parallax_soft();
  void set_parallax_thresh(int thresh);
  int get_parallax_thresh();
  void set_parallax_min(int min);
  int get_parallax_min();
  void set_parallax_type(ParallaxType ptype);
  int get_parallax_quantization();
  void set_parallax_quantization(int q);
  int get_parallax_erode_dilate();
  void set_parallax_erode_dilate(int value);
  int get_parallax_brightness();
  void set_parallax_brightness(int brightness);
  double get_parallax_contrast();
  void set_parallax_contrast(int contrast);

  void set_specular_invert(bool invert);
  bool get_specular_invert();
  void set_specular_thresh(int thresh);
  int get_specular_trhesh();
  void set_specular_contrast(int contrast);
  double get_specular_contrast();
  void set_specular_bright(int bright);
  int get_specular_bright();
  void set_specular_blur(int blur);
  int get_specular_blur();
  void set_specular_base_color(cv::Vec4b color);
  cv::Vec4b get_specular_base_color();

  void set_occlusion_invert(bool invert);
  bool get_occlusion_invert();
  void set_occlusion_thresh(int thresh);
  int get_occlusion_trhesh();
  void set_occlusion_contrast(int contrast);
  double get_occlusion_contrast();
  void set_occlusion_bright(int bright);
  int get_occlusion_bright();
  void set_occlusion_blur(int blur);
  int get_occlusion_blur();
  void set_occlusion_distance_mode(bool distance_mode);
  bool get_occlusion_distance_mode();
  void set_occlusion_distance(int distance);
  int get_occlusion_distance();

  ProcessorSettings get_settings();

  ParallaxType get_parallax_type();

  int fill_neighbours(QString fileName, QImage image);
  int set_neighbour_image(QString fileName, QImage image, int x, int y);
  int empty_neighbour(int x, int y);
  void reset_neighbours();
  void set_current_heightmap();
  QImage get_neighbour(int x, int y);

  void set_light_list(QList<LightSource *> &list);
  QList<LightSource *> *get_light_list_ptr();

  void set_position(QVector3D new_pos);
  QVector3D *get_position();
  void set_rotation(float r);
  float get_rotation();
  void set_offset(QVector3D new_off);
  QVector3D *get_offset();
  void set_selected(bool s);
  bool get_selected();
  void set_zoom(float new_zoom);
  float get_zoom();
  void set_sx(float new_sx);
  void set_sy(float new_sy);
  float get_sx();
  float get_sy();
  void set_tile_x(bool tx);
  void set_tile_y(bool ty);
  bool get_tile_x();
  bool get_tile_y();
  void set_is_parallax(bool p);
  bool get_is_parallax();
  bool get_connected();
  void set_connected(bool c);
  Sprite *get_current_frame();


  private:

  ProcessorSettings settings;
  QString m_name, m_heightmapPath, m_specularPath;
  cv::Mat m_gray;
  cv::Mat m_distance;
  cv::Mat m_normal;
  cv::Mat m_emboss_normal;
  cv::Mat m_distance_normal;
  cv::Mat new_distance;
  cv::Mat m_parallax;
  cv::Mat m_occlusion;
  cv::Mat current_heightmap;
  cv::Mat m_height_ov, aux_height_ov;

  cv::Mat current_specular;
  int specular_thresh;
  int specular_bright;
  double specular_contrast;
  int specular_blur;
  bool specular_invert;
  cv::Vec4b specular_base_color;

  cv::Mat current_parallax;
  int parallax_min;
  int parallax_max;
  int parallax_focus;
  int parallax_soft;
  int parallax_quantization;
  int parallax_brightness;
  double parallax_contrast;
  int parallax_erode_dilate;
  ParallaxType parallax_type;

  int normal_depth;
  int normal_bisel_depth;
  int normal_bisel_distance;
  int normal_blur_radius;
  int normal_bisel_blur_radius;
  bool normal_bisel_soft, tileable, update_tileable = false, parallax_invert;
  int enhance_requested=0, bump_requested=0, distance_requested=0;
  int normalInvertX, normalInvertY, normalInvertZ;
  char gradient_end;

  cv::Mat current_occlusion;
  int occlusion_thresh;
  double occlusion_contrast;
  int occlusion_bright;
  int occlusion_blur;
  bool occlusion_invert;
  bool occlusion_distance_mode;
  int occlusion_distance;

  QList<LightSource *> lightList;

  QVector3D position;
  QVector3D offset;
  float rotation = 0;
  float zoom;
  float sx, sy;
  bool selected, tileX, tileY, is_parallax, connected;

  bool customHeightMap, customSpecularMap;

  QMutex normal_mutex, parallax_mutex, specular_mutex, occlusion_mutex, normal_ready, specular_ready, parallax_ready, occlussion_ready;
  int normal_counter, parallax_counter, specular_counter, occlussion_counter;

  QPainter normal_painter;
  QBrush normal_brush;

  QFuture <void> normal_future;


  int current_frame_id = 0;
  Sprite *current_frame;
};

#endif // IMAGEPROCESSOR_H
