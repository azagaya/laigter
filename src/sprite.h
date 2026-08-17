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
  OcclussionOverlay,
  NUM_TEXTURE_TYPES
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
  bool get_image_shared(TextureTypes type, QImage *dst);
  quint64 get_revision(TextureTypes type) const {return textures[static_cast<int>(type)].revision();}
  bool IsLocked(TextureTypes type) {return textures[static_cast<int>(type)].IsLocked();}
  void set_texture(TextureTypes type, Texture t);
  Sprite &operator=(const Sprite &S);
  QString get_file_name();
  QSize size();
};

#endif // SPRITE_H
