#include <QtGui>
#include <QSqlQuery>
#include <QMessageBox>

#include "admissionPage.h"
#include "ui_admissionPage.h"
#include "dbConnection.h"

AdmissionPage::AdmissionPage(QWidget *parent): ui(new Ui::admissionPage)
{
    ui->setupUi(this);
}

AdmissionPage::~AdmissionPage()
{
    delete ui;
}

void AdmissionPage::on_cbUpload_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Upload Picture"), ".", tr("Image files (*.jpeg, *.png, *jpg"));
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
}
