QT += core
QT -= gui

TARGET = VLN1
CONFIG += console
CONFIG -= app_bundle
CONFIG += c++11

TEMPLATE = app

SOURCES += main.cpp \
    itemManager.cpp \
    consoleIndex.cpp \
    Item.cpp

HEADERS += \
    itemManager.h \
    consoleIndex.h \
    Item.h

