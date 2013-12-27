#-------------------------------------------------
#
# Project created by QtCreator 2013-10-20T12:58:25
#
#-------------------------------------------------

QT       += core gui

QT += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Accounts_Project
TEMPLATE = app


SOURCES += main.cpp \
    homescreen.cpp \
    adminWindow.cpp \
    admissionPage.cpp \
    dbConnection.cpp \
    students.cpp \
    standard.cpp \
    reciept.cpp \
    feeStructure.cpp \
    address.cpp \
    studentsprofile.cpp \
    getregnodialog.cpp

HEADERS  += homescreen.h \
    admin.h \
    adminWindow.h \
    admissionPage.h \
    dbConnection.h \
    students.h \
    standard.h \
    reciept.h \
    feeStructure.h \
    address.h \
    studentsprofile.h \
    getregnodialog.h

FORMS    += homescreen.ui \
    adminWindow.ui \
    admissionPage.ui \
    studentsprofile.ui \
    getregnodialog.ui
