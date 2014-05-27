#include <QtGui>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlError>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <fstream>

#include "feeReceipt.h"
//#include "ui_feeReceipt.h"
//#include "dbConnection.h"
//#include "feeStructure.h"

using namespace std;

FeeReceipt::FeeReceipt(Ui::adminWindow *parentUi, QWidget *parent): QWidget(parent), ui(new Ui::FeeReceipt)
{
    ui->setupUi(this);
    for(int i = 0; i<=8; i++)
    {
        duesItem[i] = new QTableWidgetItem("");
        ui->twFeeReceipt->setItem(i, 1, duesItem[i]);
        currentItem[i] = new QTableWidgetItem("");
        ui->twFeeReceipt->setItem(i, 2, currentItem[i]);
        depositeItem[i] = new QTableWidgetItem("");
        ui->twFeeReceipt->setItem(i, 3, depositeItem[i]);
        clearedItem[i] = new QTableWidgetItem("");
        ui->twFeeReceipt->setItem(i, 4, clearedItem[i]);
    }
    pUi = parentUi;
}

FeeReceipt::~FeeReceipt()
{
    delete ui;
}

 void FeeReceipt::generateReceipt(long regdNo, int index)
 {
     Students stud;
     stmt.sprintf("SELECT name, father, baseAdd, town, pin, roll, image, class FROM students where regNo = %ld", regdNo);
     query.exec(stmt);
     if(query.next())
     {
//         stud.regNo = query.value(0).toLongLong();
         stud.name = query.value(0).toString();
         stud.father = query.value(1).toString();
         stud.add.baseAdd = query.value(2).toString();
         stud.add.town = query.value(3).toString();
         stud.add.pin = query.value(4).toLongLong();
         stud.roll = query.value(5).toInt();
         stud.image = query.value(6).toString();
         stud.std = query.value(7).toString();
         QString str;
         str = QString::number(regdNo);
         ui->lNameLabel->setText(stud.name);
         str = QString::number(stud.roll);
         ui->lRollLabel->setText(str);
         ui->lFNameLabel->setText(stud.father);
         QString address;
         address = stud.add.baseAdd.append("\n"+stud.add.town);// + "\n" + stud.add.pin +"\n");
         ui->lAddressLabel->setText(address);
         ui->deReceiptDate->setDate(QDate::currentDate());
         ui->lClassLabel->setText(stud.std);
         QPixmap pm;
         pm.load(stud.image, 0, Qt::AutoColor);
         pm.scaled(51, 71);
         ui->lPhoto->setPixmap(pm);
         pUi->tabWidget->insertTab(index, this, "Fee Receipt");
         pUi->tabWidget->setCurrentIndex(index);
         pUi->statusBar->showMessage(" Fee Receipt Generated", 5000);
     }
     else
     {
         QMessageBox::critical(0, QObject::tr("INVALID REGISTRATION NUMBER!!"), query.lastError().text());
         delete this;
     }
 }


void FeeReceipt::on_pbClose_clicked()
{
    this->close();
}

void FeeReceipt::on_pbReset_clicked()
{
    try
    {
        for(int i = -1; i<=8; i++)
        {
            depositeItem[i+1]->setText("");
            clearedItem[i+1]->setText("");
        }
        pUi->statusBar->showMessage(" Fields Reset!!", 5000);
    }
    catch(exception& e)
    {
        cout<<e.what();
    }
}
