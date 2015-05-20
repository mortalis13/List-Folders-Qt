#ifndef DIRNODE_H
#define DIRNODE_H

#include "Models/Tree/treenode.h"
#include <QList>
#include <QVariant>

class DirNode:public TreeNode
{
public:
    DirNode(QString text, QList<TreeNode*> children);

    QList<TreeNode*> children;
};

#endif // DIRNODE_H
