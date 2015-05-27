#ifndef MODELFUNCTIONS_H
#define MODELFUNCTIONS_H

#include "Models/treemodel.h"

#include <QObject>

#include "Models/Tree/dirnode.h"

class ModelFunctions
{
public:
    static QString formatPath(QString path);
    static QString getPath(QString path);
    static QString extractIconName(QString path);
    static bool matches(QString regex, QString text);
    static QString regexFind(QString pattern, QString text, int group = 1);
    
    static QString readFile(QString path);
    static void writeFile(QString path, QString text);
    
    static QString formatTime(int time, QString format);
    
    static QString encodeFields(const QHash<QString, QVariant> &fields);
    static QHash<QString, QVariant> decodeFields(QString json);
    
    static DirNode *decodeTree(QString json);
    static TreeModel *getTreeModel(DirNode *root);

private:
    static QList<TreeNode *> *parseTree(QJsonArray array, DirNode *parent);

};

#endif // MODELFUNCTIONS_H
