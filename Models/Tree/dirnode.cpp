#include "dirnode.h"

DirNode::DirNode(QString text) : TreeNode(text)
{
  treeChildren=NULL;                            // init the pointer to prevent crashes on destroying the object
}

DirNode::DirNode(QString text, QJsonArray children) : TreeNode(text)
{
  this->children=children;
  treeChildren=NULL;
}

DirNode::~DirNode()
{
  if(treeChildren!=NULL)
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
