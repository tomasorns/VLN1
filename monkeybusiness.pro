#-------------------------------------------------
#
# Project created by QtCreator 2015-12-13T19:37:26
#
#-------------------------------------------------

QT += core gui
QT += core sql

CONFIG += c++11


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = monkeybusiness
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Computer.cpp \
    Item.cpp \
    itemManager.cpp \
    repositories.cpp

HEADERS  += mainwindow.h \
    Computer.h \
    Item.h \
    itemManager.h \
    repositories.h

FORMS    += mainwindow.ui
