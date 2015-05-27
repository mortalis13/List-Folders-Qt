#include "treeviewer.h"
#include "ui_treeviewer.h"
#include <QFileDialog>
#include <QShortcut>
#include <QJsonArray>
#include <QDebug>

TreeViewer::TreeViewer(TreeViewerModel& model, QWidget *parent) :
  QMainWindow(parent),
  m_model(model),
  ui(new Ui::TreeViewer)
{
  ui->setupUi(this);
  init();
  addActions();
  addShortcuts();

  setAttribute(Qt::WA_DeleteOnClose);
}

TreeViewer::~TreeViewer()
{
  unloadTree();
  delete ui;
  qDebug() << "Destroy TreeViewer";
}

void TreeViewer::init(){
//  QString path="C:/1-Roman/Documents/8-test/list-test/en/en.json";
//  ui->lePath->setText(path);

  treeModel=NULL;

  ui->tree->header()->hide();
  ui->tree->setAnimated(true);
}

void TreeViewer::addActions()
{
  connect( ui->bUnloadTree, SIGNAL(clicked()), this, SLOT(bUnloadTreeClick()) );
  connect( ui->bLoadTree, SIGNAL(clicked()), this, SLOT(bLoadTreeClick()) );
  connect( ui->bBrowse, SIGNAL(clicked()), this, SLOT(bBrowseClick()) );

  connect( ui->tree, SIGNAL(clicked(const QModelIndex &)), this, SLOT(treeClick(const QModelIndex &)) );
}

void TreeViewer::addShortcuts()
{
  QShortcut *bLoadTree=new QShortcut(QKeySequence("Ctrl+R"), this);
  connect( bLoadTree, SIGNAL(activated()), ui->bLoadTree, SLOT(click()) );

  QShortcut *bBrowse=new QShortcut(QKeySequence("Ctrl+O"), this);
  connect( bBrowse, SIGNAL(activated()), ui->bBrowse, SLOT(click()) );

  QShortcut *quit=new QShortcut(QKeySequence("Esc"), this);
  connect( quit, SIGNAL(activated()), this, SLOT(close()) );
}

void TreeViewer::setController(TreeViewerController &controller)
{
  m_controller=&controller;
}

void TreeViewer::bLoadTreeClick()
{
   QString treePath=path();
   if(treePath.length()==0){
     ui->bBrowse->click();
     return;
   }
   unloadTree();

   treeModel=m_controller->getTreeModel(treePath);
//   ui->tree->setModel(treeModel);
}

void TreeViewer::bUnloadTreeClick()
{
  unloadTree();
}

void TreeViewer::unloadTree(){
  if(treeModel!=NULL){
    m_controller->freeMemory(treeModel);
    treeModel=NULL;
  }
}

void TreeViewer::bBrowseClick(){
  QString dir=path();
  if(dir.length()==0) dir="export/tree/json";

  QString filename = QFileDialog::getOpenFileName(
          this, tr("Select a JSON file"), dir,
          tr("JSON files (*.json)") );
  if( !filename.isNull() )
  {
    setPath(filename);
  }
}

void TreeViewer::treeClick(const QModelIndex &index){
  QTreeView* tree=ui->tree;
  if(tree->isExpanded(index))
    tree->collapse(index);
  else
    tree->expand(index);
}

// ----------------------------------------------------------------------------------------------

QString TreeViewer::path(){
  return ui->lePath->text();
}

void TreeViewer::setPath(QString path){
  ui->lePath->setText(path);
}
