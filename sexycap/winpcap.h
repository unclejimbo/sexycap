#ifndef WINPCAP_H
#define WINPCAP_H

#include <QObject>
#include <QList>
#include <QItemSelectionModel>
#include <pcap.h>
#include "packetmodel.h"

class WinPcap : public QObject
{
    Q_OBJECT
    Q_PROPERTY(PacketModel* packetModel READ packetModel)

public:
    typedef struct UserParam
    {
        int dl_type;
        PacketModel* packet_model;
    }UserParam;

    WinPcap(QObject* parent = 0);
    ~WinPcap();

    bool readDevices();
    PacketModel* packetModel();

    // qml interfaces
    Q_INVOKABLE const QList<QObject*> devices();
    Q_INVOKABLE bool captureStart(int device_index, bool mixed, QString timeout = "1000");
    Q_INVOKABLE bool captureStop();
    Q_INVOKABLE QString displaySelected(int index);

private:
    void capture(UserParam param);

    pcap_if_t* _alldevs;
    pcap_t* _adapter;
    QList<QObject*> _devices;
    PacketModel _packet_model;
};

#endif // WINPCAP_H
