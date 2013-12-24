#include "students.h"
#include "address.h"

#include <QDate>
#include <QString>

Students::Students(long rno, QDate rdate, QString nam, QDate dob, QString blood, QString mother,
                   QString father, Address add, QString email, long contact, int roll, QString image)
{
    regNo = rno;
    regDate = rdate;
    name = nam;
    this->dob = dob;
    bloodGrp = blood;
    this->mother = mother;
    this->father = father;
    this->add.setBaseAdd(add.getBaseAdd());
    this->add.setTown(add.getTown());
    this->add.setPin(add.getPin());
    this->add.setState(add.getState());
    this->email = email;
    this->contact = contact;
    this->roll = roll;
    this->image = image;
}

void Students::setStudent(long rno, QDate rdate, QString nam, QDate dob, QString blood, QString mother,
                          QString father, Address add, QString email, long contact, int roll, QString image)
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

void Students::getStudent(long rno, QDate rdate, QString nam, QDate dob, QString blood, QString mother,
                          QString father, Address add, QString email, long contact, int roll, QString image)
{
    rno = regNo;
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
