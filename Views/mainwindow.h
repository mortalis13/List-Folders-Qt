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
    void updateState(int progress);
private slots:
    void bScanDirClick();

private:
    Ui::MainWindow *ui;
    Controller* m_controller;
    Model &m_model;
};

#endif // MAINWINDOW_H
