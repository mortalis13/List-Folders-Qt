#include "controller.h"

Controller::Controller(MainWindow& view, Model& model) :
    QObject(0),
    m_view(view),
    m_model(model)
{
}

void Controller::setText(const QString& text)
{
    QString res=m_model.processText(text);
    m_view.printResult(res);
}

void Controller::scanDir(const QString& path)
{
    QString res="";
    res=m_model.startScan(path);
    m_view.printResult(res);
}
