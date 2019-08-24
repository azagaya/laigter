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

#include "openglwidget.h"
#include <QPainter>
#include <QDebug>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLFramebufferObject>
#include <QOpenGLVersionProfile>
#include <QApplication>

OpenGlWidget::OpenGlWidget(QWidget *parent)
{
    m_zoom = 1.0;

    laigter = QImage(":/images/laigter-texture.png");
    ambientColor = QColor("white");
    ambientIntensity = 0.8;
    lightPosition = QVector3D(0.7,0.7,0.3);
    m_light = true;
    m_parallax = false;
    parallax_height = 0.03;
    tileX = false;
    tileY = false;
    m_pixelated = false;
    lightSelected = false;
    
    currentLight = new LightSource();
    currentLight->set_light_position(lightPosition);
    QColor c;
    c.setRgbF(0.0,1,0.7);
    currentLight->set_diffuse_color(c);
    currentLight->set_specular_color(c);
    currentLight->set_specular_scatter(32);
    currentLight->set_diffuse_intensity(0.6);
    currentLight->set_specular_intensity(0.6);
    lightList.append(currentLight);

    currentLight = new LightSource();
    currentLight->set_light_position(lightPosition);
    c.setRgbF(0.0,1,0.7);
    currentLight->set_diffuse_color(c);
    currentLight->set_specular_color(c);
    currentLight->set_specular_scatter(32);
    currentLight->set_diffuse_intensity(0.6);
    currentLight->set_specular_intensity(0.6);
    lightList.append(currentLight);

    backgroundColor.setRgbF(0.2,0.2,0.3);

    pixelSize = 3;
    
    QSurfaceFormat format;
    format.setProfile( QSurfaceFormat::CompatibilityProfile);
    
    format.setSamples(32);
    
    setFormat(format);
    
    refreshTimer.setInterval(1.0/60.0*1000.0);
    refreshTimer.setSingleShot(false);
    
    connect(&refreshTimer,SIGNAL(timeout()),this,SLOT(force_update()));
    
    refreshTimer.start();
    
    need_to_update = true;
    export_render = false;
    exportFullView = false;
    
    addLight = false;

    this->setMouseTracking(true);
}

