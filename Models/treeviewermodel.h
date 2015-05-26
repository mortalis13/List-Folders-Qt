#ifndef TREEVIEWERMODEL_H
#define TREEVIEWERMODEL_H

#include <QJsonArray>
#include "Models/treemodel.h"

class TreeViewerModel
{
public:
  TreeViewerModel();
  TreeModel* getTree(const QString &path);
  void showTree(DirNode *root);
};

#endif // TREEVIEWERMODEL_H
