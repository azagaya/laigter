/*
 * Laigter: an automatic map generator for lighting effects.
 * Copyright (C) 2019  Pablo Ivan Fonovich
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 * Contact: azagaya.games@gmail.com
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "src/imageloader.h"
#include "src/imageprocessor.h"
#include "src/lightsource.h"
#include "src/brushinterface.h"
#include "gui/languageselector.h"
#include "src/project.h"
#include <QColor>
#include <QFileSystemWatcher>
#include <QGraphicsScene>
#include <QList>
#include <QListWidgetItem>
#include <QMainWindow>
#include <QOpenGLWidget>
#include <QThread>
#include <QVector3D>
#include <QPluginLoader>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  void dropEvent(QDropEvent *event);
  void dragEnterEvent(QDragEnterEvent *e);
  void openDroppedFiles(QList<QUrl> urlList, QStringList *fileNames);

  Project project;

public slots:
  void update_scene();
  void add_processor(ImageProcessor *p);
  void selectedLightChanged(LightSource *light);
  void stopAddingLight();
  void set_light_color(const QColor &color);
  void set_ambient_color(const QColor &color);
  void set_background_color(const QColor &color);
  void selectedProcessorsChanged(QList<ImageProcessor *> list);
  void processor_selected(ImageProcessor *processor, bool selected);
  void set_enabled_map_controls(bool e);
  void set_enabled_light_controls(bool e);
  void select_plugin(BrushInterface *b);
  ImageProcessor *find_processor(QString name);
  void retranslate();

signals:
  void normal_depth_changed(int value);
private slots:

  void connect_processor(ImageProcessor *p);
  void disconnect_processor(ImageProcessor *p);
  void showContextMenuForListWidget(const QPoint &pos);
  void list_menu_action_triggered(QAction *action);
  void openGL_initialized();
  void on_actionOpen_triggered();

  void on_actionFitZoom_triggered();

  void on_actionZoom_100_triggered();

  void on_actionZoomIn_triggered();

  void on_actionZoomOut_triggered();

  void on_actionExport_triggered();

  void on_pushButtonColor_clicked();

  void on_horizontalSliderDiffHeight_valueChanged(int value);

  void on_horizontalSliderDiffLight_valueChanged(int value);

  void on_horizontalSliderAmbientLight_valueChanged(int value);

  void on_pushButtonAmbientColor_clicked();

  void on_listWidget_itemSelectionChanged();

  void on_pushButton_clicked();

  void on_pushButtonBackgroundColor_clicked();

  void on_pushButton_2_clicked();

  void on_comboBox_currentIndexChanged(int index);

  void on_pushButtonExportTo_clicked();

  void open_files(QStringList fileNames);

  void on_actionPresets_triggered();

  void on_horizontalSliderSpec_valueChanged(int value);

  void on_horizontalSliderSpecScatter_valueChanged(int value);

  void on_comboBoxView_currentIndexChanged(int index);

  void on_actionExportPreview_triggered();

  void on_actionAbout_triggered();

  void on_actionAdd_Light_triggered(bool checked);

  void on_checkBoxLightsPerTexture_toggled(bool checked);

  void onFileChanged(const QString &file_path);

  void on_actionLoadPlugins_triggered();

  void on_actionInstall_Plugin_triggered();

  void on_actionDelete_Plugin_triggered();


  void on_actionLanguages_triggered();

  void on_listWidget_itemClicked(QListWidgetItem *item);

  void on_actionSaveProject_triggered();

  private:
  Ui::MainWindow *ui;
  QOpenGLWidget *gl;
  QGraphicsScene *m_normal_scene;
  QGraphicsScene *m_raw_scene;
  ImageProcessor *processor;
  ImageProcessor *sample_processor;
  QColor currentColor, currentAmbientcolor, currentBackgroundColor,
      currentSpecColor, currentSpecBaseColor;
  QThread *processingThread;
  QList<ImageProcessor *> processorList;
  QList<ImageProcessor *> selectedProcessors;
  ImageLoader il;
  QFileSystemWatcher fs_watcher;
  QList <QDockWidget*> plugin_docks_list;
  QList <QPluginLoader *> plugin_list;
  QList <BrushInterface *> brush_list;
  LanguageSelector *el;
  QListWidgetItem *current_item;

  protected slots:
  virtual void changeEvent(QEvent * event);
};

#endif // MAINWINDOW_H
