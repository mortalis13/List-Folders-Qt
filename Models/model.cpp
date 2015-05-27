#include "model.h"

#include "Models/scandirectory.h"
#include "Models/modelobserver.h"
#include "Models/modelfunctions.h"

Model::Model()
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

void Model::stopScan(){
  scandir->stopScan();
}

/*
 * Returns fields map which is used by the view to fill the field values on the form
 */
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

/*
 * Saves form fields to the database
 */
void Model::saveConfig(const QHash<QString, QVariant> &fields)
{
  QString json=ModelFunctions::encodeFields(fields);
  db->updateConfig("last", json);
  db->closeConnection();               // edit place of closing DB
}

/*
 * Registers view to get the model state messages
 */
void Model::registerObserver(ModelObserver *observer){
  observers.append(observer);
}
