#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QtSql>

class Database
{
public:
  Database();
  void updateConfig(QString name, QString value);
  QString loadLastOptions();
  QString getOption(QString name);
  void closeConnection();
private:
  QString options_table="options";
  QString config_table="config";
  QString table;
  QString sql;
  
  bool connected;
    
  QSqlDatabase db;  
  QSqlQuery query;
  
  bool createConnection();
  void initDatabase();
  bool exists(QString table, QString name);
  void updateOption(QString name, QString value, QString dbtable);
  QString getOption(QString name, QString table);
};

#endif // DATABASE_H
