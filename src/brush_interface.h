#ifndef BRUSHINTERFACE_H
#define BRUSHINTERFACE_H

#include "src/processor_interface.h"

#include <QObject>
#include <QtPlugin>

QT_BEGIN_NAMESPACE
class QImage;
class QPainter;
class QWidget;
class QPainterPath;
class QPoint;
class QRect;
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
  virtual void setProcessor(ProcessorInterface *processor) = 0;
  virtual QString getIcon() = 0;
  virtual QString getName() = 0;
  virtual QImage getBrushSprite() = 0;
  virtual QObject *getObject() = 0;

signals:
  void selected_changed(BrushInterface *brush);
};

/* Moc bakes this into the plugin, so qobject_cast already refuses one built
 * against another version even before we look at the metadata. Bump it
 * together with LAIGTER_PLUGIN_API */
#define BrushInterface_iid "org.azagaya.laigter.plugins.BrushInterface/3.0"

/* Plugins put this number in their metadata.json and laigter only loads an
 * exact match, a newer plugin is as unusable as an older one. Bump it whenever
 * plugins built for the previous one stop working, like the qt6 port did.
 * A plugin can also say "dev" to skip the check while being worked on. */
#define LAIGTER_PLUGIN_API 3

Q_DECLARE_INTERFACE(BrushInterface, BrushInterface_iid)

#endif // BRUSHINTERFACE_H
