#ifndef STANDARD_H
#define STANDARD_H

#include <QString>

#include "feeStructure.h"

using namespace std;

class Standard
{
    QString std;
    int strength;
    QString classTeacher;
    int nos;
    QString subjects[10];
    FeeStructure struc;

public :
    Standard();

    Standard(QString std, int str, QString cTeacher, QString sub[], int nos, FeeStructure struc);

    void getStandard(QString std, int str, QString cTeacher, QString sub[], int nos,
                     FeeStructure struc);

    void setStandard(QString std, int str, QString cTeacher, QString sub[], int nos,
                     FeeStructure struc);
};

#endif // STANDARD_H
