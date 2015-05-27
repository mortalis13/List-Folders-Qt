#include "Models/modelfunctions.h"

#include <QDebug>
#include <QFile>
#include <QVariant>
#include <QHash>
#include <QRegExp>

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonParseError>

#include "Models/Tree/treenode.h"
#include "Models/Tree/dirnode.h"
#include "Models/Tree/filenode.h"
#include "Models/treemodel.h"

// ----------------------------------------------------- strings -----------------------------------------------------

/*
 * Formats path, fixes backslashes, trims
 */
QString ModelFunctions::formatPath(QString path){
  path=path.replace("\\", "/");
  path=path.trimmed();
  return path;
}

/*
 * Returns full path relative to the main .exe
 */
QString ModelFunctions::getPath(QString path) {
  // return Application.StartupPath + "\\" + path;
  return path;
}

/*
 * Returns file name from the full path of the JSON file
 * the name is assigned to the root directory name
 */
QString ModelFunctions::extractIconName(QString path) {
  QString icon;
  icon = regexFind("/([^/]+\\.[^/.]+)$", path);
  if (icon.length()==0) icon = "file.png";
  return icon;
}

bool ModelFunctions::matches(QString regex, QString text)
{
    QRegExp rx(regex);
    if(rx.indexIn(text)!=-1)
        return true;
    return false;
}

/*
 * Returns the result of the string search using regex
 * The 'group' parameter corresponds to the regex group in parenthesis
 * If the whole result is needed group=0 should be passed
 */
QString ModelFunctions::regexFind(QString pattern, QString text, int group) {
  QString res;

  QRegExp rx(pattern);
  if(rx.indexIn(text)!=-1)
      res=rx.cap(group);

  return res;
}

// ----------------------------------------------------- read/write -----------------------------------------------------

QString ModelFunctions::readFile(QString path) {
  QFile file(path);
  
  if (!file.open(QIODevice::ReadOnly)) {
    qWarning("Couldn't open file.");
    return QString();
  }
  
  QByteArray byteArray=file.readAll();
  QString res(byteArray);
  
  return res;
}

void ModelFunctions::writeFile(QString path, QString text) {
  QFile file(path);
  
  if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
    qWarning("Couldn't open file.");
    return;
  }
  
  file.write(text.toStdString().c_str());
}

// ----------------------------------------------------- logging -----------------------------------------------------

QString ModelFunctions::formatTime(int time, QString format)
{
  QString res;
  return res.sprintf(qPrintable(format), (float)time / 1000);
}

// ----------------------------------------------------- Fields JSON serialization -----------------------------------------------------

QString ModelFunctions::encodeFields(const QHash<QString, QVariant> &fields)
{
  QJsonArray jsonArray;
  QString json;

  foreach (QString key, fields.keys()) {
    QJsonObject item;
    item[key]=fields[key].toString();
    jsonArray.append(item);
  }

  QJsonDocument doc(jsonArray);
  QByteArray byteArray=doc.toJson();
  json=QString(byteArray);

  return json;
}

QHash<QString, QVariant> ModelFunctions::decodeFields(QString json){
  QHash<QString, QVariant> fields;
  
  QByteArray byteArray(qPrintable(json));
  QJsonDocument doc(QJsonDocument::fromJson(byteArray));
  QJsonArray array=doc.array();

  foreach (QJsonValue val, array) {
    QJsonObject item=val.toObject();
    QString key=item.keys()[0];
    QString value=item[key].toString();
    
    fields.insert(key, value);
  }
  
  return fields;
}

// ----------------------------------------------------- Tree JSON serialization -----------------------------------------------------

DirNode* ModelFunctions::decodeTree(QString json){
  QByteArray byteArray(json.toUtf8());

  QJsonParseError error;
  QJsonDocument doc( QJsonDocument::fromJson(byteArray, &error) );

  if(error.error)
    qDebug() << "QJsonDocument error: " << error.errorString();

  QJsonArray array=doc.array();

  DirNode *root=new DirNode("root");
  QList<TreeNode*> *tree=parseTree(array, root);
  root->treeChildren=tree;

  return root;
}

QList<TreeNode*>* ModelFunctions::parseTree(QJsonArray array, DirNode *parent){
  QList<TreeNode*> *list=new QList<TreeNode*>();

  foreach(QJsonValue val, array){
    QJsonObject item=val.toObject();
    QString text=item["text"].toString();
    QString icon=item["icon"].toString();

    if(item.contains("children")){
      QJsonArray childrenArray=item["children"].toArray();
      DirNode *dir=new DirNode(text);
      QList<TreeNode*> *children=parseTree(childrenArray, dir);

      dir->treeChildren=children;
      dir->setParent(parent);
      dir->icon=icon;

      list->append(dir);
    }
    else{
      FileNode *file=new FileNode(text, icon);
      file->setParent(parent);
      list->append(file);
    }
  }

  return list;
}

TreeModel* ModelFunctions::getTreeModel(DirNode* root){
  TreeModel* treeModel=new TreeModel(root);
  return treeModel;
}
