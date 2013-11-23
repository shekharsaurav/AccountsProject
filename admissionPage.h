#ifndef ADMISSIONPAGE_H
#define ADMISSIONPAGE_H

#include <QtWidgets>
#include "ui_admissionPage.h"

class AdmissionPage : public QWidget
{
    Q_OBJECT

public:
    explicit  AdmissionPage(QWidget *parent = 0);
    ~AdmissionPage();

private slots:

    void on_cbUpload_clicked();

private:
    Ui::admissionPage *ui;

};

#endif // ADMISSIONPAGE_H
