#-------------------------------------------------
#
# Project created by QtCreator 2014-08-31T17:26:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LED-Cube-Software
TEMPLATE = app


SOURCES += main.cpp\
        cubewindow.cpp \
    effecthandler.cpp \
    usbhandler.cpp \
    rs232.c \
    array3d.cpp \
    mathfunctions.cpp \
    particle.cpp \
    cubefont.cpp

HEADERS  += cubewindow.h \
    effecthandler.h \
    usbhandler.h \
    cubeTools.h \
    rs232.h \
    array3d.h \
    mathfunctions.h \
    particle.h \
    cubefont.h \
    constants.h

FORMS    += cubewindow.ui

QMAKE_CXXFLAGS += -std=c++11

INCLUDEPATH += $$PWD/../../../../../usr/local/include
DEPENDPATH += $$PWD/../../../../../usr/local/include
