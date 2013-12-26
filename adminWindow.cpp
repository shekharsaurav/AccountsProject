#include <QtGui>

#include "adminWindow.h"
#include "ui_adminWindow.h"
#include "admissionPage.h"
#include "studentsprofile.h"

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

    cout<<"index selected : "<< i;
    switch(i)
    {
        case 0 : AdmissionPage *page = new AdmissionPage();
                 tabIndex++;
                 ui->tabWidget->insertTab(tabIndex ,page, word);
                 ui->tabWidget->;
                 ui->statusBar->showMessage(" New Admission Form" , 5000);
                 break;

        case 3 : StudentsProfile *profile = new StudentsProfile();
                 tabIndex++;
                 ui->tabWidget->insertTab(tabIndex, profile, word);
                 ui->statusBar->showMessage(" Student's profile displayed.");
                 break;
    }
}

void AdminWindow::on_tabWidget_tabCloseRequested(int index)
{
    if(index!=0)
        ui->tabWidget->removeTab(index);
}
