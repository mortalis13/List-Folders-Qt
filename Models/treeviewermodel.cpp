#include "treeviewermodel.h"
#include <QJsonArray>
#include <QDebug>
#include "Models/modelfunctions.h"

TreeViewerModel::TreeViewerModel()
{
}

void TreeViewerModel::showTree(DirNode *root)
{
  QList<TreeNode*> list=*(root->treeChildren);

  foreach(TreeNode* item, list){
    DirNode *d=dynamic_cast<DirNode*>(item);
    if(d){
      qDebug() << "Dir: " << item->text;
      showTree(d);
    }
    else{
      qDebug() << "  File: " << item->text;
    }

  }
}

TreeModel* TreeViewerModel::getTree(const QString& path)
{
  DirNode* root;
  TreeModel* treeModel;
  QString json;

  json=ModelFunctions::readFile(path);
  root=ModelFunctions::decodeTree(json);

  treeModel=ModelFunctions::getTreeModel(root);

//  showTree(root);
//  qDebug() << "JSON: " << json;

  return treeModel;
}
