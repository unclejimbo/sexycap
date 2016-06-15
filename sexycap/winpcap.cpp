#include "winpcap.h"

#include <iostream>
#include <thread>
#include <QTextStream>
#include "device.h"
#include "ethernet.h"
#include "packetmodel.h"

WinPcap::WinPcap(QObject *parent)
    :QObject(parent)
{
    _alldevs = nullptr;
}

WinPcap::~WinPcap()
{
    pcap_freealldevs(_alldevs);
    _alldevs = nullptr;
    for (auto d : _devices)
        delete d;
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

PacketModel* WinPcap::packetModel()
{
    return &_packet_model;
}

const QList<QObject*> WinPcap::devices()
{
    return _devices;
}

void packetHandler(u_char* param, const pcap_pkthdr* header, const u_char* pkt_data)
{
    auto user_param = reinterpret_cast<WinPcap::UserParam*>(param);

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
        pkt = new Ethernet(nullptr);
        pkt->parse(pkt_data);
        break;
    default:
        break;
    }

    user_param->packet_model->add_packet(pkt, time, len);
}

bool WinPcap::captureStart(int device_index, bool mixed, QString filter)
{
    _packet_model.clear_all();
    auto selected_device = _alldevs;
    for (int i = 0; i++ < device_index; selected_device = _alldevs->next) {
        // Continue until find the correct device
    }
    int mixed_mode = mixed ? PCAP_OPENFLAG_PROMISCUOUS : 0;
    if (filter.isEmpty())
        filter = "ip and udp";
    char errbuf[PCAP_ERRBUF_SIZE];

    _adapter = pcap_open(selected_device->name,
                         65535,   // capture all data
                         mixed_mode,
                         1000,
                         nullptr, // remote auth off
                         errbuf);
    if (_adapter == nullptr) {
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
    if (pcap_compile(_adapter, &fcode, filter.toStdString().c_str(), 1, netmask) < 0) {
        return false;
    }

    if (pcap_setfilter(_adapter, &fcode) < 0) {
        return false;
    }

    UserParam param = { DLT_EN10MB, &_packet_model };
    //std::thread t(&WinPcap::capture, this, param);
    //t.detach();
    pcap_loop(_adapter, 1, packetHandler, reinterpret_cast<u_char*>(&param));

    return true;
}

bool WinPcap::captureStop()
{
    pcap_breakloop(_adapter);
    return true;
}

QString WinPcap::displaySelected(int index)
{
    auto pm = _packet_model.at(index);
    if (pm != nullptr)
        return pm->full_text();
    else
        return QString("");
}

void WinPcap::capture(WinPcap::UserParam param)
{
    pcap_loop(_adapter, 2, packetHandler, reinterpret_cast<u_char*>(&param));
}
