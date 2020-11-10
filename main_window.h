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

#include "gui/language_selector.h"
#include "src/brush_interface.h"
#include "src/image_loader.h"
#include "src/image_processor.h"
#include "src/light_source.h"
#include "src/project.h"

#include "gui/nb_selector.h"
#include "gui/widgets/animation_dock.h"
#include "gui/widgets/sprite_properties_dock.h"

#include <QColor>
#include <QFileSystemWatcher>
#include <QGraphicsScene>
#include <QList>
#include <QListWidgetItem>
#include <QMainWindow>
#include <QOpenGLWidget>
#include <QPluginLoader>
#include <QThread>
#include <QVector3D>

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  Project project;

private:
  ImageLoader il;
  ImageProcessor *processor;
  ImageProcessor *sample_processor;
  LanguageSelector *el;
  QColor currentColor, currentAmbientcolor, currentBackgroundColor,
      currentSpecColor, currentSpecBaseColor;
  QFileSystemWatcher fs_watcher;
  QGraphicsScene *m_normal_scene;
  QGraphicsScene *m_raw_scene;
  QList<BrushInterface *> brush_list;
  QList<QDockWidget *> plugin_docks_list;
  QList<QPluginLoader *> plugin_list;
  QList<ImageProcessor *> processorList;
  QList<ImageProcessor *> selectedProcessors;
  QListWidgetItem *current_item;
  QOpenGLWidget *gl;
  QThread *processingThread;
  Ui::MainWindow *ui;
  QDockWidget *animation_dock, *sprite_dock;
  AnimationDock *animation_widget;
  SpritePropertiesDock *sprite_widget;
  NBSelector nbSelector;

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  void dropEvent(QDropEvent *event);
  void dragEnterEvent(QDragEnterEvent *e);
  void openDroppedFiles(QList<QUrl> urlList, QStringList *fileNames);
  void SaveProject(QString path);
  void LoadProject(QString path);
  bool ExportMap(TextureTypes type, ImageProcessor *p, QString postfix, QString destination = "", bool useAlpha = false);
  QStringList FindSimilarFiles(QString file_name, QStringList checkedFiles, QString *prefix);

public slots:
  ImageProcessor *find_processor(QString name);
  int get_processor_index(ImageProcessor *p);
  void setCurrentItem(QListWidgetItem *i);
  void update_scene();
  void add_processor(ImageProcessor *p);
  void remove_processor(ImageProcessor *p);
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
  void retranslate();

signals:
  void normal_depth_changed(int value);

private slots:
  void connect_processor(ImageProcessor *p);
  void disconnect_processor(ImageProcessor *p);
  void showContextMenuForListWidget(const QPoint &pos);
  void list_menu_action_triggered(QAction *action);
  void openGL_initialized();
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
  void selectNeighbours();
  void loadHeightmap();
  void loadSpecular();
  void splitInFrames(int h_frames, int v_frames, ImageProcessor *processor);
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
  void on_blendSlider_valueChanged(int value);

  void on_actionLoadProject_triggered();

  void on_actionSave_Project_As_triggered();

  void on_actionImport_triggered();

  void on_actionThemes_triggered();

  void on_deletePushButton_clicked();

protected slots:
  virtual void changeEvent(QEvent *event);
};

#endif // MAINWINDOW_H
