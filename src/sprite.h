#ifndef SPRITE_H
#define SPRITE_H

#include <QObject>

class Sprite : public QObject
{
  Q_OBJECT
  public:
  explicit Sprite(QObject *parent = nullptr);

  signals:

};

#endif // SPRITE_H
