#include "slider.h"

#include <QStyleOptionSlider>
#include <QToolTip>
#include <QPainter>
#include <QDebug>
#include <QFile>
#include <math.h>

Slider::Slider(QWidget * parent)
    : QSlider(parent)
{
  spin_box.setParent(this);
  spin_box.setMaximum(this->maximum());
  spin_box.setMinimum(this->minimum());
  connect(this,SIGNAL(valueChanged(int)),&spin_box,SLOT(setValue(int)));
  connect(&spin_box,SIGNAL(valueChanged(int)),this,SLOT(setValue(int)));
  connect(this,SIGNAL(rangeChanged(int,int)),this,SLOT(setSpinBoxRange(int,int)));
  QFile style(":/styles/spinboxslider.qss");
  style.open(QIODevice::ReadOnly);
  setStyleSheet(style.readAll());
}

Slider::Slider(Qt::Orientation orientation, QWidget * parent)
    : QSlider(orientation, parent)
{
}

void Slider::setSpinBoxRange(int min, int max){
  spin_box.setMaximum(max);
  spin_box.setMinimum(min);
}

void Slider::resizeEvent(QResizeEvent *ev) {
  QSlider::resizeEvent(ev);
  setMinimumSize(QSize(50,20));
  spin_box.move(width()*float(value())/maximum()*0.5, height()/2-spin_box.height()/2);
}

void Slider::sliderChange(QAbstractSlider::SliderChange change)
{
  QSlider::sliderChange(change);

  if (change == QAbstractSlider::SliderValueChange )
  {
    spin_box.resize(15*ceil(log10(value()+2)),20);
    spin_box.move(width()*float(value())/maximum()*0.5, height()/2-spin_box.height()/2);
  }
}

