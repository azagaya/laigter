#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>

class GraphicsView : public QGraphicsView
{
Q_OBJECT
public:
    GraphicsView(QWidget *parent);
public slots:
    void zoom_in(double sx = 1.01, double sy = 1.01);
    void zoom_out(double sx = 0.99, double sy = 0.99);
signals:
    void zoomed_in(double sx, double sy);
    void zoomed_out(double sx, double sy);
private:
    virtual void wheelEvent(QWheelEvent *event);
};

#endif // GRAPHICSVIEW_H
