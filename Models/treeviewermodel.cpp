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

TreeModel* TreeViewerModel::getTreeModel(const QString& path)
{
  QString json;

  DirNode* root;
  TreeModel* treeModel;

  json=ModelFunctions::readFile(path);
  root=ModelFunctions::decodeTree(json);
  treeModel=ModelFunctions::getTreeModel(root);

  qDebug() << "Root size: " << sizeof(*root);

//  showTree(root);
//  qDebug() << "JSON: " << json;

  return treeModel;
}

void TreeViewerModel::deleteTree(DirNode* parent){
  QList<TreeNode*> list=*(parent->treeChildren);

  foreach(TreeNode* item, list){
    DirNode *d=dynamic_cast<DirNode*>(item);
    if(d){
      deleteTree(d);
      delete d;
    }
    else{
      delete item;
    }
  }
}

void TreeViewerModel::freeMemory(TreeModel *treeModel){
  qDebug() << "  == Unloading Tree ==";

  DirNode* root=treeModel->getRoot();
  deleteTree(root);
  delete root;
  delete treeModel;
}
