#ifndef STUDENTSPROFILE_H
#define STUDENTSPROFILE_H

#include <QWidget>

namespace Ui {
class StudentsProfile;
}

class StudentsProfile : public QWidget
{
    Q_OBJECT

public:
    explicit StudentsProfile(QWidget *parent = 0);
    ~StudentsProfile();

private:
    Ui::StudentsProfile *ui;
};

#endif // STUDENTSPROFILE_H
