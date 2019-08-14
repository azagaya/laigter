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
#include <QCommandLineParser>
#include "gui/presetsmanager.h"

void applyPresetSettings(QByteArray& setting, ImageProcessor &p){
    Ui::preset_codes_array& presetCodes = PresetsManager::get_preset_codes();
    QList<QByteArray> aux = setting.split('\t');
    if (aux[0] == presetCodes[0]){
        p.set_normal_depth(aux[1].toInt());
    }else if (aux[0] == presetCodes[1]){
        p.set_normal_blur_radius(aux[1].toInt());
    }else if (aux[0] == presetCodes[2]){
        p.set_normal_bisel_depth(aux[1].toInt());
    }else if (aux[0] == presetCodes[3]){
        p.set_normal_bisel_distance(aux[1].toInt());
    }else if (aux[0] == presetCodes[4]){
        p.set_normal_bisel_blur_radius(aux[1].toInt());
    }else if (aux[0] == presetCodes[5]){
        p.set_normal_bisel_soft((bool)aux[1].toInt());
    }else if (aux[0] == presetCodes[6]){
        p.set_tileable((bool)aux[1].toInt());
    }else if (aux[0] == presetCodes[7]){
        p.set_normal_invert_x((bool)aux[1].toInt());
    }else if (aux[0] == presetCodes[8]){
        p.set_normal_invert_y((bool)aux[1].toInt());
    }else if (aux[0] == presetCodes[9]){
        p.set_parallax_type((ParallaxType)aux[1].toInt());
    }else if (aux[0] == presetCodes[10]){
        p.set_parallax_thresh(aux[1].toInt());
    }else if (aux[0] == presetCodes[11]){
        p.set_parallax_focus(aux[1].toInt());
    }else if (aux[0] == presetCodes[12]){
        p.set_parallax_soft(aux[1].toInt());
    }else if (aux[0] == presetCodes[13]){
        p.set_parallax_min(aux[1].toInt());
    }else if (aux[0] == presetCodes[14]){
        p.set_parallax_erode_dilate(aux[1].toInt());
    }else if (aux[0] == presetCodes[15]){
        p.set_parallax_brightness(aux[1].toInt());
    }else if (aux[0] == presetCodes[16]){
        p.set_parallax_contrast(aux[1].toInt());
    }else if (aux[0] == presetCodes[17]){
        p.set_parallax_invert((bool)aux[1].toInt());
    }else if (aux[0] == presetCodes[18]){
        p.set_specular_blur(aux[1].toInt());
    }else if (aux[0] == presetCodes[19]){
        p.set_specular_bright(aux[1].toInt());
    }else if (aux[0] == presetCodes[20]){
        p.set_specular_contrast(aux[1].toInt());
    }else if (aux[0] == presetCodes[21]){
        p.set_specular_thresh(aux[1].toInt());
    }else if (aux[0] == presetCodes[22]){
        p.set_specular_invert((bool)aux[1].toInt());
    }else if (aux[0] == presetCodes[23]){
        p.set_occlusion_blur(aux[1].toInt());
    }else if (aux[0] == presetCodes[24]){
        p.set_occlusion_bright(aux[1].toInt());
    }else if (aux[0] == presetCodes[25]){
        p.set_occlusion_invert((bool)aux[1].toInt());
    }else if (aux[0] == presetCodes[26]){
        p.set_occlusion_thresh(aux[1].toInt());
    }else if (aux[0] == presetCodes[27]){
        p.set_occlusion_contrast(aux[1].toInt());
    }else if (aux[0] == presetCodes[28]){
        p.set_occlusion_distance(aux[1].toInt());
    }else if (aux[0] == presetCodes[29]){
        p.set_occlusion_distance_mode((bool)aux[1].toInt());
    }
}

void applyPresets(QString &preset, ImageProcessor &p){
    QFile selected_preset(preset);
    if(!selected_preset.open(QIODevice::ReadOnly)){
        return;
    }
    QByteArray settings = selected_preset.readAll();
    QList<QByteArray> settings_list = settings.split('\n');

    for (int i=0; i< settings_list.count(); i++){
        QByteArray setting = settings_list.at(i);
        applyPresetSettings(setting, p);
    }
}

QCoreApplication* createApplication(int &argc, char *argv[])
{
    for (int i = 1; i < argc; ++i)
        if (!qstrcmp(argv[i], "--no-gui"))
            return new QCoreApplication(argc, argv);
    return new QApplication(argc, argv);
}

