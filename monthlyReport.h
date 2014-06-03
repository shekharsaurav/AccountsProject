#ifndef MONTHLYREPORT_H
#define MONTHLYREPORT_H

#include <QWidget>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QString>
#include <QSqlError>
#include <QMessageBox>

#include "ui_adminWindow.h"3
#include "feeStructure.h"



namespace Ui {
class MonthlyReport;
}

class MonthlyReport : public QWidget
{
    Q_OBJECT

public:
    explicit MonthlyReport(Ui::adminWindow *parentUi, QWidget *parent = 0);

    ~MonthlyReport();

    bool createReport();
    
    bool updateReport(int month, int year, bool status, double depTut, double depGenr, double depExam, double dueRAddm, double depRAddm, double depDevlp, double depComp, double dueMis, double depMis, double depPrev, double depReg = 0, double dueReg = 0, double dueTut = 0, double dueGenr = 0, double dueExam = 0, double dueDevlp = 0, double dueComp = 0);

    bool reportExist(int month, int year);

private:

    int month;

    int year;

    double duesRegFee = 0;
    double duesTutFee = 0;
    double duesGenrFee = 0;
    double duesExamFee = 0;
    double duesReAddmFee = 0;
    double duesDevlpFee = 0;
    double duesCompFee = 0;
    double duesPrev = 0;
    double duesLateFee = 0;
    double duesMisc = 0;
    double depRegFee = 0;
    double depTutFee = 0;
    double depGenrFee = 0;
    double depExamFee = 0;
    double depReAddmFee = 0;
    double depDevlpFee = 0;
    double depCompFee = 0;
    double depPrevDues = 0;
    double depLateFee = 0;
    double depMisc = 0;

    double totalDues = 0;

    double totalDeposite = 0;

    QString stmt;

    QSqlQuery query;

    FeeStructure struc;

    QString std[6] = {"NUR", "LKG", "UKG", "I", "II", "III"};

    Ui::adminWindow *pUi;

    Ui::MonthlyReport *ui;
};

#endif // MONTHLYREPORT_H
