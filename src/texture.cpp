#include "texture.h"

Texture::Texture(QObject *parent) : QObject(parent)
{

}

Texture::Texture(Texture &T){
  image = T.image;
  type = T.type;
}

Texture &Texture::operator=(const Texture &T){
  image = T.image;
  type = T.type;
  return *this;
}

bool Texture::set_image(QImage i){
  if (mutex.tryLock()){
    image = i.copy();
    mutex.unlock();
    return true;
  }
  return false;
}

bool Texture::get_image(QImage *dst){
  if (mutex.tryLock()){
    *dst = image.copy();
    mutex.unlock();
    return true;
  }
  return false;
}

void Texture::set_type(QString t){
  type = t;
}

QString Texture::get_type(){
  return type;
}

void Texture::lock(){
  mutex.lock();
}

void Texture::unlock(){
  mutex.unlock();
}

QSize Texture::size(){
  return  image.size();
}
