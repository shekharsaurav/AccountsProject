#ifndef FEERECEIPT_H
#define FEERECEIPT_H

#include <QtWidgets>
#include <QSqlDatabase>
#include <QTableWidget>
#include <QSqlQuery>
#include <QSqlError>

#include "ui_feeReceipt.h"
#include "feeStructure.h"
#include "ui_adminWindow.h"
#include "students.h"

class FeeReceipt : public QWidget
{
    Q_OBJECT

public:
    explicit FeeReceipt(Ui::adminWindow *parentUi, QWidget *parent = 0);

    ~FeeReceipt();

    void generateReceipt(long regdNo, int index);

private slots:

    void on_pbClose_clicked();

    void on_pbReset_clicked();

    void on_pbDeposite_clicked();

    void on_cbExamFee_stateChanged(int arg1);

    void on_cbReAddmFee_stateChanged(int arg1);

    void on_cbMonth_currentIndexChanged(int index);

    void updateFeeDues();

    void updateStudentsFeeDeposite();

    void on_twFeeReceipt_cellActivated(int row, int column);

private:
    Ui::FeeReceipt *ui;

    Ui::adminWindow *pUi;

    QSqlQuery query;

    QString stmt;

    QString str;

    FeeStructure feeStruc;

//    Students stud;
    long regNo;

    QString name;

    int month;

    QTableWidgetItem *duesItem[11];

    QTableWidgetItem *currentItem[11];

    QTableWidgetItem *depositeItem[11];

    QTableWidgetItem *clearedItem[11];

    double totalDues = 0;

    double totalCurrent = 0;

    double totalDeposite = 0;

    double clearedDouble = 0;

    int diff;

    long receiptNo;
};

#endif // FEERECEIPT_H









