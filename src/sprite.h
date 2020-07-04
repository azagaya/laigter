#ifndef SPRITE_H
#define SPRITE_H

#include "texture.h"

#include <QObject>

enum class TextureTypes
{
  Diffuse,
  Normal,
  Specular,
  Parallax,
  Occlussion,
  Heightmap,
  Distance,
  Neighbours,
  SpecularBase,
  OcclussionBase,
  Color,
  TextureOverlay,
  NormalOverlay,
  HeightmapOverlay,
  SpecularOverlay,
  ParallaxOverlay,
  OcclussionOverlay
};

class Sprite
{
public:
  QString fileName;
  QString specularPath = "";
  QString heightmapPath = "";
  QVector<QVector<QString>> neighbours_paths;

private:
  QVector<Texture> textures;

public:
  explicit Sprite();
  explicit Sprite(const Sprite &S);
  void set_image(TextureTypes type, QImage i);
  bool get_image(TextureTypes type, QImage *dst);
  void set_texture(TextureTypes type, Texture t);
  Sprite &operator=(const Sprite &S);
  QString get_file_name();
  QSize size();
};

#endif // SPRITE_H
