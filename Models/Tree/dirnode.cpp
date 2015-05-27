#include "dirnode.h"

DirNode::DirNode(QString text) : TreeNode(text)
{
//  treeChildren=new QList<TreeNode*>();
//  m_parent=new TreeNode();
//  children=new QJsonArray();
}

DirNode::DirNode(QString text, QJsonArray children) : TreeNode(text)
{
  this->children=children;
}

DirNode::~DirNode()
{
  delete treeChildren;
}

void DirNode::setParent(DirNode *parent)
{
  m_parent=parent;
}

void DirNode::write(QJsonObject &json) const
{
    json["text"]=text;
    json["icon"]=icon;
    json["children"]=children;
}
