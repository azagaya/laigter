#include "sprite.h"

Sprite::Sprite()
{
  textures.resize(16);
  neighours_paths.resize(3);
  neighours_paths[0].resize(3);
  neighours_paths[1].resize(3);
  neighours_paths[2].resize(3);
}

Sprite::Sprite(const Sprite &S)
{
  textures = S.textures;
  fileName = S.fileName;
  heightmapPath = S.heightmapPath;
  specularPath = S.specularPath;
  neighours_paths.resize(3);
  neighours_paths[0].resize(3);
  neighours_paths[1].resize(3);
  neighours_paths[2].resize(3);
}

Sprite &Sprite::operator=(const Sprite &S)
{
  textures = S.textures;
  fileName = S.fileName;
  heightmapPath = S.heightmapPath;
  specularPath = S.specularPath;
  neighours_paths.resize(3);
  neighours_paths[0].resize(3);
  neighours_paths[1].resize(3);
  neighours_paths[2].resize(3);
  return *this;
}

void Sprite::set_image(TextureTypes type, QImage i)
{
  int t = static_cast<int>(type);
  textures[t].set_image(i);
}

bool Sprite::get_image(TextureTypes type, QImage *dst)
{
  int t = static_cast<int>(type);
  return textures[t].get_image(dst);
}

void Sprite::set_texture(TextureTypes type, Texture t)
{
  int tex = static_cast<int>(type);
  textures[tex].lock();
  textures[tex] = t;
  textures[tex].unlock();
}

QSize Sprite::size() { return textures[0].size(); }

QString Sprite::get_file_name(){
  return fileName;
}
