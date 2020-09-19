#ifndef ANIMATION_DOCK_H
#define ANIMATION_DOCK_H

#include <QWidget>
#include "src/image_processor.h"

namespace Ui {
class AnimationDock;
}

class AnimationDock : public QWidget
{
  Q_OBJECT

private:
  Ui::AnimationDock *ui;
  ImageProcessor *m_current_processor;

public:
  explicit AnimationDock(QWidget *parent = nullptr);
  ~AnimationDock();

public slots:
  void setCurrentProcessor(ImageProcessor *p);
  void setCurrentFrame(int index);
  void updateProcessorFrame(int index);
private slots:
  void on_fpsSpinBox_valueChanged(int arg1);

  void on_playButton_toggled(bool checked);

  void on_leftButton_clicked();

  void on_rightButton_clicked();


  void on_deleteFrameButton_pressed();
};

#endif // ANIMATION_DOCK_H