void OpenGlWidget::initializeGL()
{
    initializeOpenGLFunctions();
    
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glClearColor(backgroundColor.redF()*ambientColor.redF()*ambientIntensity,
                 backgroundColor.greenF()*ambientColor.greenF()*ambientIntensity,
                 backgroundColor.blueF()*ambientColor.blueF()*ambientIntensity,1.0);

    setUpdateBehavior(QOpenGLWidget::PartialUpdate);
    
    m_program.create();
    m_program.addShaderFromSourceFile(QOpenGLShader::Vertex,":/shaders/vshader.glsl");
    m_program.addShaderFromSourceFile(QOpenGLShader::Fragment,":/shaders/fshader.glsl");
    m_program.link();
    
    lightProgram.create();
    lightProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,":/shaders/lvshader.glsl");
    lightProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,":/shaders/lfshader.glsl");
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
    glVertexAttribPointer(static_cast<GLuint>(vertexLocation), 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
    glEnableVertexAttribArray(static_cast<GLuint>(vertexLocation));
    
    int texCoordLocation = m_program.attributeLocation("aTexCoord");
    glVertexAttribPointer(static_cast<GLuint>(texCoordLocation), 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                          (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(static_cast<GLuint>(texCoordLocation));
    
    VAO.release();
    VBO.release();
    
    lightVAO.bind();
    VBO.bind();
    vertexLocation = m_program.attributeLocation("aPos");
    glVertexAttribPointer(static_cast<GLuint>(vertexLocation), 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
    glEnableVertexAttribArray(static_cast<GLuint>(vertexLocation));
    
    texCoordLocation = m_program.attributeLocation("aTexCoord");
    glVertexAttribPointer(static_cast<GLuint>(texCoordLocation), 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                          (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(static_cast<GLuint>(texCoordLocation));
    lightVAO.release();
    VBO.release();
    
    initialized();
    
}

void OpenGlWidget::loadTextures(){
    m_image = processor->get_texture();
    parallaxMap = processor->get_parallax();
    specularMap = processor->get_specular();
    normalMap = processor->get_normal();
    occlusionMap = processor->get_occlusion();
    m_texture = new QOpenGLTexture(*m_image);
    pixelsX = m_image->width();
    pixelsY = m_image->height();
    m_parallaxTexture = new QOpenGLTexture(*parallaxMap);
    m_specularTexture = new QOpenGLTexture(*specularMap);
    m_normalTexture = new QOpenGLTexture(*normalMap);
    m_occlusionTexture = new QOpenGLTexture(*occlusionMap);
    laigterTexture = new QOpenGLTexture(laigter);
}

void OpenGlWidget::paintGL()
{
    if (need_to_update){
        need_to_update = false;
        update_scene();
    }
    if (export_render){
        export_render = false;
        renderedPreview = calculate_preview();
    }
}

void OpenGlWidget::update(){
    //need_to_update = true;
    QOpenGLWidget::update();
}

void OpenGlWidget::force_update(){
    if (need_to_update)
        update();
}

void OpenGlWidget::update_scene(){
    glClearColor(backgroundColor.redF()*ambientColor.redF()*ambientIntensity,
                 backgroundColor.greenF()*ambientColor.greenF()*ambientIntensity,
                 backgroundColor.blueF()*ambientColor.blueF()*ambientIntensity,1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    QMatrix4x4 transform;
    transform.setToIdentity();
    transform.translate(texturePosition);
    float scaleX = !tileX ? sx : 1;
    float scaleY = !tileY ? sy : 1;
    transform.scale(scaleX,scaleY,1);
    float zoomX = !tileX ? m_zoom : 1;
    float zoomY = !tileY ? m_zoom : 1;
    transform.scale(zoomX,zoomY,1);
    
    /* Start first pass */
    
    m_program.bind();
    
    VAO.bind();
    
    int i1 = m_pixelated ? GL_NEAREST_MIPMAP_NEAREST : GL_LINEAR_MIPMAP_LINEAR;
    int i2 = m_pixelated ? GL_NEAREST : GL_LINEAR;
    
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, i1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, i2);
    
    if (tileX || tileY){
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }else{
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    }
    
    glActiveTexture(GL_TEXTURE0);
    m_program.setUniformValue("light",m_light);
    m_texture->bind(0);
    m_program.setUniformValue("texture",0);
    m_program.setUniformValue("transform",transform);
    m_program.setUniformValue("pixelsX",pixelsX);
    m_program.setUniformValue("pixelsY",pixelsY);
    m_program.setUniformValue("pixelSize",pixelSize);
    m_program.setUniformValue("pixelated",m_pixelated);
    
    
    
    scaleX = tileX ? sx : 1;
    scaleY = tileY ? sy : 1;
    zoomX = tileX ? m_zoom : 1;
    zoomY = tileY ? m_zoom : 1;
    m_program.setUniformValue("ratio",QVector2D(1/scaleX/zoomX,1/scaleY/zoomY));
    
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, i1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, i2);
    
    m_normalTexture->bind(1);
    m_program.setUniformValue("normalMap",1);
    
    m_parallaxTexture->bind(2);
    m_program.setUniformValue("parallaxMap",2);
    
    m_specularTexture->bind(3);
    m_program.setUniformValue("specularMap",3);
    
    m_occlusionTexture->bind(4);
    m_program.setUniformValue("occlusionMap",4);
    
    m_program.setUniformValue("viewPos",QVector3D(0,0,1));
    m_program.setUniformValue("parallax",m_parallax);
    m_program.setUniformValue("height_scale",parallax_height);
    
    apply_light_params();
    m_texture->bind(0);
    glDrawArrays(GL_QUADS, 0, 4);
    
    m_program.release();
    
    /* Render light texture */
    

    if (lightList.count() > 0){
        foreach(LightSource *light, lightList){
            float x = static_cast<float>(laigter.width())/width();
            float y = static_cast<float>(laigter.height())/height();
            transform.setToIdentity();
            transform.translate(light->get_light_position());
            transform.scale(static_cast<float>(0.3)*x,static_cast<float>(0.3)*y,1);

            lightProgram.bind();
            lightVAO.bind();
            lightProgram.setUniformValue("transform",transform);

            laigterTexture->bind(0);
            if (m_light){

                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

                glActiveTexture(GL_TEXTURE0);

                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
                lightProgram.setUniformValue("texture",0);
                double r,g,b;
                light->get_diffuse_color().getRgbF(&r,&g,&b,nullptr);
                QVector3D color = QVector3D(r,g,b);
                lightProgram.setUniformValue("lightColor",color);
                glDrawArrays(GL_QUADS, 0, 4);

            }
        }
        lightProgram.release();
    }
}

void OpenGlWidget::resizeGL(int w, int h)
{
    sx = (float)m_image->width()/w;
    sy = (float)m_image->height()/h;
    need_to_update = true;
}


void OpenGlWidget::setImage(QImage *image){
    m_image = image;
    m_texture->destroy();
    m_texture->create();
    m_texture->setData(*m_image);
    sx = (float)m_image->width()/width();
    sy = (float)m_image->height()/height();
    pixelsX = image->width();
    pixelsY = image->height();
    
}

void OpenGlWidget::setNormalMap(QImage *image){
    normalMap = image;
    m_normalTexture->destroy();
    m_normalTexture->create();
    m_normalTexture->setData(*normalMap);
}

void OpenGlWidget::setOcclusionMap(QImage *image){
    occlusionMap = image;
    m_occlusionTexture->destroy();
    m_occlusionTexture->create();
    m_occlusionTexture->setData(*occlusionMap);
}

void OpenGlWidget::setParallaxMap(QImage *image){
    parallaxMap = image;
    m_parallaxTexture->destroy();
    m_parallaxTexture->create();
    m_parallaxTexture->setData(*parallaxMap);
}

void OpenGlWidget::setSpecularMap(QImage *image){
    specularMap = image;
    m_specularTexture->destroy();
    m_specularTexture->create();
    m_specularTexture->setData(*specularMap);
}

void OpenGlWidget::setZoom(float zoom){
    m_zoom = zoom;
    need_to_update = true;
}

void OpenGlWidget::setTileX(bool x){
    tileX = x;
    texturePosition.setX(0);
    need_to_update = true;
}

void OpenGlWidget::setTileY(bool y){
    tileY = y;
    texturePosition.setY(0);
    need_to_update = true;
}

void OpenGlWidget::setParallax(bool p){
    m_parallax = p;
    need_to_update = true;
}

void OpenGlWidget::wheelEvent(QWheelEvent *event)
{
    QPoint degree = event->angleDelta() / 8;
    
    if(!degree.isNull() && degree.y()!= 0)
    {
        QPoint step = degree/qAbs(degree.y());
        setZoom(step.y() > 0 ? m_zoom * 1.1 * step.y() : - m_zoom * 0.9 * step.y());
    }
}

void OpenGlWidget::resetZoom(){
    setZoom(1.0);
    texturePosition = QVector3D(0,0,0);
}

void OpenGlWidget::fitZoom(){
    float x,y,s;
    x = (float)m_image->width()/width();
    y = (float)m_image->height()/height();
    s = qMax(x,y);
    setZoom(1/s);
    texturePosition = QVector3D(0,0,0);
}

float OpenGlWidget::getZoom(){
    return m_zoom;
}

void OpenGlWidget::mousePressEvent(QMouseEvent *event){
    float lightWidth = (float)laigter.width()/width()*0.3;//en paintgl la imagen la escalamos por 0.3
    float lightHeight = (float)laigter.height()/height()*0.3;
    float mouseX = (float)event->localPos().x()/width()*2-1;
    float mouseY = -(float)event->localPos().y()/height()*2+1;
    if (event->buttons() & Qt::LeftButton)
    {
        if (addLight){
            set_add_light(true);
        }
        if (lightList.count() > 0){
            foreach (LightSource *light, lightList){
                lightPosition = light->get_light_position();
                if (qAbs(mouseX-lightPosition.x()) < lightWidth &&
                        qAbs(mouseY-lightPosition.y()) < lightHeight &&
                        m_light){
                    lightSelected = true;
                    currentLight = light;
                    break;
                }else{
                    textureOffset = QVector3D(mouseX,mouseY,0)- texturePosition;
                }
            }
        }
    }
    else if (event->buttons() & Qt::RightButton){
        if (addLight && lightList.count() > 0){
            foreach (LightSource *light, lightList){
                lightPosition = light->get_light_position();
                if (qAbs(mouseX-lightPosition.x()) < lightWidth &&
                        qAbs(mouseY-lightPosition.y()) < lightHeight &&
                        m_light){
                    remove_light(light);
                    break;
                }
            }
        }
    }
}

void OpenGlWidget::mouseMoveEvent(QMouseEvent *event){

    float mouseX = (float)event->localPos().x()/width()*2-1;
    float mouseY = -(float)event->localPos().y()/height()*2+1;
    QVector3D newLightPos(mouseX,mouseY,currentLight->get_height());

    if (addLight){
        update_light_position(newLightPos);
        need_to_update = true;
        return;
    }
    if (event->buttons() & Qt::LeftButton)
    {
        if (lightSelected){
            update_light_position(newLightPos);
        }else{
            if (!tileX)
                texturePosition.setX(mouseX-textureOffset.x());
            if (!tileY)
                texturePosition.setY(mouseY-textureOffset.y());
        }
        need_to_update = true;
    }
    else if (event->buttons() & Qt::RightButton){
        
    }
}

void OpenGlWidget::update_light_position(QVector3D new_pos){
    float lightWidth = (float)laigter.width()/width()*0.3;//en paintgl la imagen la escalamos por 0.3
    float lightHeight = (float)laigter.height()/height()*0.3;
    lightPosition.setX(new_pos.x());
    if (lightPosition.x() >= 1-lightWidth/2) lightPosition.setX(1-lightWidth/2);
    else if (lightPosition.x() < -1+lightWidth/2) lightPosition.setX(-1+lightWidth/2);
    lightPosition.setY(new_pos.y());
    if (lightPosition.y() > 1-lightHeight/2) lightPosition.setY(1-lightHeight/2);
    else if (lightPosition.y() < -1+lightHeight/2) lightPosition.setY(-1+lightHeight/2);
    currentLight->set_light_position(lightPosition);
}
void OpenGlWidget::mouseReleaseEvent(QMouseEvent *event){
    lightSelected = false;
}

void OpenGlWidget::setLight(bool light){
    m_light = light;
    need_to_update = true;
}

void OpenGlWidget::setParallaxHeight(int height){
    parallax_height = height/1000.0;
    need_to_update = true;
}

void OpenGlWidget::setLightColor(QColor color){
    currentLight->set_diffuse_color(color);
    need_to_update = true;
}

void OpenGlWidget::setSpecColor(QColor color){
    currentLight->set_specular_color(color);
    need_to_update = true;
}

void OpenGlWidget::setBackgroundColor(QColor color){
    backgroundColor = color;
    need_to_update = true;
}

void OpenGlWidget::setLightHeight(float height){
    lightPosition = currentLight->get_light_position();
    lightPosition.setZ(height);
    currentLight->set_light_position(lightPosition);
    need_to_update = true;
}

void OpenGlWidget::setLightIntensity(float intensity){
    currentLight->set_diffuse_intensity(intensity);
    need_to_update = true;
}

void OpenGlWidget::setSpecIntensity(float intensity){
    currentLight->set_specular_intensity(intensity);
    need_to_update = true;
}

void OpenGlWidget::setSpecScatter(int scatter){
    currentLight->set_specular_scatter(scatter);
    need_to_update = true;
}

void OpenGlWidget::setAmbientColor(QColor color){
    ambientColor = color;
    need_to_update = true;
}

void OpenGlWidget::setAmbientIntensity(float intensity){
    ambientIntensity = intensity;
    need_to_update = true;
}

void OpenGlWidget::setPixelated(bool pixelated){
    m_pixelated = pixelated;
    need_to_update = true;
}

void OpenGlWidget::setPixelSize(int size){
    pixelSize = size;
}

QImage OpenGlWidget::renderBuffer(){
    return grabFramebuffer();
}

QImage OpenGlWidget::calculate_preview(){
    if (!tileX && !tileY){
        QOpenGLFramebufferObjectFormat format;
        format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
        format.setSamples(16);
        QOpenGLFramebufferObject frameBuffer(m_image->width(), m_image->height(), format);
        
        QMatrix4x4 transform;
        transform.setToIdentity();

        /* Start first pass */
        
        frameBuffer.bind();
        glViewport(0, 0, m_image->width(), m_image->height());
        m_program.bind();
        
        VAO.bind();
        
        int i1 = m_pixelated ? GL_NEAREST_MIPMAP_NEAREST : GL_LINEAR_MIPMAP_LINEAR;
        int i2 = m_pixelated ? GL_NEAREST : GL_LINEAR;
        
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, i1);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, i2);
        
        if (tileX || tileY){
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        }else{
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        }
        
        glActiveTexture(GL_TEXTURE0);
        m_program.setUniformValue("light",m_light);
        m_texture->bind(0);
        m_program.setUniformValue("texture",0);
        m_program.setUniformValue("transform",transform);
        m_program.setUniformValue("pixelsX",pixelsX);
        m_program.setUniformValue("pixelsY",pixelsY);
        m_program.setUniformValue("pixelSize",pixelSize);
        m_program.setUniformValue("pixelated",m_pixelated);
        
        m_program.setUniformValue("ratio",QVector2D(1,1));
        
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, i1);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, i2);
        
        m_normalTexture->bind(1);
        m_program.setUniformValue("normalMap",1);
        
        m_parallaxTexture->bind(2);
        m_program.setUniformValue("parallaxMap",2);
        
        m_specularTexture->bind(3);
        m_program.setUniformValue("specularMap",3);
        
        m_occlusionTexture->bind(4);
        m_program.setUniformValue("occlusionMap",4);


        float scaleX = !tileX ? sx : 1;
        float scaleY = !tileY ? sy : 1;
        float zoomX = !tileX ? m_zoom : 1;
        float zoomY = !tileY ? m_zoom : 1;
        
        m_program.setUniformValue("viewPos",QVector3D(-texturePosition.x(),
                                                      -texturePosition.y(),1));
        m_program.setUniformValue("parallax",m_parallax);
        m_program.setUniformValue("height_scale",parallax_height);
        
        QVector3D pos((lightPosition.x()-texturePosition.x())/scaleX/zoomX,
                      (lightPosition.y()-texturePosition.y())/scaleY/zoomY,
                      lightPosition.z());
        
        apply_light_params();
        m_texture->bind(0);
        glDrawArrays(GL_QUADS, 0, 4);
        
        m_program.release();
        
        frameBuffer.release();
        return frameBuffer.toImage();
    } else {
        QOpenGLFramebufferObjectFormat format;
        format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
        format.setSamples(16);
        QOpenGLFramebufferObject frameBuffer(width(), height(), format);

        QMatrix4x4 transform;
        transform.setToIdentity();
        transform.translate(texturePosition);
        float scaleX = !tileX ? sx : 1;
        float scaleY = !tileY ? sy : 1;
        transform.scale(scaleX,scaleY,1);
        float zoomX = !tileX ? m_zoom : 1;
        float zoomY = !tileY ? m_zoom : 1;
        transform.scale(zoomX,zoomY,1);

        /* Start first pass */
        frameBuffer.bind();
        m_program.bind();

        VAO.bind();

        int i1 = m_pixelated ? GL_NEAREST_MIPMAP_NEAREST : GL_LINEAR_MIPMAP_LINEAR;
        int i2 = m_pixelated ? GL_NEAREST : GL_LINEAR;


        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, i1);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, i2);

        if (tileX || tileY){
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        }else{
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        }

        glActiveTexture(GL_TEXTURE0);
        m_program.setUniformValue("light",m_light);
        m_texture->bind(0);
        m_program.setUniformValue("texture",0);
        m_program.setUniformValue("transform",transform);
        m_program.setUniformValue("pixelsX",pixelsX);
        m_program.setUniformValue("pixelsY",pixelsY);
        m_program.setUniformValue("pixelSize",pixelSize);
        m_program.setUniformValue("pixelated",m_pixelated);



        scaleX = tileX ? sx : 1;
        scaleY = tileY ? sy : 1;
        zoomX = tileX ? m_zoom : 1;
        zoomY = tileY ? m_zoom : 1;
        m_program.setUniformValue("ratio",QVector2D(1/scaleX/zoomX,1/scaleY/zoomY));


        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, i1);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, i2);

        m_normalTexture->bind(1);
        m_program.setUniformValue("normalMap",1);

        m_parallaxTexture->bind(2);
        m_program.setUniformValue("parallaxMap",2);

        m_specularTexture->bind(3);
        m_program.setUniformValue("specularMap",3);

        m_occlusionTexture->bind(4);
        m_program.setUniformValue("occlusionMap",4);

        m_program.setUniformValue("viewPos",QVector3D(0,0,1));
        m_program.setUniformValue("parallax",m_parallax);
        m_program.setUniformValue("height_scale",parallax_height);

        apply_light_params();
        m_texture->bind(0);
        glDrawArrays(GL_QUADS, 0, 4);

        m_program.release();
        frameBuffer.release();

        return frameBuffer.toImage();

    }
}