int main(int argc, char *argv[])
{
    QCoreApplication::setApplicationName("laigter");
    QCoreApplication::setApplicationVersion("1.5.1.0");

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

    QCommandLineParser argsParser;
    argsParser.setApplicationDescription("Test helper");
    argsParser.addHelpOption();
    argsParser.addVersionOption();

    QCommandLineOption softOpenGl(QStringList() << "s" << "software-opengl",
        "Use software opengl renderer.");
    argsParser.addOption(softOpenGl);

    QCommandLineOption noGuiOption(QStringList() << "g" << "no-gui",
        "do not start graphical interface");
    argsParser.addOption(noGuiOption);

    QCommandLineOption inputDiffuseTextureOption(QStringList() << "d" << "diffuse",
        "diffuse texture to load",
        "diffuse texture path");
    argsParser.addOption(inputDiffuseTextureOption);

    QCommandLineOption outputNormalTextureOption(QStringList() << "n" << "normal",
        "generate normals");
    argsParser.addOption(outputNormalTextureOption);

    QCommandLineOption outputSpecularTextureOption(QStringList() << "c" << "specular",
        "generate specular");
    argsParser.addOption(outputSpecularTextureOption);

    QCommandLineOption outputOcclusionTextureOption(QStringList() << "o" << "occlusion",
        "generate occlusion");
    argsParser.addOption(outputOcclusionTextureOption);

    QCommandLineOption outputParallaxTextureOption(QStringList() << "p" << "parallax",
        "generate parallax");
    argsParser.addOption(outputParallaxTextureOption);

    QCommandLineOption pressetOption(QStringList() << "r" << "preset",
        "presset to load",
        "preset file path");
    argsParser.addOption(pressetOption);

    QScopedPointer<QCoreApplication> app(createApplication(argc, argv));
    argsParser.process(*app.data());

    QString inputDiffuseTextureOptionValue = argsParser.value(inputDiffuseTextureOption);
    if(!inputDiffuseTextureOptionValue.trimmed().isEmpty()){
        QFileInfo info(inputDiffuseTextureOptionValue);
        QString suffix = info.suffix(); // just the last suffix, not the complete one

        QString pressetOptionValue = argsParser.value(pressetOption);
        ImageLoader il;
        bool succes;
        QImage auximage = il.loadImage(inputDiffuseTextureOptionValue , &succes);
        auximage = auximage.convertToFormat(QImage::Format_RGBA8888_Premultiplied);
        ImageProcessor *processor = new ImageProcessor();
        processor->loadImage(inputDiffuseTextureOptionValue , auximage);
        if(!pressetOptionValue.trimmed().isEmpty()){
            applyPresets(pressetOptionValue, *processor);
        }
        QString pathWithoutExtension = info.absoluteFilePath().remove("."+suffix);
        if(argsParser.isSet(outputNormalTextureOption)){
            QImage normal = processor->get_normal();
            QString name = pathWithoutExtension+"_n."+suffix;
            normal.save(name);
        }
        if(argsParser.isSet(outputSpecularTextureOption)){
            QImage specular = processor->get_specular();
            QString name = pathWithoutExtension+"_s."+suffix;
            specular.save(name);
        }
        if(argsParser.isSet(outputOcclusionTextureOption)){
            QImage occlusion = processor->get_occlusion();
            QString name = pathWithoutExtension+"_o."+suffix;
            occlusion.save(name);
        }
        if(argsParser.isSet(outputParallaxTextureOption)){
            QImage parallax = processor->get_parallax();
            QString name = pathWithoutExtension+"_p."+suffix;
            parallax.save(name);
        }
    }

    QApplication* a = qobject_cast<QApplication *>(app.data());
    int returnCode;
    if (a) {
        a->installTranslator(&translator);
        bool softOpenGlValue = argsParser.isSet(softOpenGl);
        if (softOpenGlValue){
            a->setAttribute(Qt::AA_UseSoftwareOpenGL);
            qDebug() << "Soft OpenGL";
        }
        MainWindow w;
        QGuiApplication::setWindowIcon(QIcon(":/images/laigter-icon.png"));
        w.show();
        qRegisterMetaType<ProcessedImage>("ProcessedImage");
        returnCode = app->exec();
    } else {
        // do CLI only things here
        returnCode = 0;
    }
    return returnCode;
}
