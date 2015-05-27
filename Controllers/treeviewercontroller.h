#ifndef TREEVIEWERCONTROLLER_H
#define TREEVIEWERCONTROLLER_H

#include <QObject>
#include <QJsonArray>

#include "Models/treeviewermodel.h"
#include "Views/treeviewer.h"
#include "Models/treemodel.h"

class TreeViewer;

class TreeViewerController
{
public:
  TreeViewerController(TreeViewer& view, TreeViewerModel &model);
  
  TreeModel *getTreeModel(const QString& path);
  void freeMemory(TreeModel* treeModel);
  
private:
  TreeViewer& m_view;     // references to the view and model
  TreeViewerModel& m_model;
  
};

#endif // TREEVIEWERCONTROLLER_H
