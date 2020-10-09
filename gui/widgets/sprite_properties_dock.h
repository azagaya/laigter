#ifndef SPRITE_PROPERTIES_DOCK_H
#define SPRITE_PROPERTIES_DOCK_H

#include "src/image_processor.h"
#include <QWidget>

namespace Ui
{
class SpritePropertiesDock;
}

class SpritePropertiesDock : public QWidget
{
  Q_OBJECT
  /* Member variables */

private:
  Ui::SpritePropertiesDock *ui;
  ImageProcessor *current_processor = nullptr;

  /* Methods */
public:
  explicit SpritePropertiesDock(QWidget *parent = nullptr);
  ~SpritePropertiesDock();
  void SetCurrentProcessor(ImageProcessor *processor);

public slots:
  void updatePosition();
  void setCurrentFrame(int i);

signals:
  void neighboursButtonPressed();
  void heightmapButtonPressed();
  void specularButtonPressed();
  void framesChanged(int, int);

private slots:
  void on_scaleSpinBox_valueChanged(double arg1);
  void on_rotationSpinBox_valueChanged(double arg1);
  void on_xPositionSpinBox_valueChanged(int arg1);
  void on_yPositionSpinBox_valueChanged(int arg1);
  void on_tileCheckBox_toggled(bool checked);
  void on_neighboursButton_pressed();
  void on_heightmapButton_pressed();
  void on_specularButton_pressed();
  void on_hFramesSpinBox_valueChanged(int arg1);
  void on_vFramesSpinBox_valueChanged(int arg1);
  void on_radioButton_2_toggled(bool checked);
};

#endif // SPRITE_PROPERTIES_DOCK_H
