#ifndef MODELFUNCTIONS_H
#define MODELFUNCTIONS_H

#include <QObject>
#include <QRegExp>

#include "Models/Tree/treenode.h"
#include "Models/Tree/dirnode.h"
#include "Models/Tree/filenode.h"
#include "Models/treemodel.h"

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
    static QString encodeFields(const QHash<QString, QVariant> &fields);
    static QHash<QString, QVariant> decodeFields(QString json);
    static DirNode *decodeTree(QString json);
    static TreeModel *getTreeModel(DirNode *root);
    
    static QString getNameFromPath(QString path);
    static QString extractIconName(QString path);
private:
    static QList<TreeNode *> *parseTree(QJsonArray &array, DirNode *parent);
};

#endif // MODELFUNCTIONS_H
