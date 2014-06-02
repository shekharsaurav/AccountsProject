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

#include "admissionPage.h"
#include "ui_admissionPage.h"
#include "dbConnection.h"
#include "students.h"
#include "ui_adminWindow.h"

using namespace std;

AdmissionPage::AdmissionPage(Ui::adminWindow *parentUi, QWidget *parent): ui(new Ui::admissionPage)
{
    ui->setupUi(this);
    ui->deRegDate->setDate(QDate::currentDate());
    int regNo = 0;
    QSqlQuery query;
    QString reg;
    query.exec("Select regNo from STUDENTS order by regNo desc limit 1;");
    if(query.next())
    {
        regNo = query.value(0).toInt(0)+1;
        reg = QString::number(regNo);
        ui->leRegNo->setText(reg);
    }
    else
        ui->leRegNo->setText("0001");
    pUi = parentUi;
 }

AdmissionPage::~AdmissionPage()
{
    delete ui;
}

void AdmissionPage::on_cbUpload_clicked()
{
    fileName = QFileDialog::getOpenFileName(this, tr("Upload Picture"), ".", tr("Image files (*.jpeg, *.png, *.jpg"));
    fileName =copyImage(fileName);
    pm.load(fileName, 0, Qt::AutoColor);
    pm.scaled(121, 141);
    ui->lPhoto->setPixmap(pm);
    pUi->statusBar->showMessage(tr(" Photo Uploaded"), 5000);
}

void AdmissionPage::on_pbSubmit_clicked()
{
    if (ui->leNameStudent->text().isEmpty() || ui->cbGender->currentIndex() == 0 || ui->leNationality->text().isEmpty() ||
            ui->leNameFather->text().isEmpty() || ui->leNameMother->text().isEmpty() ||
            ui->leFatherOccupation->text().isEmpty() || ui->leMotherOccupation->text().isEmpty() ||
            ui->teBaseAdd->toPlainText().isNull() || ui->leTown->text().isEmpty() ||
            ui->leState->text().isEmpty() || ui->lePincode->text().isEmpty() ||
            ui->lePhone->text().isEmpty())
    {
         QMessageBox::critical(0, tr("Submission Failure"),tr("Some mandatory fields are empty!!"));
         pUi->statusBar->showMessage(tr(" Some mandatory fields are empty!"), 5000 );
    }
    else
    {
        if((QMessageBox::warning(this, tr("Confirm Submission"), tr("Confirm admission?\n Note: Database will be updated."),QMessageBox::Yes, QMessageBox::Cancel)) == QMessageBox::Yes)
        {
            Students studx;
            studx.regNo = ui->leRegNo->text().toLong();
            studx.regDate = ui->deRegDate->date();
            studx.name = ui->leNameStudent->text();
            studx.dob = ui->deDOB->date();
            int index = ui->cbGender->currentIndex();
            if(index == 1)
                studx.gender = true;
            else if(index == 2)
                studx.gender = false;
            studx.std = ui->leStd->text();
            studx.nationality = ui->leNationality->text();
            studx.religion = ui->leReligion->text();
            studx.bloodGrp = ui->leBloodGrp->text();
            studx.mother = ui->leNameMother->text();
            studx.occpMother = ui->leMotherOccupation->text();
            studx.occpFather = ui->leFatherOccupation->text();
            studx.father = ui->leNameFather->text();
            studx.add.baseAdd = ui->teBaseAdd->toPlainText();
            studx.add.town = ui->leTown->text();
            studx.add.pin = ui->lePincode->text().toLong();
            studx.add.state = ui->leState->text();
            studx.email = ui->leEmail->text();
            studx.contact1 = ui->lePhone->text().toLongLong();
            studx.contact2 = ui->lePhone_2->text().toLongLong();
            studx.image = fileName;
            QString stmt;
// = "INSERT INTO STUDENTS values (";
//        sprintf(stmt,"INSERT INTO STUDENTS values (%ld, \"%s\", \"%s\", \"%s\", %d, \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", %ld, \"%s\", \"%s\", %ld, %ld, %d, \"%s\");",
//                studx.regNo, studx.regDate.toString().data(), studx.name.data(), studx.dob.toString().data(), studx.gender,
//                studx.bloodGrp.data(), studx.nationality.data(), studx.religion.data(), studx.mother.data(),
//                studx.occpMother.data(), studx.father.data(), studx.occpFather.data(), studx.add.baseAdd.data(),
//                studx.add.town.data(), studx.add.pin, studx.add.state.data(), studx.email.data(), studx.contact1,
//                studx.contact2, 0, studx.image.data());
            stmt.sprintf("INSERT INTO STUDENTS values (%ld, \"%s\", \"%s\", \"%s\", %d, \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", %ld, \"%s\", \"%s\", %lld, %lld, %d, \"%s\", \"%s\");",
                                         studx.regNo, studx.regDate.toString("yyyy-MM-dd").toStdString().c_str(), studx.name.toStdString().c_str(), studx.dob.toString("yyyy-MM-dd").toStdString().c_str(), studx.gender,
                                        studx.bloodGrp.toStdString().c_str(), studx.nationality.toStdString().c_str(), studx.religion.toStdString().c_str(),
                                        studx.mother.toStdString().c_str(), studx.occpMother.toStdString().c_str(), studx.father.toStdString().c_str(),
                                        studx.occpFather.toStdString().c_str(), studx.add.baseAdd.toStdString().c_str(), studx.add.town.toStdString().c_str(),
                                        studx.add.pin, studx.add.state.toStdString().c_str(), studx.email.toStdString().c_str(), studx.contact1,
                                        studx.contact2, 0, studx.image.toStdString().c_str(), studx.std.toStdString().c_str());
//            cout<<"\n\n"<<stmt.toStdString()<<"\n\n";
            QSqlDatabase::database().transaction();
            QSqlQuery query;
            query.exec(stmt);
            QSqlDatabase::database().commit();
            int result = query.numRowsAffected();
            if(result != -1)
            {
                QMessageBox::about(0, tr("Submission Successful"),tr("Student's Details generated in database successfully.."));
                pUi->statusBar->showMessage(tr(" Database updated successfully!"), 5000 );
            }
            else
            {
                 QMessageBox::critical(0, tr("Submission failed"), query.lastError().text());
                 pUi->statusBar->showMessage(tr(" Submission failed!"), 5000 );
            }
            stmt.sprintf("CREATE TABLE reg%ld (month INT, receiptNo BIGINT, regFeeDues DOUBLE, regFeeDep DOUBLE, tutFeeDues DOUBLE, tutFeeDep DOUBLE, genFeeDues DOUBLE, genFeeDep DOUBLE, examFeeDues DOUBLE, examFeeDep DOUBLE, reAddFeeDues DOUBLE, reAddFeeDep DOUBLE, devlpFeeDues DOUBLE, devlpFeeDep DOUBLE, compFeeDues DOUBLE, compFeeDep DOUBLE, miscDues DOUBLE, miscDep DOUBLE, TotDues DOUBLE, TotDep Double);", studx.regNo);
            query.exec(stmt);
            QSqlDatabase::database().commit();
            result = query.numRowsAffected();
            if(result != -1)
            {
                pUi->statusBar->showMessage(tr(" Financial account created for the student."), 8000);
            }
            else
            {
                pUi->statusBar->showMessage(tr(" Financial transaction failed!"));
            }
        }
    }
}

