QT += core
QT -= gui

TARGET = VLN1
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    Item.cpp \
    itemManager.cpp \
    consoleIndex.cpp

HEADERS += \
    Item.h \
    itemManager.h \
    consoleIndex.h

