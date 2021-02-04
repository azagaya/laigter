#ifndef EXPORTWIDGET_H
#define EXPORTWIDGET_H

#include <QWidget>

#include "src/image_processor.h"
#include "src/open_gl_widget.h"
#include "src/project.h"

namespace Ui
{
class ExportWidget;
}

class ExportWidget : public QWidget
{
  Q_OBJECT

public:
  explicit ExportWidget(QWidget *parent = nullptr);
  bool ExportMap(TextureTypes type, ImageProcessor *p, QString postfix, QString destination = "", bool useAlpha = false);

  QList<ImageProcessor *> processorList;
  QList<ImageProcessor *> selectedProcessors;
  OpenGlWidget *oglWidget;
  Project project;
  ~ExportWidget();

private slots:
  void on_pushButton_2_clicked();

  void on_pushButton_clicked();

private:
  Ui::ExportWidget *ui;
};

#endif // EXPORTWIDGET_H
