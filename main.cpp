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

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

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
    if (argc > 1){
        if (*argv[1] == 's'){
            a.setAttribute(Qt::AA_UseSoftwareOpenGL);
            qDebug() << "Soft OpenGL";
        }
    }
    MainWindow w;
    QGuiApplication::setWindowIcon(QIcon(":/images/laigter-icon.png"));
    w.show();
    qRegisterMetaType<ProcessedImage>("ProcessedImage");
    return a.exec();
}
