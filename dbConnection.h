#ifndef DBCONNECTION_H
#define DBCONNECTION_H

#include  <QtSql/QSqlDatabase>

class DbConnection
{

public:
    bool createConnection();
    void removeConnection();
    QSqlDatabase db;
//    ~DbConnection();
};

#endif // DBCONNECTION_H
