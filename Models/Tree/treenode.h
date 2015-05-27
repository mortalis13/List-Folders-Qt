#ifndef TREENODE_H
#define TREENODE_H

#include <QObject>

class TreeNode
{
public:
    TreeNode(QString text);

    QString text;
    QString icon;

    TreeNode* m_parent;               // needed for the tree view model
    
    virtual void f() {}               // for dynamic_cast (which requires source class to be polymorphic)
};

#endif // TREENODE_H
