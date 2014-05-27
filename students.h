#ifndef STUDENTS_H
#define STUDENTS_H

#include "standard.h"
#include "address.h"
#include "feeStructure.h"
#include "admissionPage.h"
#include "studentsprofile.h"
#include "updatestudentprofile.h"
#include "feeReceipt.h"

#include <QString>
#include <QDate>

class Students : public Standard
{
    long regNo;
    QDate regDate;
    QString name;
    QDate dob;
    bool gender;
    QString nationality;
    QString religion;
    QString bloodGrp;
    QString mother;
    QString occpMother;
    QString father;
    QString occpFather;
    Address add;
    QString email;
    qlonglong contact1;
    qlonglong contact2;
    int roll;
    QString image;
    QString std;

public:
//    Students(long rno, QDate rdate, QString nam, QDate dob, bool gen, QString nat, QString rel, QString blood,
//             QString mother, QString father, Address add, QString email, long contact1, long contact2, int roll, QString image);


    void setStudent(long rno, QDate rdate, QString nam, QDate dob, bool gen, QString nat, QString rel, QString blood,
                    QString mother, QString ocMot, QString father, QString ocFat, Address add, QString email, long contact1, long contact2, int roll, QString image);

    void getStudent(long rno, QDate rdate, QString nam, QDate dob, bool gen, QString nat, QString rel, QString blood,
                    QString mother, QString ocMot, QString father, QString ocFat, Address add, QString email, long contact1, long contact2, int roll, QString image);

    friend class AdmissionPage;

    friend class StudentsProfile;

    friend class UpdateStudentProfile;

    friend class FeeReceipt;
};

#endif // STUDENTS_H
