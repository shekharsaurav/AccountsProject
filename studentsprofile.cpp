#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>
#include <iostream>

#include "studentsprofile.h"
#include "ui_studentsprofile.h"
#include "getregnodialog.h"
#include "adminWindow.h"
#include "updatestudentprofile.h"

using namespace std;

StudentsProfile::StudentsProfile(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StudentsProfile)
{
    ui->setupUi(this);
}

StudentsProfile::~StudentsProfile()
{
    delete ui;
}

void StudentsProfile::showProfile(long reqStudent, int index, Ui::adminWindow *adUi)
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

        QString str;
        str = QString::number(studProf.regNo);
        ui->leRegNoP->setText(str);
        ui->deRegDateP->setDate(studProf.regDate);
        ui->leNameStudentP->setText(studProf.name);
        ui->deDOBP->setDate(studProf.dob);
        if(studProf.gender == 1)
            ui->leGenderP->setText("Male");
        else
            ui->leGenderP->setText("Female");
        ui->leBloodGrpP->setText(studProf.bloodGrp);
        ui->leNationalityP->setText(studProf.nationality);
        ui->leReligionP->setText(studProf.religion);
        ui->leNameMotherP->setText(studProf.mother);
        ui->leMotherOccupationP->setText(studProf.occpMother);
        ui->leNameFatherP->setText(studProf.father);
        ui->leFatherOccupationP->setText(studProf.occpFather);
        ui->teBaseAddP->setPlainText(studProf.add.baseAdd);
        ui->leTownP->setText(studProf.add.town);
        str = QString::number(studProf.add.pin);
        ui->lePincodeP->setText(str);
        ui->leStateP->setText(studProf.add.state);
        ui->leEmailP->setText(studProf.email);
        str = QString::number(studProf.contact1);
        ui->lePhoneP->setText(str);
        str = QString::number(studProf.contact2);
        ui->lePhoneP_2->setText(str);
        QPixmap pm;
        pm.load(studProf.image, 0, Qt::AutoColor);
        pm.scaled(121, 141);
        ui->lPhotoP->setPixmap(pm);
        adUi->tabWidget->insertTab(index, this, "Student Profile");
        adUi->tabWidget->setCurrentIndex(index);
        adUi->statusBar->showMessage(" Student's profile displayed.", 5000);
    }
    else
    {
        QMessageBox::critical(0, QObject::tr("Invalid Request"), query.lastError().text());
        delete this;
    }
    tabId = index;
    pUi = adUi;
}

void StudentsProfile::on_pbClose_clicked()
{
    pUi->tabWidget->removeTab(tabId);
    this->close();
}


void StudentsProfile::on_pbUpdate_clicked()
{
    UpdateStudentProfile *profile = new UpdateStudentProfile();
    profile->showProfile(ui->leRegNoP->text().toLong(), tabId+1 , pUi);
}
