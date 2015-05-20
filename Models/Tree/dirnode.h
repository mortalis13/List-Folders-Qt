#ifndef DIRNODE_H
#define DIRNODE_H

#include "Models/Tree/treenode.h"
#include <QList>
#include <QVariant>
#include <QJsonArray>
#include <QJsonObject>

class DirNode:public TreeNode
{
public:
    DirNode(QString text, QJsonArray children);
    void write(QJsonObject &json) const;
    QJsonArray children;
};

#endif // DIRNODE_H
