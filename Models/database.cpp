#include "database.h"

#include <QtSql>

Database::Database()
{
  connected=createConnection();
  if(connected) query=*new QSqlQuery();
  initDatabase();
}

/*
 * Connects to the local .db file (SQLite database)
 * if no file then creates it
 */
bool Database::createConnection(){
  db = QSqlDatabase::addDatabase( "QSQLITE" );
  db.setDatabaseName( "config.db" );

  if( !db.open() )
  {
    qDebug() << db.lastError();
    qFatal( "Failed to connect." );
    return false;
  }
  qDebug( "Connected!" );

  return true;
}

void Database::closeConnection(){
  db.close();
}

/*
 * Creates tables in the database if they don't exist
 */
void Database::initDatabase(){
  if(!connected) return;

  query.prepare( "CREATE TABLE IF NOT EXISTS config ( \
    id INTEGER UNIQUE PRIMARY KEY AUTOINCREMENT, \
    name VARCHAR(200) UNIQUE DEFAULT NULL, \
    value LONGTEXT \
  )" );
  
  if( !query.exec() )
    qDebug() << "initDatabase() error: " << query.lastError();
  else{
    qDebug() << "Database initialized!";
  }
}

/*
 * Checks if "name" exists in the table
 */
bool Database::exists(QString table, QString name){
  QString sql = "select count(*) from " + table + " where name=:name";
  
  query.prepare(sql);
  query.bindValue(":name", name);
  
  if( !query.exec() )
    qDebug() << "exists() error: " << query.lastError();
  else
  {
    query.next();
    int res=query.value(0).toInt();
    if(res==0) return false;
    return true;
  }
  
  return false;
}

/*
 * General update method for 'config' and 'options' tables
 */
void Database::updateOption(QString name, QString value, QString dbtable){
  if (!connected) return;

  table=options_table;
  if(dbtable.length()!=0) table=dbtable;
  
  sql="update "+table+" set value=:value where name=:name";
  if(!exists(table, name)){
    sql="insert into "+table+" (name,value) values(:name, :value)";
  }
  
  query.prepare(sql);
  query.bindValue(":name", name);
  query.bindValue(":value", value);
  
  if( !query.exec() )
    qDebug() << "updateOption() error: " << query.lastError();
  else
    qDebug() << "updateOption() success";
}

/*
 * Adds or updates last option in the 'config' table
 * Redirects to the updateOption()
 */
void Database::updateConfig(QString name, QString value)
{
  updateOption(name, value, config_table);
}

/*
 * Loads last options from the database to assign them to the form fields
 */
QString Database::loadLastOptions(){
  return getOption("last", config_table);
}

/*
 * Gets option from 'options' table
 */
QString Database::getOption(QString name){
  return getOption(name, options_table);
}

/*
 * Retrieves option from the database when an item is selected in the dropdown
 * to load options set into the form fields
 */
QString Database::getOption(QString name, QString table){
  if (!connected) return QString();

  sql="select value from "+table+" where name=:name";
  
  query.prepare(sql);
  query.bindValue(":name", name);
  query.exec();

  if( !query.exec() )
    qDebug() << "getOption() error: " << query.lastError();
  else{
    if(query.next()){
      QString res=query.value(0).toString();
      qDebug() << "getOption() success";
      return res;
    }
  }
  
  return QString();
}
