#ifndef ADMISSIONPAGE_H
#define ADMISSIONPAGE_H

#include <QtWidgets>
#include <QSqlDatabase>
#include "ui_admissionPage.h"
#include "students.h"
#include "ui_adminWindow.h"


class AdmissionPage : public QWidget
{
    Q_OBJECT

public:
    explicit AdmissionPage(Ui::adminWindow *parentUi, QWidget *parent = 0);
    ~AdmissionPage();
   // friend class Students;

private slots:

    void on_cbUpload_clicked();

    void on_pbSubmit_clicked();

    void on_pbReset_clicked();
    
private:
    Ui::admissionPage *ui;

    QString fileName;

    QPixmap pm;

    QString copyImage(QString);

    Ui::adminWindow *pUi;
 };

#endif // ADMISSIONPAGE_H
