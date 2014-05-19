#-------------------------------------------------
#
# Project created by QtCreator 2014-05-04T11:25:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Debugging
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    backup.cpp \
    task.cpp \
    netlink.cpp

HEADERS  += dialog.h \
    backup.h \
    task.h

FORMS    += dialog.ui
