#include "winpcap.h"

#include <iostream>
#include <thread>
#include <chrono>
#include <QTextStream>
#include "device.h"
#include "ethernet.h"
#include "packetmodel.h"

WinPcap::WinPcap(QObject *parent)
    :QObject(parent)
{
    _alldevs = nullptr;
    QObject::connect(this, SIGNAL(redraw(QModelIndex,int,int)),
                     &_packet_model, SIGNAL(rowsInserted(QModelIndex,int,int)));
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

pcap_t* WinPcap::adapter() const
{
    return _adapter;
}

PacketModel* WinPcap::packetModel()
{
    return &_packet_model;
}

bool WinPcap::stop() const
{
    return _stop;
}

void WinPcap::setStop(bool status)
{
    _mtx.lock();
    _stop = status;
    _mtx.unlock();
}

const QList<QObject*> WinPcap::devices()
{
    return _devices;
}

//void packetHandler(u_char* param, const pcap_pkthdr* header, const u_char* pkt_data)
//{
//    auto user_param = reinterpret_cast<WinPcap::UserParam*>(param);

//    // parse time
//    time_t local_tv_sec = header->ts.tv_sec;
//    struct tm ltime;
//    localtime_s(&ltime, &local_tv_sec);
//    char timestr[16];
//    strftime(timestr, sizeof(timestr), "%H:%M:%S", &ltime);
//    QString time;
//    QTextStream(&time) << timestr << "." << header->ts.tv_usec;

//    // parse header length
//    int len = header->len;

//    Packet* pkt = nullptr;
//    switch(user_param->dl_type) {
//    case DLT_EN10MB:
//        pkt = new Ethernet(nullptr);
//        pkt->parse(pkt_data);
//        break;
//    default:
//        break;
//    }

//    if (pkt != nullptr)
//        user_param->packet_model->add_packet(pkt, time, len);
//}

void captureStartImp(int dl_type, WinPcap* pcap)
{
    pcap_pkthdr* header;
    const u_char* pkt_data;
    int i = 0;

    while(!pcap->stop()) {
        pcap_next_ex(pcap->adapter(), &header, &pkt_data);

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
        switch(dl_type) {
        case DLT_EN10MB:
            pkt = new Ethernet(nullptr);
            pkt->parse(pkt_data);
            break;
        default:
            break;
        }

        if (pkt != nullptr) {
            pcap->packetModel()->add_packet(pkt, time, len);
            emit pcap->redraw(QModelIndex(), i, i);
            ++i;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

bool WinPcap::captureStart(int device_index, bool mixed, QString filter)
{
    _packet_model.clear_all();
    setStop(false);
    auto selected_device = _alldevs;
    for (int i = 0; i++ < device_index; selected_device = _alldevs->next) {
        // Continue until find the correct device
    }
    int mixed_mode = mixed ? PCAP_OPENFLAG_PROMISCUOUS : 0;
    if (filter.isEmpty())
        filter = "";
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

    std::thread(captureStartImp, DLT_EN10MB, this).detach();

    return true;
}

bool WinPcap::captureStop()
{
    setStop(true);
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

/*void pcap_imp(pcap_t* adapter, int cnt, pcap_handler handler, WinPcap::UserParam param)
{
    pcap_loop(adapter, cnt, handler, reinterpret_cast<u_char*>(&param));
}*/
