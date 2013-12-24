#include "homescreen.h"
#include "dbConnection.h"

#include <QApplication>
#include <iostream>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DbConnection dbcObject;
    if(!dbcObject.createConnection())
    {
        std::cout<<"\n\n<-----------------Database Connection failed!!-------------->\n\n";
    }
    HomeScreen window;
    window.show();
    return a.exec();
}
