TEMPLATE = app

QT += qml quick widgets

CONFIG += c++11

SOURCES += main.cpp \
    winpcap.cpp \
    device.cpp \
    ethernet.cpp \
    ipv4.cpp \
    arp.cpp \
    packetmodel.cpp \
    udp.cpp \
    tcp.cpp

RESOURCES += qml.qrc

# C++ libraries
INCLUDEPATH += "..\include" \
    "C:\Program Files (x86)\Windows Kits\10\Include\10.0.10240.0\ucrt"

LIBS += -L"..\lib" -lwpcap \
    -L"E:\_dependencies\lib\x86" -lucrt \
    -lws2_32

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    winpcap.h \
    protocols.h \ 
    device.h \
    ethernet.h \
    ipv4.h \
    arp.h \
    packetmodel.h \
    packet.h \
    udp.h \
    tcp.h

DEFINES += WPCAP HAVE_REMOTE
