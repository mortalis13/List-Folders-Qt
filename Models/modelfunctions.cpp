#include "Models/modelfunctions.h"

#include <QFile>
#include <QVariant>
#include <QHash>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

ModelFunctions::ModelFunctions()
{
}

bool ModelFunctions::matches(QString regex, QString text)
{
    QRegExp rx(regex);
    if(rx.indexIn(text)!=-1)
        return true;
    return false;
}

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

QString ModelFunctions::formatTime(int time, QString format)
{
  QString res;
  return res.sprintf(qPrintable(format), (float)time / 1000);
}

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

void ModelFunctions::writeFile(QString path, QString text) {
  QFile file(path);
  
  if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
    qWarning("Couldn't open file.");
    return;
  }
  
  file.write(text.toStdString().c_str());
}
