#ifndef MODELOBSERVER_H
#define MODELOBSERVER_H

#include <QtCore>

class ModelObserver
{
public:
  ModelObserver();
  virtual void updateState(QString currentDir, QString timeString, int progress, int dirCount, int rootDirCount)=0;
  virtual void updateStatusBar(QString type, QString currentDir="", QString totalTime="")=0;
  virtual void scanningFinished(int totalTime)=0;
};

#endif // MODELOBSERVER_H
