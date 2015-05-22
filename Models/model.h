#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include "Models/modelobserver.h"

class Model : public QObject
{
    Q_OBJECT
public:
    explicit Model(QObject *parent = 0);
    void startScan(const QHash<QString, QVariant> &fields);
    QString processText(const QString& text);
    void registerObserver(ModelObserver *observer);
signals:

public slots:

private:
    QList<ModelObserver*> observers;
    void notifyObservers();
};

#endif // MODEL_H
