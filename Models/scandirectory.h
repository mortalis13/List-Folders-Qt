#ifndef SCANDIRECTORY_H
#define SCANDIRECTORY_H

#include <QObject>
#include <QStringList>

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

#include "Models/Tree/treenode.h"

#include "Models/testbase.h"

class TestBase;

class ScanDirectory : public QObject
{
    Q_OBJECT

public:
    explicit ScanDirectory(QObject *parent = 0);
    void startScan();
    void init(const QHash<QString, QVariant> &fields);
    void test();
    QString getResult();
    void fillList();
    QString getList();
    QString getText();
    QString getJson();
private:
    const QString nl="\n";
    const QString pad="    ";
    const QString iconsPath="./lib/images/";

    QString path;       //??

    QString text;
    QString json;
    QJsonArray jsonArray;
//    QList<TreeNode*> jsonArray;

    QList<QString> nameList;
    QList<TestBase*> nodeList;

    QStringList filterExt;
    QStringList excludeExt;
    QStringList filterDir;

    bool doExportText;
    bool doExportTree;

    QString exportName;

    int dirCount;
    int rootDirCount;
    long prevTime;
    int totalTime;

    static bool scanCanceled;

    static QString exts[];
    static QString imageExts[];
    static QString musicExts[];
    static QString videoExts[];
    static QString codeExts[];
    
    QJsonArray fullScan(const QString& dir, int level=0);
    QList<TreeNode *> fullScan2(const QString &dir, int level);
    void fullScan1(const QString &dir, int level=0);
    QString getPadding(int level);
    QStringList getFilters(const QString& filter);
    QString getIcon(const QString &file);
};

#endif // SCANDIRECTORY_H
