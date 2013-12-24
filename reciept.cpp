#include "reciept.h"


Reciept::Reciept(double rno, QDate d, int r, double rf, double tf, double dues, double gf, double ef,
                 double raf, double lf, double df, double cf, double oth)
{
    recieptNo = rno;
    date = d;
    roll = r;
    regFee = rf;
    tutFee = tf;
    this->dues = dues;
    genrFee = gf;
    examFee = ef;
    reAddmFee = raf;
    lateFee = lf;
    devlpFee = df;
    compFee = cf;
    othReciept = oth;
}

void Reciept::generateReciept(double rno, QDate d, int r, double rf, double tf, double dues, double gf,
                              double ef, double raf, double lf, double df, double cf, double oth)
{
    recieptNo = rno;
    date = d;
    roll = r;
    regFee = rf;
    tutFee = tf;
    this->dues = dues;
    genrFee = gf;
    examFee = ef;
    reAddmFee = raf;
    lateFee = lf;
    devlpFee = df;
    compFee = cf;
    othReciept = oth;
}

void Reciept::getReciept(double rno, QDate d, int r, double rf, double tf, double dues, double gf, double ef,
                         double raf, double lf, double df, double cf, double oth)
{
    rno = recieptNo;
    d = date;
    r = roll;
    rf = regFee;
    tf = tutFee;
    dues = this->dues;
    gf = genrFee;
    ef = examFee;
    raf = reAddmFee;
    lf = lateFee;
    df = devlpFee;
    cf = compFee;
    oth = othReciept;
}
