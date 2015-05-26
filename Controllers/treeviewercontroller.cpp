#include "treeviewercontroller.h"
#include <QJsonArray>

TreeViewerController::TreeViewerController(TreeViewer& view, TreeViewerModel &model):
  m_view(view),
  m_model(model)
{
}

TreeModel* TreeViewerController::getTree(const QString& path){
  qDebug("getTree()");

  TreeModel* treeModel;
  treeModel=m_model.getTree(path);

  return treeModel;
}

// TNModel* TreeViewerController::getTree1(const QString& path){
//   qDebug("getTNTree()");

//   TNModel* treeModel;
//   treeModel=m_model.getTree1(path);

//   return treeModel;
// }

void TreeViewerController::test(){
  qDebug("test()");
}
