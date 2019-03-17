#include "mainwindow.h"
#include "src/imageprocessor.h"
#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
#if defined(Q_OS_WIN)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QString locale = QLocale::system().name().split("_").at(0);
    QTranslator translator;
    translator.load(":/laigter_"+locale);

    QApplication a(argc, argv);
    a.installTranslator(&translator);


    MainWindow w;
    QGuiApplication::setWindowIcon(QIcon(":/images/laigter-icon.png"));
    w.show();
    qRegisterMetaType<ProcessedImage>("ProcessedImage");
    return a.exec();
}
