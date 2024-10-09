#include "slider.h"
#include "qevent.h"
#include "qscreen.h"

#include <math.h>

#include <QFile>
#include <QPainter>
#include <QStyleOptionSlider>
#include <QToolTip>
#include <QMouseEvent>

Slider::Slider(QWidget *parent) : QSlider(parent)
{
  spin_box.setParent(this);
  spin_box.setMaximum(maximum());
  spin_box.setMinimum(minimum());
  spin_box.setObjectName("flatSpinBox");
  connect(this, SIGNAL(valueChanged(int)), &spin_box, SLOT(setValue(int)));
  connect(&spin_box, SIGNAL(valueChanged(int)), this, SLOT(setValue(int)));
  connect(this, SIGNAL(rangeChanged(int,int)), this,
          SLOT(setSpinBoxRange(int,int)));
}

Slider::Slider(Qt::Orientation orientation, QWidget *parent)
    : QSlider(orientation, parent)
{
}

void Slider::setValueFromSpinBox(int v) { setValue(v * maximum() / 100.0); }

void Slider::setValueToSpinBox(int v)
{
  spin_box.setValue(v * 100.0 / maximum());
}

void Slider::setSpinBoxRange(int min, int max)
{
  spin_box.setMaximum(max);
  spin_box.setMinimum(min);
}

void Slider::resizeEvent(QResizeEvent *ev)
{
  QSlider::resizeEvent(ev);
  setMinimumSize(QSize(50, 20));
  QString num = QString::number(value());
  QFontMetrics fm(spin_box.font());
  int width = fm.size(Qt::TextSingleLine, num + " ").width() + handler_min / 2;
  spin_box.resize(width, 20);
}

void Slider::sliderChange(QAbstractSlider::SliderChange change)
{
  QSlider::sliderChange(change);
  if (change == QAbstractSlider::SliderValueChange)
  {
    QString num = QString::number(value());
    QFontMetrics fm(spin_box.font());
    int width = fm.size(Qt::TextSingleLine, num + " ").width() + handler_min / 2;
    spin_box.resize(width, 20);
  }
}

void Slider::paintEvent(QPaintEvent *ev)
{
  QSlider::paintEvent(ev);
  QRect rect(1.0 * (width() - handler_right_offset) * (value() - minimum()) / (maximum() - minimum()) + handler_min * (maximum() - value()) / (maximum() - minimum()), 8, 4, 4);
  QPainter painter(this);

  if (isEnabled())
    painter.fillRect(rect, palette().highlight());
  else
    painter.fillRect(rect, QBrush(QColor(200, 200, 200)));
}


void Slider::mouseDoubleClickEvent( QMouseEvent * e ){
    spin_box.setFocus();
    spin_box.selectAll();
}


void Slider::mousePressEvent(QMouseEvent *event)
{

    QPointF new_position = event->position();
    new_position.setX(0.5*handler_min * (event->position().x() - width()) / (handler_min - width()) +
                      (width() - handler_right_offset)*(event->position().x() - handler_min) / (width()- handler_min));
    event = new QMouseEvent(event->type(), new_position, new_position + pos(), event->button(), event->buttons(), event->modifiers());    QSlider::mousePressEvent(event);
    delete event;

}

void Slider::mouseMoveEvent(QMouseEvent *event)
{
    QPointF new_position = event->position();
    new_position.setX(0.5*handler_min * (event->position().x() - width()) / (handler_min - width()) +
                      (width() - handler_right_offset)*(event->position().x() - handler_min) / (width()- handler_min));
    event = new QMouseEvent(event->type(), new_position, this->mapToGlobal(new_position), event->button(), event->buttons(), event->modifiers());
    QSlider::mouseMoveEvent(event);
    delete event;
}
