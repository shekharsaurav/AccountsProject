#ifndef STUDENTS_H
#define STUDENTS_H

#include "standard.h"
#include "address.h"
#include "feeStructure.h"

#include <QString>
#include <QDate>

class Students : public Standard
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

public:
    Students(long rno, QDate rdate, QString nam, QDate dob, QString blood, QString mother, QString father,
             Address add, QString email, long contact, int roll, QString image);

    void setStudent(long rno, QDate rdate, QString nam, QDate dob, QString blood, QString mother, QString father,
            Address add, QString email, long contact, int roll, QString image);

    void getStudent(long rno, QDate rdate, QString nam, QDate dob, QString blood, QString mother, QString father,
                    Address add, QString email, long contact, int roll, QString image);
};

#endif // STUDENTS_H
