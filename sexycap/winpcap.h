#ifndef WINPCAP_H
#define WINPCAP_H

#include <mutex>
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
    pcap_t* adapter() const;
    PacketModel* packetModel();
    bool stop() const;
    void setStop(bool status);

    // qml interfaces
    Q_INVOKABLE const QList<QObject*> devices();
    Q_INVOKABLE bool captureStart(int device_index, bool mixed, QString timeout = "1000");
    Q_INVOKABLE bool captureStop();
    Q_INVOKABLE QString displaySelected(int index);

signals:
    void redraw(QModelIndex,int,int);

private:
    pcap_if_t* _alldevs;
    pcap_t* _adapter;
    QList<QObject*> _devices;
    PacketModel _packet_model;
    bool _stop;
    std::mutex _mtx;
};

#endif // WINPCAP_H
