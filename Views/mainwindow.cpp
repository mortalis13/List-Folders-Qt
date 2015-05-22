#include "Views/mainwindow.h"
#include "Views/functions.h"
#include "ui_mainwindow.h"
#include "Models/modelobserver.h"

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
  delete ui;
}

void MainWindow::setController(Controller& controller)
{
  m_controller=&controller;
}

void MainWindow::printResult(const QString &text)
{
  ui->teOut->setPlainText(text);
}

void MainWindow::bScanDirClick(){
  QHash<QString, QVariant> fields;
  fields=Functions::getFieldsMap(ui);
  m_controller->scanDir(fields);
}

void MainWindow::init(){
  QString path="C:/1-Roman/Documents/8-test/list-test/en";
  ui->lePath->setText(path);
  ui->chExportText->setChecked(true);
}

void MainWindow::updateState(int progress)
{
  QString text="Progress: " + QString::number(progress);

  //  ui->leExportName->setText(text);
  ui->teOut->appendPlainText(text);

  //  printResult("Progress: ");
//  printResult("Progress: "+progress);
}
