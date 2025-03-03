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

#include "open_gl_widget.h"

#include <math.h>

#include <QApplication>
#include <QFileInfo>
#include <QImageWriter>
#include <QOpenGLFramebufferObject>
#include <QOpenGLVersionProfile>
#include <QOpenGLVertexArrayObject>
#include <QPainter>

#include <QElapsedTimer>

QElapsedTimer elapsed_timer;

OpenGlWidget::OpenGlWidget(QWidget *parent)
{
  Q_UNUSED(parent)
  m_zoom = 1.0;
  laigter = QImage(":/images/laigter_texture.png");
  ambientColor = QColor("white");
  ambientIntensity = 0.8f;
  lightPosition = QVector3D(0.4f * width() * devicePixelRatioF(), 0.4f * height() * devicePixelRatioF(), 0.3f);
  m_light = true;
  m_parallax = false;
  parallax_height = 0.03f;
  // processor->set_tile_x(false);
  // processor->set_tile_y(false);
  m_pixelated = false;
  m_toon = false;
  lightSelected = false;
  currentLight = new LightSource();
  currentLight->set_light_position(lightPosition);
  QColor c;
  c.setRgbF(0.0, 1, 0.7);
  currentLight->set_diffuse_color(c);
  currentLight->set_specular_color(c);
  currentLight->set_specular_scatter(32);
  currentLight->set_diffuse_intensity(0.6f);
  currentLight->set_specular_intensity(0.6f);
  lightList.append(currentLight);
  currentLightList = &lightList;
  backgroundColor.setRgbF(0.2, 0.2, 0.3);
  pixelSize = 3;
  refreshTimer.setInterval(1.0 / 60.0 * 1000.0);
  refreshTimer.setSingleShot(false);
  connect(&refreshTimer, SIGNAL(timeout()), this, SLOT(force_update()));
  refreshTimer.start();
  need_to_update = false;
  export_render = false;
  exportFullView = false;
  addLight = false;
  this->setMouseTracking(true);
  viewmode = 0;
  sample_light_list_used = true;
  oldPos = QPoint(0, 0);
  currentBrush = nullptr;
  elapsed_timer.start();
}

void OpenGlWidget::initializeGL()
{
  initializeOpenGLFunctions();
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);
  glClearColor(
      backgroundColor.redF() * ambientColor.redF() * ambientIntensity,
      backgroundColor.greenF() * ambientColor.greenF() * ambientIntensity,
      backgroundColor.blueF() * ambientColor.blueF() * ambientIntensity, 1.0);

  setUpdateBehavior(QOpenGLWidget::PartialUpdate);
  m_program.create();
  m_program.addShaderFromSourceFile(QOpenGLShader::Vertex,
                                    ":/shaders/vshader.glsl");
  m_program.addShaderFromSourceFile(QOpenGLShader::Fragment,
                                    ":/shaders/fshader.glsl");
  m_program.link();
  lightProgram.create();
  lightProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,
                                       ":/shaders/lvshader.glsl");
  lightProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,
                                       ":/shaders/lfshader.glsl");
  cursorProgram.create();
  cursorProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,
                                        ":/shaders/lvshader.glsl");
  cursorProgram.addShaderFromSourceFile(
      QOpenGLShader::Fragment, ":/shaders/cursor_fragment_shader.glsl");

  // set up vertex data (and buffer(s)) and configure vertex attributes
  // ------------------------------------------------------------------
  float vertices[] = {
      -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, // bot left
      1.0f, -1.0f, 0.0f, 1.0f, 1.0f,  // bot right
      -1.0f, 1.0f, 0.0f, 0.0f, 0.0f,  // top left
      1.0f, 1.0f, 0.0f, 1.0f, 0.0f,   // top right
  };

  // bind the Vertex Array Object first, then bind and set vertex buffer(s),
  // and then configure vertex attributes(s).

  VAO.bind();
  VBO.create();
  VBO.bind();
  VBO.allocate(vertices, sizeof(vertices));
  m_program.setAttributeBuffer("aPos", GL_FLOAT, 0, 3, 5 * sizeof(float));
  m_program.enableAttributeArray("aPos");
  m_program.setAttributeBuffer("aTexCoord", GL_FLOAT, (3 * sizeof(float)), 2,
                               5 * sizeof(float));
  m_program.enableAttributeArray("aTexCoord");
  VAO.release();
  VBO.release();

  VBO.bind();
  lightProgram.setAttributeBuffer("aPos", GL_FLOAT, 0, 3, 5 * sizeof(float));
  lightProgram.enableAttributeArray("aPos");
  lightProgram.setAttributeBuffer("aTexCoord", GL_FLOAT, 3 * sizeof(float), 2,
                                  5 * sizeof(float));
  lightProgram.enableAttributeArray("aTexCoord");
  lightVAO.release();
  VBO.release();
  initialized();
}

void OpenGlWidget::loadTextures()
{
  processor = processorList.at(0);
  QImage i(processor->get_texture()->size(), QImage::Format_RGBA8888);
  i.fill(Qt::transparent);
  m_texture = new QOpenGLTexture(i);
  m_parallaxTexture = new QOpenGLTexture(i);
  m_specularTexture = new QOpenGLTexture(i);
  m_normalTexture = new QOpenGLTexture(i);
  m_occlusionTexture = new QOpenGLTexture(i);
  laigterTexture = new QOpenGLTexture(laigter);
  brushTexture = new QOpenGLTexture(laigter);
}

void OpenGlWidget::paintGL()
{
  if (need_to_update)
  {
    need_to_update = false;
    update_scene();
  }

  if (export_render)
  {
    export_render = false;
    renderedPreview = calculate_preview(m_fullPreview);
  }
}

void OpenGlWidget::update() {
  QOpenGLWidget::update();
}

void OpenGlWidget::force_update()
{
  if (need_to_update)
    update();
}

