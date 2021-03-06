#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "winpcap.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;

    // Initialize WinPcap and embed it into qml
    WinPcap pcap;
    pcap.readDevices();
    engine.rootContext()->setContextProperty("pcap", &pcap);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
