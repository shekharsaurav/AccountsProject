#include "getFeeStructureDialog.h"
#include "ui_getFeeStructureDialog.h"
#include "feeStructure.h"
#include "feeStructurePage.h"

GetFeeStructureDialog::GetFeeStructureDialog(QWidget *parent) : QDialog(parent), ui(new Ui::GetFeeStructureDialog)
{
    ui->setupUi(this);
}

GetFeeStructureDialog::~GetFeeStructureDialog()
{
    delete ui;
}



void GetFeeStructureDialog::on_buttonBox_accepted()
{
    FeeStructurePage *feeStruc = new FeeStructurePage();
    feeStruc->
}
