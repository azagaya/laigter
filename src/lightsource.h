#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include <QObject>

class LightSource : public QObject
{
    Q_OBJECT
public:
    explicit LightSource(QObject *parent = nullptr);

signals:

public slots:
};

#endif // LIGHTSOURCE_H
