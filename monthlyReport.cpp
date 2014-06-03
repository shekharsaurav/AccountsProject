#include <algorithm>
#include <iostream>
#include <cstring>
#include <fstream>

#include "monthlyReport.h"
#include "ui_monthlyReport.h"


using namespace std;

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

bool MonthlyReport::reportExist(int month, int year)
{
    stmt.sprintf("select * from monthlyReport where month = %d and year = %d;", month, year);
    query.exec(stmt);
    if(query.next())
        return true;
    else
        return false;
}

bool MonthlyReport::createReport()
{
    month = QDate::currentDate().month();
    year = QDate::currentDate().year();
    int count;
    bool exist = reportExist(month, year);
    if(exist)
    {
        pUi->statusBar->showMessage("Report already exists for the month!!", 5000);
        return true;
    }
    else
    {
        for(int i = 0; i < 6; i++)
        {

            stmt.sprintf("SELECT * FROM feestructure WHERE class = \"%s\";", std[i].toStdString().c_str());
            query.exec(stmt);
            cout<<"Before upHere";
            if(query.next())
            {
                cout<<"UP Here";
                struc.tutFee = query.value(2).toDouble();
                struc.genrFee = query.value(3).toDouble();
                struc.examFee = query.value(4).toDouble();
                struc.devlpFee = query.value(6).toDouble();
                struc.compFee = query.value(7).toDouble();
                stmt.sprintf("SELECT COUNT(regNo) FROM students WHERE class = \"%s\";", std[i].toStdString().c_str());
                query.exec(stmt);
                if(query.next())
                {
                    cout<<"UP one level";
                    count = query.value(0).toInt();
                    if( count != 0 )
                    {
                        duesTutFee += count * struc.tutFee;
                        if (month == 4 || month == 5 || month == 7 || month == 8 || month == 9 || month == 10)
                        {
                            duesGenrFee += count * struc.genrFee;
                        }
                        if (month == 2 || month == 7 || month == 11)
                        {
                            duesExamFee += count * struc.examFee;
                        }
                        duesDevlpFee += count * struc.devlpFee;
                        duesCompFee += count * struc.compFee;
                    }
                }
                else
                {
                    QMessageBox::critical(this, tr("Count Error"), query.lastError().text(), QMessageBox::Ok);
//                    return false;
                }
            }
            else
            {
                QMessageBox::warning(this, tr("SQL Error"), query.lastError().text(), QMessageBox::Ok, QMessageBox::Cancel);
                pUi->statusBar->showMessage(query.lastError().text(),10000);
//                return false;
            }
        }
        stmt.sprintf("INSERT INTO monthlyReport (month, year, tutFeeDues, genrFeeDues, examFeeDues, devlpFeeDues, compFeeDues) VALUES (%d, %d, %f, %f %f, %f, %f);", month, year, duesTutFee, duesGenrFee, duesExamFee, duesDevlpFee, duesCompFee);
        query.exec(stmt);
        if(query.numRowsAffected() != 1)
        {
            QMessageBox::critical(this, tr("Creation Error!"), query.lastError().text(), QMessageBox::Ok);
            return false;
        }
        else
            return true;
    }
}