QImage OpenGlWidget::get_preview(){
    export_render = true;
    need_to_update = true;
    while(export_render){
        QApplication::processEvents();
    }
    return renderedPreview;
}

void OpenGlWidget::apply_light_params(){
    double r,g,b;
    QVector3D color;
    if (lightList.count() == 0) return;
    m_program.setUniformValue("lightNum",lightList.count());
    for(int i=0; i < lightList.count() ; i++){
        lightList.at(i)->get_diffuse_color().getRgbF(&r,&g,&b,nullptr);
        color = QVector3D(r,g,b);
        QString Light = "Light["+QString::number(i)+"]";
        m_program.setUniformValue((Light+".lightPos").toUtf8().constData(),lightList.at(i)->get_light_position());
        m_program.setUniformValue((Light+".lightColor").toUtf8().constData(),color);
        lightList.at(i)->get_specular_color().getRgbF(&r,&g,&b,nullptr);
        color = QVector3D(r,g,b);
        m_program.setUniformValue((Light+".specColor").toUtf8().constData(),color);
        m_program.setUniformValue((Light+".diffIntensity").toUtf8().constData(),lightList.at(i)->get_diffuse_intensity());
        m_program.setUniformValue((Light+".specIntensity").toUtf8().constData(),lightList.at(i)->get_specular_intesity());
        m_program.setUniformValue((Light+".specScatter").toUtf8().constData(),lightList.at(i)->get_specular_scatter());
        ambientColor.getRgbF(&r,&g,&b,nullptr);
        color = QVector3D(r,g,b);
        m_program.setUniformValue("ambientColor",color);
        m_program.setUniformValue("ambientIntensity",ambientIntensity);
    }
}

void OpenGlWidget::set_add_light(bool add){
    addLight = add;
    if (addLight){
        LightSource *l = new LightSource();
        l->copy_settings(currentLight);
        currentLight = l;
        lightList.append(l);
        need_to_update = true;
    }else{
        remove_light(currentLight);
    }
}

void OpenGlWidget::remove_light(LightSource *light){
    if (lightList.count() > 1){
        lightList.removeOne(light);
        if (currentLight == light)
            currentLight = lightList.last();
        delete light;
        need_to_update = true;
    }
}
