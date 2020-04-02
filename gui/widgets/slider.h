#ifndef SLIDER_H
#define SLIDER_H

#include <QObject>
#include <QSlider>
#include <QSpinBox>

class Slider : public QSlider {
  Q_OBJECT

private:
  QSpinBox spin_box;

public:
  explicit Slider(QWidget *parent = nullptr);
  explicit Slider(Qt::Orientation orientation, QWidget *parent = nullptr);

protected:
  virtual void resizeEvent(QResizeEvent *ev) override;
  virtual void sliderChange(SliderChange change) override;
  virtual void paintEvent(QPaintEvent *ev) override;

private slots:
  void setSpinBoxRange(int min, int max);
  void setValueFromSpinBox(int v);
  void setValueToSpinBox(int v);

signals:
  void resized();
};

#endif // SLIDER_H
