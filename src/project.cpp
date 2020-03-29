#include "project.h"

#include <QFile>
#include <QImage>
#include <QDebug>

extern "C" {
#include "thirdparty/zip.h"
}

Project::Project(QObject *parent) : QObject(parent)
{

}

bool Project::save(QString path){
  struct zip_t *zip = zip_open(path.toUtf8()+"sample.zip", ZIP_DEFAULT_COMPRESSION_LEVEL, 'w');
  {
    for (int j = 0; j < processorList->count(); j++){
      ImageProcessor *p = processorList->at(j);
      for (int i = 0; i < p->frames.count(); i++){
        QString name = p->frames.at(i).fileName;
        zip_entry_open(zip, (p->get_name()+"/"+name.split("/").last()).toUtf8());
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
  zip_close(zip);
  return true;
}
