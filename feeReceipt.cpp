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
#include "students.h"

using namespace std;

FeeReceipt::FeeReceipt(Ui::adminWindow *parentUi, QWidget *parent): QWidget(parent), ui(new Ui::FeeReceipt)
{
    ui->setupUi(this);

    for(int i = 0; i<=9; i++)
    {
        duesItem[i] = ui->twFeeReceipt->item(i, 1);
        currentItem[i] = ui->twFeeReceipt->item(i, 2);
        depositeItem[i] = ui->twFeeReceipt->item(i, 3);
        clearedItem[i] = ui->twFeeReceipt->item(i, 4);
    }
    pUi = parentUi;
}

FeeReceipt::~FeeReceipt()
{
    delete ui;
}

 void FeeReceipt::generateReceipt(long regdNo, int index)
 {
     regNo = regdNo;
     Students stud;
     stmt.sprintf("SELECT name, father, baseAdd, town, pin, roll, image, class FROM students where regNo = %ld", regdNo);
     query.exec(stmt);
     if(query.next())
     {
         stud.regNo = regdNo;
         stud.name = query.value(0).toString();
         name = stud.name;
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
             stmt.sprintf("SELECT * FROM reg%ld;", regdNo);
             query.exec(stmt);
             if(!query.next())
             {
                 totalCurrent += feeStruc.regFee;
                 str = QString::number(feeStruc.regFee);
                 currentItem[0]->setText(str);
                 status = true;
             }
             else
             {
                 rep = updateFeeDues();
                 totalCurrent += totalDues;
//                 cout<<"\nDues::"<<totalDues<<"\nDeposite::"<<totalCurrent<<"\n";
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
                 str = QString::number(feeStruc.duesMisc);
                 duesItem[8]->setText(str);

             }
             if(rep > 0)
             {
                totalCurrent += feeStruc.tutFee;
                str = QString::number(feeStruc.tutFee);
                currentItem[1]->setText(str);
                totalCurrent += feeStruc.devlpFee;
                str = QString::number(feeStruc.devlpFee);
                currentItem[6]->setText(str);
                totalCurrent += feeStruc.compFee;
                str = QString::number(feeStruc.compFee);
                currentItem[7]->setText(str);
             }
             str = QString::number(totalCurrent);
             currentItem[9]->setText(str);
         }
         stmt = "SELECT receiptNo FROM feereceipt ORDER BY receiptNo DESC LIMIT 1;";
         query.exec(stmt);
         if(query.next())
         {
             receiptNo = query.value(0).toLongLong()+1;
             str = QString::number(receiptNo);
             ui->leReceipNo->setText(str);
         }
         else
         {
             receiptNo = 1;
             str = QString::number(receiptNo);
             ui->leReceipNo->setText(str);
         }
         month = ui->deReceiptDate->date().month();
         if(month > 3)
             ui->cbMonth->setCurrentIndex(month - 3);
         else
             ui->cbMonth->setCurrentIndex(month + 9);
         ui->pbDeposite->setEnabled(true);
         pUi->tabWidget->insertTab(index, this, "Fee Receipt");
         pUi->tabWidget->setCurrentIndex(index);
         pUi->statusBar->showMessage(" Fee Receipt Generated", 5000);
     }
     else
     {
         QMessageBox::critical(0, QObject::tr("INVALID REGISTRATION NUMBER!!"), query.lastError().text(),  QMessageBox::Ok);
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
        for(int i = 0; i<=9; i++)
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
    if((QMessageBox::warning(this, tr("Confirm transaction"), tr("Confirm Transaction?\n Note: Database would be updated!!"),
                            QMessageBox::Yes, QMessageBox::Cancel)) == QMessageBox::Yes)
    {
        feeStruc.depRegFee = depositeItem[0]->text().toDouble();
        feeStruc.depTutFee = depositeItem[1]->text().toDouble();
        feeStruc.depGenrFee = depositeItem[2]->text().toDouble();
        feeStruc.depExamFee = depositeItem[3]->text().toDouble();
        feeStruc.depReAddmFee = depositeItem[4]->text().toDouble();
        feeStruc.depDevlpFee = depositeItem[6]->text().toDouble();
        feeStruc.depCompFee = depositeItem[7]->text().toDouble();
        feeStruc.depMisc = depositeItem[8]->text().toDouble();
        feeStruc.depPrevDues = depositeItem[5]->text().toDouble();
        totalDeposite = depositeItem[9]->text().toDouble();
        switch(ui->cbMonth->currentIndex())
        {
            case 1: month = 4;
            break;
            case 2: month = 5;
            break;
            case 3: month = 6;
            break;
            case 4: month = 7;
            break;
            case 5: month = 8;
            break;
            case 6: month = 9;
            break;
            case 7: month = 10;
            break;
            case 8: month = 11;
            break;
            case 9: month = 12;
            break;
            case 10: month = 1;
            break;
            case 11: month = 2;
            break;
            case 12: month = 3;
            break;
        }
        try
        {
            stmt.sprintf("INSERT INTO feereceipt VALUES (%ld, \"%s\", %d, %ld, \"%s\", %f, %f, %f , %f, %f, %f, %f, %f, %f, %f, %f);",
                     ui->leReceipNo->text().toLong(), ui->deReceiptDate->date().toString("yyyy-MM-dd").toStdString().c_str(), month,
                     regNo, name.toStdString().c_str(), feeStruc.depRegFee, feeStruc.depTutFee, feeStruc.depGenrFee,
                     feeStruc.depExamFee, feeStruc.depReAddmFee, feeStruc.depLateFee, feeStruc.depDevlpFee, feeStruc.depCompFee,
                     feeStruc.depMisc, feeStruc.depPrevDues, totalDeposite);

            query.exec(stmt);
            mReport = new MonthlyReport(pUi);
            if(query.numRowsAffected() != -1)
            {
                pUi->statusBar->showMessage(" Receipt Added!!");
                if(!status)
                {
                    status = mReport->updateReport(month, QDate::currentDate().year(), false, feeStruc.depTutFee, feeStruc.depGenrFee, feeStruc.depExamFee,
                                         currentItem[4]->text().toDouble(), feeStruc.depReAddmFee, feeStruc.depDevlpFee, feeStruc.depCompFee, currentItem[8]->text().toDouble(),
                                         feeStruc.depMisc, feeStruc.depPrevDues);
                    if(status)
                    {
                        pUi->statusBar->showMessage("Monthly Report Updated", 5000);
                    }
                }
                else
                {
                    status = mReport->updateReport(month, QDate::currentDate().year(), true, feeStruc.depTutFee, feeStruc.depGenrFee, feeStruc.depExamFee,
                                                  currentItem[4]->text().toDouble(), feeStruc.depReAddmFee, feeStruc.depDevlpFee, feeStruc.depCompFee, currentItem[8]->text().toDouble(),
                                                  feeStruc.depMisc, feeStruc.depPrevDues, feeStruc.depRegFee, currentItem[0]->text().toDouble(), currentItem[1]->text().toDouble(), currentItem[2]->text().toDouble(),
                            currentItem[3]->text().toDouble(), currentItem[6]->text().toDouble(), currentItem[7]->text().toDouble());
                    if(status)
                    {
                        pUi->statusBar->showMessage("Monthly Report Updated", 5000);
                    }
                }
                updateStudentsFeeDeposite();
                ui->pbDeposite->setEnabled(false);
                ui->twFeeReceipt->setDisabled(true);
                ui->cbExamFee->setDisabled(true);
                ui->cbReAddmFee->setDisabled(true);
                ui->pbPrint->setEnabled(true);
            }
            else
            {
                QMessageBox::critical(this, tr("Receipt submission failed!"), query.lastError().text(), QMessageBox::Ok);
            }
        }
        catch(exception& e)
        {
            cout<<"\n"<<e.what();
        }
    }
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
    int flagSet = 0;
    if( index == 0)
    {
        QMessageBox::warning(this, tr("Month Feild empty!"), tr("Please select the month uptill which the fee is to be deposited!"), QMessageBox::Ok);
    }
    else if (index == 1 || index == 2 || index == 4 || index == 5 || index == 6 || index ==7)
    {
        if(rep > 0)
        {
            str = QString::number(feeStruc.genrFee);
            currentItem[2]->setText(str);
            totalCurrent += feeStruc.genrFee;
            str = QString::number(totalCurrent);
            currentItem[9]->setText(str);
            flagSet = 1;
        }
    }
    else
    {
        if(flagSet == 1)
        {
            currentItem[2]->setText("");
            totalCurrent -= feeStruc.genrFee;
            str = QString::number(totalCurrent);
            currentItem[9]->setText(str);
            flagSet = 0;
        }
    }
}

