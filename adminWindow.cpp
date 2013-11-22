#include <QtGui>

#include "adminWindow.h"
#include "ui_adminWindow.h"

AdminWindow::AdminWindow(QWidget *parent):QMainWindow(parent), ui(new Ui::adminWindow)
{
    ui->setupUi(this);
}

AdminWindow::~AdminWindow()
{
    delete ui;
}


void AdminWindow::on_twStudents_clicked(const QModelIndex &index)
{
    ui->pbStudents->setEnabled(true);
}

void AdminWindow::on_twFaculty_clicked(const QModelIndex &index)
{
    ui->pbFaculty->setEnabled(true);
}

void AdminWindow::on_twAccounts_clicked(const QModelIndex &index)
{
    ui->pbAccounts->setEnabled(true);
}

void AdminWindow::on_pbStudents_clicked()
{
    int i;
    QWidget *page = new QWidget();
    i = ui->tabWidget->insertTab(2 ,page, "New Tab");
//    int index = ui->twStudents->currentIndex().row();
//    switch(index)
//    {
//    case 0:
//    }
}

void AdminWindow::on_tabWidget_tabCloseRequested(int index)
{
    if(index!=0)
        ui->tabWidget->removeTab(index);
}
