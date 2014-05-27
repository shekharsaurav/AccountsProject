#include "getregnodialog.h"
#include "ui_getregnodialog.h"
#include "studentsprofile.h"
#include "updatestudentprofile.h"
#include "feeReceipt.h"

GetRegNoDialog::GetRegNoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GetRegNoDialog)
{
    ui->setupUi(this);
}

GetRegNoDialog::~GetRegNoDialog()
{
    delete ui;
}

void GetRegNoDialog::on_buttonBox_accepted()
{
    if(taskId == 1)
    {
        FeeReceipt *receipt = new FeeReceipt(adwn);
        receipt->generateReceipt(ui->leGetRegNo->text().toLong(), index);
        this->close();
    }

    if(taskId == 3)
    {
        StudentsProfile *profile = new StudentsProfile(adwn);
        profile->showProfile(ui->leGetRegNo->text().toLong(), index);
        this->close();
    }

    else if(taskId == 4)
    {
        UpdateStudentProfile *profile = new UpdateStudentProfile(adwn);
        profile->showProfile(ui->leGetRegNo->text().toLong(), index);
        this->close();
    }
}

void GetRegNoDialog::on_buttonBox_rejected()
{
    this->close();
}
