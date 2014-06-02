#include "monthlyReport.h"
#include "ui_monthlyReport.h"

MonthlyReport::MonthlyReport(Ui::adminWindow *parentUi, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MonthlyReport)
{
    ui->setupUi(this);
    pUi = parentUi;
}

MonthlyReport::~MonthlyReport()
{
    delete ui;
}
