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

private:
    Ui::FeeReceipt *ui;

    Ui::adminWindow *pUi;

//    Students stud;

    QSqlQuery query;

    QString stmt;

    QTableWidgetItem *duesItem[11];

    QTableWidgetItem *currentItem[11];

    QTableWidgetItem *depositeItem[11];

    QTableWidgetItem *clearedItem[11];
};

#endif // FEERECEIPT_H
