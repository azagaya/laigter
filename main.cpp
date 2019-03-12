#include "mainwindow.h"
#include "src/imageprocessor.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    qRegisterMetaType<ProcessedImage>("ProcessedImage");
    return a.exec();
}
