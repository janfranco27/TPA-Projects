#-------------------------------------------------
#
# Project created by QtCreator 2014-08-18T16:18:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Observer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    graph.cpp \
    subject.cpp \
    graphline.cpp \
    graphpoints.cpp

HEADERS  += mainwindow.h \
    graph.h \
    subject.h \
    graphline.h \
    graphpoints.h

FORMS    += mainwindow.ui
