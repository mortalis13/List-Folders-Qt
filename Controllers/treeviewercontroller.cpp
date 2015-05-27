#include "treeviewercontroller.h"
#include <QJsonArray>

TreeViewerController::TreeViewerController(TreeViewer& view, TreeViewerModel &model):
  m_view(view),
  m_model(model)
{
}

TreeModel* TreeViewerController::getTreeModel(const QString& path){
  qDebug("getTree()");

  TreeModel* treeModel;
  treeModel=m_model.getTreeModel(path);

  return treeModel;
}

void TreeViewerController::freeMemory(TreeModel *treeModel){
  m_model.freeMemory(treeModel);
}
