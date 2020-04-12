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

#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include "brush_interface.h"
#include "image_processor.h"
#include "light_source.h"

#include <QList>
#include <QObject>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLWidget>
#include <QPixmap>
#include <QTimer>
#include <QWheelEvent>

enum ViewMode
{
  Texture,
  NormalMap,
  SpecularMap,
  ParallaxMap,
  OcclusionMap,
  Preview
};

class OpenGlWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
  Q_OBJECT

public:
  BrushInterface *currentBrush;
  ImageProcessor *processor;
  QList<LightSource *> *sampleLightList;
  bool need_to_update;
  int blend_factor = 0;

private:
  GLuint shaderProgram, vertexShader, fragmentShader;
  LightSource *currentLight;
  QColor lightColor, specColor, ambientColor, backgroundColor;
  QImage m_image, normalMap, parallaxMap, laigter, specularMap, occlusionMap,
      renderedPreview;
  QList<ImageProcessor *> processorList, selectedProcessors;
  QList<LightSource *> *currentLightList;
  QList<LightSource *> lightList;
  QOpenGLBuffer VBO, VBO3D;
  QOpenGLShaderProgram m_program, simpleProgram, lightProgram, cursorProgram;
  QOpenGLTexture *m_texture, *m_normalTexture, *laigterTexture, *brushTexture,
      *m_parallaxTexture, *m_specularTexture, *m_occlusionTexture;
  QOpenGLVertexArrayObject VAO, VAO3D;
  QOpenGLVertexArrayObject lightVAO;
  QPoint oldPos;
  QPointF old_position;
  QString exportBasePath;
  QTimer refreshTimer;
  QVector3D lightPosition, texturePosition, textureOffset;
  QVector3D origin = QVector3D(0,0,0);
  bool export_render, exportFullView, addLight;
  bool lightSelected;
  bool m_fullPreview, m_autosave;
  bool m_light, tileX, tileY, m_parallax, m_pixelated, m_toon;
  bool sample_light_list_used;
  float diffIntensity, ambientIntensity, specIntensity, specScatter;
  float m_zoom, m_global_zoom = 1;
  float sx, sy, parallax_height;
  int pixelsX, pixelsY, pixelSize;
  int viewmode;

public:
  OpenGlWidget(QWidget *parent = nullptr);

public slots:
  float getZoom();
  void add_processor(ImageProcessor *p);
  void clear_processor_list();
  void fitZoom();
  void force_update();
  void loadTextures();
  void remove_light(LightSource *light);
  void resetZoom();
  void setAmbientColor(QColor color);
  void setAmbientIntensity(float intensity);
  void setBackgroundColor(QColor color);
  void setImage(QImage *image);
  void setLight(bool light);
  void setLightColor(QColor color);
  void setLightHeight(float height);
  void setLightIntensity(float intensity);
  void setNormalMap(QImage *normalMap);
  void setOcclusionMap(QImage *occlusionMap);
  void setParallax(bool p);
  void setParallaxHeight(int height);
  void setParallaxMap(QImage *parallaxMap);
  void setPixelSize(int size);
  void setPixelated(bool pixelated);
  void setSpecColor(QColor color);
  void setSpecIntensity(float intensity);
  void setSpecScatter(int scatter);
  void setSpecularMap(QImage *image);
  void setTileX(bool x);
  void setTileY(bool y);
  void setToon(bool toon);
  void setZoom(float zoom);
  void set_add_light(bool add);
  void set_all_processors_selected(bool selected);
  void set_current_light_list(QList<LightSource *> *list);
  void set_current_processor(ImageProcessor *p);
  void set_processor_list(QList<ImageProcessor *> list);
  QList<ImageProcessor *> * get_processor_list();
  void set_processor_selected(ImageProcessor *processor, bool selected);
  void set_view_mode(int mode);
  void update();
  void update_light_position(QVector3D new_pos);
  void update_scene();
  void use_sample_light_list(bool l);
  ImageProcessor *get_current_processor();
  QImage calculate_preview(bool fullPreview = false);
  QImage get_preview(bool fullPreview = true, bool autosave = false,
                     QString basePath = "");
  QImage renderBuffer();
  QList<ImageProcessor *> get_all_selected_processors();
  QList<LightSource *> *get_current_light_list_ptr();

signals:
  void initialized();
  void processor_selected(ImageProcessor *processor, bool selected);
  void selectedLightChanged(LightSource *light);
  void selectedProcessorsChanged(QList<ImageProcessor *> list);
  void set_enabled_light_controls(bool e);
  void set_enabled_map_controls(bool e);
  void stopAddingLight();

protected:
  void initializeGL() override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void mousePressEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;
  void paintGL() override;
  void resizeGL(int width, int height) override;
  void wheelEvent(QWheelEvent *event) override;

private:
  void apply_light_params();
  void select_current_light_list();
  void select_light(LightSource *light);
};

#endif // OPENGLWIDGET_H
