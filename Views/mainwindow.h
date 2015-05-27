#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "Controllers/controller.h"
#include "Models/model.h"
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
    
    void loadConfig();
    void updateState(QString currentDir, QString timeString, int progress, int dirCount, int rootDirCount);
    void updateStatusBar(QString type, QString currentDir="", QString totalTime="");
    void scanningFinished(int totalTime);
    void init();
    
    void setController(Controller& controller);
    void printResult(const QString& text);
    QString path();
    void setPath(QString path);
    
private slots:
    void bScanDirClick();
    void bTreeViewerClick();
    void bBrowseClick();
    
    void bClearExcludeExtClick();
    void bClearFilterDirClick();
    void bClearFilterExtClick();
    void bClearOutClick();

private:
    const QString nl="\n";

    bool scanStarted;
    bool scanCanceled;

    Ui::MainWindow *ui;
    Controller* m_controller;
    Model &m_model;
    
    void addActions();
    void addShortcuts();
    void prepareProcessing();
};

#endif // MAINWINDOW_H
