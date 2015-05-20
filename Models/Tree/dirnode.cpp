#include "dirnode.h"

DirNode::DirNode(QString text, QList<TreeNode*> children) : TreeNode(text)
{
    this->children=children;
}
