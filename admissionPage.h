#ifndef ADMISSIONPAGE_H
#define ADMISSIONPAGE_H

#include <QtWidgets>
#include <QSqlDatabase>
#include "ui_admissionPage.h"
#include "students.h"

class AdmissionPage : public QWidget
{
    Q_OBJECT

public:
    explicit  AdmissionPage(QWidget *parent = 0);
    ~AdmissionPage();
    friend class Students;

private slots:

    void on_cbUpload_clicked();

    void on_pbSubmit_clicked();

private:
    Ui::admissionPage *ui;
    QString fileName;
};

#endif // ADMISSIONPAGE_H
