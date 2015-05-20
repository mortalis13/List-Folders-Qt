#ifndef FILENODE_H
#define FILENODE_H

#include <QObject>
#include "Models/Tree/treenode.h"
#include <QJsonArray>
#include <QJsonObject>

class FileNode:public TreeNode
{
public:
    FileNode(QString text, QString icon);
    void write(QJsonObject &json) const;
};

#endif // FILENODE_H
