#-------------------------------------------------
#
# Project created by QtCreator 2015-03-26T16:20:27
#
#-------------------------------------------------
TEMPLATE = lib

HEADERS +=\
    vein-component_global.h \
    vcmp_entitydata.h \
    vcmp_componentdata.h \
    vcmp_introspectiondata.h \
    vcmp_errordata.h

exists( ../../project-paths.pri ) {
  include(../../project-paths.pri)
}


QT       -= gui

TARGET = vein-component
DEFINES += VEINCOMPONENT_LIBRARY

SOURCES += \
    vcmp_entitydata.cpp \
    vcmp_componentdata.cpp \
    vcmp_introspectiondata.cpp \
    vcmp_errordata.cpp

unix {
    target.path = /usr/lib
    INSTALLS += target
}

INCLUDEPATH += $$VEIN_EVENT_INCLUDEDIR
LIBS += $$VEIN_EVENT_LIBDIR -lvein-event

QMAKE_CXXFLAGS += -Wall -Wfloat-equal -std=c++0x
