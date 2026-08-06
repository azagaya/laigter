#ifndef BRUSHINTERFACE_H
#define BRUSHINTERFACE_H

#include <QObject>
#include <QtPlugin>

QT_BEGIN_NAMESPACE
class QImage;
class QPainter;
class QWidget;
class QPainterPath;
class QPoint;
class QRect;
class ImageProcessor;
QT_END_NAMESPACE

class BrushInterface
{
public:
  virtual void mousePress(const QPoint &pos) = 0;
  virtual void mouseMove(const QPoint &oldPos, const QPoint &newPos) = 0;
  virtual void mouseRelease(const QPoint &pos) = 0;
  virtual void setPressure(float pressure) = 0;
  virtual bool get_selected() = 0;
  virtual void set_selected(bool s) = 0;
  virtual QWidget *loadGUI(QWidget *parent = nullptr) = 0;
  virtual void setProcessor(ImageProcessor **processor) = 0;
  virtual QString getIcon() = 0;
  virtual QString getName() = 0;
  virtual QImage getBrushSprite() = 0;
  virtual QObject *getObject() = 0;

signals:
  void selected_changed(BrushInterface *brush);
};

#define BrushInterface_iid "org.azagaya.laigter.plugins.BrushInterface/1.0"

/* Plugins put this number in their metadata.json and laigter does not load
 * anything older. Bump it whenever plugins built for the previous one stop
 * working, like the qt6 port did, since qt5 plugins cannot be loaded at all.
 * A plugin can also say "dev" to skip the check while being worked on. */
#define LAIGTER_PLUGIN_API 2

Q_DECLARE_INTERFACE(BrushInterface, BrushInterface_iid)

#endif // BRUSHINTERFACE_H
