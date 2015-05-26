#ifndef TREENODE_H
#define TREENODE_H

#include <QObject>
//#include "dirnode.h"

//class DirNode;

class TreeNode
{
public:
    TreeNode();
    TreeNode(QString text);

    QString text;
    QString icon;
    QString toString();

    TreeNode* m_parent;

    virtual void f() {}
};

#endif // TREENODE_H
