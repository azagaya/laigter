#include "lightsource.h"

LightSource::LightSource(int id, QObject *parent) : QObject(parent), id(id)
{

}

void LightSource::set_height(float height){
    lightHeight = height;
}

float LightSource::get_height(){
    return lightHeight;
}

void LightSource::set_diffuse_color(QColor color){
    diffuseColor = color;
}

QColor LightSource::get_diffuse_color(){
    return diffuseColor;
}

void LightSource::set_light_position(QVector3D position){
    lightPosition = position;
}

QVector3D LightSource::get_light_position(){
    return lightPosition;
}

void LightSource::set_specular_color(QColor color){
    specularColor = color;
}

QColor LightSource::get_specular_color(){
    return specularColor;
}

void LightSource::set_specular_scatter(float scatter){
    specularScatter = scatter;
}

float LightSource::get_specular_scatter(){
    return  specularScatter;
}

void LightSource::set_diffuse_intensity(float intensity){
    diffuseIntensity = intensity;
}

float LightSource::get_diffuse_intensity(){
    return diffuseIntensity;
}

void LightSource::set_specular_intensity(float intensity){
    specularIntensity = intensity;
}

float LightSource::get_specular_intesity(){
    return specularIntensity;
}
