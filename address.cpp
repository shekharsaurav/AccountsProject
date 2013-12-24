#include "address.h"

#include <QString>

Address::Address()
{
    baseAdd = "";
    town = "";
    pin = 0;
    state = "";
}

Address::Address(QString base, QString t, long p, QString st)
{
    baseAdd = base;
    town = t;
    pin = p;
    state = st;
}

void Address::setBaseAdd(QString base)
{
    baseAdd = base;
}

QString Address::getBaseAdd()
{
    return baseAdd;
}

void Address::setPin(long p)
{
    pin = p;
}

long Address::getPin()
{
    return pin;
}

void Address::setState(QString st)
{
    state = st;
}

QString Address::getState()
{
    return state;
}

void Address::setTown(QString t)
{
    town = t;
}

QString Address::getTown()
{
    return town;
}

