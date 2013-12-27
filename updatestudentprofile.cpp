#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <fstream>
#include <cstring>
#include <QSqlDatabase>
#include <iostream>


#include "updatestudentprofile.h"
#include "ui_updatestudentprofile.h"
#include "students.h"

using namespace std;

UpdateStudentProfile::UpdateStudentProfile(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UpdateStudentProfile)
{
    ui->setupUi(this);
}

UpdateStudentProfile::~UpdateStudentProfile()
{
    delete ui;
}

void UpdateStudentProfile::showProfile(long reqStudent, int index, Ui::adminWindow *adUi)
{
    Students studProf;
    QSqlQuery query;
    QString stmt;
    stmt.sprintf("Select * from STUDENTS where regNo = %ld;", reqStudent);
    query.exec(stmt);
    if(query.next())
    {
        studProf.regNo = query.value(0).toLongLong();
        studProf.regDate = query.value(1).toDate();
        studProf.name = query.value(2).toString();
        studProf.dob = query.value(3).toDate();
        studProf.gender = query.value(4).toBool();
        studProf.bloodGrp = query.value(5).toString();
        studProf.nationality = query.value(6).toString();
        studProf.religion = query.value(7).toString();
        studProf.mother = query.value(8).toString();
        studProf.occpMother = query.value(9).toString();
        studProf.father = query.value(10).toString();
        studProf.occpFather = query.value(11).toString();
        studProf.add.baseAdd = query.value(12).toString();
        studProf.add.town = query.value(13).toString();
        studProf.add.pin = query.value(14).toLongLong();
        studProf.add.state = query.value(15).toString();
        studProf.email = query.value(16).toString();
        studProf.contact1 = query.value(17).toLongLong();
        studProf.contact2 = query.value(18).toLongLong();
        studProf.roll = query.value(19).toInt();
        studProf.image = query.value(20).toString();
        fileName = studProf.image;

        QString str;
        str = QString::number(studProf.regNo);
        ui->leRegNo->setText(str);
        ui->deRegDate->setDate(studProf.regDate);
        ui->leNameStudent->setText(studProf.name);
        ui->deDOB->setDate(studProf.dob);
        if(studProf.gender == 1)
            ui->cbGender->setCurrentIndex(1);
        else
            ui->cbGender->setCurrentIndex(2);
        ui->leBloodGrp->setText(studProf.bloodGrp);
        ui->leNationality->setText(studProf.nationality);
        ui->leReligion->setText(studProf.religion);
        ui->leNameMother->setText(studProf.mother);
        ui->leMotherOccupation->setText(studProf.occpMother);
        ui->leNameFather->setText(studProf.father);
        ui->leFatherOccupation->setText(studProf.occpFather);
        ui->teBaseAdd->setPlainText(studProf.add.baseAdd);
        ui->leTown->setText(studProf.add.town);
        str = QString::number(studProf.add.pin);
        ui->lePincode->setText(str);
        ui->leState->setText(studProf.add.state);
        ui->leEmail->setText(studProf.email);
        str = QString::number(studProf.contact1);
        ui->lePhone->setText(str);
        str = QString::number(studProf.contact2);
        ui->lePhone_2->setText(str);
        pm.load(studProf.image, 0, Qt::AutoColor);
        pm.scaled(121, 141);
        ui->lPhoto->setPixmap(pm);
        adUi->tabWidget->insertTab(index, this, "Student Profile");
        adUi->tabWidget->setCurrentIndex(index);
        adUi->statusBar->showMessage(" Student's profile displayed.", 5000);
    }
    else
    {
        QMessageBox::critical(0, QObject::tr("Invalid Request"), query.lastError().text());
        delete this;
    }
    pUi = adUi;
}

