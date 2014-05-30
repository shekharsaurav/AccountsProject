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
    for(int i = 0; i<=9; i++)
    {
        duesItem[i] = new QTableWidgetItem("");
        duesItem[i]->setTextAlignment(Qt::AlignVCenter);
        duesItem[i]->setTextAlignment(Qt::AlignRight);
        duesItem[i]->setTextColor(Qt::red);
        ui->twFeeReceipt->setItem(i, 1, duesItem[i]);
        currentItem[i] = new QTableWidgetItem("");
        currentItem[i]->setTextAlignment(Qt::AlignVCenter);
        currentItem[i]->setTextAlignment(Qt::AlignRight);
        ui->twFeeReceipt->setItem(i, 2, currentItem[i]);
        depositeItem[i] = new QTableWidgetItem("");
        depositeItem[i]->setTextAlignment(Qt::AlignVCenter);
        depositeItem[i]->setTextAlignment(Qt::AlignRight);
        depositeItem[i]->setTextColor(Qt::green);
        ui->twFeeReceipt->setItem(i, 3, depositeItem[i]);
        clearedItem[i] = new QTableWidgetItem("");
        ui->twFeeReceipt->setItem(i, 4, clearedItem[i]);
        clearedItem[i]->setTextAlignment(Qt::AlignVCenter);
        clearedItem[i]->setTextAlignment(Qt::AlignRight);
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
         stmt.sprintf("SELECT * FROM feestructure WHERE class = \"%s\";", stud.std.toStdString().c_str());
         query.exec(stmt);
         if(query.next())
         {
             feeStruc.std  = stud.std;
             feeStruc.regFee = query.value(1).toDouble();
             feeStruc.tutFee = query.value(2).toDouble();
             feeStruc.genrFee = query.value(3).toDouble();
             feeStruc.examFee = query.value(4).toDouble();
             feeStruc.reAddmFee = query.value(5).toDouble();
             feeStruc.devlpFee = query.value(7).toDouble();
             feeStruc.compFee = query.value(8).toDouble();
             stmt.sprintf("SELECT COUNT(*) FROM reg%ld;", regdNo);
             query.exec(stmt);
             if(query.nextResult() == 0)
             {
                 totalCurrent += feeStruc.regFee;
                 str = QString::number(feeStruc.regFee);
                 currentItem[0]->setText(str);
             }
             else
             {
                 stmt.sprintf("SELECT * FROM reg%ld ORDER BY receiptNo DESC LIMIT 1;", regdNo);
                 query.exec(stmt);
                 int curMonth = ui->deReceiptDate->date().month();
                 if(query.next())
                 {
                    int mon = query.value(0).toInt();
                    if((curMonth >= 1 && curMonth <= 3 && mon >= 1 && mon <= 3) || (curMonth >= 4 && curMonth <= 12 && mon >=4 && mon <=12))
                    {
                        diff = curMonth - mon;
                    }
                    else
                    {
                        diff = curMonth;
                        diff += (12 - mon);
                    }
                    if(curMonth - mon <= 1 )
                    {
                        feeStruc.duesRegFee = query.value(1).toDouble();
                        feeStruc.duesTutFee = query.value(3).toDouble();
                        feeStruc.duesGenrFee = query.value(5).toDouble();
                        feeStruc.duesExamFee = query.value(7).toDouble();
                        feeStruc.duesReAddmFee = query.value(9).toDouble();
                        feeStruc.duesLateFee = query.value(11).toDouble();
                        feeStruc.duesDevlpFee = query.value(13).toDouble();
                        feeStruc.duesCompFee = query.value(15).toDouble();
                        totalDues = query.value(17).toDouble();
                    }
                    else
                    {
                      updateFeeDues(curMonth);
                    }
                    totalCurrent += totalDues;
                    str = QString::number(totalDues);
                    currentItem[5]->setText(str);
                    duesItem[9]->setText(str);
                    str = QString::number(feeStruc.duesRegFee);
                    duesItem[0]->setText(str);
                    str = QString::number(feeStruc.duesTutFee);
                    duesItem[1]->setText(str);
                    str = QString::number(feeStruc.duesGenrFee);
                    duesItem[2]->setText(str);
                    str = QString::number(feeStruc.duesExamFee);
                    duesItem[3]->setText(str);
                    str = QString::number(feeStruc.duesReAddmFee);
                    duesItem[4]->setText(str);
                    str = QString::number(feeStruc.duesDevlpFee);
                    duesItem[6]->setText(str);
                    str = QString::number(feeStruc.duesCompFee);
                    duesItem[7]->setText(str);
                 }
             }
             totalCurrent += feeStruc.tutFee;
             str = QString::number(feeStruc.tutFee);
             currentItem[1]->setText(str);
             totalCurrent += feeStruc.devlpFee;
             str = QString::number(feeStruc.devlpFee);
             currentItem[6]->setText(str);
             totalCurrent += feeStruc.compFee;
             str = QString::number(feeStruc.compFee);
             currentItem[7]->setText(str);
             str = QString::number(totalCurrent);
             currentItem[9]->setText(str);
         }
         pUi->tabWidget->insertTab(index, this, "Fee Receipt");
         pUi->tabWidget->setCurrentIndex(index);
         pUi->statusBar->showMessage(" Fee Receipt Generated", 5000);
     }
     else
     {
         QMessageBox::critical(0, QObject::tr("INVALID REGISTRATION NUMBER!!"), query.lastError().text());
         delete this;
     }
     ui->pbReset->setEnabled(true);
 }


