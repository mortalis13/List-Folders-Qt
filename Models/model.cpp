#include "model.h"
#include "Models/scandirectory.h"
#include "Models/test.h"
#include "Models/modelobserver.h"

#include <QDir>

Model::Model(QObject *parent) :
    QObject(parent)
{
}

void Model::startScan(const QHash<QString, QVariant> &fields)
{
    ScanDirectory *scandir=new ScanDirectory();
    scandir->init(fields);
    scandir->registerObservers(observers);
    scandir->startScan();
}

void Model::registerObserver(ModelObserver *observer){
  observers.append(observer);
}

void Model::notifyObservers(){
  foreach(ModelObserver *observer, observers)
    observer->updateState(5);
}
