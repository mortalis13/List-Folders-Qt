#ifndef TN_H
#define TN_H

#include <QtCore>

class TN
{
public:
  TN();
  QString text;
  
  TN* m_parent;
  QList<TN*> *m_children;
};

#endif // TN_H
