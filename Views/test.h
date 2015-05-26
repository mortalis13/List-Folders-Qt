#ifndef TEST_H
#define TEST_H

#include <QtCore>

class Test
{
public:
  Test();
  QString text;

  Test* parent;
  QList<Test*> *children;
};

#endif // TEST_H
