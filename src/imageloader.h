#ifndef IMAGELOADER_H
#define IMAGELOADER_H

#include <QObject>
#include <QImage>

class ImageLoader : public QObject
{
    Q_OBJECT
public:
    explicit ImageLoader(QObject *parent = nullptr);
    QImage loadTga(const char* filePath, bool *success);
    QImage loadImage(QString fileName, bool *success);

signals:

public slots:
};

#endif // IMAGELOADER_H
