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

bool Project::load(QString project_path, QList<ImageProcessor *> *p_list, QJsonObject *general_settings){
  void *buf = NULL;
  size_t bufsize;
  QJsonDocument doc;
  QJsonObject project_json;
  QByteArray data;

  /*TODO erase this when using real general_settings */
  general_settings = new QJsonObject;

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
      QImage diffuse;
      data.clear();
      QJsonArray frames = p_json.value("frames").toArray();
      for (int j = 0; j < frames.count(); j++)
      {
        QJsonObject frame = frames.at(j).toObject();
        zip_entry_open(zip, frame.value("diffuse").toString().toUtf8());
        {
          zip_entry_read(zip, &buf, &bufsize);
          data.append((char*)buf, bufsize);
          diffuse = QImage::fromData(data);
          p->loadImage("", diffuse);
        }
        zip_entry_close(zip);
      }

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

bool Project::save(QString path, QJsonObject general_settings)
{
  QJsonArray json_array;
  m_path = path;
  struct zip_t *zip = zip_open(path.toUtf8(), ZIP_DEFAULT_COMPRESSION_LEVEL, 'w');
  for (int j = 0; j < processorList->count(); j++)
  {
    ImageProcessor *p = processorList->at(j);
    QJsonObject processor_json;
    processor_json.insert("processor name", p->get_name());
    processor_json.insert("frame count", p->frames.count());

    QJsonArray frames_json;
    for (int i = 0; i < p->frames.count(); i++)
    {
      QJsonObject frame_json;
      frame_json.insert("id", i);
      p->set_current_frame_id(i);
      Sprite *s = p->get_current_frame();
      QString name;
      QImage texture;
      bool save = true;
      for (int i = 0; i < types.count(); i++)
      {
        s->get_image((TextureTypes)i, &texture);
        switch ((TextureTypes)i)
        {
          case TextureTypes::Heightmap:
          {
            name = s->heightmapPath;
            save = name != "";
            break;
          }

          case TextureTypes::SpecularBase:
          {
            name = s->specularPath;
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
            name = s->fileName;
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
