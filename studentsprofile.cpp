#include "studentsprofile.h"
#include "ui_studentsprofile.h"

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
