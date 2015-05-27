#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include "Models/scandirectory.h"
#include "Models/modelobserver.h"
#include "Models/database.h"

class Model
{
public:
    explicit Model();
    
    void startScan(const QHash<QString, QVariant> &fields);
    void stopScan();
    
    void saveConfig(const QHash<QString, QVariant> &fields);
    QHash<QString, QVariant> loadConfig();
    void registerObserver(ModelObserver *observer);

private:
    QList<ModelObserver*> observers;
    ScanDirectory *scandir;
    Database *db;
};

#endif // MODEL_H