int FeeReceipt::updateFeeDues()
{
    stmt.sprintf("SELECT * FROM reg%ld ORDER BY receiptNo DESC LIMIT 1;", regNo);
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
       feeStruc.depRegFee = query.value(3).toDouble();
       feeStruc.depTutFee = query.value(5).toDouble();
       feeStruc.depGenrFee = query.value(7).toDouble();
       feeStruc.depExamFee = query.value(9).toDouble();
       feeStruc.depReAddmFee = query.value(11).toDouble();
//       feeStruc.depLateFee = query.value(13).toDouble();
       feeStruc.depDevlpFee = query.value(13).toDouble();
       feeStruc.depCompFee = query.value(15).toDouble();
       feeStruc.depMisc = query.value(17).toDouble();
       totalDeposite = query.value(19).toDouble();

       feeStruc.duesRegFee = query.value(2).toDouble();
       feeStruc.duesTutFee = query.value(4).toDouble();
       feeStruc.duesGenrFee = query.value(6).toDouble();
       feeStruc.duesExamFee = query.value(8).toDouble();
       feeStruc.duesReAddmFee = query.value(10).toDouble();
//       feeStruc.duesLateFee = query.value(12).toDouble();
       feeStruc.duesDevlpFee = query.value(12).toDouble();
       feeStruc.duesCompFee = query.value(14).toDouble();
       feeStruc.duesMisc = query.value(16).toDouble();
       totalDues = query.value(18).toDouble();

       if(curMonth - mon <= 1 )
       {
           feeStruc.duesRegFee -= feeStruc.depRegFee;
           feeStruc.duesTutFee -= feeStruc.depTutFee;
           feeStruc.duesGenrFee -= feeStruc.depGenrFee;
           feeStruc.duesExamFee -= feeStruc.depExamFee;
           feeStruc.duesReAddmFee -= feeStruc.depReAddmFee;
//           feeStruc.duesLateFee -= feeStruc.depLateFee;
           feeStruc.duesDevlpFee -= feeStruc.depDevlpFee;
           feeStruc.duesCompFee -= feeStruc.depCompFee;
           feeStruc.duesMisc -= feeStruc.depMisc;
           totalDues -= totalDeposite;
           return diff;
       }
       else
       {
           while(diff != 1 )
           {
                feeStruc.duesRegFee = feeStruc.duesRegFee - feeStruc.depRegFee;
                feeStruc.duesTutFee = feeStruc.duesTutFee + feeStruc.tutFee - feeStruc.depTutFee;
                int dueMonth = curMonth - (diff - 1);
                if(dueMonth == 4 || dueMonth == 5 || dueMonth == 7 || dueMonth == 8 || dueMonth == 9 || dueMonth == 10)
                {
                    feeStruc.duesGenrFee = feeStruc.duesGenrFee + feeStruc.genrFee - feeStruc.depGenrFee;
                }
                else
                {
                    feeStruc.duesGenrFee = feeStruc.duesGenrFee - feeStruc.depGenrFee;
                }
                if(dueMonth == 2 || dueMonth == 7 || dueMonth == 11)
                {
                    feeStruc.duesExamFee = feeStruc.duesExamFee + feeStruc.examFee -  feeStruc.depExamFee;
                }
                else
                {
                    feeStruc.duesExamFee = feeStruc.duesExamFee - feeStruc.depExamFee;
                }
                feeStruc.duesReAddmFee = feeStruc.duesReAddmFee - feeStruc.depReAddmFee;
//                feeStruc.duesLateFee = feeStruc.duesLateFee - feeStruc.depLateFee;
                feeStruc.duesDevlpFee = feeStruc.duesDevlpFee + feeStruc.devlpFee - feeStruc.depDevlpFee;
                feeStruc.duesCompFee = feeStruc.duesCompFee + feeStruc.compFee - feeStruc.depCompFee;
                feeStruc.duesMisc = feeStruc.duesMisc - feeStruc.depMisc;
                totalDues = feeStruc.duesRegFee + feeStruc.duesTutFee + feeStruc.duesGenrFee + feeStruc.duesExamFee +
                        feeStruc.duesReAddmFee + feeStruc.duesLateFee + feeStruc.duesDevlpFee + feeStruc.duesCompFee + feeStruc.duesMisc;
                stmt.sprintf("INSERT INTO reg\"%s\" VALUES (%d, %ld, %ld, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f,  %f, %f, %f, %f, %f, %f, %f, %f);",
                             regNo, dueMonth, 0, feeStruc.duesRegFee, 0, feeStruc.duesTutFee, 0, feeStruc.duesGenrFee, 0, feeStruc.duesExamFee, 0, feeStruc.duesReAddmFee, 0,
                             feeStruc.duesDevlpFee, 0, feeStruc.duesCompFee, 0, feeStruc.duesMisc, 0, totalDues, 0);
                query.exec(stmt);
                if(query.numRowsAffected() != -1)
                    cout<<"Databases Updated";
                else
                    cout<<"Database UPdate failed";
                feeStruc.depRegFee = 0;
                feeStruc.depTutFee = 0;
                feeStruc.depGenrFee= 0;
                feeStruc.depExamFee = 0;
                feeStruc.depReAddmFee = 0;
//                feeStruc.depLateFee = 0;
                feeStruc.depCompFee = 0;
                feeStruc.depMisc = 0;
                feeStruc.depDevlpFee = 0;

                diff--;
           }
       }
    }
    return INT_MAX;
}


