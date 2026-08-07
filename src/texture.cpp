#include "texture.h"

Texture::Texture(QObject *parent) : QObject(parent) {}

/* QObject cannot be copied, so the copy starts as a fresh one with no parent
 * and only the data is taken from T */
Texture::Texture(const Texture &T) : QObject()
{
  image = T.image;
  type = T.type;
}

Texture &Texture::operator=(const Texture &T)
{
  image = T.image;
  type = T.type;
  return *this;
}

bool Texture::set_image(QImage i)
{
  if (mutex.tryLock())
  {
         image = i.copy();
    mutex.unlock();
    return true;
  }
  return false;
}

bool Texture::get_image(QImage *dst)
{
  if (mutex.tryLock())
  {
    *dst = image.copy();
    mutex.unlock();
    return true;
  }
  return false;
}

void Texture::set_type(QString t) { type = t; }

QString Texture::get_type() { return type; }

void Texture::lock() { mutex.lock(); }

void Texture::unlock() { mutex.unlock(); }

QSize Texture::size() { return image.size(); }
