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

