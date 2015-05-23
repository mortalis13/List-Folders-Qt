#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include "Models/scandirectory.h"
#include "Models/modelobserver.h"
#include "Models/database.h"

class Model : public QObject
{
    Q_OBJECT
public:
    explicit Model(QObject *parent = 0);
    void startScan(const QHash<QString, QVariant> &fields);
    QString processText(const QString& text);
    void registerObserver(ModelObserver *observer);
    void saveConfig(const QHash<QString, QVariant> &fields);
    QHash<QString, QVariant> loadConfig();
    void stopScan();
signals:

public slots:

private:
    QList<ModelObserver*> observers;
    ScanDirectory *scandir;
    Database *db;
};

#endif // MODEL_H
