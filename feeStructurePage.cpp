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

#include "feeStructurePage.h"
#include "ui_feeStructurePage.h"
#include "dbConnection.h"
#include "feeStructure.h"
#include "ui_adminWindow.h"

using namespace std;

FeeStructurePage::FeeStructurePage(Ui::adminWindow *parentUi, QWidget *parent): ui(new Ui::feeStructurePage )
{
    ui->setupUi(this);
    for(int i = -1; i<=6; i++)
    {
        item[i+1] = new QTableWidgetItem("0");
        ui->twFeeStruct->setItem(i, 3, item[i+1]);
    }
    pUi = parentUi;
}

FeeStructurePage::~FeeStructurePage()
{
    delete ui;
}

void FeeStructurePage::on_twFeeStruct_itemChanged(QTableWidgetItem *item)
{
    ui->pbReset->setEnabled(true);
    ui->pbUpdate->setEnabled(true);
}

void FeeStructurePage::on_pbClose_clicked()
{
    this->close();
}

void FeeStructurePage::on_pbReset_clicked()
{
    try
    {
        for(int i = -1; i<=6; i++)
        {
            item[i+1]->setText("");
        }
         pUi->statusBar->showMessage(tr(" Fields Reset!!"), 5000 );
    }
    catch(exception& e)
    {
       cout<<e.what();
    }
}

void FeeStructurePage::showFeeStructure(QString std, int index, Ui::adminWindow *adUi)
{
    FeeStructure feeStruc;
    QSqlQuery query;
    QString stmt;
    stmt.sprintf("SELECT * FROM feestructure WHERE class = \"%s\";", std);
    query.exec(stmt);
    if(query.next())
    {
        feeStruc.std = query.value(0).toString();
        feeStruc.regFee = query.value(1).toDouble();
        feeStruc.tutFee = query.value(2).toDouble();
        feeStruc.genrFee = query.value(3).toDouble();
        feeStruc.examFee = query.value(4).toDouble();
        feeStruc.reAddmFee = query.value(5).toDouble();
        feeStruc.lateFee = query.value(6).toDouble();
        feeStruc.devlpFee = query.value(7).toDouble();
        feeStruc.compFee = query.value(8).toDouble();
        ui->leClass->setText(feeStruc.std);
        item[0]->setText(feeStruc.regFee.toString());
    }
}

void FeeStructurePage::on_pbUpdate_clicked()
{
    if (ui->leClass->text().isEmpty() || item[0]->text().isEmpty() || item[1]->text().isEmpty() || item[2]->text().isEmpty() || item[3]->text().isEmpty() ||
            item[4]->text().isEmpty() || item[5]->text().isEmpty() || item[6]->text().isEmpty() || item[7]->text().isEmpty())
    {
         QMessageBox::critical(0, tr("Submission Failure"),tr("Some fields are empty!!"));
         pUi->statusBar->showMessage(tr(" Some mandatory fields are empty!"), 5000 );
    }
    else
    {
        if((QMessageBox::warning(this, tr("Confirm Submission"), tr("Confirm update?\n Note: Fee Structure will be updated!!"), QMessageBox::Yes, QMessageBox::Cancel)) == QMessageBox::Yes )
        {
            FeeStructure struc;
            struc.std = ui->leClass->text();
            struc.regFee = item[0]->text().toDouble();
            struc.tutFee = item[1]->text().toDouble();
            struc.genrFee = item[2]->text().toDouble();
            struc.examFee = item[3]->text().toDouble();
            struc.reAddmFee = item[4]->text().toDouble();
            struc.lateFee = item[5]->text().toDouble();
            struc.devlpFee = item[6]->text().toDouble();
            struc.compFee = item[7]->text().toDouble();
            QString stmt;
            stmt.sprintf("INSERT INTO feestructure VALUES (\"%s\", %f, %f, %f, %f, %f, %f, %f, %f);", struc.std.toStdString().c_str(), struc.regFee, struc.tutFee, struc.genrFee, struc.examFee,
                         struc.reAddmFee, struc.lateFee, struc.devlpFee, struc.compFee);
            QSqlDatabase::database().transaction();
            QSqlQuery query;
            query.exec(stmt);
            QSqlDatabase::database().commit();
            int result = query.numRowsAffected();
            if(result != -1)
            {
                QMessageBox::about(0, tr("Submission Successful"), tr("Fee Structure updated in database successfully.."));
                pUi->statusBar->showMessage(tr(" Database updated successfully!"), 5000 );
            }
            else
            {
                 QMessageBox::critical(0, tr("Submission failed"), query.lastError().text());
                 pUi->statusBar->showMessage(tr(" Submission failed!"), 5000 );
            }
        }
    }
}
