#include "winpcap.h"

#include <iostream>
#include <QTextStream>
#include "device.h"
#include "ethernet.h"

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

typedef struct UserParam
{
    int dl_type;
    QVector<QObject*>* packets;
}UserParam;

void packetHandler(u_char* param, const pcap_pkthdr* header, const u_char* pkt_data)
{
    auto user_param = reinterpret_cast<UserParam*>(param);

    // parse time
    time_t local_tv_sec = header->ts.tv_sec;
    struct tm ltime;
    localtime_s(&ltime, &local_tv_sec);
    char timestr[16];
    strftime(timestr, sizeof(timestr), "%H:%M:%S", &ltime);
    QString time;
    QTextStream(&time) << timestr << "." << header->ts.tv_usec;

    // parse header length
    int len = header->len;

    Packet* pkt = nullptr;
    switch(user_param->dl_type) {
    case DLT_EN10MB:
        pkt = new Ethernet(time, len);
        pkt->parse(pkt_data);
        user_param->packets->append(pkt);
        break;
    default:
        break;
    }
}

bool WinPcap::captureStart(int device_index, bool mixed, QString timeout)
{
    auto selected_device = _alldevs;
    for (int i = 0; i++ < device_index; selected_device = _alldevs->next) {
        // Continue until find the correct device
    }
    int mixed_mode = mixed ? PCAP_OPENFLAG_PROMISCUOUS : 0;
    int timeOut = timeout.toInt();
    char errbuf[PCAP_ERRBUF_SIZE];

    auto adapter = pcap_open(selected_device->name,
                             65535,   // capture all data
                             mixed_mode,
                             timeOut,
                             nullptr, // remote auth off
                             errbuf);
    if (adapter == nullptr) {
        std::cerr << "ERROR::WinPcap::captureStart: "
                  << errbuf << std::endl;
        return false;
    }

    u_int netmask;
    if (selected_device->addresses != nullptr)
        netmask = (reinterpret_cast<struct sockaddr_in*>(selected_device->addresses->netmask))->sin_addr.S_un.S_addr;
    else
        netmask = 0xffffff; // default C class network

    struct bpf_program fcode;
    if (pcap_compile(adapter, &fcode, "ip", 1, netmask) < 0) {
        return false;
    }

    if (pcap_setfilter(adapter, &fcode) < 0) {
        return false;
    }

    UserParam param = { DLT_EN10MB, &_packets };
    pcap_loop(adapter, 1, packetHandler, reinterpret_cast<u_char*>(&param));

    return true;
}

bool WinPcap::captureStop()
{
    return true;
}
