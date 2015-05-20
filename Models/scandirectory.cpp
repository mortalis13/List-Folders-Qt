#include "scandirectory.h"
#include <QDir>
#include <QHash>
#include <QVariant>
#include <Models/Tree/dirnode.h>
#include <Models/Tree/filenode.h>
#include <Models/Tree/treenode.h>

ScanDirectory::ScanDirectory(QObject *parent) : QObject(parent)
{
    text="";
    exportName="";

    dirCount=0;
    rootDirCount=0;
    prevTime=0;
    totalTime=0;

    nodeList=*new QList<TestBase*>();
}

void ScanDirectory::init(const QHash<QString, QVariant> &fields){
    QString filterExtText, excludeExtText, filterDirText;

    path=fields.value("path").toString();

    filterExtText=fields.value("filterExt").toString();
    excludeExtText=fields.value("excludeExt").toString();
    filterDirText=fields.value("filterDir").toString();

    doExportText=fields.value("doExportText").toBool();
    doExportTree=fields.value("doExportTree").toBool();
    exportName=fields.value("exportName").toString();

    filterExt=getFilters(filterExtText);
    excludeExt=getFilters(excludeExtText);
    filterDir=getFilters(filterDirText);
}

// sets of extensions for tree view icons (stored in lib/images)

QString ScanDirectory::exts[]={
  "chm", "css", "djvu", "dll", "doc", 
  "exe", "html", "iso", "js", "msi", 
  "pdf", "php", "psd", "rar", "txt", 
  "xls", "xml", "xpi", "zip",
};

QString ScanDirectory::imageExts[]={
  "png", "gif", "jpg", "jpeg", "tiff", "bmp",
};

QString ScanDirectory::musicExts[]={
  "mp3", "wav", "ogg", "alac", "flac",
};

QString ScanDirectory::videoExts[]={
  "mkv", "flv", "vob", "avi", "wmv",
  "mov", "mp4", "mpg", "mpeg", "3gp",
};

QString ScanDirectory::codeExts[] ={
  "c", "cpp", "cs", "java",
};

QString ScanDirectory::startScan()
{
    jsonArray=fullScan(path);

//    DirNode* d=(DirNode*) jsonArray[0];
//    QList<TreeNode*> ch=d->children;

    return text;
}

QString ScanDirectory::getResult(){
    QString res="resultx";

    DirNode* d=(DirNode*) jsonArray[0];
//    QList<TreeNode*> ch=d->children;

//    TreeNode* t=jsonArray[0];
//    res=t->text;

    res=d->text;

//    res=nameList[0];

//    res=nodeList[0]->text;

    return res;
}

void ScanDirectory::fillList(){
    TestBase* tb=new TestBase("123");
    nodeList.append(tb);
}

QString ScanDirectory::getList(){
    QString res="resultx";
    res=nodeList[0]->text;

    return res;
}

void ScanDirectory::test()
{
    FileNode file("file1.txt", "icon");
    QList<TreeNode> list;
    list.append(file);

    int x=1;
}

QList<TreeNode*> ScanDirectory::fullScan(const QString &dir, int level)
{
    QString pad;
    QList<TreeNode*> json, res;

    QDir qdir=QDir(dir);
    pad=getPadding(level);

    qdir.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
    foreach(QFileInfo nextDir, qdir.entryInfoList()){
        QString name=nextDir.fileName();
        QString currentDir="[" + name + "]";

        text+=pad+currentDir+nl;

        TestBase* node1=new TestBase(name);
        nodeList.append(node1);

        res=fullScan(nextDir.absoluteFilePath(), level+1);

        DirNode* node=new DirNode(name, res);
        json.append(node);
    }

    qdir.setFilter(QDir::Files);
    foreach(QFileInfo nextFile, qdir.entryInfoList()){
        QString name=nextFile.fileName();
        QString currentFile=name;

        text+=pad+currentFile+nl;

        TestBase* node1=new TestBase(name);
        nodeList.append(node1);

        FileNode* node=new FileNode(name, getIcon(name));
        json.append(node);
    }

    return json;
}

void ScanDirectory::fullScan1(const QString &dir, int level)
{
    QString pad;
    QList<TreeNode> json, res;

    QDir qdir=QDir(dir);
    pad=getPadding(level);

    qdir.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
    foreach(QFileInfo nextDir, qdir.entryInfoList()){
        QString name=nextDir.fileName();
        QString currentDir="[" + name + "]";

        text+=pad+currentDir+nl;

        fullScan(nextDir.absoluteFilePath(), level+1);
    }

    qdir.setFilter(QDir::Files);
    foreach(QFileInfo nextFile, qdir.entryInfoList()){
        QString name=nextFile.fileName();
        QString currentFile=name;

        text+=pad+currentFile+nl;
    }
}

// --------------------------------------------------- helpers ---------------------------------------------------

QString ScanDirectory::getPadding(int level){
    QString resPad = "";
    for (int i = 0; i < level; i++) {
        resPad += pad;
    }
    return resPad;
}

// --------------------------------------------------- filters ---------------------------------------------------

QStringList ScanDirectory::getFilters(const QString &filter)
{
    return filter.split("\n");
}

QString ScanDirectory::getIcon(const QString &file)
{
    return file;
}
