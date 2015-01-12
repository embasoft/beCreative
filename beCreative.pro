#-------------------------------------------------
#
# Project created by QtCreator 2015-01-04T19:34:28
#
#-------------------------------------------------

QT       -= gui

TARGET = beCreative
TEMPLATE = lib

DEFINES += BECREATIVE_LIBRARY

SOURCES += becreative.cpp \
    Core/changeshandler.cpp \
    Core/romstream.cpp \
    Core/rom.cpp

HEADERS += becreative.h\
        becreative_global.h \
    Core/changeshandler.h \
    Core/romstream.h \
    Core/rom.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