void OpenGlWidget::update_scene()
{
  glClearColor(
      backgroundColor.redF() * ambientColor.redF() * ambientIntensity,
      backgroundColor.greenF() * ambientColor.greenF() * ambientIntensity,
      backgroundColor.blueF() * ambientColor.blueF() * ambientIntensity, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);

  defaultFramebufferObject();
  glViewport(0, 0, m_width, m_height);

  QVector3D color;
  float r, g, b;
  GLfloat bkColor[4];
  glGetFloatv(GL_COLOR_CLEAR_VALUE, bkColor);

  int i1 = m_pixelated ? GL_LINEAR_MIPMAP_LINEAR : GL_LINEAR_MIPMAP_LINEAR;
  int i2 = m_pixelated ? GL_NEAREST : GL_LINEAR;

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, i1);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, i2);

  QVector3D viewport_size(m_width, m_height, 1.0);

  projection.setToIdentity();
  projection.ortho(-0.5 * m_width, 0.5 * m_width, -0.5 * m_height, 0.5 * m_height, -1, 1);

  float *current_vertices = nullptr;

  m_program.bind();
  m_program.setUniformValue("view_mode", viewmode);
  m_program.setUniformValue("pixelated", m_pixelated);
  backgroundColor.getRgbF(&r, &g, &b, nullptr);
  color = QVector3D(bkColor[0], bkColor[1], bkColor[2]);
  m_program.setUniformValue("outlineColor", color);
  m_program.setUniformValue("toon", m_toon);
  m_program.setUniformValue("viewPos", QVector3D(0, 0, 1));
  m_program.setUniformValue("height_scale", parallax_height);
  m_program.setUniformValue("blend_factor", static_cast<float>(blend_factor / 100.0));
  m_program.setUniformValue("zoom", m_global_zoom);
  m_program.setUniformValue("viewport_size", QVector2D(m_width, m_height));
  apply_light_params(projection, view);

  foreach (ImageProcessor *processor, processorList)
  {
    if (processor->get_current_frame()->get_image(TextureTypes::Diffuse, &m_image))
    {
      m_image = *processor->get_texture();
      setImage(&m_image);
    }
    if (processor->get_current_frame()->get_image(TextureTypes::Normal, &normalMap))
    {
      setNormalMap(&normalMap);
    }
    if (processor->get_current_frame()->get_image(TextureTypes::Specular, &specularMap))
    {
      setSpecularMap(&specularMap);
    }
    if (processor->get_current_frame()->get_image(TextureTypes::Parallax, &parallaxMap))
    {
      setParallaxMap(&parallaxMap);
    }
    if (processor->get_current_frame()->get_image(TextureTypes::Occlussion, &occlusionMap))
    {
      setOcclusionMap(&occlusionMap);
    }

    bool useAlpha;

    switch (viewmode)
    {
      case ViewMode::NormalMap:
        useAlpha = processor->get_use_normal_alpha();
        break;
      case ViewMode::ParallaxMap:
        useAlpha = processor->get_use_parallax_alpha();
        break;
      case ViewMode::SpecularMap:
        useAlpha = processor->get_use_specular_alpha();
        break;
      case ViewMode::OcclusionMap:
        useAlpha = processor->get_use_occlusion_alpha();
        break;
      default:
        useAlpha = false;
    }

    transform.setToIdentity();
    QVector3D texPos = *processor->get_position();
    transform.translate(texPos);

    float scaleX = !processor->get_tile_x() ? 0.5 * m_image.width() : 1.5 * m_image.width();
    float scaleY = !processor->get_tile_y() ? 0.5 * m_image.height() : 1.5 * m_image.height();

    /* Adjust for retina and apply individual zoom*/
    scaleX *= devicePixelRatioF();
    scaleY *= devicePixelRatioF();

    transform.rotate(processor->get_rotation(), QVector3D(0, 0, 1));

    transform.scale(scaleX, scaleY, 1);
    float zoomX = processor->get_zoom();
    float zoomY = processor->get_zoom();
    transform.scale(zoomX, zoomY, 1);

    /* Start first pass */

    VAO.bind();

    if (processor->get_tile_x() || processor->get_tile_y())
    {
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }
    else
    {
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                      GL_CLAMP_TO_BORDER);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
                      GL_CLAMP_TO_BORDER);
    }

    glActiveTexture(GL_TEXTURE0);

    m_program.setUniformValue("transform", transform);
    m_program.setUniformValue("view", view);
    m_program.setUniformValue("projection", projection);
    m_program.setUniformValue("inv_transform", transform.inverted());
    m_program.setUniformValue("inv_view", view.inverted());
    m_program.setUniformValue("inv_projection", projection.inverted());
    m_program.setUniformValue("pixelsX", pixelsX);
    m_program.setUniformValue("pixelsY", pixelsY);
    m_program.setUniformValue("pixelSize", pixelSize);
    m_program.setUniformValue("selected", processor->get_selected());
    m_program.setUniformValue("textureScale", processor->get_zoom());
    float rotation = M_PI / 180.0 * processor->get_rotation();
    m_program.setUniformValue("rotation_angle", rotation + global_rotation);
    zoomX = processor->get_tile_x() ? 1.0 / 3 : 1;
    zoomY = processor->get_tile_y() ? 1.0 / 3 : 1;
    m_program.setUniformValue("ratio", QVector2D(1 / zoomX, 1 / zoomY));
    m_program.setUniformValue("useAlpha", useAlpha);
    m_texture->bind(0);
    m_program.setUniformValue("diffuse", 0);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, i1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, i2);
    m_normalTexture->bind(1);
    m_program.setUniformValue("normalMap", 1);
    m_parallaxTexture->bind(2);
    m_program.setUniformValue("parallaxMap", 2);
    m_specularTexture->bind(3);
    m_program.setUniformValue("specularMap", 3);
    m_occlusionTexture->bind(4);
    m_program.setUniformValue("occlussionMap", 4);
    m_program.setUniformValue("parallax", processor->get_is_parallax() &&
                                              viewmode == Preview);
    // m_texture->bind(0);

    current_vertices = processor->vertices[processor->get_current_frame_id()].data();
    m_program.setUniformValue("rect", QVector4D(current_vertices[3], current_vertices[8], current_vertices[14], current_vertices[4]));

    VBO.bind();
    if (processor->frame_mode == "Animation")
    {
      glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * 20, current_vertices);
    }
    else
    {
      float vertices[] = {
          -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, // bot left
          1.0f, -1.0f, 0.0f, 1.0f, 1.0f,  // bot right
          -1.0f, 1.0f, 0.0f, 0.0f, 0.0f,  // top left
          1.0f, 1.0f, 0.0f, 1.0f, 0.0f,   // top right
      };
      glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * 20, vertices);
    }
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    VBO.release();
  }

  /* Render light texture */
  m_program.release();
  QList<LightSource *> currentLightList;
  if (sample_light_list_used)
    currentLightList = *sampleLightList;
  else
  {
    foreach (ImageProcessor *processor, processorList)
    {
      foreach (LightSource *l, *processor->get_light_list_ptr())
      {
        currentLightList.append(l);
      }
    }
  }

  if (currentLightList.count() > 0)
  {
    foreach (LightSource *light, currentLightList)
    {
      float x = static_cast<float>(laigter.width()) * 0.125 / m_global_zoom;
      float y = static_cast<float>(laigter.height()) * 0.125 / m_global_zoom;
      /* Fix for retina */
      x *= devicePixelRatioF();
      y *= devicePixelRatioF();

      transform.setToIdentity();
      transform.translate(light->get_light_position());
      transform.scale(x, y, 1);
      lightProgram.bind();
      lightVAO.bind();

      lightProgram.setUniformValue("transform", transform);
      lightProgram.setUniformValue("view", view);
      lightProgram.setUniformValue("projection", projection);
      laigterTexture->bind(0);

      if (m_light)
      {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                        GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
                        GL_LINEAR);
        glActiveTexture(GL_TEXTURE0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                        GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
                        GL_CLAMP_TO_BORDER);
        lightProgram.setUniformValue("texture", 0);
        lightProgram.setUniformValue("pixelSize", 3.0 / x, 3.0 / y);
        lightProgram.setUniformValue("selected", currentLight == light);
        lightProgram.setUniformValue("zoom", m_global_zoom);
        light->get_diffuse_color().getRgbF(&r, &g, &b, nullptr);
        color = QVector3D(r, g, b);
        lightProgram.setUniformValue("lightColor", color);

        float vertices[] = {
            -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, // bot left
            1.0f, -1.0f, 0.0f, 1.0f, 1.0f,  // bot right
            -1.0f, 1.0f, 0.0f, 0.0f, 0.0f,  // top left
            1.0f, 1.0f, 0.0f, 1.0f, 0.0f,   // top right
        };

        VBO.bind();
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        VBO.release();
      }
    }
    lightProgram.release();
  }
  /* Render brush cursor */

  if (currentBrush && currentBrush->get_selected())
  {
    setCursor(Qt::BlankCursor);
    brushTexture->destroy();
    brushTexture->create();
    QImage b = currentBrush->getBrushSprite();
    brushTexture->setData(currentBrush->getBrushSprite());
    float x = static_cast<float>(brushTexture->width()) * 0.5f;
    float y = static_cast<float>(brushTexture->height()) * 0.5f;

    /* Fix for retina */
    x *= devicePixelRatioF();
    y *= devicePixelRatioF();

    QPointF cursor = mapFromGlobal(QCursor::pos());
    cursor = LocalToWorld(cursor);
    transform.setToIdentity();
    transform.translate(floor(cursor.x()), floor(cursor.y()));
    transform.scale(x, y, 1);
    cursorProgram.bind();
    lightVAO.bind();
    cursorProgram.setUniformValue("transform", transform);
    cursorProgram.setUniformValue("projection", projection);
    cursorProgram.setUniformValue("view", view);
    brushTexture->bind(0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glActiveTexture(GL_TEXTURE0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    cursorProgram.setUniformValue("texture", 0);
    cursorProgram.setUniformValue("scale", processor->get_zoom());
    cursorProgram.setUniformValue("pixelSize", 1.0 / brushTexture->width(), 1.0 / brushTexture->height());
    cursorProgram.setUniformValue("pixelated", false);
    cursorProgram.setUniformValue("zoom", m_global_zoom);

    VBO.bind();
    float vertices[] = {
        -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, // bot left
        1.0f, -1.0f, 0.0f, 1.0f, 1.0f,  // bot right
        -1.0f, 1.0f, 0.0f, 0.0f, 0.0f,  // top left
        1.0f, 1.0f, 0.0f, 1.0f, 0.0f,   // top right
    };
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * 20, vertices);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    cursorProgram.release();
  }
  else
    setCursor(Qt::ArrowCursor);
}

