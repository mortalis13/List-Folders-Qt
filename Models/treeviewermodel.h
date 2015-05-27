#ifndef TREEVIEWERMODEL_H
#define TREEVIEWERMODEL_H

#include "Models/treemodel.h"

#include <QJsonArray>

#include "Models/Tree/dirnode.h"

class TreeViewerModel
{
public:
  TreeModel* getTreeModel(const QString &path);
  void showTree(DirNode *root);
  void freeMemory(TreeModel* treeModel);

private:
  void deleteTree(DirNode *parent);
};

#endif // TREEVIEWERMODEL_H
