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

class OpenGlWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    OpenGlWidget(QWidget *parent = nullptr);

public slots:
    void setImage(QImage image);
    void setNormalMap(QImage normalMap);
    void setParallaxMap(QImage parallaxMap);
    void setZoom(float zoom);
    void resetZoom();
    void fitZoom();
    float getZoom();
    void setLight(bool light);
    void setLightColor(QVector3D color);
    void setSpecColor(QVector3D color);
    void setLightHeight(float height);
    void setLightIntensity(float intensity);
    void setAmbientIntensity(float intensity);
    void setSpecIntensity(float intensity);
    void setSpecScatter(int scatter);
    void setAmbientColor(QVector3D color);
    void setBackgroundColor(QVector3D color);
    void setTileX(bool x);
    void setTileY(bool y);

    void setPixelated(bool pixelated);

    void setParallaxHeight(int height);
    void setParallax(bool p);
signals:
    void initialized();
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
    QOpenGLTexture *m_texture, *m_normalTexture, *laigterTexture, *m_parallaxTexture;
    QOpenGLVertexArrayObject VAO;
    QOpenGLVertexArrayObject lightVAO;
    QOpenGLBuffer VBO;
    QOpenGLShaderProgram m_program;
    QOpenGLShaderProgram lightProgram;
    QImage m_image, normalMap, parallaxMap, laigter;
    QVector3D lightPosition, lightColor, specColor, ambientColor, backgroundColor, texturePosition, textureOffset;
    bool m_light, tileX, tileY, m_parallax, m_pixelated;
    float sx, sy, parallax_height;
    float m_zoom;
    float diffIntensity, ambientIntensity, specIntensity, specScatter;
    int pixelsX, pixelsY;
    bool lightSelected;
};

#endif // OPENGLWIDGET_H
