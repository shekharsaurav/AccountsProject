#ifndef ADDRESS_H
#define ADDRESS_H

#include <QString>

class Address
{
    QString baseAdd;
    QString town;
    long pin;
    QString state;

public :
    Address();

    Address(QString base, QString t, long p, QString st);

    QString getBaseAdd();

    void setBaseAdd(QString base);

    QString getTown();

    void setTown(QString t);

    long getPin();

    void setPin(long p);

    QString getState();

    void setState(QString st);

    friend class AdmissionPage;

    friend class StudentsProfile;

    friend class UpdateStudentProfile;
};

#endif // ADDRESS_H
