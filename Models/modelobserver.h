#ifndef MODELOBSERVER_H
#define MODELOBSERVER_H

#include <QtCore>

// helper class to notify the view about the model state changes

class ModelObserver
{
public:
  ModelObserver();
  virtual void updateState(QString currentDir, QString timeString, int progress, int dirCount, int rootDirCount)=0;
  virtual void updateStatusBar(QString type, QString currentDir="", QString totalTime="")=0;
  virtual void scanningFinished(int totalTime)=0;
};

#endif // MODELOBSERVER_H
