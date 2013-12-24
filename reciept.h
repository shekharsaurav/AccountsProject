#ifndef RECIEPT_H
#define RECIEPT_H

#include <QDate>

class Reciept
{
    int recieptNo;
    QDate date;
    int roll;
    double regFee;
    double tutFee;
    double dues;
    double genrFee;
    double examFee;
    double reAddmFee;
    double lateFee;
    double devlpFee;
    double compFee;
    double othReciept;

public :
    Reciept(double rno, QDate d, int r, double rf, double tf, double dues, double gf, double ef, double raf,
            double lf, double df, double cf, double oth);

    void generateReciept(double rno, QDate d, int r, double rf, double tf, double dues, double gf, double ef,
                         double raf, double lf, double df, double cf, double oth);

    void getReciept(double rno, QDate d, int r, double rf, double tf, double dues, double gf, double ef,
                    double raf, double lf, double df, double cf, double oth);
};


#endif // RECIEPT_H