void OpenGlWidget::resizeGL(int w, int h)
{
  w *= devicePixelRatioF();
  h *= devicePixelRatioF();
  sx = (float)m_image.width() / w;
  sy = (float)m_image.height() / h;
  need_to_update = true;
  m_width = w;
  m_height = h;
}

void OpenGlWidget::setImage(QImage *image)
{
  if (m_texture->isCreated())
    m_texture->destroy();

  m_texture->create();
  m_texture->setData(*image);
  sx = (float)image->width() / m_width;
  sy = (float)image->height() / m_height;
  pixelsX = image->width();
  pixelsY = image->height();

  m_texture->generateMipMaps();
}

void OpenGlWidget::setNormalMap(QImage *image)
{
  m_normalTexture->destroy();
  if (m_normalTexture->create())
    m_normalTexture->setData(*image);

  m_normalTexture->generateMipMaps();
}

void OpenGlWidget::setOcclusionMap(QImage *image)
{
  m_occlusionTexture->destroy();
  m_occlusionTexture->create();
  m_occlusionTexture->setData(*image);

  m_occlusionTexture->generateMipMaps();
}

void OpenGlWidget::setParallaxMap(QImage *image)
{
  m_parallaxTexture->destroy();
  m_parallaxTexture->create();
  m_parallaxTexture->setData(*image);
  m_parallaxTexture->generateMipMaps();
}

void OpenGlWidget::setSpecularMap(QImage *image)
{
  m_specularTexture->destroy();
  if (m_specularTexture->create())
    m_specularTexture->setData(*image);
  m_specularTexture->generateMipMaps();
}

void OpenGlWidget::setZoom(float zoom)
{
  m_global_zoom = zoom;
  updateView();
}

void OpenGlWidget::setTileX(bool x)
{
  foreach (ImageProcessor *p, get_all_selected_processors())
    p->set_tile_x(x);

  need_to_update = true;
}

void OpenGlWidget::setTileY(bool y)
{
  foreach (ImageProcessor *p, get_all_selected_processors())
    p->set_tile_y(y);

  need_to_update = true;
}

void OpenGlWidget::setParallax(bool p)
{
  foreach (ImageProcessor *processor, get_all_selected_processors())
    processor->set_is_parallax(p);
  need_to_update = true;
}

void OpenGlWidget::wheelEvent(QWheelEvent *event)
{
  QPointF mouse_position = LocalToWorld(event->position());

  QPoint pixels = event->pixelDelta();
  QPoint degree = event->angleDelta();

  double zoom = 0;

  if (!pixels.isNull())
  {
    zoom = pixels.y() > 0 ? 1.05 : 0.95;
  }

  else if (!degree.isNull() && degree.y() != 0)
  {
    zoom = degree.y() > 0 ? 1.05 : 0.95;
  }

  if (zoom > 0)
  {

    float dx = (1 - 1.0 / zoom) * (mouse_position.x() + origin.x());
    float dy = (1 - 1.0 / zoom) * (mouse_position.y() + origin.y());

    origin -= QVector3D(dx, dy, 0);

    setZoom(zoom * m_global_zoom);
  }
}

