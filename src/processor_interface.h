#ifndef PROCESSOR_INTERFACE_H
#define PROCESSOR_INTERFACE_H

#include <QImage>
#include <QRect>
#include <QVector3D>

/* Everything a brush plugin is allowed to touch of the processor. Plugins
 * only need this header, so they no longer build laigter sources. Adding or
 * reordering anything here breaks already built plugins, so bump
 * LAIGTER_PLUGIN_API when you do. */
class ProcessorInterface
{
public:
  virtual ~ProcessorInterface() {}

  virtual QImage get_normal_overlay() = 0;
  virtual QImage get_texture_overlay() = 0;
  virtual QImage get_occlusion_overlay() = 0;
  virtual QImage get_parallax_overlay() = 0;
  virtual QImage get_specular_overlay() = 0;
  virtual QImage get_heightmap_overlay() = 0;

  virtual void set_normal_overlay(QImage no) = 0;
  virtual void set_texture_overlay(QImage to) = 0;
  virtual void set_occlussion_overlay(QImage oo) = 0;
  virtual void set_parallax_overlay(QImage po) = 0;
  virtual void set_specular_overlay(QImage so) = 0;
  virtual void set_heightmap_overlay(QImage ho) = 0;

  virtual QVector3D *get_position() = 0;
  virtual bool get_tile_x() = 0;
  virtual bool get_tile_y() = 0;

  // diffuse of the frame being edited, so plugins dont need Sprite
  virtual void get_current_diffuse(QImage *diffuse) = 0;

  // these were public members before the interface
  virtual void request_rect(QRect r) = 0;
  virtual void set_normal_counter(int c) = 0;
  virtual void set_parallax_counter(int c) = 0;
  virtual void set_specular_counter(int c) = 0;
  virtual void set_occlussion_counter(int c) = 0;
};

#endif // PROCESSOR_INTERFACE_H
