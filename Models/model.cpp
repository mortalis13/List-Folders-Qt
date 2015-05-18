#include "model.h"
#include "Models/scandirectory.h"
#include <QDir>

Model::Model(QObject *parent) :
    QObject(parent)
{
}

QString Model::startScan(const QString &path)
{
    QString res;

    ScanDirectory scandir;
    res=scandir.startScan(path);

    return res;
}

QString Model::processText(const QString &text){
    return "="+text+"=";
}
