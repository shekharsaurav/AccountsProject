#include "getregnodialog.h"
#include "ui_getregnodialog.h"
#include "studentsprofile.h"

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
     StudentsProfile *profile = new StudentsProfile(this);
     profile->showProfile(ui->leGetRegNo->text().toLong(0, 10), index,  adwn);
     this->close();
}

void GetRegNoDialog::on_buttonBox_rejected()
{
    this->close();
}
