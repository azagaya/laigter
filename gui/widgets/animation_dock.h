#ifndef ANIMATION_DOCK_H
#define ANIMATION_DOCK_H

#include "gui/widgets/animationcreator.h"
#include "src/image_processor.h"
#include <QWidget>

namespace Ui
{
class AnimationDock;
}

class AnimationDock : public QWidget
{
  Q_OBJECT

private:
  Ui::AnimationDock *ui;
  ImageProcessor *m_current_processor;
  AnimationCreator *animation_creator;

public:
  explicit AnimationDock(QWidget *parent = nullptr);
  ~AnimationDock();
  void updateList(QString animation_name);

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
  void on_addFrameButton_pressed();
  void on_deleteEmptyButton_pressed();
  void on_editorPushButton_pressed();
  void on_comboBox_activated(const QString &arg1);
};

#endif // ANIMATION_DOCK_H
