include(../../../coverage.pri)
TEMPLATE = app
LANGUAGE = C++
TARGET   = chaserstep_test

QT      += testlib xml
CONFIG  -= app_bundle

INCLUDEPATH  += ../../../plugins/interfaces
INCLUDEPATH  += ../../src
QMAKE_LIBDIR += ../../src
LIBS         += -lqlcengine

SOURCES += chaserstep_test.cpp
HEADERS += chaserstep_test.h