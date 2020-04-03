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

bool Project::save(QString path)
{
  QString zipname = path;
  QJsonObject json;
  struct zip_t *zip = zip_open(zipname.toUtf8(), ZIP_DEFAULT_COMPRESSION_LEVEL, 'w');
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
          name = dir.path() + "/" +
                 name.split("/").last().split(".").join(
                     suffixes.at(i) + ".");
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
      frames_json.append(frame_json);
    }
    processor_json.insert("frames", frames_json);
    QJsonDocument doc_json(processor_json);

    zip_entry_open(zip, "project.json");
    {
      zip_entry_write(zip, doc_json.toJson(), doc_json.toJson().count());
    }
    zip_entry_close(zip);
  }

  zip_close(zip);
  return true;
}
