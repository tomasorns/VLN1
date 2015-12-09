QT += core
QT -= gui
QT += core sql

TARGET = VLN1
CONFIG += console
CONFIG -= app_bundle
CONFIG += c++11

TEMPLATE = app

SOURCES += main.cpp \
    itemManager.cpp \
    consoleIndex.cpp \
    Item.cpp \
    Computer.cpp \
    repositories.cpp

HEADERS += \
    itemManager.h \
    consoleIndex.h \
    Item.h \
    Computer.h \
    repositories.h
