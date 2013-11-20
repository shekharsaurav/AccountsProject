#include "homescreen.h"
#include "ui_homescreen.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QMessageBox>
//#include <QDebug>
#include <iostream>
#include <QSqlQuery>
#include "adminWindow.h"

using namespace std;
//#include "admin.h"

HomeScreen::HomeScreen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HomeScreen)
{
    ui->setupUi(this);
}

HomeScreen::~HomeScreen()
{
    delete ui;
}

void HomeScreen::on_leUsername_editingFinished()
{
    if(!ui->leUsername->text().isEmpty())
        ui->pbLogin->setEnabled(true);
}

void HomeScreen::on_pbCancel_clicked()
{
    this->close();
}

void HomeScreen::on_pbLogin_clicked()
{
    if(ui->lePassword->text().isEmpty())
        ui->lStatus->setText("Enter your Password..");
    if(createConnection())
    {
        cout<<"Function Returned";
         this->close();
//        Options *dialog = new Options;
//        dialog->show();
        AdminWindow *window = new AdminWindow;
        window->show();
       //int result = QMessageBox::Information(this,tr("Login Info"), tr("Login Successful"), QMessageBox::Ok | QMessageBox::Escape);
       //if(result == QMessageBox::Yes)
    }
}

void HomeScreen::on_leUsername_textEdited(const QString &arg1)
{
    if(arg1.isEmpty())
    {
        ui->pbLogin->setEnabled(false);
        ui->lStatus->setText("Enter your Username..");
    }
}


bool HomeScreen::createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setPort(3306);
    db.setDatabaseName("account");
    db.setUserName("root");
    db.setPassword("root");
    db.open();
    if(!db.open())
    {
        QMessageBox::critical(0, QObject::tr("Database Error"), db.lastError().text());
        return false;
    }
    else
        cout<<"Database connected";
    QSqlQuery query;
    query.exec("SELECT username, password from admin");
    if(query.next())
    {
        cout<<"Query Executed";
        ui->lStatus->setText("Query Executed");
        if(ui->leUsername->text() == query.value(0))
        {
            if(ui->lePassword->text() == query.value(0))
            {
                cout<<"Login Successful";
                ui->lStatus->setText("Login Successfull!!");
            }
            else
                ui->lStatus->setText("Wrong Password");
        }
        else
            ui->lStatus->setText("Wrong Username");
    }
    db.commit();
    return true;
}
