#include "gui/presets_manager.h"
#include "gui/presets_manager.h"
#include "project.h"

#include <QDebug>
#include <QFile>
#include <QImage>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStandardPaths>
#include <QTemporaryDir>

extern "C"
{
#include "thirdparty/zip.h"
}

Project::Project(QObject *parent) : QObject(parent) {}

QString Project::GetCurrentPath(){
  return m_path;
}

bool Project::load(QString project_path, QList<ImageProcessor *> *p_list, QJsonObject *general_settings){
  void *buf = NULL;
  size_t bufsize;
  QJsonDocument doc;
  QJsonObject project_json;
  QByteArray data;

  QFileInfo info(project_path);
  if (!info.exists())
  {
    return 1;
  }

  m_path = project_path;

  struct zip_t *zip = zip_open(project_path.toUtf8(), 0, 'r');
  {
    /* Load project json */
    zip_entry_open(zip, "project.json");
    {
      zip_entry_read(zip, &buf, &bufsize);
    }
    zip_entry_close(zip);
    data.append((char*)buf, bufsize);
    QJsonParseError e;
    doc = QJsonDocument::fromJson(data,&e);
    project_json = doc.object();
    /* Set general settings */
    general_settings->insert("general", project_json.value("general"));

    /* Start generating the processors */
    QJsonArray processors = project_json.value("processors").toArray();
    for (int i = 0; i < processors.count(); i++)
    {
      QJsonObject p_json = processors.at(i).toObject();
      QString processor_name = p_json.value("processor name").toString();
      ImageProcessor *p = new ImageProcessor;
      p->set_name(processor_name);
      /* Read Diffuse image. Maps are calculated when settings applied */

      QJsonArray frames = p_json.value("frames").toArray();
      for (int j = 0; j < frames.count(); j++)
      {
        data.clear();
        QImage diffuse;
        QJsonObject frame = frames.at(j).toObject();
        QString path = frame.value("diffuse").toString();
        zip_entry_open(zip, path.toUtf8());
        {
          zip_entry_read(zip, &buf, &bufsize);
          data.append((char*)buf, bufsize);
          diffuse = QImage::fromData(data);
          p->loadImage(path, diffuse);
        }
        zip_entry_close(zip);

        /* Restore Neighbours */
        data.clear();
        path = frame.value("neighbours").toString();
        zip_entry_open(zip, path.toUtf8());
        {
          zip_entry_read(zip, &buf, &bufsize);
          data.append((char*)buf, bufsize);
          p->get_current_frame()->set_image(TextureTypes::Neighbours, QImage::fromData(data));
        }
        zip_entry_close(zip);


      }

      /* restore postion of processor */
      QVector3D position;
      position.setX(p_json.value("position").toObject().value("x").toDouble());
      position.setY(p_json.value("position").toObject().value("y").toDouble());
      position.setZ(p_json.value("position").toObject().value("z").toDouble());

      p->set_position(position);

      /* restore tile options */

      p->set_tile_x(p_json.value("tile x").toBool());
      p->set_tile_y(p_json.value("tile y").toBool());

      /* restore individual zoom */

      p->set_zoom(p_json.value("zoom").toDouble());

      /* Read Presets */
      data.clear();
      zip_entry_open(zip, (processor_name+"/"+processor_name+".presets").toUtf8());
      {
        zip_entry_read(zip, &buf, &bufsize);
        data.append((char*)buf, bufsize);
      }
      zip_entry_close(zip);

      PresetsManager::applyPresetsString(data,p);
      p_list->append(p);
    }

  }
  zip_close(zip);

  free(buf);
  return true;
}

bool Project::save(QString path, QList<ImageProcessor *>processorList, QJsonObject general_settings)
{
  QJsonArray json_array;
  m_path = path;
  struct zip_t *zip = zip_open(path.toUtf8(), ZIP_DEFAULT_COMPRESSION_LEVEL, 'w');
  for (int j = 0; j < processorList.count(); j++)
  {
    ImageProcessor *p = processorList.at(j);
    QJsonObject processor_json;
    processor_json.insert("processor name", p->get_name());
    processor_json.insert("frame count", p->frames.count());

    QJsonArray frames_json;
    for (int i = 0; i < p->frames.count(); i++)
    {
      QJsonObject frame_json;
      frame_json.insert("id", i);
      Sprite s;
      s = p->frames[i];
      QString name;
      for (int i = 0; i < types.count(); i++)
      {
        QImage texture;
        s.get_image((TextureTypes)i, &texture);
        bool save = true;
        switch ((TextureTypes)i)
        {
          case TextureTypes::Heightmap:
          {
            name = s.heightmapPath;
            save = name != "";
            break;
          }

          case TextureTypes::SpecularBase:
          {
            name = s.specularPath;
            save = name != "";
            break;
          }

          case TextureTypes::OcclussionBase:
          {
            save = false;
            break;
          }

          default:
          {
            name = s.fileName;
            break;
          }
        }

        if (save)
        {
          QDir dir(QStandardPaths::writableLocation(
              QStandardPaths::TempLocation));
          name = dir.path() + "/" + name.split("/").last().split(".").join(suffixes.at(i) + ".");
          texture.save(name);
          QString entry_name = p->get_name() + "/" + types.at(i) + "/" + name.split("/").last();

          frame_json.insert(types.at(i), entry_name);

          zip_entry_open(zip, entry_name.toUtf8());
          {
            QFile f(name);
            if (f.open(QIODevice::ReadOnly))
            {
              QByteArray a = f.readAll();
              zip_entry_write(zip, a, a.count());
              f.close();
            }
          }
          zip_entry_close(zip);
        }
      }
      zip_entry_open(zip, (p->get_name() + "/" +p->get_name()+".presets").toUtf8());
      {
        QDir dir(QStandardPaths::writableLocation(
            QStandardPaths::TempLocation));
        name = dir.path() + "/" + p->get_name()+".presets";
        PresetsManager::SaveAllPresets(p,name);
        QFile f(name);
        if (f.open(QIODevice::ReadOnly))
        {
          QByteArray content = f.readAll();
          zip_entry_write(zip, content, content.count());
        }
      }
      zip_entry_close(zip);
      frames_json.append(frame_json);
    }
    processor_json.insert("frames", frames_json);
    processor_json.insert("presets",p->get_name() + "/" +p->get_name()+".presets");
    QJsonObject position;
    position.insert("x",p->get_position()->x());
    position.insert("y",p->get_position()->y());
    position.insert("z",p->get_position()->z());
    processor_json.insert("position",position);

    /* tile preview options */
    processor_json.insert("tile x", p->get_tile_x());
    processor_json.insert("tile y", p->get_tile_y());

    /* individual zoom option */
    processor_json.insert("zoom", p->get_zoom());

    json_array.append(processor_json);

  }
  QJsonObject project_json;
  project_json.insert("processors",json_array);
  project_json.insert("general",general_settings);
  QJsonDocument json_project(project_json);
  zip_entry_open(zip, "project.json");
  {
    zip_entry_write(zip, json_project.toJson(), json_project.toJson().count());
  }
  zip_entry_close(zip);

  zip_close(zip);

  return true;
}
