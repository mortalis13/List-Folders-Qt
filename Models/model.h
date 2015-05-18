#ifndef MODEL_H
#define MODEL_H

#include <QObject>

class Model : public QObject
{
    Q_OBJECT
public:
    explicit Model(QObject *parent = 0);
    QString startScan(const QString& path);
    QString processText(const QString& text);
signals:

public slots:
};

#endif // MODEL_H
