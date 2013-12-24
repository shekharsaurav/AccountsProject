#include "standard.h"

Standard::Standard()
{
    std = "";
    strength = 0;
    classTeacher = "";
    nos = 0;
}

Standard::Standard(QString std, int str, QString cTeacher, QString sub[], int nos,
                   FeeStructure struc)
{
    this->std = std;
    strength = str;
    classTeacher = cTeacher;
    this->nos = nos;
    while(nos-->0)
        subjects[nos-1] = sub[nos-1];
    this->struc = struc;
}

void Standard::getStandard(QString std, int str, QString cTeacher, QString sub[], int nos,
                           FeeStructure struc)
{
    std = this->std;
    str = strength;
    cTeacher = classTeacher;
    int n = this->nos;
    while(n-->0)
        sub[n-1] = subjects[n-1];
    nos = this->nos;
    struc = this->struc;
}

void Standard::setStandard(QString std, int str, QString cTeacher, QString sub[], int nos,
                 FeeStructure struc)
{
    this->std = std;
    strength = str;
    classTeacher = cTeacher;
    this->nos = nos;
    while(nos-->0)
        subjects[nos-1] = sub[nos-1];
    this->struc = struc;
}