void OpenGlWidget::resetZoom()
{
  origin = QVector3D(0, 0, 0);
  setZoom(1.0);
}

void OpenGlWidget::fitZoom()
{
  float x_min, x_max, y_min, y_max;

  /* Only take into account lights if in preview mode */

  if (viewmode == ViewMode::Preview)
  {
    QList<LightSource *> currentLightList;
    if (sample_light_list_used)
      currentLightList = *sampleLightList;
    else
    {
      foreach (ImageProcessor *processor, processorList)
      {
        foreach (LightSource *l, *processor->get_light_list_ptr())
          currentLightList.append(l);
      }
    }

    x_min = currentLightList.at(0)->get_light_position().x();
    x_max = x_min;
    y_min = currentLightList.at(0)->get_light_position().y();
    y_max = y_min;
    /* Get min and max from lights positions */
    foreach (LightSource *s, currentLightList)
    {
      float x = s->get_light_position().x();
      float y = s->get_light_position().y();
      if (x < x_min)
      {
        x_min = x;
      }
      if (x > x_max)
      {
        x_max = x;
      }
      if (y < y_min)
      {
        y_min = y;
      }
      if (y > y_max)
      {
        y_max = y;
      }
    }

    /*
   * Change the 0.125 if we change light icon size.
   * It comes from the 0.25 texture scale times 0.5 for each side
   */
    x_min -= laigter.width() * 0.125;
    x_max += laigter.width() * 0.125;
    y_min -= laigter.height() * 0.125;
    y_max += laigter.height() * 0.125;
  }
  else
  {
    x_min = get_current_processor()->get_position()->x();
    x_max = x_min;
    y_min = get_current_processor()->get_position()->y();
    y_max = y_min;
  }
  foreach (ImageProcessor *p, processorList)
  {
    float w = p->get_texture()->width() / 2.0;
    float h = p->get_texture()->height() / 2.0;
    if (x_min > p->get_position()->x() - w)
    {
      x_min = p->get_position()->x() - w;
    }
    if (x_max < p->get_position()->x() + w)
    {
      x_max = p->get_position()->x() + w;
    }
    if (y_min > p->get_position()->y() - h)
    {
      y_min = p->get_position()->y() - h;
    }
    if (y_max < p->get_position()->y() + h)
    {
      y_max = p->get_position()->y() + h;
    }
  }

  float dx = x_max - x_min;
  float dy = y_max - y_min;
  dx *= devicePixelRatioF();
  dy *= devicePixelRatioF();
  float zoom = m_width / dx;
  if (height() / dy < zoom)
  {
    zoom = m_height / dy;
  }
  setZoom(zoom);

  origin.setX(-0.5 * (x_max + x_min));
  origin.setY(-0.5 * (y_max + y_min));

  updateView();
}

float OpenGlWidget::getZoom()
{
  return m_global_zoom;
}

void OpenGlWidget::tabletEvent(QTabletEvent *event)
{
  if (currentBrush && currentBrush->get_selected())
  {
    currentBrush->setPressure(event->pressure());
  }
}

void OpenGlWidget::mousePressEvent(QMouseEvent *event)
{

  old_position = event->localPos();
  global_mouse_press_position = LocalToWorld(event->localPos());
  local_mouse_press_position = LocalToView(event->localPos());
  if (currentBrush && currentBrush->get_selected())
  {
    QPoint tpos = QPoint(floor(global_mouse_last_position.x()), floor(global_mouse_last_position.y()));
    oldPos = tpos;
    currentBrush->setProcessor(&processor);
    currentBrush->mousePress(tpos);
  }

  /* In rendering, we are reducing the size of the light by 0.25 */
  float lightWidth = (float)laigter.width() * 0.25;
  float lightHeight = (float)laigter.height() * 0.25;

  if (event->buttons() & (Qt::LeftButton | Qt::MiddleButton))
  {
    if (addLight)
    {
      set_add_light(true);
      return;
    }

    bool selected = false;
    /* We first check if we selected a light, and if not, we scan if we
         * selected a texture */
    if (sample_light_list_used)
    {
      foreach (LightSource *light, *sampleLightList)
      {
        lightPosition = light->get_light_position();
        if (qAbs(global_mouse_press_position.x() - lightPosition.x()) < 0.5 * lightWidth / m_global_zoom &&
            qAbs(global_mouse_press_position.y() - lightPosition.y()) < 0.5 * lightHeight / m_global_zoom && m_light)
        {
          lightSelected = true;
          select_light(light);
          break;
        }
      }
    }
    else
    {
      /* Loops for selecting textues */
      foreach (ImageProcessor *p, processorList)
      {
        currentLightList = p->get_light_list_ptr();
        foreach (LightSource *light, *currentLightList)
        {
          lightPosition = light->get_light_position();
          if (qAbs(global_mouse_press_position.x() - lightPosition.x()) < 0.5 * lightWidth &&
              qAbs(global_mouse_press_position.y() - lightPosition.y()) < 0.5 * lightHeight &&
              m_light)
          {
            lightSelected = true;
            select_light(light);
            break;
          }
        }
        if (lightSelected)
          break;
      }
    }

    if (!lightSelected)
    {
      if (QApplication::keyboardModifiers() != Qt::CTRL && QApplication::keyboardModifiers() != Qt::SHIFT)
        set_all_processors_selected(false);

      set_enabled_light_controls(false);
      for (int i = processorList.count() - 1; i >= 0; i--)
      {
        ImageProcessor *processor = processorList.at(i);
        processor->set_offset(QVector3D(global_mouse_press_position) - *processor->get_position());
        float w = processor->get_tile_x() ? 3.0 * processor->texture.width() : processor->texture.width();
        float h = processor->get_tile_y() ? 3.0 * processor->texture.height() : processor->texture.height();

        if (processor->getFrameMode() == "Animation")
        {
          w /= processor->getHFrames();
          h /= processor->getVFrames();
        }

        if (qAbs(global_mouse_press_position.x() - processor->get_position()->x()) < w * processor->get_zoom() * 0.5 &&
            qAbs(global_mouse_press_position.y() - processor->get_position()->y()) < h * processor->get_zoom() * 0.5 &&
            not selected)
        {
          set_processor_selected(processor, true);
          selected = true;
          QPoint point = global_mouse_press_position.toPoint();
          point.setY(-point.y());
          point = point - QPoint(processor->get_position()->x(), -processor->get_position()->y()) + QPoint(processor->texture.width() / 2.0, processor->texture.height() / 2.0);
          if (processor->frame_mode == "Sheet")
            processor->set_current_frame_id(processor->get_frame_at_point(point));
        }
      }
    }
    else
      set_enabled_light_controls(true);
  }
  else if (event->buttons() & Qt::RightButton)
  {
    int count;
    if (sample_light_list_used)
    {
      count = sampleLightList->count();
      if (addLight && sampleLightList->count() > 0)
      {
        foreach (LightSource *light, *sampleLightList)
        {
          if (light == currentLight)
            continue;

          lightPosition = light->get_light_position();
          if (qAbs(global_mouse_press_position.x() - lightPosition.x()) < lightWidth &&
              qAbs(global_mouse_press_position.y() - lightPosition.y()) < lightHeight &&
              m_light)
          {
            remove_light(light);
            break;
          }
        }
        if (count == sampleLightList->count())
          stopAddingLight();
      }
    }
    else
    {
      bool removed = false;
      foreach (ImageProcessor *p, processorList)
      {
        currentLightList = p->get_light_list_ptr();
        count = currentLightList->count();
        foreach (LightSource *light, *currentLightList)
        {
          if (light == currentLight)
            continue;

          lightPosition = light->get_light_position();
          if (qAbs(global_mouse_press_position.x() - lightPosition.x()) < lightWidth &&
              qAbs(global_mouse_press_position.y() - lightPosition.y()) < lightHeight &&
              m_light)
          {
            remove_light(light);
            removed = true;
            break;
          }
        }
        if (removed)
          break;
      }
      if (!removed)
        stopAddingLight();
    }
  }
  need_to_update = true;
}

