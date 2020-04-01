#include "project.h"

#include <QDebug>
#include <QFile>
#include <QImage>
#include <QStandardPaths>
#include <QTemporaryDir>

extern "C"
{
#include "thirdparty/zip.h"
}

Project::Project(QObject *parent) : QObject(parent)
{
}

<<<<<<< HEAD
bool Project::save(QString path){
  QString zipname = path;
  struct zip_t *zip = zip_open(zipname.toUtf8(), ZIP_DEFAULT_COMPRESSION_LEVEL, 'w');
  {
    for (int j = 0; j < processorList->count(); j++){
      ImageProcessor *p = processorList->at(j);
      for (int i = 0; i < p->frames.count(); i++){
        Sprite *s = p->get_current_frame();
        QString name;
        QImage texture;
        bool save = true;
        for (int i=0; i < types.count(); i++){
          s->get_image((TextureTypes)i,&texture);

          switch ((TextureTypes) i) {

          case TextureTypes::Heightmap:
            name = s->heightmapPath;
            save = name != "";

            break;
          case TextureTypes::SpecularBase:
            name = s->specularPath;
            save = name != "";
            break;
          case TextureTypes::OcclussionBase:
            save = false;
            break;
          default:
            name = s->fileName;
            break;
          }

          QDir dir(QStandardPaths::writableLocation(QStandardPaths::TempLocation));
          name = dir.path()+"/"+name.split("/").last().split(".").join(suffixes.at(i)+".");

          texture.save(name);

          zip_entry_open(zip, (p->get_name()+"/"+types.at(i)+"/"+name.split("/").last()).toUtf8());
          {
            QFile f(name);
            if (f.open(QIODevice::ReadOnly)){
              QByteArray a = f.readAll();
              const char *buf = a.constData();
              zip_entry_write(zip, buf, a.count());
              f.close();
            }
          }
          zip_entry_close(zip);
        }
      }
    }
  }
  zip_close(zip);
  return true;
=======
bool Project::save(QString path)
{
	struct zip_t *zip = zip_open(path.toUtf8()+"sample.zip", ZIP_DEFAULT_COMPRESSION_LEVEL, 'w');
	{
		for (int j = 0; j < processorList->count(); j++)
		{
			ImageProcessor *p = processorList->at(j);
			for (int i = 0; i < p->frames.count(); i++)
			{
				Sprite *s = p->get_current_frame();
				QString name;
				QImage texture;
				bool save = true;
				for (int i=0; i < types.count(); i++)
				{
					s->get_image((TextureTypes)i,&texture);
					switch ((TextureTypes) i)
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

					QDir dir(QStandardPaths::writableLocation(QStandardPaths::TempLocation));
					name = dir.path()+"/"+name.split("/").last().split(".").join(suffixes.at(i)+".");
					texture.save(name);
					zip_entry_open(zip, (p->get_name()+"/"+types.at(i)+"/"+name.split("/").last()).toUtf8());
					{
						QFile f(name);
						if (f.open(QIODevice::ReadOnly))
						{
							QByteArray a = f.readAll();
							const char *buf = a.constData();
							zip_entry_write(zip, buf, a.count());
							f.close();
						}
					}
					zip_entry_close(zip);
				}
			}
		}
	}
	zip_close(zip);
	return true;
>>>>>>> df610b52b5c36d592c12f73fd53de2d615a537bd
}
