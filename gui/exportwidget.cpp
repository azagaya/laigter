#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QImageWriter>
#include <QMessageBox>

#include "exportwidget.h"
#include "ui_exportwidget.h"

ExportWidget::ExportWidget(QWidget *parent) : QWidget(parent),
                                              ui(new Ui::ExportWidget)
{
  ui->setupUi(this);
}

ExportWidget::~ExportWidget()
{
  delete ui;
}

bool ExportWidget::ExportMap(TextureTypes type, ImageProcessor *p, QString postfix, QString destination, bool useAlpha)
{
  QImage n;
  QString suffix;
  QString name;
  QFileInfo info;
  bool saved = true;

  p->sprite.get_image(type, &n);
  QString file_name = p->sprite.get_file_name();
  info = QFileInfo(file_name);
  if (!info.exists())
  {
    info = QFileInfo(project.GetCurrentPath());
    file_name = info.dir().path() + "/" + file_name.split("/").last();
    info = QFileInfo(file_name);
  }
  suffix = info.completeSuffix();
  if (!QImageWriter::supportedImageFormats().contains(suffix.toUtf8()))
  {
    suffix = "png";
  }
  if (destination == "")
  {
    name = p->m_absolute_path + "/" + info.baseName() + postfix + "." + suffix;
  }
  else
  {
    name = destination + "/" + info.baseName() + postfix + "." + suffix;
  }
  if (useAlpha)
  {
    n.setAlphaChannel(p->get_texture()->convertToFormat(QImage::Format_Alpha8));
  }
  saved &= n.save(name);

  return saved;
}

void ExportWidget::on_pushButton_2_clicked()
{
  close();
}

void ExportWidget::on_pushButton_clicked()
{
  QString message = "";
  bool saved = true;
  QString path = "";
  if (ui->radioButtonTargetPos->isChecked())
  {
    path = ui->lineEdit->text();
  }
  foreach (ImageProcessor *p, processorList)
  {
    if (ui->checkBoxNormal->isChecked())
    {
      saved &= ExportMap(TextureTypes::Normal, p, ui->lineEditNormalPostfix->text(), path, p->get_use_normal_alpha());
    }
    if (ui->checkBoxParallax->isChecked())
    {
      saved &= ExportMap(TextureTypes::Parallax, p, ui->lineEditParallaxPostfix->text(), path, p->get_use_parallax_alpha());
    }
    if (ui->checkBoxSpecular->isChecked())
    {
      saved &= ExportMap(TextureTypes::Specular, p, ui->lineEditSpecularPostfix->text(), path, p->get_use_specular_alpha());
    }
    if (ui->checkBoxOcclusion->isChecked())
    {
      saved &= ExportMap(TextureTypes::Occlussion, p, ui->lineEditOcclusionPostFix->text(), path, p->get_use_occlusion_alpha());
    }
    if (ui->checkBoxDifusse->isChecked())
    {
      saved &= ExportMap(TextureTypes::Color, p, ui->lineEditDiffusePostFix->text(), path);
    }
  }
  if (ui->checkBoxPreview->isChecked())
  {
    QImage n;
    QString suffix;
    QString name;
    QFileInfo info;
    foreach (ImageProcessor *p, processorList)
    {
      oglWidget->set_current_processor(p);

      p->animation.stop();
      n = oglWidget->get_preview(false, false);
      info = QFileInfo(p->sprite.get_file_name());

      suffix = info.completeSuffix();
      if (path == "")
      {
        path = info.absolutePath();
      }
      name = path + "/" + info.fileName().remove("." + suffix) + ui->lineEditPreviewPostfix->text() + "." + suffix;
      n.save(name);
    }
  }

  if (saved)
  {
    message = tr("All selected maps were exported.\n");
  }
  else
  {
    message = tr("Could not export maps. Check destination's permissions.\n");
  }
  QMessageBox msgBox;
  msgBox.setText(message);
  msgBox.exec();
  close();
}
