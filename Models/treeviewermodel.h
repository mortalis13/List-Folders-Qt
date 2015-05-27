#ifndef TREEVIEWERMODEL_H
#define TREEVIEWERMODEL_H

#include <QJsonArray>
#include "Models/treemodel.h"
#include "Models/Tree/dirnode.h"

class TreeViewerModel
{
public:
  TreeViewerModel();
  TreeModel* getTreeModel(const QString &path);
  void showTree(DirNode *root);
  void freeMemory(TreeModel* treeModel);

private:
//  DirNode* root;
//  TreeModel* treeModel;

  void deleteTree(DirNode *parent);
};

#endif // TREEVIEWERMODEL_H
