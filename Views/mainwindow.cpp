#include "Views/mainwindow.h"
#include "Views/functions.h"
#include "Views/treeviewer.h"
#include "ui_mainwindow.h"
#include "Models/modelobserver.h"
#include <QFileDialog>
#include <QShortcut>

MainWindow::MainWindow(Model &model, QWidget *parent) :
  QMainWindow(parent),
  m_model(model),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  scanStarted=false;
  scanCanceled=false;
  addActions();
  addShortcuts();
  model.registerObserver(this);
}

MainWindow::~MainWindow()
{
  QHash<QString, QVariant> fields;
  fields=Functions::getFieldsMap(ui);
  m_controller->saveConfig(fields);

  delete ui;
}

void MainWindow::addActions()
{
  connect(ui->bScanDir, SIGNAL(clicked()), this, SLOT(bScanDirClick()));
  connect(ui->bTreeViewer, SIGNAL(clicked()), this, SLOT(bTreeViewerClick()));
  connect(ui->bBrowse, SIGNAL(clicked()), this, SLOT(bBrowseClick()));

  connect(ui->bClearExcludeExt, SIGNAL(clicked()), this, SLOT(bClearExcludeExtClick()));
  connect(ui->bClearFilterDir, SIGNAL(clicked()), this, SLOT(bClearFilterDirClick()));
  connect(ui->bClearFilterExt, SIGNAL(clicked()), this, SLOT(bClearFilterExtClick()));
  connect(ui->bClearOut, SIGNAL(clicked()), this, SLOT(bClearOutClick()));
}

void MainWindow::addShortcuts()
{
  QShortcut *bScanDir=new QShortcut(QKeySequence("Ctrl+R"), this);
  connect(bScanDir, SIGNAL(activated()), ui->bScanDir, SLOT(click()));

  QShortcut *bBrowse=new QShortcut(QKeySequence("Ctrl+O"), this);
  connect(bBrowse, SIGNAL(activated()), ui->bBrowse, SLOT(click()));

  QShortcut *bTreeViewer=new QShortcut(QKeySequence("Ctrl+T"), this);
  connect(bTreeViewer, SIGNAL(activated()), ui->bTreeViewer, SLOT(click()));

  QShortcut *quit=new QShortcut(QKeySequence("Esc"), this);
  connect(quit, SIGNAL(activated()), this, SLOT(close()));
}

void MainWindow::setController(Controller& controller)
{
  m_controller=&controller;
}

void MainWindow::loadConfig(){
  QHash<QString, QVariant> fields;
  fields=m_controller->loadConfig();
  Functions::loadConfig(ui, fields);
}

void MainWindow::printResult(const QString &text)
{
  ui->teOut->setPlainText(text);
}

// ---------------------------------------------- button handlers ----------------------------------------------

void MainWindow::bScanDirClick(){
  if(!scanStarted){
    scanStarted=true;
    scanCanceled=false;
    prepareProcessing();
    QHash<QString, QVariant> fields;
    fields=Functions::getFieldsMap(ui);
    m_controller->scanDir(fields);
  }
  else{
    m_controller->stopScan();
    updateStatusBar("cancel");
    scanStarted=false;
    scanCanceled=true;
  }
}

void MainWindow::bTreeViewerClick(){
  TreeViewerModel treeViewerModel;
  TreeViewer *treeViewer=new TreeViewer(treeViewerModel, this);
  TreeViewerController treeViewerController(*treeViewer, treeViewerModel);

  treeViewer->setController(treeViewerController);
  treeViewer->show();
}

void MainWindow::bBrowseClick(){
  QString dir=path();
  if(dir.length()==0) dir=QDir::currentPath();

  QString dirname = QFileDialog::getExistingDirectory( 
          this, tr("Select a Directory"), dir);
  if( !dirname.isNull() )
  {
    setPath(dirname);
  }
}

void MainWindow::bClearExcludeExtClick(){
  ui->teExcludeExt->clear();
}

void MainWindow::bClearFilterDirClick(){
  ui->teFilterDir->clear();
}

void MainWindow::bClearFilterExtClick(){
  ui->teFilterExt->clear();
}

void MainWindow::bClearOutClick(){
  ui->teOut->clear();
}

// ----------------------------------------------------------------------------------------------

QString MainWindow::path(){
  return ui->lePath->text();
}

void MainWindow::setPath(QString path){
  ui->lePath->setText(path);
}

void MainWindow::prepareProcessing(){
  ui->progressBar->setValue(0);
  Functions::clearLog(ui);
  ui->bScanDir->setText("Stop");
}

void MainWindow::init(){
  QString path="C:/1-Roman/Documents/8-test/list-test/en";
  ui->lePath->setText(path);
  ui->chExportText->setChecked(true);
}

void MainWindow::updateState(QString currentDir, QString timeString, int progress, int dirCount, int rootDirCount)
{
  Functions::log(ui, currentDir);
  Functions::log(ui, timeString+"\t Dir: "+QString::number(dirCount)+"/"+QString::number(rootDirCount)+
                 " \t Progress: "+QString::number(progress)+"%\n");
  Functions::setProgress(ui, progress);
}

void MainWindow::updateStatusBar(QString type, QString currentDir, QString totalTime)
{
  QString text="";
  QStringList types={"scanning", "finish", "cancel"};

  switch(types.indexOf(type)){
  case 0:
    text="Scanning: "+currentDir;
    break;
  case 1:
    text="Scanning finished (time: "+totalTime+")";
    break;
  case 2:
    text="Scanning canceled";
    break;
  }
  ui->statusBar->showMessage(text);
}

void MainWindow::scanningFinished(int totalTime){
  Functions::log(ui, "----------------------------");
  QString time=Functions::formatTime(totalTime, "%.2f s");
  Functions::log(ui, "Total time: "+time);

  Functions::setProgress(ui, 100);
  if(!scanCanceled)
    updateStatusBar("finish", "", time);
  ui->bScanDir->setText("Scan Directory");

//  MainForm.startScan=true;
}
