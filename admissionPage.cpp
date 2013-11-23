#include <QtGui>

#include "admissionPage.h"
#include "ui_admissionPage.h"

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
