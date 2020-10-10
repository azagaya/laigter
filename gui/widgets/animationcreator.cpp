#include "animationcreator.h"
#include "QPushButton"
#include "ui_animationcreator.h"

AnimationCreator::AnimationCreator(QWidget *parent) : QWidget(parent),
                                                      ui(new Ui::AnimationCreator)
{
  ui->setupUi(this);
}

AnimationCreator::~AnimationCreator()
{
  delete ui;
}

void AnimationCreator::setCurrentProcessor(ImageProcessor *p)
{
  processor = p;
  this->disconnect();
  QImage texture = p->texture.copy();
  float h = texture.height() / p->getVFrames();
  float w = texture.width() / p->getHFrames();
  int k = 0;

  QString style = "QPushButton { \
                     border: 2px solid transparent;\
                     padding: 0px; \
                     background: 2px solid rgba(29, 161, 242, 25);\
                     }\
                   QPushButton:checked\
                     {\
                          border: 2px solid rgb(29, 161, 242);\
                          background: 2px solid rgba(29, 161, 242, 50);\
                      }";

  QLayoutItem *item;
  while ((item = ui->gridLayout->takeAt(0)))
  {
    QWidget *widget = item->widget();
    widget->deleteLater();
    delete item;
  }

  ui->listWidget->clear();
  for (int j = 0; j < p->getVFrames(); j++)
  {
    for (int i = 0; i < p->getHFrames(); i++)
    {
      QPushButton *frame = new QPushButton();
      frame->setProperty("frame_id", k);
      frame->setCheckable(true);
      k++;
      QImage image = texture.copy(QRect(i * w, j * h, w, h));

      frame->setMinimumSize(image.size() + QSize(3, 3));
      frame->setIconSize(image.size());
      frame->setIcon(QPixmap::fromImage(image));
      frame->setStyleSheet(style);
      ui->gridLayout->addWidget(frame, j, i);

      connect(frame, SIGNAL(clicked()), this, SLOT(updateAnimation()));
    }
  }

  ui->listWidget->addItems(processor->getAnimationNames());
}

void AnimationCreator::updateAnimation()
{
  if (ui->listWidget->selectedItems().size() == 0)
    return;
  QString animation_name = ui->listWidget->currentItem()->text();
  Animation *animation = processor->getAnimation(animation_name);

  if (animation == nullptr)
  {
    return;
  }

  animation->frames_id.clear();
  for (int i = 0; i < ui->gridLayout->rowCount(); i++)
  {
    for (int j = 0; j < ui->gridLayout->columnCount(); j++)
    {
      int frame = ((QPushButton *)ui->gridLayout->itemAtPosition(i, j)->widget())->property("frame_id").toInt();
      if (((QPushButton *)ui->gridLayout->itemAtPosition(i, j)->widget())->isChecked())
      {
        animation->frames_id.append(frame);
      }
      else if (animation->frames_id.contains(i))
      {
        animation->frames_id.removeAll(frame);
      }
    }
  }
}

void AnimationCreator::on_pushButton_clicked()
{
  QString name = ui->lineEdit->text();
  if (name != "" and !processor->getAnimation(name))
  {
    ui->listWidget->addItem(name);
    processor->animation_list.append(Animation(name));
    ui->listWidget->setCurrentRow(ui->listWidget->count() - 1);
    for (int i = 0; i < ui->gridLayout->rowCount(); i++)
    {
      for (int j = 0; j < ui->gridLayout->columnCount(); j++)
      {
        ((QPushButton *)ui->gridLayout->itemAtPosition(i, j)->widget())->setChecked(false);
      }
    }
  }
}

void AnimationCreator::on_listWidget_currentTextChanged(const QString &currentText)
{
}

void AnimationCreator::on_listWidget_currentRowChanged(int currentRow)
{
  if (currentRow < 0)
    return;
  Animation *animation = processor->getAnimation(ui->listWidget->item(currentRow)->text());
  if (!animation)
    return;
  for (int i = 0; i < ui->gridLayout->rowCount(); i++)
  {
    for (int j = 0; j < ui->gridLayout->columnCount(); j++)
    {
      int frame = ((QPushButton *)ui->gridLayout->itemAtPosition(i, j)->widget())->property("frame_id").toInt();

      ((QPushButton *)ui->gridLayout->itemAtPosition(i, j)->widget())->setChecked(animation->frames_id.contains(frame));
    }
  }
}