void FeeReceipt::on_pbClose_clicked()
{
    this->close();
}

void FeeReceipt::on_pbReset_clicked()
{
    try
    {
        for(int i =0; i<=8; i++)
        {
            depositeItem[i]->setText("");
            clearedItem[i]->setText("");
        }
        pUi->statusBar->showMessage(" Fields Reset!!", 5000);
    }
    catch(exception& e)
    {
        cout<<e.what();
    }
}

void FeeReceipt::on_pbDeposite_clicked()
{
//    if((QMessageBox::warning(this, tr("Confirm transaction"), tr("Confirm Transaction?\n Note: Database would be updated!!"),
//                            QMessageBox::yes, QMessageBox::Cancel)) == QMessageBox::Yes)
//    {
//        FeeStructure
//    }
}

void FeeReceipt::on_cbExamFee_stateChanged(int arg1)
{
    if(ui->cbExamFee->isChecked())
    {
        totalCurrent += feeStruc.examFee;
        str = QString::number(feeStruc.examFee);
        currentItem[3]->setText(str);
        str = QString::number(totalCurrent);
        currentItem[9]->setText(str);
    }
    else
    {
        currentItem[3]->setText("");
        totalCurrent -= feeStruc.examFee;
        str = QString::number(totalCurrent);
        currentItem[9]->setText(str);
    }
}

void FeeReceipt::on_cbReAddmFee_stateChanged(int arg1)
{
    if(ui->cbReAddmFee->isChecked())
    {
        totalCurrent += feeStruc.reAddmFee;
        str = QString::number(feeStruc.reAddmFee);
        currentItem[4]->setText(str);
        str = QString::number(totalCurrent);
        currentItem[9]->setText(str);
    }
    else
    {
        currentItem[4]->setText("");
        totalCurrent -= feeStruc.reAddmFee;
        str = QString::number(totalCurrent);
        currentItem[9]->setText(str);
    }
}

void FeeReceipt::on_cbMonth_currentIndexChanged(int index)
{
    if( index == 0)
    {
        QMessageBox::warning(this, tr("Month Feild empty!"), tr("Please select the month uptill which the fee is to be deposited!"), QMessageBox::Ok);
    }
    else if (index == 1 || index == 2 || index == 4 || index == 5 || index == 6 || index ==7)
    {
        str = QString::number(feeStruc.genrFee);
        currentItem[2]->setText(str);
        totalCurrent += feeStruc.genrFee;
        str = QString::number(totalCurrent);
        currentItem[9]->setText(str);
    }
    else
    {
        currentItem[2]->setText("");        
        totalCurrent -= feeStruc.genrFee;
        str = QString::number(totalCurrent);
        currentItem[9]->setText(str);
    }
}

void FeeReceipt::updateFeeDues(int curMonth)
{
    while(diff != 1 )
    {
        feeStruc.duesRegFee = query.value(1).toDouble();
        totalDues += feeStruc.duesRegFee;
        feeStruc.duesTutFee = query.value(3).toDouble() + feeStruc.tutFee;
        totalDues += feeStruc.duesTutFee;
        int dueMonth = curMonth - (diff - 1);
        if(dueMonth == 4 || dueMonth == 5 || dueMonth == 7 || dueMonth == 8 || dueMonth == 9 || dueMonth == 10)
        {
           feeStruc.duesGenrFee = query.value(5).toDouble() + feeStruc.tutFee;
           totalDues += feeStruc.duesGenrFee;
        }
        else
        {
            feeStruc.duesGenrFee = query.value(5).toDouble();
            totalDues += feeStruc.duesGenrFee;
        }
        if(dueMonth == 2 || dueMonth == 7 || dueMonth == 11)
        {
            feeStruc.duesExamFee = query.value(7).toDouble() + feeStruc.examFee;
            totalDues += feeStruc.duesExamFee;
        }
        else
        {
            feeStruc.duesExamFee = query.value(7).toDouble();
            totalDues += feeStruc.duesExamFee;
        }
        feeStruc.duesReAddmFee = query.value(9).toDouble();
        totalDues += feeStruc.duesReAddmFee;
        feeStruc.duesLateFee = query.value(11).toDouble();
        totalDues += feeStruc.duesLateFee;
        feeStruc.duesDevlpFee = query.value(13).toDouble() + feeStruc.devlpFee;
        totalDues += feeStruc.duesDevlpFee;
        feeStruc.duesCompFee = query.value(15).toDouble() + feeStruc.compFee;
        totalDues += feeStruc.duesCompFee;
    }
}

void FeeReceipt::on_twFeeReceipt_itemEntered(QTableWidgetItem *item)
{
    static double prevMisc = 0;
    if (item->column() == 2 && item->row() == 8)
    {
        totalCurrent -= prevMisc;
        totalCurrent += item->text().toDouble();
        prevMisc = item->text().toDouble();
        str = QString::number(totalCurrent);
        currentItem[9]->setText(str);
    }
}

//void FeeReceipt::on_twFeeReceipt_itemChanged(QTableWidgetItem *item)
//{
//    static double prevMisc = 0;
//    if (item->column() == 2 && item->row() == 8)
//    {
//        totalCurrent -= prevMisc;
//        totalCurrent += item->text().toDouble();
//        prevMisc = item->text().toDouble();
//        str = QString::number(totalCurrent);
//        currentItem[9]->setText(str);
//    }
//}
