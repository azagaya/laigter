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

class OpenGlWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
public:
    OpenGlWidget(QWidget *parent = nullptr);
public slots:
    void setImage(QImage image);
    void setNormalMap(QImage normalMap);
    void setZoom(float zoom);
    void resetZoom();
    void fitZoom();
    float getZoom();
protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width, int height) override;
    void wheelEvent(QWheelEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
private:
    GLuint shaderProgram, vertexShader, fragmentShader;
    QOpenGLTexture *m_texture, *m_normalTexture;
    QOpenGLVertexArrayObject VAO;
    QOpenGLVertexArrayObject lightVAO;
    QOpenGLBuffer VBO;
    QOpenGLShaderProgram m_program;
    QOpenGLShaderProgram lightProgram;
    QImage m_image, normalMap;
    QVector3D lightPosition;
    float sx, sy;
    float m_zoom;

};

#endif // OPENGLWIDGET_H
