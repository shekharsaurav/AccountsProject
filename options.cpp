#include <QtGui>
#include "options.h"


Options::Options(QWidget *parent) : QDialog(parent)
{
    setupUi(this);
}

Options::~Options()
{
    delete this;
}
