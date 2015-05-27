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

  QJsonArray children;                      // separate children array for the serialization
  QList<TreeNode*>* treeChildren;           // the structure based on pointer for the tree view model
                                            // (** this needs refactoring to leave only one children member **)
};

#endif // DIRNODE_H
