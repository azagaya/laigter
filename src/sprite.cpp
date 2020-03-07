#include "sprite.h"

Sprite::Sprite()
{
  diffuse.set_type("diffuse");
  normal.set_type("normal");
  specular.set_type("specular");
  parallax.set_type("parallax");
  occlussion.set_type("occlussion");
}

Sprite::Sprite(const Sprite &S){
  diffuse.lock();
  diffuse = S.diffuse;
  diffuse.unlock();

  normal.lock();
  normal = S.normal;
  normal.unlock();

  specular.lock();
  specular = S.specular;
  specular.unlock();

  parallax.lock();
  parallax = S.parallax;
  parallax.unlock();

  occlussion.lock();
  occlussion = S.occlussion;
  occlussion.unlock();

  diffuse.set_type("diffuse");
  normal.set_type("normal");
  specular.set_type("specular");
  parallax.set_type("parallax");
  occlussion.set_type("occlussion");
}

Sprite& Sprite::operator=(const Sprite &S){
  diffuse.lock();
  diffuse = S.diffuse;
  diffuse.unlock();

  normal.lock();
  normal = S.normal;
  normal.unlock();

  specular.lock();
  specular = S.specular;
  specular.unlock();

  parallax.lock();
  parallax = S.parallax;
  parallax.unlock();

  occlussion.lock();
  occlussion = S.occlussion;
  occlussion.unlock();

  diffuse.set_type("diffuse");
  normal.set_type("normal");
  specular.set_type("specular");
  parallax.set_type("parallax");
  occlussion.set_type("occlussion");

  return *this;
}

void Sprite::set_image(QString type, QImage i){
  if (type == "diffuse"){
    diffuse.set_image(i);
  }else if (type == "normal"){
    normal.set_image(i);
  }else if (type == "specular"){
    specular.set_image(i);
  }else if (type == "parallax"){
    parallax.set_image(i);
  } else if (type == "occlussion"){
    occlussion.set_image(i);
  }
}

bool Sprite::get_image(QString type, QImage *dst){
  if (type == "diffuse"){
    return diffuse.get_image(dst);
  }else if (type == "normal"){
    return normal.get_image(dst);
  }else if (type == "specular"){
    return specular.get_image(dst);
  }else if (type == "parallax"){
    return parallax.get_image(dst);
  } else if (type == "occlussion"){
    return occlussion.get_image(dst);
  }
  return false;
}

void Sprite::set_texture(QString type, Texture t){
  if (type == "diffuse"){
    diffuse.lock();
    diffuse = t;
    diffuse.unlock();
  }else if (type == "normal"){
    normal.lock();
    normal = t;
    normal.unlock();
  }else if (type == "specular"){
    specular.lock();
    specular = t;
    specular.unlock();
  }else if (type == "parallax"){
    parallax.lock();
    parallax = t;
    parallax.unlock();
  } else if (type == "occlussion"){
    occlussion.lock();
    occlussion = t;
    occlussion.unlock();
  }
}

