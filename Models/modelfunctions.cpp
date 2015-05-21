#include "Models/modelfunctions.h"

#include <QFile>

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
  path=path.replace("\\\\", "/");
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

void ModelFunctions::writeFile(QString path, QString text) {
  QFile file(path);
  
  if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
    qWarning("Couldn't open file.");
    return;
  }
  
  file.write(text.toStdString().c_str());
}
