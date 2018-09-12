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
    SingleColourEffects/fireworkseffect.cpp \
    SingleColourEffects/gameoflifeeffect.cpp \
    SingleColourEffects/mathfunctioneffect.cpp \
    SingleColourEffects/mathfunctions.cpp \
    SingleColourEffects/oneafteranothereffect.cpp \
    SingleColourEffects/plainseffect.cpp \
    SingleColourEffects/raineffect.cpp \
    SingleColourEffects/randwarpeffect.cpp \
    SingleColourEffects/shrinkboxeffect.cpp \
    SingleColourEffects/singlecoloureffect.cpp \
    SingleColourEffects/texteffect.cpp \
    SingleColourEffects/waterfalleffect.cpp \
    Array/array2d.cpp \
    Array/array3d.cpp \
    FullColourEffects/fullcoloureffect.cpp \
    effect.cpp \
    FullColourEffects/huelampeffect.cpp \
    configdialog.cpp

HEADERS  += cubewindow.h \
    effecthandler.h \
    usbhandler.h \
    cubeTools.h \
    rs232.h \
    particle.h \
    letter.h \
    font.h \
    constants.h \
    SingleColourEffects/fireworkseffect.h \
    SingleColourEffects/gameoflifeeffect.h \
    SingleColourEffects/mathfunctioneffect.h \
    SingleColourEffects/mathfunctions.h \
    SingleColourEffects/oneafteranothereffect.h \
    SingleColourEffects/plainseffect.h \
    SingleColourEffects/raineffect.h \
    SingleColourEffects/randwarpeffect.h \
    SingleColourEffects/shrinkboxeffect.h \
    SingleColourEffects/singlecoloureffect.h \
    SingleColourEffects/texteffect.h \
    SingleColourEffects/waterfalleffect.h \
    Array/array2d.h \
    Array/array3d.h \
    FullColourEffects/fullcoloureffect.h \
    effect.h \
    FullColourEffects/huelampeffect.h \
    configdialog.h

FORMS    += cubewindow.ui \
    configdialog.ui

QMAKE_CXXFLAGS += -std=c++11

INCLUDEPATH += $$PWD/../../../../../usr/local/include
DEPENDPATH += $$PWD/../../../../../usr/local/include

RESOURCES += \
    ressources.qrc
