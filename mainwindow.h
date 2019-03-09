#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QOpenGLWidget>
#include "src/imageprocessor.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void update_scene(QPixmap pixmap, ProcessedImage type);
private slots:
    void on_actionOpen_triggered();

    void on_actionFitZoom_triggered();

    void on_actionZoom_100_triggered();

    void on_actionZoomIn_triggered();

    void on_actionZoomOut_triggered();

    void on_actionExport_triggered();

private:
    QPixmap m_pixmap;
    Ui::MainWindow *ui;
    QOpenGLWidget *gl;
    QGraphicsScene *m_normal_scene;
    QGraphicsScene *m_raw_scene;
    ImageProcessor processor;
};

#endif // MAINWINDOW_H
