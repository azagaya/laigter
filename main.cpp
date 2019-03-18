#include "mainwindow.h"
#include "src/imageprocessor.h"
#include <QApplication>
#include <QTranslator>
#include <QFile>
#include <QStandardPaths>

int main(int argc, char *argv[])
{
#if defined(Q_OS_WIN)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QString locale = QLocale::system().name().split("_").at(0);
    QTranslator translator;
    bool loaded = translator.load(":/laigter_"+locale);
    if (!loaded) translator.load("laigter_en");

    QApplication a(argc, argv);
    a.installTranslator(&translator);

    MainWindow w;
    QGuiApplication::setWindowIcon(QIcon(":/images/laigter-icon.png"));
    w.show();
    qRegisterMetaType<ProcessedImage>("ProcessedImage");
    return a.exec();
}
