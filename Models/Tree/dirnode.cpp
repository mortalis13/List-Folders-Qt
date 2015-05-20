#include "dirnode.h"

DirNode::DirNode(QString text, QJsonArray children) : TreeNode(text)
{
    this->children=children;
}

void DirNode::write(QJsonObject &json) const
{
    json["text"]=text;
    json["icon"]=icon;
    json["children"]=children;
}
