#include "scandirectory.h"
#include <QDir>
#include <QHash>
#include <QVariant>
#include <QDebug>
#include <QThread>
#include <Models/Tree/dirnode.h>
#include <Models/Tree/filenode.h>
#include <Models/Tree/treenode.h>
#include <Models/modelfunctions.h>
#include "Models/modelobserver.h"

ScanDirectory::ScanDirectory() : QThread()
{
  text="";
  exportName="";

  dirCount=0;
  rootDirCount=0;
  prevTime=0;
  totalTime=0;

//connect( this, SIGNAL(updateState(int)), this, SLOT(notifyObservers(int)) );
  connect( this, SIGNAL(updateState(QString, QString, int)), this, SLOT(notifyObservers(QString, QString, int)) );
  connect( this, SIGNAL(updateStatusBar(QString, QString)), this, SLOT(notifyUpdateStatusBar(QString, QString)) );
  connect( this, SIGNAL(scanningFinished()), this, SLOT(notifyScanningFinished()) );
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

void ScanDirectory::init(const QHash<QString, QVariant> &fields){
  QString filterExtText, excludeExtText, filterDirText;

  path=fields.value("path").toString();
  path=ModelFunctions::formatPath(path);

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

void ScanDirectory::prepareProcessing(){
  time.start();
}

void ScanDirectory::startScan()
{
  prepareProcessing();
  start();
  scanCanceled=false;

//  jsonArray=fullScan(path);
//  QJsonDocument doc(jsonArray);
//  QByteArray byteArray=doc.toJson();
//  json=QString(byteArray);
}

void ScanDirectory::stopScan()
{
  scanCanceled=true;
}

void ScanDirectory::run(){
  jsonArray=fullScan(path);
  
  QJsonDocument doc(jsonArray);
  QByteArray byteArray=doc.toJson();
  json=QString(byteArray);

  done();
}

void ScanDirectory::done(){
  if(doExportText) exportText();
  if(doExportTree) exportTree();

  emit scanningFinished();
}

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
       emit updateStatusBar("scanning", currentDir);
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
      dirCount++;
      int progress=(int) ((float) dirCount/rootDirCount*100);
      logStats(currentDir, progress);
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

// --------------------------------------------------- logging ---------------------------------------------------

int ScanDirectory::logStats(QString currentDir, int progress){
  int timeDiff=time.elapsed();
  totalTime+=timeDiff;

  QString timeString=ModelFunctions::formatTime(timeDiff, "Time: %.2f s ");
  emit updateState(currentDir, timeString, progress);
  time.restart();
}

/*
 * Gets top-level count of directories to be scanned
 */
int ScanDirectory::getDirCount(int totalCount){
  int filteredCount=filterDir.size();
  if(filteredCount==0) return totalCount;
  return filteredCount;
}

// --------------------------------------------------- helpers ---------------------------------------------------

/*
 * Replaces strings from the tree template (strings format: '_string_') with the 'replacement' text
 */
QString ScanDirectory::replaceTemplate(QString tmpl, QString replacement, QString text){
  text=text.replace(tmpl, replacement);
  return text;
}

/*
 * Outputs padding spaces for text output depending on nesting level
 */
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

/*
 * Cleans, trims and checks filters for emptiness
 */
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

/*
 * Gets text for the tree template
 */
QString ScanDirectory::getFiltersText() {
  QString filterExtText="", excludeExtText="", filterDirText="", filters="";
  
  if(filterExt.size()!=0){
    filterExtText = filterExt.join(",");
  }
  if(excludeExt.size()!=0){
    excludeExtText = excludeExt.join(",");
  }
  if(filterDir.size()!=0){
    filterDirText = filterDir.join(",");
  }
  
  filters="Files include ["+filterExtText+"]";
  filters+=", Files exclude ["+excludeExtText+"]";
  filters+=", Directories ["+filterDirText+"]";
  
  return filters;
}

// --------------------------------------------------- exports ---------------------------------------------------

/*
 * Exports text to a .txt file in 'export/text'
 */
void ScanDirectory::exportText(){
  QString exportPath, fileName, ext, text;

  exportPath = ModelFunctions::getPath("export/text/");
  ext=".txt";
  fileName = getExportName(ext);
  fileName = exportPath + fileName;
  
  text=this->text;
  ModelFunctions::writeFile(fileName, text);
}

/*
 * Exports .json and .html files to the 'export/tree'
 * The .html file can be used directly to view the tree
 * The jsTree plugin must be in the 'tree/lib'
 *
 * The method gets the .html template from 'templates/tree.html', 
 * replaces template strings with the current data and create new .html in the 'exports/tree'
 * Then creates .json in the 'exports/tree/json' which is read by the script in the exported .html page
 */
void ScanDirectory::exportTree(){
  QString tmpl, doc, treeName, 
  exportPath, jsonFolder, jsonPath, 
  exportDoc, exportJSON;
  QString filters;
  QString jsonFile, htmlFile;
  
  if(json.length()==0) return;
  
  treeName=getExportName("");
  
  tmpl=ModelFunctions::getPath("templates/tree.html");
  exportPath=ModelFunctions::getPath("export/tree/");
  jsonFolder="json/";                                                   // should be "/" because "\" prints as control symbol
  jsonPath=exportPath+jsonFolder;
  
  exportDoc=treeName+".html";
  exportJSON=treeName+".json";
  
  doc=ModelFunctions::readFile(tmpl);
  if (doc.length()==0) {
    qWarning("No \"templates/tree.html\" file");
    return;
  }
  
  doc=replaceTemplate("_jsonPath_", jsonFolder+exportJSON, doc);
  doc=replaceTemplate("_Title_", "Directory: "+treeName, doc);
  doc=replaceTemplate("_FolderPath_", "Directory: "+path, doc);
  
  filters=getFiltersText();
  doc=replaceTemplate("_Filters_", "Filters: "+filters, doc);
  
  htmlFile=exportPath+exportDoc;                                        // get paths
  jsonFile=jsonPath+exportJSON;
    
  ModelFunctions::writeFile(htmlFile, doc);                                   // write results
  ModelFunctions::writeFile(jsonFile, json);
}

/*
 * Returns the name that will be used to export 
 * text, markup and tree views of the directory structure
 */
QString ScanDirectory::getExportName(QString ext){
  bool useCurrentDir=true;
  QString exportName, name, res;
  
  exportName="no-name";
  
  if(this->exportName.length()!=0){
    exportName=this->exportName;
    useCurrentDir=false;
  }
  
  if(useCurrentDir){
    res = ModelFunctions::regexFind("/([^/]+)/?$", path);
    if(res.length()!=0)
      exportName=res;
  }
  
  name=exportName;
  if(ext.length()!=0) name+=ext;
  
  return name;
}

// --------------------------------------------------- service ---------------------------------------------------

void ScanDirectory::registerObservers(QList<ModelObserver *> observers){
  this->observers=observers;
}

void ScanDirectory::notifyObservers(QString currentDir, QString timeString, int progress){
  foreach(ModelObserver *observer, observers)
    observer->updateState(currentDir, timeString, progress, dirCount, rootDirCount);
}

void ScanDirectory::notifyUpdateStatusBar(QString type, QString currentDir)
{
  foreach(ModelObserver *observer, observers)
    observer->updateStatusBar(type, currentDir);
}

void ScanDirectory::notifyScanningFinished()
{
  foreach(ModelObserver *observer, observers)
    observer->scanningFinished(totalTime);
}

//void ScanDirectory::notifyObservers(int progress){
//  foreach(ModelObserver *observer, observers)
//    observer->updateState(progress);
//}

// --------------------------------------------------- test ---------------------------------------------------

QString ScanDirectory::getResult(){
  QString res="resultx";
  return res;
}

void ScanDirectory::test()
{
  FileNode file("file1.txt", "icon");
  QList<TreeNode> list;
  list.append(file);
}
