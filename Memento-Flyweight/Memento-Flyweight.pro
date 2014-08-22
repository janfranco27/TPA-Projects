#-------------------------------------------------
#
# Project created by QtCreator 2014-08-03T21:15:03
#
#-------------------------------------------------

QT       += core gui
CONFIG += c++11
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Memento-Flyweight
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    figura.cpp \
    circulo.cpp \
    cuadrado.cpp \
    memento.cpp \
    caretaker.cpp \
    circuloflyweight.cpp \
    cuadradoflyweight.cpp \
    canvasview.cpp

HEADERS  += mainwindow.h \
    figura.h \
    circulo.h \
    cuadrado.h \
    memento.h \
    caretaker.h \
    circuloflyweight.h \
    cuadradoflyweight.h \
    canvasview.h

FORMS    += mainwindow.ui
