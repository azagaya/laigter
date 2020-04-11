#include "animation_dock.h"
#include "ui_animation_dock.h"

#include <QDebug>

AnimationDock::AnimationDock(QWidget *parent) :
                                                QWidget(parent),
                                                ui(new Ui::AnimationDock)
{
  ui->setupUi(this);
  m_current_processor = nullptr;
}

AnimationDock::~AnimationDock()
{
  delete ui;
}

void AnimationDock::setCurrentProcessor(ImageProcessor *p)
{
  m_current_processor = p;
  ui->listWidget->setCurrentRow(p->get_current_frame_id());
  ui->playButton->setChecked(p->animation.isActive());
  for (int i = 0; i < ui->listWidget->count(); i++) {
    delete ui->listWidget->item(i);
  }
  ui->listWidget->clear();
  for (int i = 0; i < p->frames.count(); i++)
  {
    QListWidgetItem *item = new QListWidgetItem;
    QImage image;
    p->frames[i].get_image(TextureTypes::Diffuse, &image);
    item->setIcon(QPixmap::fromImage(image));
    ui->listWidget->addItem(item);

  }
  if (m_current_processor)
  {
    disconnect(m_current_processor, SIGNAL(frameChanged(int)), this, SLOT(setCurrentFrame(int)));
    disconnect(ui->listWidget, SIGNAL(currentRowChanged(int)), m_current_processor, SLOT(set_current_frame_id(int)));
  }
  connect(m_current_processor, SIGNAL(frameChanged(int)), this, SLOT(setCurrentFrame(int)));
  connect(ui->listWidget, SIGNAL(currentRowChanged(int)), this, SLOT(updateProcessorFrame(int)));
}

void AnimationDock::updateProcessorFrame(int index)
{
  if (index >= 0 && index < m_current_processor->frames.count())
  {
    m_current_processor->set_current_frame_id(index);
  }
}

void AnimationDock::on_fpsSpinBox_valueChanged(int arg1)
{
  m_current_processor->setAnimationRate(arg1);
}

void AnimationDock::on_playButton_toggled(bool checked)
{
  m_current_processor->playAnimation(checked);
}

void AnimationDock::on_leftButton_clicked()
{
  QList <QListWidgetItem *> item_list = ui->listWidget->selectedItems();
  if (item_list.count() > 0)
  {
    int index = ui->listWidget->currentRow();
    if (index == 0)
    {
      return;
    }
    m_current_processor->playAnimation(false);
    Sprite s(m_current_processor->frames[index]);
    m_current_processor->frames[index] = m_current_processor->frames[index-1];
    m_current_processor->frames[index-1] = s;
    ui->listWidget->insertItem(index-1, ui->listWidget->takeItem(index));
    ui->listWidget->setCurrentRow(index-1);
  }
}

void AnimationDock::setCurrentFrame(int index)
{
  ui->listWidget->setCurrentRow(index);
}

void AnimationDock::on_rightButton_clicked()
{
  QList <QListWidgetItem *> item_list = ui->listWidget->selectedItems();
  if (item_list.count() > 0)
  {
    int index = ui->listWidget->currentRow();
    if (index >= m_current_processor->frames.count()-1)
    {
      return;
    }
    m_current_processor->playAnimation(false);
    Sprite s(m_current_processor->frames[index]);
    m_current_processor->frames[index] = m_current_processor->frames[index+1];
    m_current_processor->frames[index+1] = s;
    ui->listWidget->insertItem(index+1, ui->listWidget->takeItem(index));
    ui->listWidget->setCurrentRow(index+1);
  }
}
