#ifndef SCANDIRECTORY_H
#define SCANDIRECTORY_H

#include <QObject>

class ScanDirectory : public QObject
{
    Q_OBJECT

public:
    explicit ScanDirectory(QObject *parent = 0);
    QString startScan(const QString& path);
private:
    const QString nl="\n";
    QString text;
    void fullScan(const QString& dir, int level=0);

};

#endif // SCANDIRECTORY_H
