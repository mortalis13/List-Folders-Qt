#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "Models/model.h"
#include "Views/mainwindow.h"

class MainWindow;

class Controller
{
public:
    explicit Controller(MainWindow& view, Model &model);
    QHash<QString, QVariant> loadConfig();
    void saveConfig(const QHash<QString, QVariant> &fields);
    void scanDir(const QHash<QString, QVariant> &fields);
    void stopScan();

private:
    MainWindow& m_view;     // references to the view and model
    Model& m_model;
};

#endif // CONTROLLER_H
