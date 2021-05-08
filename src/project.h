#ifndef PROJECT_H
#define PROJECT_H

#include "src/image_processor.h"

#include <QJsonObject>
#include <QObject>

class Project : public QObject
{
  Q_OBJECT

public:
  QList<ImageProcessor *> *processorList;

public:
  explicit Project(QObject *parent = nullptr);
  QString GetCurrentPath();

public slots:
  bool save(QString path, QList<ImageProcessor *> processorList, QJsonObject general_settings = {});
  bool load(QString project_path, QList<ImageProcessor *> *p_list, QJsonObject *general_settings = nullptr);

private:
  QString m_path;
  const QStringList suffixes = {"", "_n", "_s", "_p", "_o", "_h",
                                "_d", "_neigh", "_sb", "_ob", "_co", "_to", "_no",
                                "_ho", "_so", "_po", "_oo"};

  const QStringList types = {
      "diffuse", "normal", "specular",
      "parallax", "occlussion", "heightmap",
      "distance", "neighbours", "specularBase",
      "occlussionBase", "color", "textureOverlay", "normalOverlay",
      "heightmapOverlay", "specularOverlay", "parallaxOverlay",
      "occlussionOverlay"};
};

#endif // PROJECT_H
