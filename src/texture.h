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
  quint64 revision() const {return m_revision;}
  bool IsLocked();

public slots:
  bool set_image(QImage i);
  bool get_image(QImage *dst);
  bool get_image_shared(QImage *dst)
  {
    if (mutex.tryLock())
    {
      *dst = image;
      mutex.unlock();
      return true;
    }
    return false;
  }
  void set_type(QString t);
  void lock();
  void unlock();
  QSize size();
  QString get_type();

private:
  QMutex mutex;
  QImage image;
  QString type;
  quint64 m_revision = 0;
};

#endif // TEXTURE_H
