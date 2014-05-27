#include <QtGui>

#include "adminWindow.h"
#include "ui_adminWindow.h"

#include <iostream>

using namespace std;

AdminWindow::AdminWindow(QWidget *parent):QMainWindow(parent), ui(new Ui::adminWindow)
{
    ui->setupUi(this);
    scrollArea.setWidget(this);
    scrollArea.viewport()->setBackgroundRole(QPalette::Dark);
    scrollArea.viewport()->setAutoFillBackground(true);
    scrollArea.setWindowTitle(QObject::tr("Krishna Kids' Educational Point"));
    scrollArea.setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea.show();
    tabIndex = 1;
    connect(ui->twStudents, SLOT(entered(const QModelIndex &index)), ui->pbStudents, SIGNAL(clicked()));
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
    QModelIndex index = ui->twStudents->currentIndex();
    int i = index.row();
    QTreeWidgetItem *item = ui->twStudents->currentItem();
    QString word = item->text(0);

//    cout<<"index selected : "<< i;
    switch(i)
    {
        case 0 : tabIndex++;
                 ui->tabWidget->insertTab(tabIndex ,page, word);
                 ui->tabWidget->setCurrentIndex(tabIndex);
                 ui->statusBar->showMessage(" New Admission Form" , 5000);
                 break;

        case 1 : grnd->show();
                 grnd->adwn = ui;
                 tabIndex++;
                 grnd->index = tabIndex;
                 grnd->taskId = 1;
                 break;

//        case 2 : break;

        case 3 : grnd->show();
                 grnd->adwn = ui;
                 tabIndex++;
                 grnd->index = tabIndex;
                 grnd->taskId = 3;
                 break;

        case 4 : grnd->show();
                 grnd->adwn = ui;
                 tabIndex++;
                 grnd->index = tabIndex;
                 grnd->taskId = 4;
                 break;
    }
}

void AdminWindow::on_pbAccounts_clicked()
{
    QModelIndex index = ui->twAccounts->currentIndex();
    int i = index.row();
    QTreeWidgetItem *item = ui->twAccounts->currentItem();
    QString word = item->text(0);
    switch(i)
    {
        case 2 : gfsd->show();
                 gfsd->adwn = ui;
                 tabIndex++;
                 gfsd->index = tabIndex;
        /*tabIndex++;
                 ui->tabWidget->insertTab(tabIndex, strucPage, word);
                 ui->tabWidget->setCurrentIndex(tabIndex);
                 ui->statusBar->showMessage(" Fee Structure", 5000);*/
        break;
    }
}

void AdminWindow::on_tabWidget_tabCloseRequested(int index)
{
    if(index!=0)
    {
        ui->tabWidget->removeTab(index);
        tabIndex--;
    }
}


int AdminWindow::getTabIndex()
{
    return ++tabIndex;
}
