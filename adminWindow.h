#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QMainWindow>
#include <QScrollArea>

#include "ui_adminWindow.h"
#include "admissionPage.h"
#include "getregnodialog.h"

class AdminWindow : public QMainWindow
{
    Q_OBJECT

public :
    explicit AdminWindow(QWidget *parent = 0);
    ~AdminWindow();
    int getTabIndex();

private slots:

    void on_twStudents_clicked(const QModelIndex &index);

    void on_twFaculty_clicked(const QModelIndex &index);

    void on_twAccounts_clicked(const QModelIndex &index);

    void on_pbStudents_clicked();

    void on_tabWidget_tabCloseRequested(int index);

private:
    Ui::adminWindow *ui;

    AdmissionPage *page = new AdmissionPage(this->ui);

    GetRegNoDialog *grnd = new GetRegNoDialog();

    int tabIndex;

    QScrollArea scrollArea;

};

#endif // ADMINWINDOW_H
