#include "treeviewermodel.h"

#include <QJsonArray>
#include <QDebug>

#include "Models/modelfunctions.h"

/*
 * Returns the tree model pointer to use in the QTreeView object
 */
TreeModel* TreeViewerModel::getTreeModel(const QString& path)
{
  QString json;

  DirNode* root;
  TreeModel* treeModel=NULL;

  json=ModelFunctions::readFile(path);                          // get JSON string
  root=ModelFunctions::decodeTree(json);                        // get pointer to the root
  treeModel=ModelFunctions::getTreeModel(root);                 // get TreeModel pointer

//  showTree(root);
//  qDebug() << "JSON: " << json;

  return treeModel;
}

/*
 * Delete tree structure and tree model from the memory
 */
void TreeViewerModel::freeMemory(TreeModel *treeModel){
  qDebug() << "== Unloading Tree ==";

  DirNode* root=treeModel->getRoot();
  deleteTree(root);
  delete root;
  delete treeModel;
}

/*
 * Recursively delete all nodes and treeChildren lists from the memory
 */
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

/*
 * Show tree nodes text in the debug output
 */
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
