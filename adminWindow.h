#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QMainWindow>

#include "ui_adminWindow.h"

class AdminWindow : public QMainWindow
{
    Q_OBJECT

public :
    explicit AdminWindow(QWidget *parent = 0);
    ~AdminWindow();

private slots:

    void on_twStudents_clicked(const QModelIndex &index);

    void on_twFaculty_clicked(const QModelIndex &index);

    void on_twAccounts_clicked(const QModelIndex &index);

    void on_pbStudents_clicked();

    void on_tabWidget_tabCloseRequested(int index);

private:
    Ui::adminWindow *ui;
    int tabIndex;

};

#endif // ADMINWINDOW_H
