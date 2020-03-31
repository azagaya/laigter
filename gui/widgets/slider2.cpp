#include "slider2.h"

#include <math.h>

#include <QStyleOptionSlider>
#include <QToolTip>
#include <QPainter>
#include <QDebug>
#include <QFile>

Slider2::Slider2(QWidget *parent)
	: QSlider(parent)
{
	spin_box.setParent(this);
	spin_box.setMaximum(maximum());
	spin_box.setMinimum(minimum());
	spin_box.setAlignment(Qt::AlignCenter);
	connect(this, SIGNAL(valueChanged(int)), &spin_box, SLOT(setValue(int)));
	connect(&spin_box, SIGNAL(valueChanged(int)), this, SLOT(setValue(int)));
	connect(this, SIGNAL(rangeChanged(int, int)), this, SLOT(setSpinBoxRange(int, int)));
	QFile style(":/styles/spin_box_slider2.qss");
	style.open(QIODevice::ReadOnly);
	setStyleSheet(style.readAll());
}

Slider2::Slider2(Qt::Orientation orientation, QWidget *parent)
	: QSlider(orientation, parent)
{
}

void Slider2::setValueFromSpinBox(int v)
{
	setValue(v*maximum()/100.0);
}

void Slider2::setValueToSpinBox(int v)
{
	spin_box.setValue(value()*100.0/maximum());
}

void Slider2::setSpinBoxRange(int min, int max)
{
	spin_box.setMaximum(max);
	spin_box.setMinimum(min);
}

void Slider2::resizeEvent(QResizeEvent *ev)
{
	QSlider::resizeEvent(ev);
	setMinimumSize(QSize(50, 20));
	QString num = QString::number(spin_box.value());
	QFontMetrics fm(spin_box.font());
	spin_box.resize(width(), 15);
	spin_box.move(0.5*width() - 0.5*spin_box.width(), 0);
}

void Slider2::sliderChange(QAbstractSlider::SliderChange change)
{
	QSlider::sliderChange(change);
	if (change == QAbstractSlider::SliderValueChange )
	{
		QString num = QString::number(spin_box.value());
		QFontMetrics fm(spin_box.font());
		spin_box.resize(width(), 15);
		spin_box.move(0.5*width() - 0.5*spin_box.width(), 0);
	}
}

