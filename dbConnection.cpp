#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QMessageBox>

#include "dbConnection.h"

bool DbConnection :: createConnection()
{
      db = QSqlDatabase::addDatabase("QMYSQL");
      db.setHostName("127.0.0.1");
      db.setPort(3306);
      db.setDatabaseName("account");
      db.setUserName("shekhar");
      db.setPassword("doitnow");
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
