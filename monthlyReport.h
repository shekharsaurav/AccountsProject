#ifndef MONTHLYREPORT_H
#define MONTHLYREPORT_H

#include <QWidget>

#include "ui_adminWindow.h"

namespace Ui {
class MonthlyReport;
}

class MonthlyReport : public QWidget
{
    Q_OBJECT

public:
    explicit MonthlyReport(Ui::adminWindow *parentUi, QWidget *parent = 0);

    ~MonthlyReport();

private:

    int month;

    int year;

    double duesRegFee;
    double duesTutFee;
    double duesGenrFee;
    double duesExamFee;
    double duesReAddmFee;
    double duesDevlpFee;
    double duesCompFee;
    double duesLateFee;
    double duesMisc;
    double depRegFee;
    double depTutFee;
    double depGenrFee;
    double depExamFee;
    double depReAddmFee;
    double depDevlpFee;
    double depCompFee;
    double depLateFee;
    double depMisc;
    double depPrevDues;

    double totalDues;

    double totalDeposite;

    Ui::adminWindow *pUi;

    Ui::MonthlyReport *ui;
};

#endif // MONTHLYREPORT_H
