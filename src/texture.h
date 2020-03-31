#ifndef TEXTURE_H
#define TEXTURE_H

#include <QImage>
#include <QMutex>
#include <QObject>

class Texture : public QObject
{
  Q_OBJECT
  public:
  explicit Texture(QObject *parent = nullptr);
  explicit Texture(const Texture &T);
  Texture &operator=(const Texture &T);
  public slots:
      bool set_image(QImage i);
      bool get_image(QImage *dst);
      void set_type(QString t);
      QString get_type();
      void lock();
      void unlock();
      QSize size();


  signals:

  private:
      QMutex mutex;
      QImage image;
      QString type;
};

#endif // TEXTURE_H
