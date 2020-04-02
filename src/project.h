#ifndef PROJECT_H
#define PROJECT_H

#include "src/image_processor.h"

#include <QObject>

class Project : public QObject
{
  Q_OBJECT

public:
  QList<ImageProcessor *> *processorList;

public:
  explicit Project(QObject *parent = nullptr);

public slots:
  bool save(QString path);

private:
  const QStringList suffixes = {"", "_n", "_s", "_p", "_o", "_h",
                                "_d", "_neigh", "_sb", "_ob", "_to", "_no",
                                "_ho", "_so", "_po", "_oo"};

  const QStringList types = {
      "diffuse", "normal", "specular",
      "parallax", "occlussion", "heightmap",
      "distance", "neighbours", "specularBase",
      "occlussionBase", "textureOverlay", "normalOverlay",
      "heightmapOverlay", "specularOverlay", "parallaxOverlay",
      "occlussionOverlay"};
};

#endif // PROJECT_H
