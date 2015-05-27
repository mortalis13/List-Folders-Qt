#ifndef DIRNODE_H
#define DIRNODE_H

#include "Models/Tree/treenode.h"
#include <QList>
#include <QJsonArray>
#include <QJsonObject>


class DirNode:public TreeNode
{
public:
  DirNode(QString text);
  DirNode(QString text, QJsonArray children);
  ~DirNode();
  
  void setParent(DirNode* parent);
  void write(QJsonObject &json) const;

  QJsonArray children;
  QList<TreeNode*>* treeChildren;
};

#endif // DIRNODE_H
