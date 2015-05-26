#ifndef FILENODE_H
#define FILENODE_H

#include <QObject>
#include "Models/Tree/treenode.h"
#include "Models/Tree/dirnode.h"
#include <QJsonArray>
#include <QJsonObject>

class FileNode:public TreeNode
{
public:
    FileNode(QString text, QString icon);
    void write(QJsonObject &json) const;
    void setParent(DirNode *parent);

//    DirNode* m_parent;
};

#endif // FILENODE_H
