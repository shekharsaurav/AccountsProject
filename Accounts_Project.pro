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
    options.cpp \
    adminWindow.cpp

HEADERS  += homescreen.h \
    baseclass.h \
    admin.h \
    options.h \
    adminWindow.h

FORMS    += homescreen.ui \
    options.ui \
    adminWindow.ui
