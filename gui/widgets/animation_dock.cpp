#include "animation_dock.h"
#include "ui_animation_dock.h"

#include "src/image_loader.h"

#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QThread>

AnimationDock::AnimationDock(QWidget *parent) : QWidget(parent),
                                                ui(new Ui::AnimationDock)
{
  ui->setupUi(this);
  m_current_processor = nullptr;
  animation_creator = new AnimationCreator;
  animation_creator->setAttribute(Qt::WA_QuitOnClose, false);

  connect(animation_creator, SIGNAL(animationsUpdated()), this, SLOT(updateAnimationList()));
}

AnimationDock::~AnimationDock()
{
  animation_creator->close();
  delete ui;
}

void AnimationDock::updateAnimationList()
{
  ui->comboBox->clear();
  ui->comboBox->addItems(m_current_processor->getAnimationNames());
}

void AnimationDock::setCurrentProcessor(ImageProcessor *p)
{
  this->disconnect();
  /* reconnect animation_creator signal */
  connect(animation_creator, SIGNAL(animationsUpdated()), this, SLOT(updateAnimationList()));
  disconnect(m_current_processor, SIGNAL(frameChanged(int)), this, SLOT(setCurrentFrame(int)));
  disconnect(ui->listWidget, SIGNAL(currentRowChanged(int)), this, SLOT(updateProcessorFrame(int)));

  m_current_processor = p;

  ui->playButton->setChecked(p->animation.isActive());
  for (int i = 0; i < ui->listWidget->count(); i++)
  {
    delete ui->listWidget->item(i);
  }

  ui->listWidget->setCurrentRow(p->get_current_frame_id());
  ui->fpsSpinBox->setValue(1 / (p->animation.interval() / 1000.0));

  connect(m_current_processor, SIGNAL(frameChanged(int)), this, SLOT(setCurrentFrame(int)));
  connect(ui->listWidget, SIGNAL(currentRowChanged(int)), this, SLOT(updateProcessorFrame(int)));

  QString last_animation = p->getCurrentAnimationName();

  ui->comboBox->clear();
  ui->comboBox->addItems(p->getAnimationNames());

  ui->comboBox->setCurrentText(last_animation);
//  on_comboBox_activated(p->getCurrentAnimationName());
}

void AnimationDock::updateProcessorFrame(int index)
{

  if (index >= 0 && index < m_current_processor->get_frame_count() && ui->listWidget->selectedItems().count() > 0)
  {
    index = ui->listWidget->currentItem()->data(Qt::UserRole).toInt();
    if (!m_current_processor->animation.isActive())
    {
      m_current_processor->set_current_frame_id(index);
    }
  }
}

void AnimationDock::on_fpsSpinBox_valueChanged(int arg1)
{
  m_current_processor->setAnimationRate(arg1);
}

void AnimationDock::on_playButton_toggled(bool checked)
{
  m_current_processor->playAnimation(checked);
  checked ? ui->playButton->setIcon(QIcon::fromTheme("pause")) : ui->playButton->setIcon(QIcon::fromTheme("play"));
}

void AnimationDock::on_leftButton_clicked()
{
  QList<QListWidgetItem *> item_list = ui->listWidget->selectedItems();
  if (item_list.count() > 0)
  {
    int index = ui->listWidget->currentRow();
    if (index == 0)
    {
      return;
    }
    int id = m_current_processor->current_animation->frames_id.takeAt(index);
    m_current_processor->current_animation->frames_id.insert(index - 1, id);
    ui->listWidget->insertItem(index - 1, ui->listWidget->takeItem(index));
    ui->listWidget->setCurrentRow(index - 1);
  }
}

void AnimationDock::setCurrentFrame(int index)
{
  for (int i = 0; i < ui->listWidget->count(); i++)
  {
    if (ui->listWidget->item(i)->data(Qt::UserRole).toInt() == index)
    {
      ui->listWidget->setCurrentRow(i);
      break;
    }
  }
}

void AnimationDock::on_rightButton_clicked()
{
  QList<QListWidgetItem *> item_list = ui->listWidget->selectedItems();
  if (item_list.count() > 0)
  {
    int index = ui->listWidget->currentRow();
    if (index >= m_current_processor->current_animation->frames_id.size() - 1)
    {
      return;
    }
    int id = m_current_processor->current_animation->frames_id.takeAt(index);
    m_current_processor->current_animation->frames_id.insert(index + 1, id);
    ui->listWidget->insertItem(index + 1, ui->listWidget->takeItem(index));
    ui->listWidget->setCurrentRow(index + 1);
  }
}

void AnimationDock::on_deleteFrameButton_pressed()
{
  if (ui->listWidget->selectedItems().size() <= 0)
    return;
  m_current_processor->remove_frame(ui->listWidget->currentRow());
  delete ui->listWidget->takeItem(ui->listWidget->currentRow());
}

void AnimationDock::on_editorPushButton_pressed()
{
  animation_creator->setCurrentProcessor(m_current_processor);
  animation_creator->show();
  animation_creator->activateWindow();
}

void AnimationDock::on_comboBox_activated(const QString &arg1)
{


}

void AnimationDock::updateList(QString animation_name)
{

  ui->listWidget->clear();

  Animation *animation = m_current_processor->getAnimation(animation_name);
  if (!animation)
    return;
  QImage texture = m_current_processor->texture.copy();
  float h = texture.height() / m_current_processor->getVFrames();
  float w = texture.width() / m_current_processor->getHFrames();

  foreach (int i, animation->frames_id)
  {
    QListWidgetItem *item = new QListWidgetItem;
    QRect rect(texture.width() * m_current_processor->vertices[i][3], texture.height() * m_current_processor->vertices[i][14], w, h);
    QImage image = texture.copy(rect);
    item->setIcon(QPixmap::fromImage(image));
    item->setData(Qt::UserRole, i);
    ui->listWidget->addItem(item);
  }
  ui->comboBox->setCurrentText(animation_name);
}

void AnimationDock::on_comboBox_currentIndexChanged(const QString &arg1)
{
    Animation *animation = m_current_processor->getAnimation(arg1);

    if (!animation)
      return;

    m_current_processor->setCurrentAnimation(arg1);

    updateList(arg1);
}
