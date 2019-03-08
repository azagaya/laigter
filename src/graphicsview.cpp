#include "graphicsview.h"
#include <QDebug>
#include <QApplication>
#include <QWheelEvent>

GraphicsView::GraphicsView(QWidget *parent): QGraphicsView (parent)
{
    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
}

void GraphicsView::wheelEvent(QWheelEvent *event){
    if (QApplication::keyboardModifiers() & Qt::ControlModifier){
        QPoint np = event->angleDelta();
        double scale = 1 + np.y()/120.0*0.05;
        zoom_in(scale,scale);
        scale > 0 ? emit zoomed_in(scale,scale) : emit zoomed_out(scale,scale);
    }else{
        QGraphicsView::wheelEvent(event);
    }

}

void GraphicsView::zoom_in(double sx, double sy){
    scale(sx,sy);
}

void GraphicsView::zoom_out(double sx, double sy){
    scale(sx,sy);
}