void OpenGlWidget::mouseMoveEvent(QMouseEvent *event)
{

  global_mouse_last_position = LocalToWorld(event->localPos());
  local_mouse_last_position = LocalToView(event->localPos());
  QVector3D newLightPos(global_mouse_last_position.x(), global_mouse_last_position.y(), currentLight->get_height());

  if (addLight)
  {
    update_light_position(newLightPos);
    need_to_update = true;
    return;
  }

  if (event->buttons() & Qt::LeftButton)
  {
    /* If shift pressed, rotate canvas*/

    if (QApplication::keyboardModifiers() == Qt::SHIFT)
    {
      QVector3D new_point = QVector3D(local_mouse_last_position).normalized();
      QVector3D prev_point = QVector3D(local_mouse_press_position).normalized();
      float delta_rotation = acos(QVector3D::dotProduct(new_point, prev_point));
      if (prev_point.x() > 0)
      {
        delta_rotation *= prev_point.y() < new_point.y() ? 1 : -1;
      }
      else
      {
        delta_rotation *= prev_point.y() < new_point.y() ? -1 : 1;
      }
      if (!std::isnan(delta_rotation))
      {
        global_rotation += delta_rotation;
        global_rotation = (UnwrapAngle(global_rotation));
        float fixed_angle = FixAngle(global_rotation);
        if (fixed_angle == global_rotation)
        {
          local_mouse_press_position = local_mouse_last_position;
        }
        global_rotation = fixed_angle;
        updateView();
      }
    }
    else if (currentBrush && currentBrush->get_selected() && !lightSelected && event->buttons() & Qt::LeftButton)
    {
      QPoint tpos = QPoint(floor(global_mouse_last_position.x()), floor(global_mouse_last_position.y()));
      if (abs(oldPos.x() - tpos.x()) + abs(oldPos.y() - tpos.y()) > 1)
      {
        if (event->source() != Qt::MouseEventSynthesizedByQt)
        {
          currentBrush->setPressure(0.5);
        }
        if (event->source() != Qt::MouseEventSynthesizedByQt)
        {
          currentBrush->setPressure(0.5);
        }
        currentBrush->mouseMove(oldPos, tpos);
        oldPos = tpos;
      }
    }
    else
    {
      foreach (ImageProcessor *processor, processorList)
      {
        /* This check is to move ligths instead of processor if light is above processor */
        if (lightSelected)
        {
          update_light_position(newLightPos);
          break;
        }
        else if (processor->get_selected())
        {
          /* Move */
          QVector3D new_position((int)(global_mouse_last_position.x() - processor->get_offset()->x()),
                                 (int)(global_mouse_last_position.y() - processor->get_offset()->y()), 0.0);
          processor->set_position(new_position);
        }
      }
    }
    need_to_update = true;
  }
  else if (event->buttons() & Qt::MiddleButton)
  {
    origin += QVector3D(global_mouse_last_position - global_mouse_press_position);
    updateView();

    need_to_update = true;
  }

  if ((currentBrush && currentBrush->get_selected()) ||
      cursor() != QCursor(Qt::ArrowCursor))
    need_to_update = true;
}

float OpenGlWidget::UnwrapAngle(float angle)
{
  if (angle < 0)
  {
    angle += 2 * M_PI;
  }
  return fmod(angle, 2 * M_PI);
}

float OpenGlWidget::FixAngle(float angle, int step, float tol)
{
  for (float i = 0; i < 2 * M_PI; i += M_PI / step)
  {
    if (abs(angle - i) < tol * M_PI / 180.0)
    {
      angle = i;
      break;
    }
  }
  return angle;
}

void OpenGlWidget::updateView()
{
  view.setToIdentity();
  origin.setZ(0);
  view.scale(m_global_zoom);
  view.rotate(global_rotation * 180 / M_PI, 0, 0, 1);
  view.translate(origin);
  need_to_update = true;
}

void OpenGlWidget::update_light_position(QVector3D new_pos)
{
  lightPosition.setX(new_pos.x());
  lightPosition.setY(new_pos.y());
  lightPosition.setZ(new_pos.z());

  currentLight->set_light_position(lightPosition);
}

void OpenGlWidget::mouseReleaseEvent(QMouseEvent *event)
{
  lightSelected = false;
  if (currentBrush && currentBrush->get_selected() && !lightSelected && event->buttons() & Qt::LeftButton)
  {
    currentBrush->mouseRelease(QPoint(0, 0));
  }
}

void OpenGlWidget::setLight(bool light)
{
  m_light = light;
  need_to_update = true;
}

void OpenGlWidget::setParallaxHeight(int height)
{
  parallax_height = height / 1000.0;
  need_to_update = true;
}

void OpenGlWidget::setLightColor(QColor color)
{
  currentLight->set_diffuse_color(color);
  need_to_update = true;
}

void OpenGlWidget::setSpecColor(QColor color)
{
  currentLight->set_specular_color(color);
  need_to_update = true;
}

void OpenGlWidget::setBackgroundColor(QColor color)
{
  backgroundColor = color;
  need_to_update = true;
}

