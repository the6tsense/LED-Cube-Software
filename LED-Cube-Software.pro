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
    particle.cpp \
    letter.cpp \
    font.cpp \
    Effects/effect.cpp \
    Effects/fireworkseffect.cpp \
    Effects/gameoflifeeffect.cpp \
    Effects/mathfunctioneffect.cpp \
    Effects/mathfunctions.cpp \
    Effects/oneafteranothereffect.cpp \
    Effects/plainseffect.cpp \
    Effects/raineffect.cpp \
    Effects/randwarpeffect.cpp \
    Effects/shrinkboxeffect.cpp \
    Effects/texteffect.cpp \
    Effects/waterfalleffect.cpp \
    Array/array2d.cpp \
    Array/array3d.cpp

HEADERS  += cubewindow.h \
    effecthandler.h \
    usbhandler.h \
    cubeTools.h \
    rs232.h \
    particle.h \
    texteffect.h \
    letter.h \
    font.h \
    effect.h \
    constants.h \
    Effects/effect.h \
    Effects/fireworkseffect.h \
    Effects/gameoflifeeffect.h \
    Effects/mathfunctioneffect.h \
    Effects/mathfunctions.h \
    Effects/oneafteranothereffect.h \
    Effects/plainseffect.h \
    Effects/raineffect.h \
    Effects/randwarpeffect.h \
    Effects/shrinkboxeffect.h \
    Effects/texteffect.h \
    Effects/waterfalleffect.h \
    Array/array2d.h \
    Array/array3d.h

FORMS    += cubewindow.ui

QMAKE_CXXFLAGS += -std=c++11

INCLUDEPATH += $$PWD/../../../../../usr/local/include
DEPENDPATH += $$PWD/../../../../../usr/local/include

RESOURCES += \
    ressources.qrc
