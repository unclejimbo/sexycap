#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "winpcap.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;

    WinPcap pcap;
    pcap.readDevices();
    engine.rootContext()->setContextProperty("deviceModel", QVariant::fromValue(pcap.devices()));

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
