#include "controller.h"

Controller::Controller(MainWindow& view, Model& model) :
  QObject(0),
  m_view(view),
  m_model(model)
{
}

void Controller::setText(const QString& text)
{
  QString res;
  //    QString res=m_model.processText(text);
  m_view.printResult(res);
}

QHash<QString, QVariant> Controller::loadConfig()
{
  QHash<QString, QVariant> fields;
  fields=m_model.loadConfig();
  return fields;
}

void Controller::saveConfig(const QHash<QString, QVariant> &fields)
{
  m_model.saveConfig(fields);
}

void Controller::scanDir(const QHash<QString, QVariant> &fields)
{
  m_model.startScan(fields);
}

void Controller::stopScan(){
  m_model.stopScan();
}
