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
  void setController(TreeViewerController &controller);

private slots:
  void bLoadTreeClick();

private:
  Ui::TreeViewer *ui;
  void init();
  void addActions();
  void addShortcuts();
  
  TreeViewerController *m_controller;
  TreeViewerModel &m_model;
};

#endif // TREEVIEWER_H
