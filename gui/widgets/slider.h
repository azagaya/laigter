#ifndef SLIDER_H
#define SLIDER_H

#include <QObject>
#include <QSlider>
#include <QSpinBox>

class Slider : public QSlider
{
  Q_OBJECT

private:
  QSpinBox spin_box;

public:
  int handler_min = 37;
  int handler_right_offset = 12;
  explicit Slider(QWidget *parent = nullptr);
  explicit Slider(Qt::Orientation orientation, QWidget *parent = nullptr);

protected:
  virtual void resizeEvent(QResizeEvent *ev) override;
  virtual void sliderChange(SliderChange change) override;
  virtual void paintEvent(QPaintEvent *ev) override;
  virtual void mouseDoubleClickEvent( QMouseEvent * e ) override;

private slots:
  void setSpinBoxRange(int min, int max);
  void setValueFromSpinBox(int v);
  void setValueToSpinBox(int v);
  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;

signals:
  void resized();
};

#endif // SLIDER_H
