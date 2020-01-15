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

#include "gui/presetsmanager.h"
#include "mainwindow.h"
#include "src/imageprocessor.h"
#include <QApplication>
#include <QCommandLineParser>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QOpenGLContext>
#include <QStandardPaths>
#include <QTranslator>

QCoreApplication *createApplication(int &argc, char *argv[]) {
  for (int i = 1; i < argc; ++i)
    if (!qstrcmp(argv[i], "--no-gui"))
      return new QCoreApplication(argc, argv);
  return new QApplication(argc, argv);
}

int main(int argc, char *argv[]) {
  QCoreApplication::setApplicationName("laigter");
  QCoreApplication::setApplicationVersion("1.9");

  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts);

  QTranslator translator;
  bool loaded = translator.load(QLocale::system(), ":/laigter", "_");
  //bool loaded = translator.load(":/laigter_el");
  if (!loaded) {
    // Fallback to English
    translator.load(":/laigter_en");
  }


#ifndef PORTABLE
  QString appData =
      QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
  QDir dir(appData);
  if (!dir.exists())
    dir.mkpath(".");
  dir = QDir(appData + "/presets");
  if (!dir.exists())
    dir.mkpath(".");

  dir = QDir(appData + "/plugins");
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

  QCommandLineOption softOpenGl(QStringList() << "s"
                                              << "software-opengl",
                                "Use software opengl renderer.");
  argsParser.addOption(softOpenGl);

  QCommandLineOption noGuiOption(QStringList() << "g"
                                               << "no-gui",
                                 "do not start graphical interface");
  argsParser.addOption(noGuiOption);

  QCommandLineOption inputDiffuseTextureOption(QStringList() << "d"
                                                             << "diffuse",
                                               "diffuse texture to load",
                                               "diffuse texture path");
  argsParser.addOption(inputDiffuseTextureOption);

  QCommandLineOption outputNormalTextureOption(QStringList() << "n"
                                                             << "normal",
                                               "generate normals");
  argsParser.addOption(outputNormalTextureOption);

  QCommandLineOption outputSpecularTextureOption(QStringList() << "c"
                                                               << "specular",
                                                 "generate specular");
  argsParser.addOption(outputSpecularTextureOption);

  QCommandLineOption outputOcclusionTextureOption(QStringList() << "o"
                                                                << "occlusion",
                                                  "generate occlusion");
  argsParser.addOption(outputOcclusionTextureOption);

  QCommandLineOption outputParallaxTextureOption(QStringList() << "p"
                                                               << "parallax",
                                                 "generate parallax");
  argsParser.addOption(outputParallaxTextureOption);

  QCommandLineOption pressetOption(QStringList() << "r"
                                                 << "preset",
                                   "presset to load", "preset file path");
  argsParser.addOption(pressetOption);

  QSurfaceFormat fmt;
  fmt.setDepthBufferSize(24);
  fmt.setSamples(16);
  fmt.setProfile(QSurfaceFormat::CompatibilityProfile);
  QSurfaceFormat::setDefaultFormat(fmt);

  QScopedPointer<QCoreApplication> app(createApplication(argc, argv));
  argsParser.process(*app.data());
  QImage auximage;

  ImageProcessor *processor = new ImageProcessor();

  bool succes = false;
  QString inputDiffuseTextureOptionValue =
      argsParser.value(inputDiffuseTextureOption);
  if (!inputDiffuseTextureOptionValue.trimmed().isEmpty()) {
    QFileInfo info(inputDiffuseTextureOptionValue);
    QString suffix =
        info.suffix(); // just the last suffix, not the complete one

    QString pressetOptionValue = argsParser.value(pressetOption);
    ImageLoader il;
    auximage = il.loadImage(inputDiffuseTextureOptionValue, &succes);
    auximage = auximage.convertToFormat(QImage::Format_RGBA8888_Premultiplied);
    processor->loadImage(inputDiffuseTextureOptionValue, auximage);
    if (!pressetOptionValue.trimmed().isEmpty()) {
      PresetsManager::applyPresets(pressetOptionValue, *processor);
    }
    QString pathWithoutExtension = info.absoluteFilePath().remove("." + suffix);
    if (argsParser.isSet(outputNormalTextureOption)) {
      QImage normal = *processor->get_normal();
      QString name = pathWithoutExtension + "_n." + suffix;
      normal.save(name);
    }
    if (argsParser.isSet(outputSpecularTextureOption)) {
      QImage specular = *processor->get_specular();
      QString name = pathWithoutExtension + "_s." + suffix;
      specular.save(name);
    }
    if (argsParser.isSet(outputOcclusionTextureOption)) {
      QImage occlusion = *processor->get_occlusion();
      QString name = pathWithoutExtension + "_o." + suffix;
      occlusion.save(name);
    }
    if (argsParser.isSet(outputParallaxTextureOption)) {
      QImage parallax = *processor->get_parallax();
      QString name = pathWithoutExtension + "_p." + suffix;
      parallax.save(name);
    }
  }

  QApplication *a = qobject_cast<QApplication *>(app.data());
  int returnCode;
  if (a) {
    a->installTranslator(&translator);
    bool softOpenGlValue = argsParser.isSet(softOpenGl);
    if (softOpenGlValue) {
      a->setAttribute(Qt::AA_UseSoftwareOpenGL);
      qDebug() << "Soft OpenGL";
    }
    MainWindow w;
    QGuiApplication::setWindowIcon(QIcon(":/images/laigter-icon.png"));

    w.show();
    qRegisterMetaType<ProcessedImage>("ProcessedImage");

    if (succes) {
      w.add_processor(processor);
    } else {
      delete processor;
    }

    returnCode = app->exec();
  } else {
    // do CLI only things here
    returnCode = 0;
  }
  return returnCode;
}
