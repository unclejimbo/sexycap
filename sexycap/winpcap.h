#ifndef WINPCAP_H
#define WINPCAP_H

#include <QObject>
#include <QVector>
#include <QList>
#include <pcap/pcap.h>

class WinPcap : public QObject
{
    Q_OBJECT

public:
    WinPcap(QObject* parent = 0);
    ~WinPcap();

    bool readDevices();

    // qml interfaces
    Q_INVOKABLE const QList<QObject*> devices();
    Q_INVOKABLE bool captureStart(int device_index, bool mixed, QString timeout);
    Q_INVOKABLE bool captureStop();

private:
    pcap_if_t* _alldevs;
    QList<QObject*> _devices;
    QVector<QObject*> _packets;
};

#endif // WINPCAP_H
