TEMPLATE = app

QT += qml quick widgets

CONFIG += c++11

SOURCES += main.cpp \
    devicemodel.cpp \
    winpcap.cpp

RESOURCES += qml.qrc

# C++ libraries
INCLUDEPATH += "E:\_dependencies\include" \
    "C:\Program Files (x86)\Windows Kits\10\Include\10.0.10240.0\ucrt"

LIBS += -L"E:\_dependencies\lib" -lwpcap -lucrt #-lws2_32

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    winpcap.h \
    devicemodel.h \
    protocols.h

DEFINES += WPCAP HAVE_REMOTE
