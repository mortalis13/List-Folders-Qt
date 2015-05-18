#include "scandirectory.h"
#include <QDir>

ScanDirectory::ScanDirectory(QObject *parent) : QObject(parent)
{
    text="";
}

QString ScanDirectory::startScan(const QString &path)
{
    fullScan(path);
    return text;
}

void ScanDirectory::fullScan(const QString &dir, int level)
{
    QDir qdir=QDir(dir);

    qdir.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
    foreach(QFileInfo nextDir, qdir.entryInfoList()){
        text+=nextDir.fileName()+nl;
    }

    qdir.setFilter(QDir::Files);
    foreach(QFileInfo nextFile, qdir.entryInfoList()){
        text+=nextFile.fileName()+nl;
    }
}
