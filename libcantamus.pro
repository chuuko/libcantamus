#-------------------------------------------------
#
# Project created by QtCreator 2013-11-19T12:02:49
#
#-------------------------------------------------

DEFINES = LIBCANTAMUS
TARGET = cantamus
TEMPLATE = lib

CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += handleust.cpp 

HEADERS  += handleust.h 



QMAKE_CXXFLAGS = -fPIC -std=c++11 -fpermissive

QMAKE_LFLAGS -= -rpath

unix {
    target.path = /usr/lib
    INSTALLS += target
}
