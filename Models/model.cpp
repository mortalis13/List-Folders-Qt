#include "model.h"
#include "Models/scandirectory.h"
#include "Models/test.h"
#include "Models/modelobserver.h"
#include "Models/modelfunctions.h"

#include <QDir>

Model::Model(QObject *parent) :
  QObject(parent)
{
  db=new Database;
}

void Model::startScan(const QHash<QString, QVariant> &fields)
{
  scandir=new ScanDirectory();
  scandir->init(fields);
  scandir->registerObservers(observers);
  scandir->startScan();
}

QHash<QString, QVariant> Model::loadConfig()
{
  QHash<QString, QVariant> fields;
  QString json=db->loadLastOptions();
  if(json.length()==0){
    qDebug("No last config in the DB");
    return QHash<QString, QVariant>();
  }
  fields=ModelFunctions::decodeFields(json);
  return fields;
}

void Model::saveConfig(const QHash<QString, QVariant> &fields)
{
  QString json=ModelFunctions::encodeFields(fields);
  db->updateConfig("last", json);
  db->closeConnection();               // edit place of closing DB
}

void Model::registerObserver(ModelObserver *observer){
  observers.append(observer);
}

void Model::stopScan(){
  scandir->stopScan();
}
