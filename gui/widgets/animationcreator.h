#ifndef ANIMATIONCREATOR_H
#define ANIMATIONCREATOR_H

#include "src/image_processor.h"
#include <QWidget>

namespace Ui
{
class AnimationCreator;
}

class AnimationCreator : public QWidget
{
  Q_OBJECT

public:
  explicit AnimationCreator(QWidget *parent = nullptr);
  ~AnimationCreator();
  void setCurrentProcessor(ImageProcessor *p);
  ImageProcessor *processor;

public slots:

  void updateAnimation();

signals:
  void animationsUpdated(ImageProcessor *processor);

private slots:
  void on_pushButton_clicked();

  void on_listWidget_currentRowChanged(int currentRow);

  void on_deletePushButton_pressed();

private:
  Ui::AnimationCreator *ui;
};

#endif // ANIMATIONCREATOR_H
