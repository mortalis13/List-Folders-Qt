#include "Views/mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QShortcut>

#include "Views/functions.h"
#include "Views/treeviewer.h"
#include "Models/modelobserver.h"

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

/*
 * Assigns connections to the buttons
 */
void MainWindow::addActions()
{
  connect( ui->bScanDir, SIGNAL(clicked()), this, SLOT(bScanDirClick()) );
  connect( ui->bTreeViewer, SIGNAL(clicked()), this, SLOT(bTreeViewerClick()) );
  connect( ui->bBrowse, SIGNAL(clicked()), this, SLOT(bBrowseClick()) );

  connect( ui->bClearExcludeExt, SIGNAL(clicked()), this, SLOT(bClearExcludeExtClick()) );
  connect( ui->bClearFilterDir, SIGNAL(clicked()), this, SLOT(bClearFilterDirClick()) );
  connect( ui->bClearFilterExt, SIGNAL(clicked()), this, SLOT(bClearFilterExtClick()) );
  connect( ui->bClearOut, SIGNAL(clicked()), this, SLOT(bClearOutClick()) );
}

/*
 * Assigns shortcuts to the buttons
 */
void MainWindow::addShortcuts()
{
  QShortcut *bScanDir=new QShortcut(QKeySequence("Ctrl+R"), this);
  connect( bScanDir, SIGNAL(activated()), ui->bScanDir, SLOT(click()) );

  QShortcut *bBrowse=new QShortcut(QKeySequence("Ctrl+O"), this);
  connect( bBrowse, SIGNAL(activated()), ui->bBrowse, SLOT(click()) );

  QShortcut *bTreeViewer=new QShortcut(QKeySequence("Ctrl+T"), this);
  connect( bTreeViewer, SIGNAL(activated()), ui->bTreeViewer, SLOT(click()) );

  QShortcut *quit=new QShortcut(QKeySequence("Esc"), this);
  connect( quit, SIGNAL(activated()), this, SLOT(close()) );
}

/*
 * Gets the last saved config from the database and assigns it to the form fields
 */
void MainWindow::loadConfig(){
  QHash<QString, QVariant> fields;
  fields=m_controller->loadConfig();
  Functions::loadConfig(ui, fields);
}

// ---------------------------------------------- button handlers ----------------------------------------------

/*
 * Starts/stops scanning
 * The button title changes relatively to the start/stop state
 */
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

/*
 * Opens new TreeViewer window with the parent assigned to the main window
 */
void MainWindow::bTreeViewerClick(){
  TreeViewerModel treeViewerModel;
  TreeViewer *treeViewer=new TreeViewer(treeViewerModel, this);
  TreeViewerController treeViewerController(*treeViewer, treeViewerModel);

  treeViewer->setController(treeViewerController);
  treeViewer->show();
}

/*
 * Opens browse window to select a directory to scan 
 */
void MainWindow::bBrowseClick(){
  QString dir=path();
  if(dir.length()==0) dir=QDir::currentPath();

  QString dirname = QFileDialog::getExistingDirectory(this, tr("Select a Directory"), dir);
  if( !dirname.isNull() )
  {
    setPath(dirname);
  }
}

/*
 * Clear buttons for textedits
 */
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

// --------------------------------------------- helpers ---------------------------------------------

/*
 * Returns the Path field value
 */
QString MainWindow::path(){
  return ui->lePath->text();
}

void MainWindow::setPath(QString path){
  ui->lePath->setText(path);
}

/*
 * Changes the UI before the directory scanning
 */
void MainWindow::prepareProcessing(){
  ui->progressBar->setValue(0);
  Functions::clearLog(ui);
  ui->bScanDir->setText("Stop");
}

/*
 * Helper function to set initial data for the form
 */
void MainWindow::init(){
  QString path="C:/1-Roman/Documents/8-test/list-test/en";
  ui->lePath->setText(path);
  ui->chExportText->setChecked(true);
}

// --------------------------------------------- state ---------------------------------------------

/*
 * Adds lines to the log and updates the progress bar value
 */
void MainWindow::updateState(QString currentDir, QString timeString, int progress, int dirCount, int rootDirCount)
{
  Functions::log(ui, currentDir);
  Functions::log(ui, timeString+"\t Dir: "+QString::number(dirCount)+"/"+QString::number(rootDirCount)+
                 " \t Progress: "+QString::number(progress)+"%\n");
  Functions::setProgress(ui, progress);
}

/*
 * Writes the current scanning folder name, 
 * Notifies about finished/canceled scanning in the status bar
 */
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

/*
 * Writes total time of scanning to the log, 
 * updates the status bar and the UI
 */
void MainWindow::scanningFinished(int totalTime){
  scanStarted=false;
  
  Functions::log(ui, "----------------------------");
  QString time=Functions::formatTime(totalTime, "%.2f s");
  Functions::log(ui, "Total time: "+time);

  Functions::setProgress(ui, 100);
  if(!scanCanceled)
    updateStatusBar("finish", "", time);
  ui->bScanDir->setText("Scan Directory");
}

// -------------------------------------------- service --------------------------------------------

void MainWindow::setController(Controller& controller)
{
  m_controller=&controller;
}

/*
 * Debugging function
 */
void MainWindow::printResult(const QString &text)
{
  ui->teOut->setPlainText(text);
}
