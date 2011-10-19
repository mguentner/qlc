include(../../../coverage.pri)
TEMPLATE = app
LANGUAGE = C++
TARGET   = mastertimer_test

QT      += testlib xml
CONFIG  -= app_bundle

INCLUDEPATH  += ../../../plugins/interfaces
INCLUDEPATH  += ../function
INCLUDEPATH  += ../../src
QMAKE_LIBDIR += ../../src
LIBS         += -lqlcengine

SOURCES += mastertimer_test.cpp dmxsource_stub.cpp ../function/function_stub.cpp
HEADERS += mastertimer_test.h dmxsource_stub.h ../function/function_stub.h