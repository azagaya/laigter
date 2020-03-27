#ifndef SPRITE_H
#define SPRITE_H

#include <QObject>
#include "texture.h"

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
  NormalOverlay,
  HeightmapOverlay,
  SpecularOverlay,
  ParallaxOverlay,
  OcclussionOverlay
};

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
  void set_image(TextureTypes type, QImage i);
  bool get_image(TextureTypes type, QImage *dst);

  void set_texture(TextureTypes type, Texture t);

  QString get_file_name();

  QSize size();

  private:
  QVector <Texture> textures;

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

  /* Overlay for painting with brushes, can be replaced by arrays to let multiple overlays in the future */
  Texture normal_overlay;
  Texture heightmap_overlay;
  Texture specular_overlay;
  Texture parallax_overlay;
  Texture occlussion_overlay;
};

#endif // SPRITE_H
