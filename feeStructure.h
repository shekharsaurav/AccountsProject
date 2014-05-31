#ifndef FEESTRUCTURE_H
#define FEESTRUCTURE_H

#include <QString>

#include "feeStructurePage.h"

class FeeStructure
{
    QString std;
    double regFee;
    double tutFee;
    double genrFee;
    double examFee;
    double reAddmFee;
    double devlpFee;
    double compFee;
    double lateFee;
    double duesRegFee;
    double duesTutFee;
    double duesGenrFee;
    double duesExamFee;
    double duesReAddmFee;
    double duesDevlpFee;
    double duesCompFee;
    double duesLateFee;
    double duesMisc;
    double depRegFee;
    double depTutFee;
    double depGenrFee;
    double depExamFee;
    double depReAddmFee;
    double depDevlpFee;
    double depCompFee;
    double depLateFee;
    double depMisc;
    double depPrevDues;

public :
    FeeStructure();

    FeeStructure(double rf, double tf, double gf, double ef, double raf, double df, double cf, double lf);

    void getFeeStructure(double rf, double tf, double gf, double ef, double raf, double df, double cf, double lf);

    void setFeeStructure(double rf, double tf, double gf, double ef, double raf, double df, double cf, double lf);

    friend class FeeStructurePage;

    friend class FeeReceipt;

};


#endif // FEESTRUCTURE_H
