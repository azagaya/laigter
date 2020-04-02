#ifndef SLIDER_H
#define SLIDER_H

#include <QObject>
#include <QSlider>
#include <QSpinBox>

class Slider2 : public QSlider
{
  Q_OBJECT

private:
  QSpinBox spin_box;

public:
  explicit Slider2(QWidget *parent = nullptr);
  explicit Slider2(Qt::Orientation orientation, QWidget *parent = nullptr);

protected:
  virtual void resizeEvent(QResizeEvent *ev) override;
  virtual void sliderChange(SliderChange change) override;

signals:
  void resized();

private slots:
  void setSpinBoxRange(int min, int max);
  void setValueFromSpinBox(int v);
  void setValueToSpinBox(int v);
};

#endif // SLIDER_H
