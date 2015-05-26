#include "treeviewer.h"
#include "ui_treeviewer.h"
#include <QFileDialog>
#include <QShortcut>
#include <QJsonArray>

TreeViewer::TreeViewer(TreeViewerModel& model, QWidget *parent) :
  QMainWindow(parent),
  m_model(model),
  ui(new Ui::TreeViewer)
{
  ui->setupUi(this);
  init();
  addActions();
  addShortcuts();
}

TreeViewer::~TreeViewer()
{
  delete ui;
}

void TreeViewer::init(){
  QString path="C:/1-Roman/Documents/8-test/list-test/en/en.json";
  ui->lePath->setText(path);
}

void TreeViewer::addActions()
{
  connect(ui->bLoadTree, SIGNAL(clicked()), this, SLOT(bLoadTreeClick()));
}

void TreeViewer::addShortcuts()
{
  QShortcut *bLoadTree=new QShortcut(QKeySequence("Ctrl+R"), this);
  connect(bLoadTree, SIGNAL(activated()), ui->bLoadTree, SLOT(click()));

  QShortcut *quit=new QShortcut(QKeySequence("Esc"), this);
  connect(quit, SIGNAL(activated()), this, SLOT(close()));
}

void TreeViewer::setController(TreeViewerController &controller)
{
  m_controller=&controller;
}

void TreeViewer::bLoadTreeClick()
{
    QString path=ui->lePath->text();

   TreeModel* treeModel;
   treeModel=m_controller->getTree(path);
   ui->tree->setModel(treeModel);
}
