#include "lightsource.h"

LightSource::LightSource(QObject *parent) : QObject(parent) {}

void LightSource::set_height(float height) {
  settings.lightPosition.setZ(height);
}

float LightSource::get_height() { return settings.lightPosition.z(); }

void LightSource::set_diffuse_color(QColor color) {
  settings.diffuseColor = color;
}

QColor LightSource::get_diffuse_color() { return settings.diffuseColor; }

void LightSource::set_light_position(QVector3D position) {
  settings.lightPosition = position;
}

QVector3D LightSource::get_light_position() { return settings.lightPosition; }

void LightSource::set_specular_color(QColor color) {
  settings.specularColor = color;
}

QColor LightSource::get_specular_color() { return settings.specularColor; }

void LightSource::set_specular_scatter(float scatter) {
  settings.specularScatter = scatter;
}

float LightSource::get_specular_scatter() { return settings.specularScatter; }

void LightSource::set_diffuse_intensity(float intensity) {
  settings.diffuseIntensity = intensity;
}

float LightSource::get_diffuse_intensity() { return settings.diffuseIntensity; }

void LightSource::set_specular_intensity(float intensity) {
  settings.specularIntensity = intensity;
}

float LightSource::get_specular_intesity() {
  return settings.specularIntensity;
}

void LightSource::copy_settings(LightSource *l) { settings = l->settings; }
