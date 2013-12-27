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

private:
    Ui::StudentsProfile *ui;

};

#endif // STUDENTSPROFILE_H
