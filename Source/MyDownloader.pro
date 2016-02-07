#-------------------------------------------------
#
# Project created by QtCreator 2015-12-11T10:42:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyDownloader
TEMPLATE = app


SOURCES += main.cpp\
        mydownloader.cpp \
    aboutdialog.cpp \
    choosedir.cpp \
    depthdialog.cpp

HEADERS  += mydownloader.h \
    aboutdialog.h \
    choosedir.h \
    depthdialog.h

FORMS    += mydownloader.ui \
    aboutdialog.ui \
    choosedir.ui \
    depthdialog.ui
