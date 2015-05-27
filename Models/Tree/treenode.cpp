#include "treenode.h"
#include <QObject>

TreeNode::TreeNode(QString text)
{
    this->text=text;
    this->icon = "./lib/images/directory.png";                     // default folder icon
}
