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
  QJsonArray array;
  DirNode *root;
  TreeModel* treeModel;
  QString json;

  json=ModelFunctions::readFile(path);
  root=ModelFunctions::decodeTree(json);

  treeModel=ModelFunctions::getTreeModel(root);

//  showTree(root);
//  qDebug() << "JSON: " << json;

  return treeModel;
}

// TN* TreeViewerModel::getTNRoot(){
//   TN *root=new TN();
//   root->text="root";

//   TN* child;

//   QList<TN*>* rootChildren=new QList<TN*>();

//   // foo

//   TN* foo=new TN();
//   foo->m_parent=root;
//   foo->text="foo";
//   rootChildren->append(foo);

//   QList<TN*>* fooChildren=new QList<TN*>();

//   child=new TN();
//   child->m_parent=foo;
//   child->text="Mark";
//   fooChildren->append(child);

//   child=new TN();
//   child->m_parent=foo;
//   child->text="Bob";
//   fooChildren->append(child);

//   child=new TN();
//   child->m_parent=foo;
//   child->text="Kent";
//   fooChildren->append(child);

//   child=new TN();
//   child->m_parent=foo;
//   child->text="Peter";
//   fooChildren->append(child);

//   child=new TN();
//   child->m_parent=foo;
//   child->text="Joe";
//   fooChildren->append(child);

//   foo->m_children=fooChildren;

//   // bar

//   TN* bar=new TN();
//   bar->m_parent=root;
//   bar->text="bar";
//   rootChildren->append(bar);

//   QList<TN*>* barChildren=new QList<TN*>();

//   child=new TN();
//   child->m_parent=bar;
//   child->text="Ole";
//   barChildren->append(child);

//   child=new TN();
//   child->m_parent=bar;
//   child->text="Trond";
//   barChildren->append(child);

//   child=new TN();
//   child->m_parent=bar;
//   child->text="Kjetil";
//   barChildren->append(child);

//   child=new TN();
//   child->m_parent=bar;
//   child->text="Lasse";
//   barChildren->append(child);

//   bar->m_children=barChildren;

//   // baz

//   TN* baz=new TN();
//   baz->m_parent=root;
//   baz->text="baz";
//   rootChildren->append(baz);

//   QList<TN*>* bazChildren=new QList<TN*>();

//   child=new TN();
//   child->m_parent=baz;
//   child->text="Bengt";
//   bazChildren->append(child);

//   child=new TN();
//   child->m_parent=baz;
//   child->text="Sven";
//   bazChildren->append(child);

//   baz->m_children=bazChildren;

//   root->m_children=rootChildren;
  
//   return root;
// }

// TNModel* TreeViewerModel::getTree1(const QString& path)
// {
//   QJsonArray array;
//   QString json;
  
//   TN* root;
//   TNModel* treeModel;

//   json=ModelFunctions::readFile(path);
// //  root=ModelFunctions::decodeTree1(json);

//   root=getTNRoot();

//   treeModel=ModelFunctions::getTreeModel1(root);

//   return treeModel;
// }
