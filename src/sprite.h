#ifndef SPRITE_H
#define SPRITE_H

#include <QObject>
#include "texture.h"

class Sprite
{
  public:
  explicit Sprite();
  explicit Sprite(const Sprite &S);


  QString fileName;
  QString specularPath = "";
  QString heightmapPath = "";

  QVector<QVector<QString>> neighours_paths;

  Sprite& operator=(const Sprite& S);
  void set_image(QString type, QImage i);
  bool get_image(QString type, QImage *dst);

  void set_texture(QString type, Texture t);
  Texture get_texture(QString type);

  QString get_file_name();

  QSize size();

  private:
  Texture diffuse;
  Texture normal;
  Texture specular;
  Texture parallax;
  Texture occlussion;

  /* This textures are needed to generate the maps */
  Texture heightmap;
  Texture distance;
  Texture neighbours;
  Texture specular_base;
  Texture occlussion_base;
};

#endif // SPRITE_H
