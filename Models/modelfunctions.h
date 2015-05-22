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
    static QString formatPath(QString path);
    static QString getPath(QString path);
    static void writeFile(QString path, QString text);
    static QString readFile(QString path);
    static QString formatTime(int time, QString format);
};

#endif // MODELFUNCTIONS_H
