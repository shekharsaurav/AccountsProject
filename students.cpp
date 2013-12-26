#include "students.h"
#include "address.h"

#include <QDate>
#include <QString>

//Students::Students(long rno, QDate rdate, QString nam, QDate dob, bool gen, QString nat, QString rel, QString blood, QString mother,
//                   QString father, Address add, QString email, long contact1, long contact2, int roll, QString image)
//{
//    regNo = rno;
//    regDate = rdate;
//    name = nam;
//    this->dob = dob;
//    bloodGrp = blood;
//    this->mother = mother;
//    this->father = father;
//    this->add.setBaseAdd(add.getBaseAdd());
//    this->add.setTown(add.getTown());
//    this->add.setPin(add.getPin());
//    this->add.setState(add.getState());
//    this->email = email;
//    this->contact = contact;
//    this->roll = roll;
//    this->image = image;
//}

void Students::setStudent(long rno, QDate rdate, QString nam, QDate dob, bool gen, QString nat, QString rel, QString blood,
                          QString mother, QString ocMot, QString father, QString ocFat, Address add, QString email, long contact1, long contact2, int roll, QString image)
{
    regNo = rno;
    regDate = rdate;
    name = nam;
    this->dob = dob;
    gender = gen;
    nationality = nat;
    religion = rel;
    bloodGrp = blood;
    this->mother = mother;
    occpMother = ocMot;
    this->father = father;
    occpFather = ocFat;
    this->add = add;
    this->email = email;
    this->contact1 = contact1;
    this->contact2 = contact2;
    this->roll = roll;
    this->image = image;
}

void Students::getStudent(long rno, QDate rdate, QString nam, QDate dob, bool gen, QString nat, QString rel, QString blood,
                          QString mother, QString ocMot, QString father, QString ocFat, Address add, QString email, long contact1, long contact2, int roll, QString image)
{
    rno = regNo;
    rdate = regDate;
    nam = name ;
    dob = this->dob;
    gen = gender;
    nat = nationality;
    rel = religion;
    blood = bloodGrp;
    mother = this->mother;
    ocMot = occpMother;
    father = this->father;
    ocFat = occpFather;
    add = this->add;
    email = this->email ;
    contact1 = this->contact1;
    contact2 = this->contact2;
    roll = this->roll ;
    image = this->image ;
}
