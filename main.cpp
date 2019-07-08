#include "mainwindow.h"
#include "src/imageprocessor.h"
#include <QApplication>
#include <QTranslator>
#include <QFile>
#include <QStandardPaths>
#include <QDebug>
#include <QDir>

int main(int argc, char *argv[])
{
    QCoreApplication::setApplicationName("laigter");
#if defined(Q_OS_WIN)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QString locale = QLocale::system().name().split("_").at(0);
    QTranslator translator;
    bool loaded = translator.load(":/laigter_"+locale);
    if (!loaded)
        translator.load(":/laigter_en");

#ifndef PORTABLE
    QString appData = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir dir(appData);
    if (!dir.exists())
        dir.mkpath(".");
    dir = QDir(appData+"/presets");
    if (!dir.exists())
        dir.mkpath(".");

#else
    QDir dir("./presets");
    if (!dir.exists())
        dir.mkpath(".");
#endif

    QApplication a(argc, argv);
    a.installTranslator(&translator);

    MainWindow w;
    QGuiApplication::setWindowIcon(QIcon(":/images/laigter-icon.png"));
    w.show();
    qRegisterMetaType<ProcessedImage>("ProcessedImage");
    return a.exec();
}
