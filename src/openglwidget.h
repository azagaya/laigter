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

#include "geometryengine.h"

class OpenGlWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
public:
    OpenGlWidget(QWidget *parent = nullptr);
public slots:
    void setPixmap(QPixmap pixmap);
protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width, int height) override;
private:
    GLuint shaderProgram, vertexShader, fragmentShader;
    QOpenGLTexture *m_texture;
    QOpenGLVertexArrayObject VAO;
    QOpenGLBuffer VBO;
    QOpenGLShaderProgram m_program;

};

#endif // OPENGLWIDGET_H
