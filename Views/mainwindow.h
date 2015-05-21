#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <Controllers/controller.h>

namespace Ui {
class MainWindow;
}

class Controller;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setController(Controller& controller);
    void printResult(const QString& text);

    void init();
private slots:
    void bScanDirClick();

private:
    Ui::MainWindow *ui;
    Controller* m_controller;
};

#endif // MAINWINDOW_H