void OpenGlWidget::setLightHeight(float height)
{
  lightPosition = currentLight->get_light_position();
  lightPosition.setZ(height);
  currentLight->set_light_position(lightPosition);
  need_to_update = true;
}

void OpenGlWidget::setLightAnimate(bool animate)
{
  currentLight->set_animate(animate);
  need_to_update = true;
}

void OpenGlWidget::setLightSpeed(float speed)
{
  currentLight->set_speed(speed);
  need_to_update = true;
}

void OpenGlWidget::setLightIntensity(float intensity)
{
  currentLight->set_diffuse_intensity(intensity);
  need_to_update = true;
}

void OpenGlWidget::setSpecIntensity(float intensity)
{
  currentLight->set_specular_intensity(intensity);
  need_to_update = true;
}

void OpenGlWidget::setSpecScatter(int scatter)
{
  currentLight->set_specular_scatter(scatter);
  need_to_update = true;
}

void OpenGlWidget::setAmbientColor(QColor color)
{
  ambientColor = color;
  need_to_update = true;
}

void OpenGlWidget::setAmbientIntensity(float intensity)
{
  ambientIntensity = intensity;
  need_to_update = true;
}

void OpenGlWidget::setPixelated(bool pixelated)
{
  m_pixelated = pixelated;
  need_to_update = true;
}

void OpenGlWidget::setToon(bool toon)
{
  m_toon = toon;
  need_to_update = true;
}

void OpenGlWidget::setPixelSize(int size) { pixelSize = size; }

QImage OpenGlWidget::renderBuffer() { return grabFramebuffer(); }

