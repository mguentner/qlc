include(../../../coverage.pri)
TEMPLATE = app
LANGUAGE = C++
TARGET   = chaserrunner_test

QT      += testlib xml
CONFIG  -= app_bundle

INCLUDEPATH  += ../../../plugins/interfaces
INCLUDEPATH  += ../mastertimer
INCLUDEPATH  += ../../src
QMAKE_LIBDIR += ../../src
LIBS         += -lqlcengine

SOURCES += chaserrunner_test.cpp ../mastertimer/mastertimer_stub.cpp
HEADERS += chaserrunner_test.h ../mastertimer/mastertimer_stub.h