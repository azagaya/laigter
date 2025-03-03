#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include <QColor>
#include <QObject>
#include <QVector3D>

struct LightSettings
{
  QColor diffuseColor, specularColor;
  float diffuseIntensity, specularIntensity, specularScatter;
  float speed = 1.0;
  bool animate = false;
  QVector3D lightPosition;
};

class LightSource : public QObject
{
  Q_OBJECT

private:
  int id;
  bool selected;
  LightSettings settings;

public:
  explicit LightSource(QObject *parent = nullptr);

public slots:
  QColor get_diffuse_color();
  QColor get_specular_color();
  QVector3D get_light_position();
  float get_diffuse_intensity();
  float get_height();
  float get_specular_intesity();
  float get_specular_scatter();
  void copy_settings(LightSource *l);
  void set_diffuse_color(QColor color);
  void set_diffuse_intensity(float intensity);
  void set_height(float height);
  void set_light_position(QVector3D position);
  void set_specular_color(QColor color);
  void set_specular_intensity(float intensity);
  void set_specular_scatter(float scatter);

  void set_animate(bool a) {
    settings.animate = a;
  }
  void set_speed(float speed) {
    settings.speed = speed;
  }
  bool get_animate() {
    return settings.animate;
  }
  float get_speed() {
    return settings.speed;
  }
};

#endif // LIGHTSOURCE_H
