#ifndef FEESTRUCTURE_H
#define FEESTRUCTURE_H

class FeeStructure
{
    double regFee;
    double tutFee;
    double genrFee;
    double examFee;
    double reAddmFee;
    double devlpFee;
    double compFee;
    double lateFee;

public :
    FeeStructure();

    FeeStructure(double rf, double tf, double gf, double ef, double raf, double df, double cf, double lf);

    void getFeeStructure(double rf, double tf, double gf, double ef, double raf, double df, double cf, double lf);

    void setFeeStructure(double rf, double tf, double gf, double ef, double raf, double df, double cf, double lf);
};


#endif // FEESTRUCTURE_H
