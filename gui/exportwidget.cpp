#include <QDir>
#include <QFile>
#include <QFileDialog>
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

  if (ui->AnimationComboBox->currentIndex() > 0 && ui->AnimationComboBox->currentIndex() < 5)
  {
    n = rearrangeFrames(n, p);
  }

  if (type == TextureTypes::Normal)
  {

    if (ui->checkBoxInvertX->isChecked())
    {
      for (int x = 0; x < n.width(); x++)
      {
        for (int y = 0; y < n.height(); y++)
        {
          QColor color = n.pixelColor(x, y);
          color.setRedF(1.0 - color.redF());
          n.setPixelColor(x, y, color);
        }
      }
    }

    if (ui->checkBoxInvertY->isChecked())
    {
      for (int x = 0; x < n.width(); x++)
      {
        for (int y = 0; y < n.height(); y++)
        {
          QColor color = n.pixelColor(x, y);
          color.setGreenF(1.0 - color.greenF());
          n.setPixelColor(x, y, color);
        }
      }
    }

    QString embedded = ui->comboBoxNormalAlpha->currentText();

    if (embedded != "None")
    {
      n = n.convertToFormat(QImage::Format_RGBA8888_Premultiplied);
      QImage alpha;
      if (embedded == "Specular")
      {
        p->sprite.get_image(TextureTypes::Specular, &alpha);
      }
      else if (embedded == "Parallax")
      {
        p->sprite.get_image(TextureTypes::Parallax, &alpha);
      }
      else if (embedded == "Occlusion")
      {
        p->sprite.get_image(TextureTypes::Occlussion, &alpha);
      }

      for (int x = 0; x < n.width(); x++)
      {
        for (int y = 0; y < n.height(); y++)
        {
          QColor color = n.pixelColor(x, y);
          color.setAlphaF(alpha.pixelColor(x, y).redF());
          n.setPixelColor(x, y, color);
        }
      }
    }
  }

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

  if (ui->AnimationComboBox->currentIndex() == 5)
  {
    int digits = log10((float)p->get_frame_count()) + 1;
    for (int i = 0; i < p->get_frame_count(); i++)
    {
      QString frame_number = QStringLiteral("%1").arg(i, digits, 10, QLatin1Char('0'));
      QStringList path_parts = name.split("/");
      path_parts.last() = path_parts.last().split(".").join("_" + frame_number + ".");
      QString i_name = path_parts.join("/");
      QImage image = n.copy(p->getFrameRect(i));
      saved &= image.save(i_name);
      qDebug() << i_name;
    }
  }
  else
  {
    saved &= n.save(name);
  }
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

    if (ui->checkBoxCombinedMaps->isChecked())
    {
      QImage combined(p->sprite.size(), QImage::Format_RGB888);
      QImage specular, occlusion, parallax;
      p->sprite.get_image(TextureTypes::Specular, &specular);
      p->sprite.get_image(TextureTypes::Occlussion, &occlusion);
      p->sprite.get_image(TextureTypes::Parallax, &parallax);
      for (int x = 0; x < combined.width(); x++)
      {
        for (int y = 0; y < combined.height(); y++)
        {
          QColor color(specular.pixelColor(x, y).red(), occlusion.pixelColor(x, y).red(), parallax.pixelColor(x, y).red());
          combined.setPixelColor(x, y, color);
        }
      }

      QFileInfo info = QFileInfo(p->sprite.get_file_name());

      QString suffix = info.completeSuffix();
      if (path == "")
      {
        path = info.absolutePath();
      }
      QString name = path + "/" + info.fileName().remove("." + suffix) + "_sop." + suffix;
      combined.save(name);
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

      if (ui->AnimationComboBox->currentIndex() > 0 && ui->AnimationComboBox->currentIndex() < 5)
      {
        n = rearrangeFrames(n, p);
      }
      if (ui->AnimationComboBox->currentIndex() == 5)
      {
        int digits = log10((float)p->get_frame_count()) + 1;
        for (int i = 0; i < p->get_frame_count(); i++)
        {
          QString frame_number = QStringLiteral("%1").arg(i, digits, 10, QLatin1Char('0'));
          QStringList path_parts = name.split("/");
          path_parts.last() = path_parts.last().split(".").join("_" + frame_number + ".");
          QString i_name = path_parts.join("/");
          QImage image = n.copy(p->getFrameRect(i));
          saved &= image.save(i_name);
          qDebug() << i_name;
        }
      }
      else
      {
        saved &= n.save(name);
      }
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

void ExportWidget::on_pushButtonExportDirectory_clicked()
{
  ui->lineEdit->setText(QFileDialog::getExistingDirectory());
}

void ExportWidget::on_AnimationComboBox_activated(const QString &arg1)
{

  if (arg1 == "Fixed Rows")
  {
    ui->labelFrames->setText("Rows:");
    ui->labelFrames->setEnabled(true);
    ui->spinBoxFrames->setEnabled(true);
  }
  else if (arg1 == "Fixed Columns")
  {
    ui->labelFrames->setText("Columns:");
    ui->labelFrames->setEnabled(true);
    ui->spinBoxFrames->setEnabled(true);
  }
  else
  {

    ui->labelFrames->setText("");
    ui->labelFrames->setEnabled(false);
    ui->spinBoxFrames->setEnabled(false);
  }
}

QImage ExportWidget::rearrangeFrames(QImage n, ImageProcessor *p)
{
  QSize s = p->getFrameImage(0).size();
  int frames = p->get_frame_count();
  int h_frames = 1, v_frames = 1;
  bool by_rows = false;
  switch (ui->AnimationComboBox->currentIndex())
  {
    case 1:
      h_frames = frames;
      break;
    case 2:
      v_frames = frames;
      break;
    case 3:
      v_frames = ui->spinBoxFrames->value();
      h_frames = ceil((float)frames / v_frames);
      break;
    case 4:
      by_rows = true;
      h_frames = ui->spinBoxFrames->value();
      v_frames = ceil((float)frames / h_frames);
      break;
  }

  QImage aux(h_frames * s.width(), v_frames * s.height(), n.format());
  if (aux.hasAlphaChannel())
    aux.fill(Qt::transparent);
  else
    aux.fill(Qt::black);
  QPainter painter(&aux);
  int index = 0;
  if (!by_rows)
  {
    for (int i = 0; i < h_frames; i++)
      for (int j = 0; j < v_frames; j++)
      {
        {
          if (index >= frames)
            break;
          painter.drawImage(QRectF(i * s.width(), j * s.height(), s.width(), s.height()), n.copy(p->getFrameRect(index)));
          index++;
        }
      }
  }
  else
  {
    for (int j = 0; j < v_frames; j++)
      for (int i = 0; i < h_frames; i++)
      {
        {
          if (index >= frames)
            break;
          qDebug() << index << frames;
          painter.drawImage(QRectF(i * s.width(), j * s.height(), s.width(), s.height()), n.copy(p->getFrameRect(index)));
          index++;
        }
      }
  }

  return aux.copy();
}
