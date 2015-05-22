#ifndef TESTTHREAD_H
#define TESTTHREAD_H

#include <QThread>

class TestThread : public QThread
{
  Q_OBJECT
public:
  explicit TestThread(QObject *parent = 0);

signals:

public slots:

};

#endif // TESTTHREAD_H
