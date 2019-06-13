#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QOpenGLWidget>
#include <QListWidgetItem>
#include <QVector3D>
#include <QThread>
#include <QList>
#include "src/imageprocessor.h"
#include "src/imageloader.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void dropEvent(QDropEvent *event);
    void dragEnterEvent(QDragEnterEvent *e);

public slots:
    void update_scene(QImage image, ProcessedImage type);

signals:
    void normal_depth_changed(int value);
private slots:

    void connect_processor(ImageProcessor *p);
    void disconnect_processor(ImageProcessor *p);
    void showContextMenuForListWidget(const QPoint &pos);
    void list_menu_action_triggered(QAction* action);
    void openGL_initialized();
    void on_actionOpen_triggered();

    void on_actionFitZoom_triggered();

    void on_actionZoom_100_triggered();

    void on_actionZoomIn_triggered();

    void on_actionZoomOut_triggered();

    void on_actionExport_triggered();

    void on_radioButtonRaw_toggled(bool checked);

    void on_radioButtonNormal_toggled(bool checked);

    void on_radioButtonPreview_toggled(bool checked);

    void on_pushButtonColor_clicked();

    void on_horizontalSliderDiffHeight_valueChanged(int value);

    void on_horizontalSliderDiffLight_valueChanged(int value);

    void on_horizontalSliderAmbientLight_valueChanged(int value);

    void on_pushButtonAmbientColor_clicked();

    void on_actionLicencia_triggered();

    void on_actionReconocimientos_triggered();

    void on_listWidget_itemSelectionChanged();

    void on_pushButton_clicked();

    void on_pushButtonBackgroundColor_clicked();

    void on_pushButton_2_clicked();

    void on_radioButtonParallax_toggled(bool checked);

    void on_checkBoxParallax_toggled(bool checked);

    void on_sliderParallax_sliderReleased();

    void on_comboBox_currentIndexChanged(int index);

    void on_pushButtonExportTo_clicked();

    void open_files(QStringList fileNames);


    void on_actionPresets_triggered();

    void on_pushButtonColorSpec_clicked();

    void on_horizontalSliderSpec_valueChanged(int value);

    void on_horizontalSliderSpecScatter_valueChanged(int value);

private:
    QImage image, normal, parallax;
    Ui::MainWindow *ui;
    QOpenGLWidget *gl;
    QGraphicsScene *m_normal_scene;
    QGraphicsScene *m_raw_scene;
    ImageProcessor *processor;
    ImageProcessor *sample_processor;
    QVector3D currentColor, currentAmbientcolor, currentBackgroundColor, currentSpecColor;
    QThread *processingThread;
    QList <ImageProcessor *> processorList;
    ImageLoader il;
};

#endif // MAINWINDOW_H