void FeeReceipt::on_twFeeReceipt_cellActivated(int row, int column)
{
    int i;
    if (column == 1)
    {
        totalDues = 0;
        for(i = 0; i < 9; i++)
            totalDues += duesItem[i]->text().toDouble();
        str = QString::number(totalDues);
        duesItem[9]->setText(str);
    }
    else if(column == 2)
    {
        totalCurrent = 0;
        for(i = 0; i < 9; i++)
            totalCurrent += currentItem[i]->text().toDouble();

//        totalCurrent += currentItem[8]->text().toDouble();
//        prevMisc = currentItem[8]->text().toDouble();
        str = QString::number(totalCurrent);
        currentItem[9]->setText(str);
    }
    else if(column == 3)
    {
        totalDeposite = 0;
        for(i = 0; i < 9; i++)
            totalDeposite += depositeItem[i]->text().toDouble();
        str = QString::number(totalDeposite);
        depositeItem[9]->setText(str);
    }
    else if(column == 4)
    {
        totalCleared = 0;
        for(i = 0; i < 9; i++)
            totalCleared += clearedItem[i]->text().toDouble();
        str = QString::number(totalCleared);
        clearedItem[9]->setText(str);
    }
}

void FeeReceipt::updateStudentsFeeDeposite()
{
    try
    {

        feeStruc.duesRegFee = duesItem[0]->text().toDouble() + currentItem[0]->text().toDouble();
        feeStruc.duesTutFee = duesItem[1]->text().toDouble() + currentItem[1]->text().toDouble();
        feeStruc.duesGenrFee = duesItem[2]->text().toDouble() + currentItem[2]->text().toDouble();
        feeStruc.duesExamFee = duesItem[3]->text().toDouble() + currentItem[3]->text().toDouble();
        feeStruc.duesReAddmFee = duesItem[4]->text().toDouble() + currentItem[4]->text().toDouble();
        feeStruc.duesDevlpFee = duesItem[6]->text().toDouble() + currentItem[6]->text().toDouble();
        feeStruc.duesCompFee = duesItem[7]->text().toDouble() + currentItem[7]->text().toDouble();
        feeStruc.duesMisc = duesItem[8]->text().toDouble() + currentItem[8]->text().toDouble();
        totalDues = feeStruc.duesRegFee + feeStruc.duesTutFee + feeStruc.duesGenrFee + feeStruc.duesExamFee +
                feeStruc.duesReAddmFee +  feeStruc.duesDevlpFee + feeStruc.duesCompFee + feeStruc.duesMisc;

        feeStruc.depRegFee = depositeItem[0]->text().toDouble() + clearedItem[0]->text().toDouble();
        feeStruc.depTutFee = depositeItem[1]->text().toDouble() + clearedItem[1]->text().toDouble();
        feeStruc.depGenrFee = depositeItem[2]->text().toDouble() + clearedItem[2]->text().toDouble();
        feeStruc.depExamFee = depositeItem[3]->text().toDouble() + clearedItem[3]->text().toDouble();
        feeStruc.depReAddmFee = depositeItem[4]->text().toDouble() + clearedItem[4]->text().toDouble();
        feeStruc.depDevlpFee = depositeItem[6]->text().toDouble() + clearedItem[6]->text().toDouble();
        feeStruc.depCompFee = depositeItem[7]->text().toDouble() + clearedItem[7]->text().toDouble();
        feeStruc.depMisc = depositeItem[8]->text().toDouble() + clearedItem[8]->text().toDouble();
        totalDeposite = feeStruc.depRegFee + feeStruc.depTutFee + feeStruc.depGenrFee + feeStruc.depExamFee +
                feeStruc.depReAddmFee + feeStruc.depDevlpFee + feeStruc.depCompFee + feeStruc.depMisc;
            stmt.sprintf("INSERT INTO reg%ld VALUES (%d, %ld, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f);",
                     regNo, month, ui->leReceipNo->text().toLong(), feeStruc.duesRegFee, feeStruc.depRegFee, feeStruc.duesTutFee, feeStruc.depTutFee, feeStruc.duesGenrFee, feeStruc.depGenrFee,
                     feeStruc.duesExamFee, feeStruc.depExamFee, feeStruc.duesReAddmFee, feeStruc.depReAddmFee, feeStruc.duesDevlpFee, feeStruc.depDevlpFee, feeStruc.duesCompFee, feeStruc.depCompFee,
                     feeStruc.duesMisc, feeStruc.depMisc, totalDues, totalDeposite);
        query.exec(stmt);
        if(query.numRowsAffected() != -1);
//            pUi->statusBar->showMessage("Databases Updated", 5000);
        else
            pUi->statusBar->showMessage("Database Update failed", 5000);

    }
    catch(exception& e)
    {
        QMessageBox::critical(this, tr("Datatbase Issue"), e.what(), QMessageBox::Ok);
    }
}


