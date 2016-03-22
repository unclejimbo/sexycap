#ifndef WINPCAP_H
#define WINPCAP_H

#include <QObject>
#include <pcap/pcap.h>

#include "devicemodel.h"

class WinPcap : public QObject
{
    Q_OBJECT

public:
    WinPcap(QObject* parent = 0);
    ~WinPcap();

    bool readDevices();

    // qml interfaces
    Q_INVOKABLE const QList<QObject*> devices();
    Q_INVOKABLE bool captureStart(QString description, bool mixed, QString timeout);
    Q_INVOKABLE bool captureStop();

private:
    pcap_if_t* _alldevs;
    QList<QObject*> _devices;
};

#endif // WINPCAP_H
