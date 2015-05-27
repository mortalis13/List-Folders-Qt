#ifndef SCANDIRECTORY_H
#define SCANDIRECTORY_H

#include <QObject>
#include <QStringList>
#include <QThread>
#include <QTime>

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

#include "Models/Tree/treenode.h"
#include "Models/modelobserver.h"

class ScanDirectory:public QThread
{
    Q_OBJECT

public:
    explicit ScanDirectory();

    void startScan();
    void stopScan();
    
    void init(const QHash<QString, QVariant> &fields);
    void run();
    
    QString getText();
    QString getJson();
    
    void registerObservers(QList<ModelObserver *> observers);

public slots:
    void notifyObservers(QString currentDir, QString timeString, int progress);
    void notifyUpdateStatusBar(QString type, QString currentDir);
    void notifyScanningFinished();
    
signals:
    void updateState(QString, QString, int);
    void updateStatusBar(QString, QString);
    void scanningFinished();

private:
    const QString nl="\n";
    const QString pad="    ";
    const QString iconsPath="./lib/images/";

    bool scanCanceled;

    QString path;

    QString text;
    QString json;
    QJsonArray jsonArray;
    QString exportName;

    QStringList filterExt;
    QStringList excludeExt;
    QStringList filterDir;

    bool doExportText;
    bool doExportTree;

    int dirCount;
    int rootDirCount;
    long prevTime;
    int totalTime;
    QTime time;

    static QStringList exts;
    static QStringList imageExts;
    static QStringList musicExts;
    static QStringList videoExts;
    static QStringList codeExts;

    QList<ModelObserver*> observers;
    
    QJsonArray fullScan(const QString& dir, int level=0);
    void prepareProcessing();
    void done();
    
    QString replaceTemplate(QString tmpl, QString replacement, QString text);
    QString getPadding(int level);
    QStringList getFilters(QString filter);
    QString getIcon(QString file);
    
    int logStats(QString currentDir, int progress);
    int getDirCount(int totalCount);
    
    bool filterDirectory(QString dir);
    bool filterFile(QString file);
    QString getFiltersText();
    
    void exportText();
    void exportTree();
    QString getExportName(QString ext="");
    
};

#endif // SCANDIRECTORY_H
