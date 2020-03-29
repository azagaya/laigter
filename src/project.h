#ifndef PROJECT_H
#define PROJECT_H

#include "src/imageprocessor.h"
#include <QObject>

class Project : public QObject
{
  Q_OBJECT
  public:
  explicit Project(QObject *parent = nullptr);
  QList<ImageProcessor *> *processorList;

  public slots:
      bool save(QString path);
  signals:

};

#endif // PROJECT_H
