#ifndef MODELOBSERVER_H
#define MODELOBSERVER_H

class ModelObserver
{
public:
  ModelObserver();
  virtual void updateState(int progress)=0;
};

#endif // MODELOBSERVER_H