QImage OpenGlWidget::calculate_preview(bool fullPreview)
{
  QImage renderedPreview;
  if (!fullPreview)
  {
    QString aux;
    QImage n;
    QString suffix;
    QFileInfo info;

    if (processor->get_current_frame()->get_image(TextureTypes::Diffuse, &m_image))
    {
      setImage(&m_image);
    }
    if (processor->get_current_frame()->get_image(TextureTypes::Normal, &normalMap))
    {
      setNormalMap(&normalMap);
    }
    if (processor->get_current_frame()->get_image(TextureTypes::Specular, &specularMap))
    {
      setSpecularMap(&specularMap);
    }
    if (processor->get_current_frame()->get_image(TextureTypes::Parallax, &parallaxMap))
    {
      setParallaxMap(&parallaxMap);
    }
    if (processor->get_current_frame()->get_image(TextureTypes::Occlussion, &occlusionMap))
    {
      setOcclusionMap(&occlusionMap);
    }

    int w = m_image.width() * devicePixelRatioF();
    int h = m_image.height() * devicePixelRatioF();
    int m_width = (int(w / this->m_width) + 1) * this->m_width;
    int m_height = (int(h / this->m_height) + 1) * this->m_height;
    QOpenGLFramebufferObject frameBuffer(m_width, m_height);

    QVector3D texPos = *processor->get_position();

    QMatrix4x4 transform, projection, view;

    projection.setToIdentity();
    projection.ortho(-0.5 * w, m_width - 0.5 * w, -m_height + 0.5 * h, 0.5 * h, -1.0, 1.0);

    transform.setToIdentity();
    transform.translate(texPos);

    float scaleX = 0.5 * w;
    float scaleY = 0.5 * h;

    /* Adjust for retina */
    scaleX *= devicePixelRatioF();
    scaleY *= devicePixelRatioF();

    transform.scale(scaleX, scaleY, 1);

    view.setToIdentity();
    view.translate(-texPos);

    /* Start first pass */
    frameBuffer.bind();

    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glViewport(0, 0, m_width, m_height);
    m_program.bind();

    VAO.bind();

    int i1 = m_pixelated ? GL_NEAREST_MIPMAP_NEAREST
                         : GL_LINEAR_MIPMAP_LINEAR;
    int i2 = m_pixelated ? GL_NEAREST : GL_LINEAR;

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, i1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, i2);

    if (processor->get_tile_x() || processor->get_tile_y())
    {
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }
    else
    {
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                      GL_CLAMP_TO_BORDER);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
                      GL_CLAMP_TO_BORDER);
    }

    glActiveTexture(GL_TEXTURE0);
    m_program.setUniformValue("view_mode", Preview);

    m_program.setUniformValue("transform", transform);
    m_program.setUniformValue("view", view);
    m_program.setUniformValue("projection", projection);
    m_program.setUniformValue("inv_transform", transform.inverted());
    m_program.setUniformValue("inv_view", view.inverted());
    m_program.setUniformValue("inv_projection", projection.inverted());

    m_program.setUniformValue("pixelsX", pixelsX);
    m_program.setUniformValue("pixelsY", pixelsY);
    m_program.setUniformValue("pixelSize", pixelSize);
    m_program.setUniformValue("pixelated", m_pixelated);
    m_program.setUniformValue("toon", m_toon);
    m_program.setUniformValue("selected", false);
    m_program.setUniformValue("ratio", QVector2D(1, 1));
    m_program.setUniformValue("zoom", float(1.0));

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, i1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, i2);

    m_texture->bind(0);
    m_program.setUniformValue("texture", 0);

    m_normalTexture->bind(1);
    m_program.setUniformValue("normalMap", 1);

    m_parallaxTexture->bind(2);
    m_program.setUniformValue("parallaxMap", 2);

    m_specularTexture->bind(3);
    m_program.setUniformValue("specularMap", 3);

    m_occlusionTexture->bind(4);
    m_program.setUniformValue("occlusionMap", 4);

    scaleX = !processor->get_tile_x() ? sx : 1;
    scaleY = !processor->get_tile_y() ? sy : 1;

    m_program.setUniformValue("viewPos", QVector3D(-texPos.x(), -texPos.y(), 1));
    m_program.setUniformValue("parallax", processor->get_is_parallax());
    m_program.setUniformValue("height_scale", parallax_height);

    m_program.setUniformValue("viewport_size", QVector2D(m_width, m_height));

    apply_light_params(projection, view);
    m_texture->bind(0);

    VBO.bind();
    float vertices[] = {
        -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, // bot left
        1.0f, -1.0f, 0.0f, 1.0f, 1.0f,  // bot right
        -1.0f, 1.0f, 0.0f, 0.0f, 0.0f,  // top left
        1.0f, 1.0f, 0.0f, 1.0f, 0.0f,   // top right
    };
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * 20, vertices);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    m_program.release();
    frameBuffer.release();

    renderedPreview = frameBuffer.toImage().copy(0, 0, w, h);

    if (m_autosave)
    {
      if (exportBasePath == "")
      {
        info = QFileInfo(processor->get_current_frame()->get_file_name());
        suffix = info.completeSuffix();
        if (!QImageWriter::supportedImageFormats().contains(suffix.toUtf8()))
        {
          suffix = "png";
        }
        aux = processor->m_absolute_path + "/" + info.baseName() + "_v." +
              suffix;
      }
      else
      {
        info = QFileInfo(processor->get_current_frame()->get_file_name());
        suffix = info.completeSuffix();
        aux =
            exportBasePath + "/" + info.baseName() + "_v." + suffix;
        int i = 1;
        while (QFileInfo::exists(aux))
        {
          aux = exportBasePath + "/" + info.baseName() + "(" + QString::number(++i) + ")" + "_v." + suffix;
        }
      }
      renderedPreview.save(aux);
    }
  }
  else
  {
    QOpenGLFramebufferObject frameBuffer(m_width, m_height);
    frameBuffer.bind();
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    QVector3D color;
    float r, g, b;
    GLfloat bkColor[4];
    glGetFloatv(GL_COLOR_CLEAR_VALUE, bkColor);

    int i1 = m_pixelated ? GL_NEAREST_MIPMAP_NEAREST : GL_LINEAR_MIPMAP_LINEAR;
    int i2 = m_pixelated ? GL_NEAREST : GL_LINEAR;
    int xmin = m_width, xmax = 0, ymin = m_height, ymax = 0;

    QMatrix4x4 transform;

    m_program.setUniformValue("view_mode", Preview);
    m_program.setUniformValue("pixelated", m_pixelated);
    m_program.setUniformValue("toon", m_toon);
    backgroundColor.getRgbF(&r, &g, &b, nullptr);
    color = QVector3D(bkColor[0], bkColor[1], bkColor[2]);
    m_program.setUniformValue("outlineColor", color);
    m_program.setUniformValue("selected", false);
    m_program.setUniformValue("viewPos", QVector3D(0, 0, 1));
    m_program.setUniformValue("height_scale", parallax_height);
    m_program.setUniformValue("blend_factor", static_cast<float>(blend_factor / 100.0));
    m_program.setUniformValue("zoom", m_global_zoom);

    foreach (ImageProcessor *processor, processorList)
    {
      QPointF tex_position(processor->get_position()->x(), processor->get_position()->y());
      QPointF local_tex_position = WorldToLocal(tex_position);
      QSize tex_size(processor->get_texture()->size());
      /* Calculate positions for cropping after rendering */
      int xi = local_tex_position.x() - tex_size.width() / 2;
      int xf = local_tex_position.x() + tex_size.width() / 2;
      int yi = local_tex_position.y() - tex_size.height() / 2;
      int yf = local_tex_position.y() + tex_size.height() / 2;

      if (processor->get_tile_x())
      {
        xmin = 0;
        xmax = m_width - 1;
      }
      else
      {
        if (xi < xmin)
          xmin = xi;
        if (xf > xmax)
          xmax = xf;
      }

      if (processor->get_tile_y())
      {
        ymin = 0;
        ymax = m_height - 1;
      }
      else
      {
        if (yi < ymin)
          ymin = yi;
        if (yf > ymax)
          ymax = yf;
      }

      if (processor->get_current_frame()->get_image(TextureTypes::Diffuse, &m_image))
      {
        setImage(&m_image);
      }
      if (processor->get_current_frame()->get_image(TextureTypes::Normal, &normalMap))
      {
        setNormalMap(&normalMap);
      }
      if (processor->get_current_frame()->get_image(TextureTypes::Specular, &specularMap))
      {
        setSpecularMap(&specularMap);
      }
      if (processor->get_current_frame()->get_image(TextureTypes::Parallax, &parallaxMap))
      {
        setParallaxMap(&parallaxMap);
      }
      if (processor->get_current_frame()->get_image(TextureTypes::Occlussion, &occlusionMap))
      {
        setOcclusionMap(&occlusionMap);
      }

      transform.setToIdentity();

      QVector3D texPos = *processor->get_position();
      if (processor->get_tile_x())
        texPos.setX(0);
      if (processor->get_tile_y())
        texPos.setY(0);

      transform.translate(texPos);
      float scaleX = !processor->get_tile_x() ? sx : 1;
      float scaleY = !processor->get_tile_y() ? sy : 1;
      transform.scale(scaleX, scaleY, 1);
      float zoomX = !processor->get_tile_x() ? processor->get_zoom() : 1;
      float zoomY = !processor->get_tile_y() ? processor->get_zoom() : 1;
      transform.scale(zoomX, zoomY, 1);

      /* Start first pass */
      m_program.bind();
      VAO.bind();

      if (processor->get_tile_x() || processor->get_tile_y())
      {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
      }
      else
      {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                        GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
                        GL_CLAMP_TO_BORDER);
      }

      glActiveTexture(GL_TEXTURE0);
      m_program.setUniformValue("transform", transform);
      m_program.setUniformValue("pixelsX", pixelsX);
      m_program.setUniformValue("pixelsY", pixelsY);
      m_program.setUniformValue("pixelSize", pixelSize);

      scaleX = processor->get_tile_x() ? sx : 1;
      scaleY = processor->get_tile_y() ? sy : 1;
      zoomX = processor->get_tile_x() ? processor->get_zoom() : 1;
      zoomY = processor->get_tile_y() ? processor->get_zoom() : 1;

      m_program.setUniformValue("ratio", QVector2D(1 / scaleX / zoomX, 1 / scaleY / zoomY));

      m_texture->bind(0);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      m_program.setUniformValue("diffuse", 0);

      m_normalTexture->bind(1);
      m_program.setUniformValue("normalMap", 1);

      m_parallaxTexture->bind(2);
      m_program.setUniformValue("parallaxMap", 2);

      m_specularTexture->bind(3);
      m_program.setUniformValue("specularMap", 3);

      m_occlusionTexture->bind(4);
      m_program.setUniformValue("occlusionMap", 4);

      m_program.setUniformValue("parallax",
                                processor->get_is_parallax() &&
                                    viewmode == Preview);
      m_program.setUniformValue("viewport_size", QVector2D(m_width, m_height));

      apply_light_params(projection, view);
      VBO.bind();
      float vertices[] = {
          -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, // bot left
          1.0f, -1.0f, 0.0f, 1.0f, 1.0f,  // bot right
          -1.0f, 1.0f, 0.0f, 0.0f, 0.0f,  // top left
          1.0f, 1.0f, 0.0f, 1.0f, 0.0f,   // top right
      };
      glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * 20, vertices);

      glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

      m_program.release();
    }

    renderedPreview = frameBuffer.toImage();
    QRect rect(QPoint(xmin, ymin), QPoint(xmax, ymax));
    renderedPreview = renderedPreview.copy(rect);
  }
  return renderedPreview;
}

