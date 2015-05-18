#include "Views/mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->bScanDir, SIGNAL(clicked()), this, SLOT(bScanDirClick()));
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
    QString path=ui->lePath->text();
    path="C:/1-Roman/Documents/8-test/list-test/en";
    m_controller->scanDir(path);
}
