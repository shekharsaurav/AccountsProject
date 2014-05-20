#include "feeStructure.h"

FeeStructure::FeeStructure()
{
    std = "";
    regFee = 0.0;
    tutFee = 0.0;
    genrFee = 0.0;
    examFee = 0.0;
    reAddmFee = 0.0;
    devlpFee = 0.0;
    compFee = 0.0;
    lateFee = 0.0;
}


FeeStructure::FeeStructure(double rf = 0.0, double tf = 0.0, double gf = 0.0, double ef = 0.0, double raf = 0.0,
                           double df = 0.0, double cf = 0.0, double lf = 0.0)
{
    regFee = rf;
    tutFee = tf;
    genrFee = gf;
    examFee = ef;
    reAddmFee = raf;
    devlpFee = df;
    compFee = cf;
    lateFee = lf;
}

void FeeStructure::getFeeStructure(double rf = 0.0, double tf = 0.0, double gf = 0.0, double ef = 0.0,
                                   double raf = 0.0, double df = 0.0, double cf = 0.0, double lf = 0.0)
{
    rf = regFee;
    tf = tutFee;
    gf = genrFee;
    ef = examFee;
    raf = reAddmFee;
    df = devlpFee;
    cf = compFee;
    lf = lateFee;
}

void FeeStructure::setFeeStructure(double rf = 0.0, double tf = 0.0, double gf = 0.0, double ef = 0.0,
                                   double raf = 0.0, double df = 0.0, double cf = 0.0, double lf = 0.0)
{
    regFee = rf;
    tutFee = tf;
    genrFee = gf;
    examFee = ef;
    reAddmFee = raf;
    devlpFee = df;
    compFee = cf;
    lateFee = lf;
}
