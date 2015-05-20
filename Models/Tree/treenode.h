#ifndef TREENODE_H
#define TREENODE_H

#include <QObject>

class TreeNode
{
public:
    TreeNode(QString text);

    QString text;
    QString icon;
    QString toString();
};

#endif // TREENODE_H
