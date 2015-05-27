#ifndef TREEVIEWER_H
#define TREEVIEWER_H

#include <QMainWindow>

#include <Controllers/treeviewercontroller.h>
#include <Models/treeviewermodel.h>
#include "Models/treemodel.h"

namespace Ui {
class TreeViewer;
}

class TreeViewerController;

class TreeViewer : public QMainWindow
{
  Q_OBJECT

public:
  explicit TreeViewer(TreeViewerModel& model, QWidget *parent = 0);
  ~TreeViewer();
  
  QString path();
  void setPath(QString path);
  void setController(TreeViewerController &controller);
  
private:
  Ui::TreeViewer *ui;
  TreeViewerController *m_controller;
  TreeViewerModel &m_model;
  TreeModel* treeModel;
  
  void init();
  void addActions();
  void addShortcuts();
  void unloadTree();
  
private slots:
  void bLoadTreeClick();
  void bBrowseClick();
  void treeClick(const QModelIndex &index);
  
};

#endif // TREEVIEWER_H
