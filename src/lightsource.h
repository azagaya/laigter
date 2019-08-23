#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include <QObject>
#include <QColor>
#include <QVector3D>

class LightSource : public QObject
{
    Q_OBJECT
public:
    explicit LightSource(int id,QObject *parent = nullptr);


signals:

public slots:
    void set_diffuse_color(QColor color);
    QColor get_diffuse_color();
    void set_diffuse_intensity(float intensity);
    float get_diffuse_intensity();

    void set_height(float height);
    float get_height();

    void set_specular_color(QColor color);
    QColor get_specular_color();
    void set_specular_intensity(float intensity);
    float get_specular_intesity();
    void set_specular_scatter(float scatter);
    float get_specular_scatter();

    void set_light_position(QVector3D position);
    QVector3D get_light_position();

private:
    QColor diffuseColor, specularColor;
    float diffuseIntensity, specularIntensity, specularScatter, lightHeight;
    QVector3D lightPosition;
    int id;
    bool selected;


};

#endif // LIGHTSOURCE_H
