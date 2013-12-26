#include <QtGui>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlError>
#include <algorithm>
#include <iostream>
#include <cstring>

#include "admissionPage.h"
#include "ui_admissionPage.h"
#include "dbConnection.h"
#include "students.h"

using namespace std;

AdmissionPage::AdmissionPage(QWidget *parent): ui(new Ui::admissionPage)
{
    ui->setupUi(this);
    ui->deRegDate->setDate(QDate::currentDate());
    ui->leRegNo->setText("0001");
}

AdmissionPage::~AdmissionPage()
{
    delete ui;
}

void AdmissionPage::on_cbUpload_clicked()
{
    fileName = QFileDialog::getOpenFileName(this, tr("Upload Picture"), ".", tr("Image files (*.jpeg, *.png, *.jpg, *.bmp,  "));
    QPixmap pm;
    pm.load(fileName, 0, Qt::AutoColor);
    pm.scaled(121, 141);
    ui->lPhoto->setPixmap(pm);
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
         QMessageBox::critical(0, tr("Submit Faiure"),tr("Some mandatory fields are empty!!"));
    }
    else
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
        studx.contact1 = ui->lePhone->text().toLong();
        studx.contact2 = ui->lePhone_2->text().toLong();
        studx.image = fileName;
        QString stmt;
// = "INSERT INTO STUDENTS values (";
//        sprintf(stmt,"INSERT INTO STUDENTS values (%ld, \"%s\", \"%s\", \"%s\", %d, \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", %ld, \"%s\", \"%s\", %ld, %ld, %d, \"%s\");",
//                studx.regNo, studx.regDate.toString().data(), studx.name.data(), studx.dob.toString().data(), studx.gender,
//                studx.bloodGrp.data(), studx.nationality.data(), studx.religion.data(), studx.mother.data(),
//                studx.occpMother.data(), studx.father.data(), studx.occpFather.data(), studx.add.baseAdd.data(),
//                studx.add.town.data(), studx.add.pin, studx.add.state.data(), studx.email.data(), studx.contact1,
//                studx.contact2, 0, studx.image.data());
        stmt.sprintf("INSERT INTO STUDENTS values (%ld, \"%s\", \"%s\", \"%s\", %d, \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", %ld, \"%s\", \"%s\", %ld, %ld, %d, \"%s\");",
                                     studx.regNo, studx.regDate.toString().data(), studx.name.toStdString().c_str(), studx.dob.toString().data(), studx.gender,
                                     studx.bloodGrp.toStdString().c_str(), studx.nationality.toStdString().c_str(), studx.religion.toStdString().c_str(),
                                     studx.mother.toStdString().c_str(), studx.occpMother.toStdString().c_str(), studx.father.toStdString().c_str(),
                                     studx.occpFather.toStdString().c_str(), studx.add.baseAdd.toStdString().c_str(), studx.add.town.toStdString().c_str(),
                                     studx.add.pin, studx.add.state.toStdString().c_str(), studx.email.toStdString().c_str(), studx.contact1,
                                     studx.contact2, 0, studx.image.toStdString().c_str());
        cout<<"\n\n"<<stmt.toStdString()<<"\n\n";
        QSqlDatabase::database().transaction();
        QSqlQuery query;
        query.exec(stmt);
        QSqlDatabase::database().commit();
        int result = query.numRowsAffected();
        if(result != -1)
        {
            QMessageBox::about(0, tr("Submit Successful"),tr("Student's Details generated in database successfully.."));
        }
        else
        {
             QMessageBox::critical(0, tr("Submit failed"), query.lastError().text());
        }
    }
}