QImage OpenGlWidget::get_preview(bool fullPreview, bool autosave,
                                 QString basePath)
{
  m_fullPreview = fullPreview;
  m_autosave = autosave;
  exportBasePath = basePath;
  export_render = true;
  need_to_update = true;
  while (export_render)
    QApplication::processEvents();

  return renderedPreview;
}

void OpenGlWidget::apply_light_params(QMatrix4x4 projection, QMatrix4x4 view)
{
  float r, g, b;
  QVector3D color;

  QList<LightSource *> currentLightList;
  if (sample_light_list_used)
    currentLightList = *sampleLightList;
  else
  {
    foreach (ImageProcessor *processor, processorList)
    {
      foreach (LightSource *l, *processor->get_light_list_ptr())
        currentLightList.append(l);
    }
  }

  int n = currentLightList.count();
  if (n == 0)
    return;

  m_program.setUniformValue("lightNum", n);
  for (int i = 0; i < n; i++)
  {
    LightSource *light = currentLightList.at(i);
    light->get_diffuse_color().getRgbF(&r, &g, &b, nullptr);
    color = QVector3D(r, g, b);
    QString Light = "Light[" + QString::number(i) + "]";
    if (light->get_animate())
    {
      need_to_update = true;
      float w = light->get_speed();
      QVector3D pos = light->get_light_position();
      float r = pos.length();
      float theeta = atan2(pos.y(), pos.x());
      theeta += 1.0/60.0 * w;
      light->set_light_position( QVector3D(
                                          r*cos(theeta),
                                          r*sin(theeta),
                                          pos.z()
                              ));
    }
    QVector3D light_position = light->get_light_position();

    light_position.setZ(-light_position.z());

    m_program.setUniformValue((Light + ".lightPos").toUtf8().constData(), projection * view * light_position);
    m_program.setUniformValue((Light + ".lightColor").toUtf8().constData(),
                              color);
    light->get_specular_color().getRgbF(&r, &g, &b, nullptr);
    color = QVector3D(r, g, b);
    m_program.setUniformValue((Light + ".specColor").toUtf8().constData(),
                              color);
    m_program.setUniformValue(
        (Light + ".diffIntensity").toUtf8().constData(),
        light->get_diffuse_intensity());
    m_program.setUniformValue(
        (Light + ".specIntensity").toUtf8().constData(),
        light->get_specular_intesity());
    m_program.setUniformValue((Light + ".specScatter").toUtf8().constData(),
                              light->get_specular_scatter());
    ambientColor.getRgbF(&r, &g, &b, nullptr);
    color = QVector3D(r, g, b);
  }

  m_program.setUniformValue("ambientColor", color);
  m_program.setUniformValue("ambientIntensity", ambientIntensity);
}

void OpenGlWidget::set_add_light(bool add)
{
  if (add)
  {
    LightSource *l = new LightSource();
    l->copy_settings(currentLight);
    select_light(l);
    if (sample_light_list_used)
      sampleLightList->append(l);
    else
      currentLightList->append(l);

    need_to_update = true;
  }
  else if (addLight)
  {
    remove_light(currentLight);
  }

  addLight = add;
}

void OpenGlWidget::remove_light(LightSource *light)
{
  QList<LightSource *> *lList;
  if (sample_light_list_used)
    lList = sampleLightList;
  else
    lList = currentLightList;

  if (lList->count() > 1)
  {
    lList->removeOne(light);
    if (currentLight == light)
      select_light(lList->last());

    delete light;
    need_to_update = true;
  }
}

void OpenGlWidget::select_light(LightSource *light)
{
  currentLight = light;
  selectedLightChanged(currentLight);
}

QList<LightSource *> *OpenGlWidget::get_current_light_list_ptr()
{
  return currentLightList;
}

void OpenGlWidget::set_processor_list(QList<ImageProcessor *> list)
{
  processorList = list;
}

QList<ImageProcessor *> *OpenGlWidget::get_processor_list()
{
  return &processorList;
}

void OpenGlWidget::clear_processor_list()
{
  set_all_processors_selected(false);
  processorList.clear();
}

void OpenGlWidget::add_processor(ImageProcessor *p)
{
  processorList.append(p);
  set_current_processor(p);
}

void OpenGlWidget::set_current_processor(ImageProcessor *p) { processor = p; }

ImageProcessor *OpenGlWidget::get_current_processor() { return processor; }

void OpenGlWidget::set_processor_selected(ImageProcessor *processor,
                                          bool selected)
{
  processor_selected(processor, selected);
}

void OpenGlWidget::set_all_processors_selected(bool selected)
{
  foreach (ImageProcessor *processor, processorList)
    set_processor_selected(processor, selected);
}

QList<ImageProcessor *> OpenGlWidget::get_all_selected_processors()
{
  QList<ImageProcessor *> list;
  foreach (ImageProcessor *p, processorList)
  {
    if (p->get_selected())
      list.append(p);
  }
  return list;
}

void OpenGlWidget::set_view_mode(int mode)
{
  viewmode = mode;
  need_to_update = true;
}

void OpenGlWidget::use_sample_light_list(bool l)
{
  sample_light_list_used = l;
  need_to_update = true;
}

void OpenGlWidget::set_current_light_list(QList<LightSource *> *list)
{
  currentLightList = list;
  select_light(currentLightList->last());
  need_to_update = true;
}

QPointF OpenGlWidget::LocalToView(QPointF local)
{
  QPointF view;
  view.setX(local.x() * devicePixelRatioF() - 0.5 * m_width);
  view.setY(-local.y() * devicePixelRatioF() + 0.5 * m_height);
  return view;
}

QPointF OpenGlWidget::LocalToWorld(QPointF local)
{
  QVector3D local_position = QVector3D(LocalToView(local));
  QVector3D world_position = view.inverted() * local_position;
  return QPointF(world_position.x(), world_position.y());
}

QPointF OpenGlWidget::WorldToLocal(QPointF world)
{
  QVector3D world_position(world);
  QVector3D view_position = view * world_position;
  QVector3D local_position;
  local_position.setX((view_position.x() + 0.5 * m_width) / devicePixelRatioF());
  local_position.setY((view_position.y() + 0.5 * m_height) / devicePixelRatioF());
  return QPointF(local_position.x(), local_position.y());
}
