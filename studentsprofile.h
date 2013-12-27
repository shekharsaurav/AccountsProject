#ifndef STUDENTSPROFILE_H
#define STUDENTSPROFILE_H

#include <QWidget>

#include "students.h"
#include "ui_adminWindow.h"

namespace Ui {
class StudentsProfile;
}

class StudentsProfile : public QWidget
{
    Q_OBJECT

public:
    explicit StudentsProfile(QWidget *parent = 0);

    ~StudentsProfile();

    void showProfile(long reqStudent, int index, Ui::adminWindow *adUi);

private slots:
    void on_pbClose_clicked();

    void on_pbUpdate_clicked();

private:
    Ui::StudentsProfile *ui;

    Ui::adminWindow *pUi;

    int tabId;
};

#endif // STUDENTSPROFILE_H