bool MonthlyReport::updateReport(int month, int year, bool status, double depTut, double depGenr,
                                 double depExam, double dueRAddm, double depRAddm, double depDevlp, double depComp,
                                 double dueMis, double depMis, double depPrev, double depReg , double dueReg,
                                 double dueTut, double dueGenr, double dueExam, double dueDevlp,
                                 double dueComp)
{
    bool success;
    if(!reportExist(month, year))
    {
        success = createReport();
        if(!success)
        {
            return false;
        }
        else
        {
            pUi->statusBar->showMessage("Report Created Successfully", 5000);
        }
    }
    stmt.sprintf("SELECT * FROM monthlyReport WHERE month = %d and year = %d;", month, year);
    if(query.exec(stmt))
    {
        duesRegFee = query.value(2).toDouble();
        depRegFee = query.value(3).toDouble();
        duesTutFee = query.value(4).toDouble();
        depTutFee = query.value(5).toDouble();
        duesGenrFee = query.value(6).toDouble();
        depGenrFee = query.value(7).toDouble();
        duesExamFee = query.value(8).toDouble();
        depExamFee = query.value(9).toDouble();
        duesReAddmFee = query.value(10).toDouble();
        depReAddmFee = query.value(11).toDouble();
        duesDevlpFee = query.value(12).toDouble();
        depDevlpFee = query.value(13).toDouble();
        duesCompFee = query.value(14).toDouble();
        depCompFee = query.value(15).toDouble();
        duesMisc = query.value(16).toDouble();
        depMisc = query.value(17).toDouble();
        duesPrev = query.value(18).toDouble();
        depPrevDues = query.value(19).toDouble();
        totalDues = query.value(20).toDouble();
        totalDeposite = query.value(21).toDouble();
        if(!status)
        {
            duesTutFee -= depTut;
            duesGenrFee -= depGenr;
            duesDevlpFee -= depDevlp;
            duesCompFee -= depComp;
            depTutFee += depTut;
            depGenrFee += depGenr;
            depDevlpFee += depDevlp;
            depCompFee += depComp;
            if(dueRAddm != 0)
            {
                duesReAddmFee += (dueRAddm - depRAddm);
                depReAddmFee += depRAddm;
            }
            duesPrev -= depPrev;
            depPrevDues += depPrev;
            duesMisc += (dueMis - depMis);
            depMisc += depMis;
            totalDues = totalDues - depTut - depGenr - depDevlp - depComp + duesReAddmFee - depPrev + duesMisc;
            totalDeposite = totalDeposite + depTut + depGenr + depDevlp + depComp + depRAddm + depPrev + depMis;
        }
        else
        {
            duesRegFee += (dueReg - depReg);
            duesTutFee += (dueTut - depTut);
            duesGenrFee += (dueGenr - depGenr);
            duesExamFee += (dueExam - depExam);
            duesReAddmFee += (dueRAddm - depRAddm);
            duesDevlpFee += (dueDevlp - depDevlp);
            duesCompFee += (dueComp - depComp);
            duesMisc += (dueMis - depMis);
            duesPrev -= depPrev;
            depRegFee += depReg;
            depTutFee += depTut;
            depGenrFee += depGenr;
            depExamFee += depExam;
            depReAddmFee += depRAddm;
            depDevlpFee += depDevlp;
            depCompFee += depComp;
            depMisc += depMis;
            depPrevDues += depPrev;
            totalDues = totalDues + duesRegFee + duesTutFee + duesGenrFee + duesExamFee + duesReAddmFee + duesDevlpFee + duesCompFee + duesMisc - depPrev;
            totalDeposite = totalDeposite + depRegFee + depTutFee + depGenrFee + depExamFee + depReAddmFee + depDevlpFee + depCompFee + depMisc + depPrevDues;
        }
    }
    stmt.sprintf("UPDATE monthlyReport SET regFeeDues=%f, regFeeDep=%f, tutFeeDues=%f, tutFeeDep=%f, genrFeeDues=%f, genrFeeDep=%f, examFeeDues=%f, examFeeDep=%f, reAddmFeeDues=%f, reAddmFeeDep=%f, devlpFeeDues=%f, devlpFeeDep=%f, compFeeDues=%f, compFeeDep=%f, miscDues=%f, miscDep=%f, prevDues=%f, prevDuesDep=%f, totalDues=%f, totalDep=%f WHERE month=%d AND year=%d;",
                 duesRegFee, depRegFee, duesTutFee, depTutFee, duesGenrFee, depGenrFee, duesExamFee, depExamFee,
                 duesReAddmFee, depReAddmFee, duesDevlpFee, depDevlpFee, duesCompFee, depCompFee, duesMisc, depMisc,
                 duesPrev, depPrevDues, totalDues, totalDeposite, month, year);
    if(query.exec(stmt))
    {
        QMessageBox::critical(this, tr("Report Updated!"), tr("Report Successfully submitted!!"), QMessageBox::Ok);
        return true;
    }
    else
    {
        QMessageBox::critical(this, tr("Report Update Error!"), query.lastError().text(), QMessageBox::Ok);
        return false;
    }
}
