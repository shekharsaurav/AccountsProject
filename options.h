#ifndef OPTIONS_H
#define OPTIONS_H

#include <QDialog>

#include "ui_options.h"

class Options :public QDialog, public Ui::MainDialog
{
    Q_OBJECT

public:
    Options(QWidget *parent =0);
    ~Options();

private slots:

};

#endif // OPTIONS_H
