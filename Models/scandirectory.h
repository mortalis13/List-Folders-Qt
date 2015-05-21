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
    void done();
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

    bool scanCanceled;

    static QStringList exts;
    static QStringList imageExts;
    static QStringList musicExts;
    static QStringList videoExts;
    static QStringList codeExts;
    
    QJsonArray fullScan(const QString& dir, int level=0);
    QString getPadding(int level);
    QStringList getFilters(QString filter);
    QString getIcon(QString file);
    int getDirCount(int totalCount);
    bool filterDirectory(QString dir);
    bool filterFile(QString file);
    void exportText();
    void exportTree();
    QString getExportName(QString ext="");
    QString getFiltersText();
    QString replaceTemplate(QString tmpl, QString replacement, QString text);
};

#endif // SCANDIRECTORY_H