void UpdateStudentProfile::on_cbUpload_clicked()
{
    fileName = QFileDialog::getOpenFileName(this, tr("Upload Picture"), ".", tr("Image files (*.jpeg, *.png, *.jpg"));
    fileName = copyImage(fileName);
    pm.load(fileName, 0, Qt::AutoColor);
    pm.scaled(121, 141);
    ui->lPhoto->setPixmap(pm);
    pUi->statusBar->showMessage(tr(" Photo Uploaded"), 5000);
}


QString UpdateStudentProfile::copyImage(QString file)
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
        imageFile.sprintf("%s/Images/I%s.jpg", curDir.toStdString().c_str(), ui->leRegNo->text().toStdString().c_str());
//        cout<<"\n\n"<<imageFile.toStdString()<<"\n";
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
        outstream.close();
    }
    instream.close();
    return imageFile;
}

void UpdateStudentProfile::on_pbReset_clicked()
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

void UpdateStudentProfile::on_pbUpdate_clicked()
{
    if (ui->leNameStudent->text().isEmpty() || ui->cbGender->currentIndex() == 0 || ui->leNationality->text().isEmpty() ||
            ui->leNameFather->text().isEmpty() || ui->leNameMother->text().isEmpty() ||
            ui->leFatherOccupation->text().isEmpty() || ui->leMotherOccupation->text().isEmpty() ||
            ui->teBaseAdd->toPlainText().isNull() || ui->leTown->text().isEmpty() ||
            ui->leState->text().isEmpty() || ui->lePincode->text().isEmpty() ||
            ui->lePhone->text().isEmpty())
    {
         QMessageBox::critical(0, tr("Submit Faiure"),tr("Some mandatory fields are empty!!"));
         pUi->statusBar->showMessage(tr(" Some mandatory fields are empty!"), 5000 );
    }
    else
    {
        if((QMessageBox::warning(this, tr("Confirm Submission"), tr("Confirm admission?\n Note: Database will updated."),QMessageBox::Yes, QMessageBox::Cancel)) == QMessageBox::Yes)
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
            stmt.sprintf("Update STUDENTS set regDate=\"%s\", name=\"%s\", dob=\"%s\", gender=%d, bloodGrp=\"%s\", nation=\"%s\", religion=\"%s\", mother=\"%s\", occpMother=\"%s\", father=\"%s\", occpFather=\"%s\", baseAdd=\"%s\", town=\"%s\", pin=%ld, state=\"%s\", email=\"%s\", contact1=%lld, contact2=%lld, roll=%d, image=\"%s\" where regNo=%ld;",
                                        studx.regDate.toString("yyyy-MM-dd").toStdString().c_str(), studx.name.toStdString().c_str(), studx.dob.toString("yyyy-MM-dd").toStdString().c_str(), studx.gender,
                                        studx.bloodGrp.toStdString().c_str(), studx.nationality.toStdString().c_str(), studx.religion.toStdString().c_str(),
                                        studx.mother.toStdString().c_str(), studx.occpMother.toStdString().c_str(), studx.father.toStdString().c_str(),
                                        studx.occpFather.toStdString().c_str(), studx.add.baseAdd.toStdString().c_str(), studx.add.town.toStdString().c_str(),
                                        studx.add.pin, studx.add.state.toStdString().c_str(), studx.email.toStdString().c_str(), studx.contact1,
                                        studx.contact2, 0, studx.image.toStdString().c_str(), studx.regNo);
//            cout<<"\n\n"<<stmt.toStdString()<<"\n\n";
            QSqlDatabase::database().transaction();
            QSqlQuery query;
            query.exec(stmt);
            QSqlDatabase::database().commit();
            int result = query.numRowsAffected();
            if(result != -1)
            {
                QMessageBox::about(0, tr("Submit Successful"),tr("Student's Details generated in database successfully.."));
                pUi->statusBar->showMessage(tr(" Database updated successfully!"), 5000 );
            }
            else
            {
                 QMessageBox::critical(0, tr("Submit failed"), query.lastError().text());
                 pUi->statusBar->showMessage(tr(" Submission failed!"), 5000 );
            }
        }
    }
}
