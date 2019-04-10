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
    void setZoom(float zoom);
    void resetZoom();
    void fitZoom();
    float getZoom();
    void setLight(bool light);
    void setLightColor(QVector3D color);
    void setLightHeight(float height);
    void setLightIntensity(float intensity);
    void setAmbientIntensity(float intensity);
    void setAmbientColor(QVector3D color);
    void setBackgroundColor(QVector3D color);
    void setTileX(bool x);
    void setTileY(bool y);
signals:
    void initialized();
protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width, int height) override;
    void wheelEvent(QWheelEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
private:
    GLuint shaderProgram, vertexShader, fragmentShader;
    QOpenGLTexture *m_texture, *m_normalTexture, *laigterTexture;
    QOpenGLVertexArrayObject VAO;
    QOpenGLVertexArrayObject lightVAO;
    QOpenGLBuffer VBO;
    QOpenGLShaderProgram m_program;
    QOpenGLShaderProgram lightProgram;
    QImage m_image, normalMap, laigter;
    QVector3D lightPosition, lightColor, ambientColor, backgroundColor;
    bool m_light, tileX, tileY;
    float sx, sy;
    float m_zoom;
    float diffIntensity, ambientIntensity;

};

#endif // OPENGLWIDGET_H
