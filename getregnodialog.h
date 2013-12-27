#ifndef GETREGNODIALOG_H
#define GETREGNODIALOG_H

#include <QDialog>

#include "ui_adminWindow.h"

namespace Ui {
class GetRegNoDialog;
}

class GetRegNoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GetRegNoDialog(QWidget *parent = 0);

    ~GetRegNoDialog();

    Ui::adminWindow *adwn;

    int index;

    int taskId;

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::GetRegNoDialog *ui;
};

#endif // GETREGNODIALOG_H
