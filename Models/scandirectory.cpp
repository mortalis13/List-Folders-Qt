#include "scandirectory.h"
#include <QDir>
#include <QHash>
#include <QVariant>
#include <QDebug>
#include <Models/Tree/dirnode.h>
#include <Models/Tree/filenode.h>
#include <Models/Tree/treenode.h>
#include <Models/modelfunctions.h>

ScanDirectory::ScanDirectory(QObject *parent) : QObject(parent)
{
  text="";
  exportName="";

  dirCount=0;
  rootDirCount=0;
  prevTime=0;
  totalTime=0;

  scanCanceled=false;

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

QStringList ScanDirectory::exts={
  "chm", "css", "djvu", "dll", "doc",
  "exe", "html", "iso", "js", "msi",
  "pdf", "php", "psd", "rar", "txt",
  "xls", "xml", "xpi", "zip",
};

QStringList ScanDirectory::imageExts={
  "png", "gif", "jpg", "jpeg", "tiff", "bmp",
};

QStringList ScanDirectory::musicExts={
  "mp3", "wav", "ogg", "alac", "flac",
};

QStringList ScanDirectory::videoExts={
  "mkv", "flv", "vob", "avi", "wmv",
  "mov", "mp4", "mpg", "mpeg", "3gp",
};

QStringList ScanDirectory::codeExts ={
  "c", "cpp", "cs", "java",
};

void ScanDirectory::startScan()
{
  jsonArray=fullScan(path);

  QJsonDocument doc(jsonArray);
  QByteArray byteArray=doc.toJson();
  json=QString(byteArray);
}

QStringList s;

QJsonArray ScanDirectory::fullScan(const QString &dir, int level)
{
  if(scanCanceled) return QJsonArray();

  QString pad;
  QJsonArray json, res;

  QDir qdir=QDir(dir);
  pad=getPadding(level);

  qdir.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
  QFileInfoList dirList=qdir.entryInfoList();
  if (level == 0) {
    rootDirCount = getDirCount(dirList.size());
    qDebug() << "rootDirCount: " << rootDirCount;
    qDebug() << "dirList.size(): " << dirList.size();
  }

  foreach(QFileInfo nextDir, dirList){
    QString name=nextDir.fileName();
    QString currentDir="[" + name + "]";

    if(level==0){
      if(!filterDirectory(name)) continue;
      //            updateStatusBar("scanning", currentDir);
    }

    if(doExportText)
      text+=pad+currentDir+nl;

    res=fullScan(nextDir.absoluteFilePath(), level+1);
    if(scanCanceled) return QJsonArray();

    QJsonObject jsonObject;
    DirNode node(name, res);
    node.write(jsonObject);
    json.append(jsonObject);

    if (level == 0) {
      // logging
    }
  }

  qdir.setFilter(QDir::Files);
  foreach(QFileInfo nextFile, qdir.entryInfoList()){
    QString name=nextFile.fileName();
    if(!filterFile(name)) continue;

    QString currentFile=name;
    if(doExportText)
      text+=pad+currentFile+nl;

    QJsonObject jsonObject;
    FileNode node(name, getIcon(name));
    node.write(jsonObject);
    json.append(jsonObject);
  }

  return json;
}

QList<TreeNode*> ScanDirectory::fullScan2(const QString &dir, int level)
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

    res=fullScan2(nextDir.absoluteFilePath(), level+1);

    //        DirNode* node=new DirNode(name, res);
    //        json.append(node);
  }

  qdir.setFilter(QDir::Files);
  foreach(QFileInfo nextFile, qdir.entryInfoList()){
    QString name=nextFile.fileName();
    QString currentFile=name;

    text+=pad+currentFile+nl;

    //        FileNode* node=new FileNode(name, getIcon(name));
    //        json.append(node);
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

    fullScan1(nextDir.absoluteFilePath(), level+1);
  }

  qdir.setFilter(QDir::Files);
  foreach(QFileInfo nextFile, qdir.entryInfoList()){
    QString name=nextFile.fileName();
    QString currentFile=name;

    text+=pad+currentFile+nl;
  }
}

