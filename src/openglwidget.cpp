#include "openglwidget.h"
#include <QPainter>
#include <QDebug>
#include <QOpenGLVertexArrayObject>



OpenGlWidget::OpenGlWidget(QWidget *parent)
{
    //m_program = new QOpenGLShaderProgram();
}

void OpenGlWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.1, 0.1, 0.18, 0.0);

    m_program.create();
    m_program.addShaderFromSourceFile(QOpenGLShader::Vertex,":/shaders/vshader.glsl");
    m_program.addShaderFromSourceFile(QOpenGLShader::Fragment,":/shaders/fshader.glsl");
    m_program.link();

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,     0.0f, 0.0f, // bot left
        0.5f, -0.5f, 0.0f,      1.0f, 0.0f, // bot right
        0.5f,  0.5f, 0.0f,      1.0f, 1.0f,  // top right
        -0.5f,  0.5f, 0.0f,     0.0f, 1.0f // top left
    };

    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).

    VAO.bind();
    VBO.create();
    VBO.bind();

    VBO.allocate(vertices,sizeof(vertices));

    int vertexLocation = m_program.attributeLocation("aPos");
    glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(vertexLocation);

    int texCoordLocation = m_program.attributeLocation("aTexCoord");
    glVertexAttribPointer(texCoordLocation, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(texCoordLocation);

    m_program.bind();

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    VAO.release();
    VBO.release();


}


void OpenGlWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    m_program.bind();
    VAO.bind();
    m_texture = new QOpenGLTexture(QImage("/home/pablo/Imágenes/ship.png"));
    glActiveTexture(GL_TEXTURE0);
    m_texture->bind(0);
    m_program.setUniformValue("tex",0);
    glDrawArrays(GL_QUADS, 0, 4);
    m_program.release();

}

void OpenGlWidget::resizeGL(int w, int h)
{

}


void OpenGlWidget::setPixmap(QPixmap pixmap){
}



