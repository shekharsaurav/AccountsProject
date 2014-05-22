#ifndef GETFEESTRUCTUREDIALOG_H
#define GETFEESTRUCTUREDIALOG_H

#include <QDialog>

#include "ui_adminWindow.h"

namespace Ui {
    class GetFeeStructureDialog;
}

class GetFeeStructureDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GetFeeStructureDialog(QWidget *parent = 0);

    ~GetFeeStructureDialog();

    Ui::adminWindow *adwn;

    int index;

    int taskId;

private slots:

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::GetFeeStructureDialog *ui;
};

#endif // GETFEESTRUCTUREDIALOG_H
