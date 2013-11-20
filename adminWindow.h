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

private:
    Ui::adminWindow *ui;

};

#endif // ADMINWINDOW_H
