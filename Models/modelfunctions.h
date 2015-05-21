#ifndef MODELFUNCTIONS_H
#define MODELFUNCTIONS_H

#include <QObject>
#include <QRegExp>

class ModelFunctions
{
public:
    ModelFunctions();
    static bool matches(QString regex, QString text);
    static QString regexFind(QString pattern, QString text, int group = 1);
};

#endif // MODELFUNCTIONS_H