void AdmissionPage::on_pbReset_clicked()
{
    ui->leNameStudent->setText("");
    ui->deDOB->setDate(QDate::fromString("01/01/00"));
    ui->cbGender->setCurrentIndex(0);
    ui->leStd->setText("");
    ui->leBloodGrp->setText("");
    ui->leReligion->setText("");
    ui->leNationality->setText("");
    ui->leNameFather->setText("");
    ui->leFatherOccupation->setText("");
    ui->leNameMother->setText("");
    ui->leMotherOccupation->setText("");
    ui->teBaseAdd->setPlainText("");
    ui->leTown->setText("");
    ui->lePincode->setText("");
    ui->leState->setText("");
    ui->lePhone->setText("");
    ui->lePhone_2->setText("");
    ui->leEmail->setText("");
    ui->lPhoto->setText("Photo");
    pUi->statusBar->showMessage(tr(" All fields reset!"), 5000 );
}


QString AdmissionPage::copyImage(QString file)
{
    ifstream instream(file.toStdString().c_str());
    QString imageFile;
    char *buf;
    if(!instream)
        QMessageBox::critical(0, QObject::tr("Image Upload Failure"), QObject::tr("Could not read the image file!!\nTry Again..."));
    else
    {
        QString curDir;
        curDir = QDir::currentPath();
        imageFile.sprintf("%s\\Images\\I%s.jpg", curDir.toStdString().c_str(), ui->leRegNo->text().toStdString().c_str());
        cout<<"\n\n"<<imageFile.toStdString()<<"\n";
        ofstream outstream(imageFile.toStdString().c_str());
        if(!outstream)
        {
           QMessageBox::critical(0, QObject::tr("Image Upload Failure"), QObject::tr("Could not generate new image file!!\nTry Again..."));
        }
        else
        {
            while((instream.read((char*) &buf, sizeof buf)))
                outstream.write((char*) &buf, sizeof buf);
        }
        outstream.flush();
        outstream.close();
    }
    instream.close();
    return imageFile;
}
