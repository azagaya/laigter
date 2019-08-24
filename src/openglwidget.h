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

#include <QObject>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLTexture>
#include <QOpenGLBuffer>
#include <QPixmap>
#include <QWheelEvent>
#include <QObject>
#include <QTimer>
#include <QList>

#include "lightsource.h"
#include "src/imageprocessor.h"

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
    OpenGlWidget(QWidget *parent = nullptr);
    bool need_to_update;
    ImageProcessor * processor;

public slots:
    void update();
    void force_update();
    void setImage(QImage *image);
    void setNormalMap(QImage *normalMap);
    void setParallaxMap(QImage *parallaxMap);
    void setSpecularMap(QImage *image);
    void setOcclusionMap(QImage *occlusionMap);
    void setZoom(float zoom);
    void resetZoom();
    void fitZoom();
    float getZoom();
    void setLight(bool light);
    void setLightColor(QColor color);
    void setSpecColor(QColor color);
    void setLightHeight(float height);
    void setLightIntensity(float intensity);
    void setAmbientIntensity(float intensity);
    void setSpecIntensity(float intensity);
    void setSpecScatter(int scatter);
    void setAmbientColor(QColor color);
    void setBackgroundColor(QColor color);
    void setTileX(bool x);
    void setTileY(bool y);

    void setPixelated(bool pixelated);
    void setPixelSize(int size);

    void setParallaxHeight(int height);
    void setParallax(bool p);

    QImage calculate_preview();
    QImage get_preview();

    void update_scene();

    QImage renderBuffer();

    void loadTextures();

    void set_add_light(bool add);
    void update_light_position(QVector3D new_pos);
    void remove_light(LightSource *light);
signals:
    void initialized();
    void selectedLightChanged(LightSource *light);
protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width, int height) override;
    void wheelEvent(QWheelEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    GLuint shaderProgram, vertexShader, fragmentShader;
    QOpenGLTexture *m_texture, *m_normalTexture, *laigterTexture, *m_parallaxTexture, *m_specularTexture, *m_occlusionTexture;
    QOpenGLVertexArrayObject VAO;
    QOpenGLVertexArrayObject lightVAO;
    QOpenGLBuffer VBO;
    QOpenGLShaderProgram m_program, simpleProgram, lightProgram;
    QImage *m_image, *normalMap, *parallaxMap, laigter, *specularMap, *occlusionMap, renderedPreview;
    QVector3D lightPosition, texturePosition, textureOffset;
    QTimer refreshTimer;
    bool m_light, tileX, tileY, m_parallax, m_pixelated;
    float sx, sy, parallax_height;
    float m_zoom;
    float diffIntensity, ambientIntensity, specIntensity, specScatter;
    int pixelsX, pixelsY, pixelSize;
    bool lightSelected;

    bool export_render, exportFullView, addLight;

    QColor lightColor, specColor, ambientColor, backgroundColor;
    QList <LightSource *> lightList;
    LightSource *currentLight;

    void select_light(LightSource *light);
    void apply_light_params();

};

#endif // OPENGLWIDGET_H
