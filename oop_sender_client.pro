TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    getfilesize.cpp \
    client.cpp

HEADERS += \
    getfilesize.h \
    client.h
