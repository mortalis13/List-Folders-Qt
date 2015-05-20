#include "filenode.h"
#include <QObject>

FileNode::FileNode(QString text, QString icon) : TreeNode(text)
{
    this->icon=icon;
}
