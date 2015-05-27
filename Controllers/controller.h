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
    void scanDir(const QHash<QString, QVariant> &fields);
    void saveConfig(const QHash<QString, QVariant> &fields);
    QHash<QString, QVariant> loadConfig();
    void stopScan();

private:
    MainWindow& m_view;
    Model& m_model;
};

#endif // CONTROLLER_H
