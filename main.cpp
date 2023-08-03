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

#include "gui/presets_manager.h"
#include "main_window.h"
#include "src/image_processor.h"

#include <QApplication>
#include <QCommandLineParser>
#include <QDir>
#include <QDirIterator>
#include <QFile>
#include <QOpenGLContext>
#include <QSplashScreen>
#include <QStandardPaths>
#include <QTranslator>

#define cimg_use_openmp 1

QCoreApplication *createApplication(int &argc, char *argv[])
{
  bool gui = true;

  for (int i = 1; i < argc; ++i)
  {
    if (!qstrcmp(argv[i], "--no-gui") || !qstrcmp(argv[i], "-g"))
    {
      gui = false;
      break;
    }
  }

  return gui ? new QApplication(argc, argv) :  new QCoreApplication(argc, argv);
}

int main(int argc, char *argv[])
{
  QCoreApplication::setApplicationName("laigter");
  QCoreApplication::setApplicationVersion("1.10.7-beta");
  //QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts);

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
                                               "diffuse path",
                                               "Path to a diffuse image, or to a directory that contains many diffuse images");
  argsParser.addOption(inputDiffuseTextureOption);

  QCommandLineOption outputNormalTextureOption(QStringList() << "n"
                                                             << "normal",
                                               "generate normals");
  argsParser.addOption(outputNormalTextureOption);

  QCommandLineOption outputSpecularTextureOption(QStringList() << "c"
                                                               << "specular",
                                                 "generate specular");
  argsParser.addOption(outputSpecularTextureOption);

  QCommandLineOption outputOcclusionTextureOption(QStringList()
                                                      << "o"
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

  QCommandLineOption outputLocationOption(QStringList() << "l"
                                                        << "location",
                                          "output directory", "output path");

  argsParser.addOption(outputLocationOption);

  QCommandLineOption notRecursiveOption("not-recursive", "don't look for images recursively");
  argsParser.addOption(notRecursiveOption);

  QCommandLineOption flattenOutputOption("flatten", "don't save in subdirectories");
  argsParser.addOption(flattenOutputOption);

  QSurfaceFormat fmt;
  fmt.setDepthBufferSize(24);
  fmt.setSamples(16);
  fmt.setProfile(QSurfaceFormat::CompatibilityProfile);
  QSurfaceFormat::setDefaultFormat(fmt);
  QScopedPointer<QCoreApplication> app(createApplication(argc, argv));

  argsParser.process(*app.data());
  QImage auximage;

  ImageProcessor *processor = new ImageProcessor();

  bool success = false;
  QString inputDiffuseTextureOptionValue =
      argsParser.value(inputDiffuseTextureOption);

  if (!inputDiffuseTextureOptionValue.trimmed().isEmpty())
  {
    QFileInfo info(inputDiffuseTextureOptionValue);

    QStringList fileList;
    QDir inputDir;

    QString outPath = argsParser.value(outputLocationOption);
    QFileInfo outInfo(outPath);
    QDir outDir(outPath);

    if (info.isFile())
    {
        fileList.append(inputDiffuseTextureOptionValue);
        inputDir = QDir(info.absolutePath());
    }
    else if (info.isDir())
    {
        inputDir = QDir(inputDiffuseTextureOptionValue);
        QDirIterator it(inputDir, argsParser.isSet(notRecursiveOption) ? QDirIterator::NoIteratorFlags : QDirIterator::Subdirectories);

        while (it.hasNext())
        {
            QString found = it.next();
            QFileInfo info(found);

            if (info.isDir())
                continue;

            if (!outDir.relativeFilePath(found).startsWith(".."))
                continue;

            fileList.append(info.absoluteFilePath());
        }
    }


    QString pressetOptionValue = argsParser.value(pressetOption);
    ImageLoader il;





    foreach (QString imagePath, fileList)
    {
        auximage = il.loadImage(imagePath, &success);
        if (!success) continue;
        auximage = auximage.convertToFormat(QImage::Format_RGBA8888_Premultiplied);

        ImageProcessor processor;

        if (!pressetOptionValue.trimmed().isEmpty())
        {
          processor.recalculate_timer.stop();
          PresetsManager::applyPresets(pressetOptionValue, processor);
        }

        processor.loadImage(imagePath, auximage);

        QFileInfo info = QFileInfo(imagePath);
        QString suffix = info.suffix();

        QDir outputDir = outPath.isEmpty() ? QDir(info.path()) : outDir;

        QString relativeToInputPath = argsParser.isSet(flattenOutputOption) ? info.fileName() : inputDir.relativeFilePath(imagePath);
        QString pathWithoutExtension = relativeToInputPath.remove("." + suffix);

        if (argsParser.isSet(outputNormalTextureOption))
        {
          QImage normal = *processor.get_normal();
          outputDir.mkpath(QFileInfo(relativeToInputPath).path());
          QString name = outputDir.filePath(pathWithoutExtension + "_n." + suffix);
          normal.save(name);
        }

        if (argsParser.isSet(outputSpecularTextureOption))
        {
          QImage specular = *processor.get_specular();
          QString name = outputDir.filePath(pathWithoutExtension + "_s." + suffix);
          specular.save(name);
        }

        if (argsParser.isSet(outputOcclusionTextureOption))
        {
          QImage occlusion = *processor.get_occlusion();
          QString name = outputDir.filePath(pathWithoutExtension + "_o." + suffix);
          occlusion.save(name);
        }

        if (argsParser.isSet(outputParallaxTextureOption))
        {
          QImage parallax = *processor.get_parallax();
          QString name = outputDir.filePath(pathWithoutExtension + "_p." + suffix);
          parallax.save(name);
        }
    }
  }

  QApplication *a = qobject_cast<QApplication *>(app.data());
  int returnCode;
  if (a)
  {
    bool softOpenGlValue = argsParser.isSet(softOpenGl);
    if (softOpenGlValue)
    {
      a->setAttribute(Qt::AA_UseSoftwareOpenGL);
    }
    MainWindow w;
    QGuiApplication::setWindowIcon(QIcon(":/images/laigter_icon.png"));

    w.show();
    qRegisterMetaType<ProcessedImage>("ProcessedImage");

    if (success)
      w.add_processor(processor);
    else
      delete processor;

    /* Load Project if dropped. Only supports one project */
    if (argsParser.positionalArguments().count() > 0)
    {
      QString project_path = argsParser.positionalArguments().at(0);
      w.LoadProject(project_path);
    }

    returnCode = app->exec();
  }
  else
  {
    // do CLI only things here
    returnCode = 0;
  }

  return returnCode;
}
