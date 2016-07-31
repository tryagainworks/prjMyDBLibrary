#-------------------------------------------------
#
# Project created by QtCreator 2016-03-04T15:45:59
#
#-------------------------------------------------

QT       += widgets sql

TARGET = prjMyDBLibrary
TEMPLATE = lib

DEFINES += PRJMYDBLIBRARY_LIBRARY

SOURCES += prjmydblibrary.cpp

HEADERS += prjmydblibrary.h\
        prjmydblibrary_global.h

QT += sql

unix {
    target.path = /usr/lib
    INSTALLS += target
}
