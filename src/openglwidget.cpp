#include "openglwidget.h"
#include <QPainter>
#include <QDebug>
#include <QOpenGLVertexArrayObject>



OpenGlWidget::OpenGlWidget(QWidget *parent)
{
    m_zoom = 1.0;
    m_image = QImage("/home/pablo/Imágenes/ship.png");


}

void OpenGlWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glClearColor(1.0, 1.0, 1.0, 0.0);

    m_program.create();
    m_program.addShaderFromSourceFile(QOpenGLShader::Vertex,":/shaders/vshader.glsl");
    m_program.addShaderFromSourceFile(QOpenGLShader::Fragment,":/shaders/fshader.glsl");
    m_program.link();

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        -1.0f, -1.0f, 0.0f,     0.0f, 1.0f, // bot left
        1.0f, -1.0f, 0.0f,      1.0f, 1.0f, // bot right
        1.0f,  1.0f, 0.0f,      1.0f, 0.0f,  // top right
        -1.0f,  1.0f, 0.0f,     0.0f, 0.0f // top left
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


    m_texture = new QOpenGLTexture(m_image);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    VAO.release();
    VBO.release();


}


void OpenGlWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    QMatrix4x4 transform;

    transform.setToIdentity();
    transform.scale(sx,sy,1);
    transform.scale(m_zoom,m_zoom,1);

    m_program.bind();
    VAO.bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glActiveTexture(GL_TEXTURE0);
    m_texture->bind(0);
    m_program.setUniformValue("tex",0);
    m_program.setUniformValue("transform",transform);
    glDrawArrays(GL_QUADS, 0, 4);

    m_program.release();

}

void OpenGlWidget::resizeGL(int w, int h)
{
    sx = (float)m_image.width()/width();
    sy = (float)m_image.height()/height();
    update();
}


void OpenGlWidget::setImage(QImage image){
    m_image = image;
    m_texture->destroy();
    m_texture->create();
    m_texture->setData(m_image);
    sx = (float)m_image.width()/width();
    sy = (float)m_image.height()/height();
}

void OpenGlWidget::setZoom(float zoom){
    m_zoom = zoom;
    update();
}

void OpenGlWidget::wheelEvent(QWheelEvent *event)
{
    QPoint degree = event->angleDelta() / 8;

    if(!degree.isNull())
    {
        QPoint step = degree / 15;
        setZoom(step.y() > 0 ? m_zoom * 1.1 * step.y() : - m_zoom * 0.9 * step.y());
    }
}

void OpenGlWidget::resetZoom(){
    setZoom(1.0);
}

void OpenGlWidget::fitZoom(){
    float x,y,s;
    x = (float)m_image.width()/width();
    y = (float)m_image.height()/height();
    s = qMax(x,y);
    setZoom(1/s);
}

float OpenGlWidget::getZoom(){
    return m_zoom;
}



