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

private slots:
  void on_pushButton_clicked();

  void on_listWidget_currentTextChanged(const QString &currentText);

  void on_listWidget_currentRowChanged(int currentRow);

private:
  Ui::AnimationCreator *ui;
};

#endif // ANIMATIONCREATOR_H
