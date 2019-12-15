#ifndef SLIDER_H
#define SLIDER_H

#include <QObject>
#include <QSlider>
#include <QSpinBox>

class Slider : public QSlider
{
  Q_OBJECT
  signals:
      void resized();
  public:
  explicit Slider(QWidget *parent = nullptr);
  explicit Slider(Qt::Orientation orientation, QWidget *parent = nullptr);

  protected:
      virtual void resizeEvent(QResizeEvent *ev) override;
      virtual void sliderChange(SliderChange change) override;

  private slots:
      void setSpinBoxRange(int min, int max);
  private:
      QSpinBox spin_box;
};

#endif // SLIDER_H
