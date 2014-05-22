#ifndef FEESTRUCTUREPAGE_H
#define FEESTRUCTUREPAGE_H

#include <QtWidgets>
#include <QSqlDatabase>
#include <QTableWidget>

#include "ui_feeStructurePage.h"
#include "feeStructure.h"
#include "ui_adminWindow.h"

class FeeStructurePage : public QWidget
{
    Q_OBJECT

public:
    explicit FeeStructurePage(Ui::adminWindow *parentUi, QWidget *parent =0);

    ~FeeStructurePage();

    void showFeeStructure(QString std, int index);

private slots:

    void on_twFeeStruct_itemChanged(QTableWidgetItem *item);

    void on_pbClose_clicked();

    void on_pbReset_clicked();

    void on_pbUpdate_clicked();


private:
    Ui::feeStructurePage *ui;

    Ui::adminWindow *pUi;

    QTableWidgetItem *item[10];

};

#endif // FEESTRUCTUREPAGE_H
