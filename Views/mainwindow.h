#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <Controllers/controller.h>
#include <Models/model.h>
#include "Models/modelobserver.h"

namespace Ui {
class MainWindow;
}

class Controller;
class Model;

class MainWindow : public QMainWindow, public ModelObserver
{
    Q_OBJECT

public:
    explicit MainWindow(Model& model, QWidget *parent = 0);
    ~MainWindow();
    void setController(Controller& controller);
    void printResult(const QString& text);
    void init();
//    void updateState(int progress);
    void updateState(QString currentDir, QString timeString, int progress, int dirCount, int rootDirCount);
    void updateStatusBar(QString type, QString currentDir="", QString totalTime="");
    void scanningFinished(int totalTime);
    void loadConfig();
private slots:
    void bScanDirClick();

private:
    const QString nl="\n";

    Ui::MainWindow *ui;
    Controller* m_controller;
    Model &m_model;
    void prepareProcessing();
};

#endif // MAINWINDOW_H
