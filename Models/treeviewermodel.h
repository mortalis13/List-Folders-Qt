#ifndef TREEVIEWERMODEL_H
#define TREEVIEWERMODEL_H

#include <QJsonArray>
#include "Models/treemodel.h"

// #include "Models/tn.h"
// #include "Models/tnmodel.h"

class TreeViewerModel
{
public:
  TreeViewerModel();
  TreeModel* getTree(const QString &path);
  void showTree(DirNode *root);
  
  // TNModel *getTree1(const QString &path);
  // TN *getTNRoot();
  void setTNModel();
};

#endif // TREEVIEWERMODEL_H
