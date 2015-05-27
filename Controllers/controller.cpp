#include "controller.h"

Controller::Controller(MainWindow& view, Model& model) :
  m_view(view),
  m_model(model)
{
}

/*
 * Load last saved config from the DB to the form fields
 */
QHash<QString, QVariant> Controller::loadConfig()
{
  QHash<QString, QVariant> fields;
  fields=m_model.loadConfig();
  return fields;
}

/*
 * Save current field values to the DB
 */
void Controller::saveConfig(const QHash<QString, QVariant> &fields)
{
  m_model.saveConfig(fields);
}

/*
 * Start scanning subdirectories
 */
void Controller::scanDir(const QHash<QString, QVariant> &fields)
{
  m_model.startScan(fields);
}

/*
 * Stop scanning
 */
void Controller::stopScan(){
  m_model.stopScan();
}
