#include "winpcap.h"

#include <iostream>
#include "device.h"
#include "packet.h"

WinPcap::WinPcap(QObject *parent)
    :QObject(parent)
{
    _alldevs = nullptr;
}

WinPcap::~WinPcap()
{
    pcap_freealldevs(_alldevs);
    _alldevs = nullptr;
    for (auto p : _packets)
        free(p);
    for (auto d : _devices)
        free(d);
}

bool WinPcap::readDevices()
{
    char errbuf[PCAP_ERRBUF_SIZE];

    if (pcap_findalldevs_ex(const_cast<char*>(PCAP_SRC_IF_STRING), nullptr, &_alldevs, errbuf) == -1) {
        std::cerr << "ERROR::WinPcap::readDevices(): " << errbuf << std::endl;
        return false;
    }

    for(auto d = _alldevs; d != nullptr; d = d->next) {
        std::cout << d->name << std::endl;
    }

    for (auto d = _alldevs; d != nullptr; d = d->next) {
        auto dv = new Device(d->name, d->description);
        _devices.append(dv);
    }

    return true;
}

const QList<QObject*> WinPcap::devices()
{
    return _devices;
}

void packetHandler(u_char* param, const pcap_pkthdr* header, const u_char* pkt_data)
{
    auto packets = reinterpret_cast<QVector<QObject*>*>(param);

    auto pkt = new Packet(header, pkt_data);
    pkt->parse();
    packets->append(pkt);
}

bool WinPcap::captureStart(int device_index, bool mixed, QString timeout)
{
    auto d = _alldevs;
    for (int i = 0; i++ < device_index; d = _alldevs->next) {
        // Continue until find the correct device
    }
    int mixed_mode = mixed ? PCAP_OPENFLAG_PROMISCUOUS : 0;
    int timeOut = timeout.toInt();
    char errbuf[PCAP_ERRBUF_SIZE];

    auto adapter = pcap_open(d->name,
                             65535,   // capture all data
                             mixed_mode,
                             timeOut,
                             nullptr, // remote auth off
                             errbuf);
    if (adapter == nullptr) {
        std::cerr << "ERROR::WinPcap::captureStart(QString, bool, QString): "
                  << errbuf << std::endl;
        return false;
    }

    u_int netmask;
    if (d->addresses != nullptr)
        netmask = (reinterpret_cast<struct sockaddr_in*>(d->addresses->netmask))->sin_addr.S_un.S_addr;
    else
        netmask = 0xffffff; // default C class network

    pcap_loop(adapter, 1, packetHandler, reinterpret_cast<u_char*>(&_packets));

    return true;
}

bool WinPcap::captureStop()
{
    return true;
}
