#include "slider.h"

#include <math.h>

#include <QStyleOptionSlider>
#include <QToolTip>
#include <QPainter>
#include <QDebug>
#include <QFile>

Slider::Slider(QWidget * parent)
    : QSlider(parent)
{
  spin_box.setParent(this);
  spin_box.setMaximum(maximum());
  spin_box.setMinimum(minimum());
  spin_box.setObjectName("flatSpinBox");

  connect(this,SIGNAL(valueChanged(int)),&spin_box,SLOT(setValue(int)));
  connect(&spin_box,SIGNAL(valueChanged(int)),this,SLOT(setValue(int)));
  connect(this,SIGNAL(rangeChanged(int,int)),this,SLOT(setSpinBoxRange(int,int)));
//  QFile style(":/styles/spinboxslider.qss");
//  style.open(QIODevice::ReadOnly);
//  setStyleSheet(style.readAll());
}

Slider::Slider(Qt::Orientation orientation, QWidget * parent)
    : QSlider(orientation, parent)
{
}

void Slider::setValueFromSpinBox(int v){
  setValue(v*maximum()/100.0);
}

void Slider::setValueToSpinBox(int v){
  spin_box.setValue(value()*100.0/maximum());
}

void Slider::setSpinBoxRange(int min, int max){
  spin_box.setMaximum(max);
  spin_box.setMinimum(min);
}

void Slider::resizeEvent(QResizeEvent *ev) {
  QSlider::resizeEvent(ev);
  setMinimumSize(QSize(50,20));
  QString num = QString::number(value());
  QFontMetrics fm(spin_box.font());
  spin_box.resize(fm.size(Qt::TextSingleLine, num+" ").width(),20);
  // spin_box.move(0.5*width()*value()/maximum()-0.5*value()/maximum()*spin_box.width(), height()/2-spin_box.height()/2);
  //  spin_box.move(0.5*value()/maximum()*spin_box.width(), height()/2-spin_box.height()/2);
}

void Slider::sliderChange(QAbstractSlider::SliderChange change)
{
  QSlider::sliderChange(change);

  if (change == QAbstractSlider::SliderValueChange )
  {
    QString num = QString::number(value());
    QFontMetrics fm(spin_box.font());
    spin_box.resize(fm.size(Qt::TextSingleLine, num+" ").width(),20);
    //spin_box.move(0.5*width()*value()/maximum()-0.5*value()/maximum()*spin_box.width(), height()/2-spin_box.height()/2);
  }
}

void Slider::paintEvent(QPaintEvent *ev) {
  QSlider::paintEvent(ev);
  QRect rect(1.0*(width()-12.0)*(value()-minimum())/(maximum()-minimum())+37.0*(maximum()-value())/(maximum()-minimum()),8,4,4);
  QPainter painter(this);
  if (isEnabled())
    painter.fillRect(rect, palette().highlight());
  else
    painter.fillRect(rect, QBrush(QColor(200,200,200)));



}
