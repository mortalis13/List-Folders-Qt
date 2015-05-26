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
