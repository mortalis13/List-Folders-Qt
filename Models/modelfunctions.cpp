#include "Models/modelfunctions.h"

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
