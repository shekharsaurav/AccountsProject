#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QMessageBox>

#include "dbConnection.h"

bool DbConnection :: createConnection()
{
      db = QSqlDatabase::addDatabase("QMYSQL");
      db.setHostName("localhost");
      db.setPort(3306);
      db.setDatabaseName("account");
      db.setUserName("root");
      db.setPassword("root");
      if(!db.open())
      {
          QMessageBox::critical(0, QObject::tr("Database Error"), db.lastError().text());
          return false;
      }
      return true;
}

void DbConnection::removeConnection()
{
    QString conName = db.connectionName();
    db.removeDatabase(conName);
    db.close();
}

//DbConnection::~DbConnection()
//{
//    removeConnection();
//}
