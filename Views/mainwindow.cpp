#include "Views/mainwindow.h"
#include "Views/functions.h"
#include "ui_mainwindow.h"
#include "Models/modelobserver.h"
#include <QSet>

MainWindow::MainWindow(Model &model, QWidget *parent) :
  QMainWindow(parent),
  m_model(model),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  connect(ui->bScanDir, SIGNAL(clicked()), this, SLOT(bScanDirClick()));
  model.registerObserver(this);
}

MainWindow::~MainWindow()
{
  QHash<QString, QVariant> fields;
  fields=Functions::getFieldsMap(ui);
  m_controller->saveConfig(fields);

  delete ui;
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

void MainWindow::bScanDirClick(){
  prepareProcessing();
  QHash<QString, QVariant> fields;
  fields=Functions::getFieldsMap(ui);
  m_controller->scanDir(fields);
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
  updateStatusBar("finish", "", time);
  ui->bScanDir->setText("Scan Directory");

//  MainForm.startScan=true;
}
