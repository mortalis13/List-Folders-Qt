#include "filenode.h"
#include <QObject>

FileNode::FileNode(QString text, QString icon) : TreeNode(text)
{
    this->icon=icon;
}

void FileNode::write(QJsonObject &json) const
{
    json["text"]=text;
    json["icon"]=icon;
}
