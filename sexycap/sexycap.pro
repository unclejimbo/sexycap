TEMPLATE = app

QT += qml quick widgets

CONFIG += c++11

SOURCES += main.cpp \
    devicemodel.cpp \
    winpcap.cpp

RESOURCES += qml.qrc

# C++ libraries
INCLUDEPATH += E:\\_dependencies\\include

LIBS += -LE:\\_dependencies\\lib -lwpcap #-lws2_32

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    winpcap.h \
    devicemodel.h \
    protocols.h

DEFINES += WPCAP HAVE_REMOTE
