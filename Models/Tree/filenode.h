#ifndef FILENODE_H
#define FILENODE_H

#include <QObject>
#include "Models/Tree/treenode.h"

class FileNode:public TreeNode
{
public:
    FileNode(QString text, QString icon);
};

#endif // FILENODE_H
