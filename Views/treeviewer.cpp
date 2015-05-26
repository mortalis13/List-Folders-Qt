#include "treeviewer.h"
#include "ui_treeviewer.h"
#include <QFileDialog>
#include <QShortcut>
#include <QJsonArray>

#include "Models/objecttreemodel.h"
#include "testtreemodel.h"
#include "test.h"

//#include "Models/tnmodel.h"

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

void TreeViewer::setObjectModel()
{
  QObject *root=new QObject();
  root->setObjectName( "root" );

  QObject *child;
  QObject *foo = new QObject( root );
  foo->setObjectName( "foo" );
  child = new QObject( foo );
  child->setObjectName( "Mark" );
  child = new QObject( foo );
  child->setObjectName( "Bob" );
  child = new QObject( foo );
  child->setObjectName( "Kent" );

  QObject *bar = new QObject( root );
  bar->setObjectName( "bar" );
  //+. main
  child = new QObject( bar );
  child->setObjectName( "Ole" );
  child = new QObject( bar );
  child->setObjectName( "Trond" );
  child = new QObject( bar );
  child->setObjectName( "Kjetil" );
  child = new QObject( bar );
  child->setObjectName( "Lasse" );

  QObject *baz = new QObject( root );
  baz->setObjectName( "baz" );
  child = new QObject( baz );
  child->setObjectName( "Bengt" );
  child = new QObject( baz );
  child->setObjectName( "Sven" );

  ObjectTreeModel *tm=new ObjectTreeModel(root);
  ui->tree->setModel(tm);
}

void TreeViewer::setTestModel(){
    Test *root=new Test();
    root->text="root";

    Test* child;

    QList<Test*>* rootChildren=new QList<Test*>();

    // foo

    Test* foo=new Test();
    foo->parent=root;
    foo->text="foo";
    rootChildren->append(foo);

    QList<Test*>* fooChildren=new QList<Test*>();

    child=new Test();
    child->parent=foo;
    child->text="Mark";
    fooChildren->append(child);

    child=new Test();
    child->parent=foo;
    child->text="Bob";
    fooChildren->append(child);

    child=new Test();
    child->parent=foo;
    child->text="Kent";
    fooChildren->append(child);

    child=new Test();
    child->parent=foo;
    child->text="Peter";
    fooChildren->append(child);

    child=new Test();
    child->parent=foo;
    child->text="Joe";
    fooChildren->append(child);

    foo->children=fooChildren;

    // bar

    Test* bar=new Test();
    bar->parent=root;
    bar->text="bar";
    rootChildren->append(bar);

    QList<Test*>* barChildren=new QList<Test*>();

    child=new Test();
    child->parent=bar;
    child->text="Ole";
    barChildren->append(child);

    child=new Test();
    child->parent=bar;
    child->text="Trond";
    barChildren->append(child);

    child=new Test();
    child->parent=bar;
    child->text="Kjetil";
    barChildren->append(child);

    child=new Test();
    child->parent=bar;
    child->text="Lasse";
    barChildren->append(child);

    bar->children=barChildren;

    // baz

    Test* baz=new Test();
    baz->parent=root;
    baz->text="baz";
    rootChildren->append(baz);

    QList<Test*>* bazChildren=new QList<Test*>();

    child=new Test();
    child->parent=baz;
    child->text="Bengt";
    bazChildren->append(child);

    child=new Test();
    child->parent=baz;
    child->text="Sven";
    bazChildren->append(child);

    baz->children=bazChildren;

    root->children=rootChildren;


  //  QList<Test*> list=*(root->children);
  //  foreach(Test* item, list){
  //    qDebug() << "Item: " << item->text;
  //  }

    TestTreeModel *tm=new TestTreeModel(root);
    ui->tree->setModel(tm);
}

void TreeViewer::setController(TreeViewerController &controller)
{
  m_controller=&controller;
}

void TreeViewer::setTNModel(){
  TN *root=new TN();
  root->text="root";

  TN* child;

  QList<TN*>* rootChildren=new QList<TN*>();

  // foo

  TN* foo=new TN();
  foo->m_parent=root;
  foo->text="foo";
  rootChildren->append(foo);

  QList<TN*>* fooChildren=new QList<TN*>();

  child=new TN();
  child->m_parent=foo;
  child->text="Mark";
  fooChildren->append(child);

  child=new TN();
  child->m_parent=foo;
  child->text="Bob";
  fooChildren->append(child);

  child=new TN();
  child->m_parent=foo;
  child->text="Kent";
  fooChildren->append(child);

  child=new TN();
  child->m_parent=foo;
  child->text="Peter";
  fooChildren->append(child);

  child=new TN();
  child->m_parent=foo;
  child->text="Joe";
  fooChildren->append(child);

  foo->m_children=fooChildren;

  // bar

  TN* bar=new TN();
  bar->m_parent=root;
  bar->text="bar";
  rootChildren->append(bar);

  QList<TN*>* barChildren=new QList<TN*>();

  child=new TN();
  child->m_parent=bar;
  child->text="Ole";
  barChildren->append(child);

  child=new TN();
  child->m_parent=bar;
  child->text="Trond";
  barChildren->append(child);

  child=new TN();
  child->m_parent=bar;
  child->text="Kjetil";
  barChildren->append(child);

  child=new TN();
  child->m_parent=bar;
  child->text="Lasse";
  barChildren->append(child);

  bar->m_children=barChildren;

  // baz

  TN* baz=new TN();
  baz->m_parent=root;
  baz->text="baz";
  rootChildren->append(baz);

  QList<TN*>* bazChildren=new QList<TN*>();

  child=new TN();
  child->m_parent=baz;
  child->text="Bengt";
  bazChildren->append(child);

  child=new TN();
  child->m_parent=baz;
  child->text="Sven";
  bazChildren->append(child);

  baz->m_children=bazChildren;

  root->m_children=rootChildren;
  
  TNModel *tm=new TNModel(root);
  ui->tree->setModel(tm);
}

void TreeViewer::bLoadTreeClick()
{
  qDebug("Load Tree click");
  QString path=ui->lePath->text();

   TreeModel* treeModel;
   treeModel=m_controller->getTree(path);
   ui->tree->setModel(treeModel);

  // TNModel* treeModel1;
  // treeModel1=m_controller->getTree1(path);
  // ui->tree->setModel(treeModel1);

// setTNModel();
//  setTestModel();

//  setObjectModel();
}
