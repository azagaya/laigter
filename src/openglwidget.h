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
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class OpenGlWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
public:
    OpenGlWidget(QWidget *parent = nullptr);
public slots:
    void setImage(QImage image);
    void setZoom(float zoom);
    void resetZoom();
    void fitZoom();
    float getZoom();
protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width, int height) override;
    void wheelEvent(QWheelEvent *event) override;
private:
    GLuint shaderProgram, vertexShader, fragmentShader;
    QOpenGLTexture *m_texture;
    QOpenGLVertexArrayObject VAO;
    QOpenGLBuffer VBO;
    QOpenGLShaderProgram m_program;
    QImage m_image;
    float sx, sy;
    float m_zoom;

};

#endif // OPENGLWIDGET_H
