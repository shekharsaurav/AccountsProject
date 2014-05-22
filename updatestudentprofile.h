#ifndef UPDATESTUDENTPROFILE_H
#define UPDATESTUDENTPROFILE_H

#include <QWidget>

#include "ui_adminWindow.h"

namespace Ui {
class UpdateStudentProfile;
}

class UpdateStudentProfile : public QWidget
{
    Q_OBJECT

public:
    explicit UpdateStudentProfile(Ui::adminWindow *parentUi, QWidget *parent =0);
    ~UpdateStudentProfile();
    void showProfile(long reqStudent, int index);

private slots:
    void on_cbUpload_clicked();

    void on_pbReset_clicked();

    void on_pbUpdate_clicked();

private:
    Ui::UpdateStudentProfile *ui;

    QPixmap pm;

    QString fileName;

    QString copyImage(QString file);

    Ui::adminWindow *pUi;
};


#endif // UPDATESTUDENTPROFILE_H