// --------------------------------------------------- logging ---------------------------------------------------

/*
 * Gets top-level count of directories to be scanned
 */
int ScanDirectory::getDirCount(int totalCount){
  int filteredCount=filterDir.size();
  if(filteredCount==0) return totalCount;
  return filteredCount;
}

// --------------------------------------------------- helpers ---------------------------------------------------

QString ScanDirectory::getPadding(int level){
  QString resPad = "";
  for (int i = 0; i < level; i++) {
    resPad += pad;
  }
  return resPad;
}

QString ScanDirectory::getText(){
  if(text.trimmed().length()==0)
    text="No Data";
  return text;
}

QString ScanDirectory::getJson(){
  return json;
}

/*
 * Returns icon path for the tree view
 */
QString ScanDirectory::getIcon(QString file)
{
  QString ext, icon, path, iconExt;
  bool useDefault=true;

  ext="";
  icon="jstree-file";
  path=iconsPath;
  iconExt=".png";

  ext=ModelFunctions::regexFind("\\.([\\w]+)$", file);
  if(ext.length()==0) return icon;

  if(useDefault){                                             // extensions for known types
    // foreach(int i=0; i<exts.i++){
    foreach(QString item, exts){
      if(item==ext){
        icon=path+item+iconExt;
        useDefault=false;
        break;
      }
    }
  }

  if(useDefault){                                             // general extensions for "images"
    foreach(QString item, imageExts){
      if(item==ext){
        icon=path+"image"+iconExt;
        useDefault=false;
        break;
      }
    }
  }

  if(useDefault){                                             // general extensions for "music"
    foreach(QString item, musicExts){
      if(item==ext){
        icon=path+"music"+iconExt;
        useDefault=false;
        break;
      }
    }
  }

  if(useDefault){                                             // general extensions for "video"
    foreach(QString item, videoExts){
      if(item==ext){
        icon=path+"video"+iconExt;
        useDefault=false;
        break;
      }
    }
  }

  if(useDefault){                                             // general extensions for "code"
    foreach(QString item, codeExts){
      if(item==ext){
        icon=path+"code"+iconExt;
        useDefault=false;
        break;
      }
    }
  }

  return icon;
}

// --------------------------------------------------- filters ---------------------------------------------------

/*
 * Filters file extensions and returns true if the file will be included in the output
 * If exclude filter is not empty ignores the include filter
 */
bool ScanDirectory::filterFile(QString file) {
  if(excludeExt.size()!=0){
    foreach(QString ext, excludeExt){
      if(ModelFunctions::matches("\\."+ext+"$", file))
        return false;
    }
    return true;
  }

  if(filterExt.size()==0) return true;
  foreach(QString ext, filterExt){
    if(ModelFunctions::matches("\\."+ext+"$", file))
      return true;
  }
  return false;
}

/*
 * Uses form filter to filter directories from the first scanning level
 */
bool ScanDirectory::filterDirectory(QString dir) {
  if(filterDir.size()==0) return true;

  foreach(QString filter, filterDir){
    if(filter==dir)
      return true;
  }
  return false;
}

QStringList ScanDirectory::getFilters(QString filter)
{
  QStringList list;
  filter=filter.trimmed();

  if(filter.length()!=0){
    list=filter.split("\n");
    for(int i=0;i<list.size();i++){
      list[i]=list[i].trimmed();
    }
  }

  return list;
}

// --------------------------------------------------- test ---------------------------------------------------

QString ScanDirectory::getResult(){
  QString res="resultx";

  //    DirNode* d=(DirNode*) jsonArray[0];
  //    QList<TreeNode*> ch=d->children;

  //    res=d->text;

  //    res=nameList[0];
  //    res=nodeList[0]->text;

  return res;
}

void ScanDirectory::test()
{
  FileNode file("file1.txt", "icon");
  QList<TreeNode> list;
  list.append(file);

  int x=1;
}
