#ifndef BASECLASS_H
#define BASECLASS_H

class Address
{
    QString baseAdd;
    QString town;
    long pin;
    QString state;

public :
    Address(QString base = NULL, QString t = NULL, long p = 0, QString st = NULL)
    {
        baseAdd = base;
        town = t;
        pin = p;
        state = st;
    }

    QString getBaseAdd()
    {
        return baseAdd;
    }

    void setBaseAdd(QString base)
    {
        baseAdd = base;
    }

    QQString getTown()
    {
        return town;
    }

    void setTown(QString t)
    {
        town = t;
    }

    long getPin()
    {
        return pin;
    }

    void setPin(long p)
    {
        pin = p;
    }

    QString getState()
    {
        return state;
    }

    void setState(QString st)
    {
        state = st;
    }
};

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
    FeeStructure(double rf = 0.0, double tf = 0.0, double gf = 0.0, double ef = 0.0, double raf = 0.0, double df = 0.0, double cf = 0.0, double lf = 0.0)
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

    void getFeeStructure(double rf = 0.0, double tf = 0.0, double gf = 0.0, double ef = 0.0, double raf = 0.0, double df = 0.0, double cf = 0.0, double lf = 0.0)
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

    void setFeeStructure(double rf = 0.0, double tf = 0.0, double gf = 0.0, double ef = 0.0, double raf = 0.0, double df = 0.0, double cf = 0.0, double lf = 0.0)
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
};

class Standard
{
    QString std;
    int strength;
    QString classTeacher;
    QString subjects[10];
    FeeStructure struc;

public :
    Standard(QString std = NULL, int str = 0, QString cTeacher = NULL, QString sub[] = {NULL}, FeeStructure struc)
    {
        this->std = std;
        strength = str;
        classTeacher = cTeacher;
        subjects = sub;
        this->struc = struc;
    }

    void getStandard(QString std = NULL, int str = 0, QString cTeacher = NULL, QString sub[] = {NULL}, FeeStructure struc)
    {
        std = this->std;
        str = strength;
        cTeacher = classTeacher;
        sub = subjects;
        struc = this->struc;
    }

    void SetStandard(QString std = NULL, int str = 0, QString cTeacher = NULL, QString sub[] = {NULL}, FeeStructure struc)
    {
        this->std = std;
        strength = str;
        classTeacher = cTeacher;
        subjects = sub;
        this->struc = struc;
    }
};

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
    Reciept(double rno, QDate d, int r, double rf, double tf, double dues, double gf, double ef, double raf, double lf, double df, double cf, double oth)
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

    void generateReciept(double rno, QDate d, int r, double rf, double tf, double dues, double gf, double ef, double raf, double lf, double df, double cf, double oth)
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

    void getReciept(double rno, QDate d, int r, double rf, double tf, double dues, double gf, double ef, double raf, double lf, double df, double cf, double oth)
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
};

class Students : Standard
{
    long regNo;
    QDate regDate;
    QString name;
    QDate dob;
    QString bloodGrp;
    QString mother;
    QString father;
    Address add;
    QString email;
    long contact;
    int roll;
    QString image;

public :
    Students(long rno, QDate rdate, QString nam, QDate dob, QString blood, QString mother, QString father, Address add, QString email, long contact, int roll, QString image)
    {
        regNo = rno;
        regDate = rdate;
        name = nam;
        this->dob = dob;
        bloodGrp = blood;
        this->mother = mother;
        this->father = father;
        this->add = add;
        this->email = email;
        this->contact = contact;
        this->roll = roll;
        this->image = image;
    }

    void setStudent(long rno, QDate rdate, QString nam, QDate dob, QString blood, QString mother, QString father, Address add, QString email, long contact, int roll, QString image)
    {
        regNo = rno;
        regDate = rdate;
        name = nam;
        this->dob = dob;
        bloodGrp = blood;
        this->mother = mother;
        this->father = father;
        this->add = add;
        this->email = email;
        this->contact = contact;
        this->roll = roll;
        this->image = image;
    }

    void getStudent(long rno, QDate rdate, QString nam, QDate dob, QString blood, QString mother, QString father, Address add, QString email, long contact, int roll, QString image)
    {
        rno = regNoo;
        rdate = regDate;
        nam = name ;
        dob = this->dob;
        blood = bloodGrp;
        mother = this->mother;
        father = this->father ;
        add = this->add;
        email = this->email ;
        contact = this->contact;
        roll = this->roll ;
        image = this->image ;
    }
};

#endif // BASECLASS_H
