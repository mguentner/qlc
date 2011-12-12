include(../../../coverage.pri)
TEMPLATE = app
LANGUAGE = C++
TARGET   = cuestack_test

QT      += testlib xml
CONFIG  -= app_bundle

DEPENDPATH   += ../../src
INCLUDEPATH  += ../../../plugins/interfaces
INCLUDEPATH  += ../../src
QMAKE_LIBDIR += ../../src
LIBS         += -lqlcengine

SOURCES += cuestack_test.cpp
HEADERS += cuestack_test.h