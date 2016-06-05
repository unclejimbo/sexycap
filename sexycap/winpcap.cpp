#include "winpcap.h"

#include <iostream>

WinPcap::WinPcap(QObject *parent)
    :QObject(parent)
{
    _alldevs = nullptr;
}

WinPcap::~WinPcap()
{
    pcap_freealldevs(_alldevs);
    _alldevs = nullptr;
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
        _devices.append(std::move(new DeviceModel(d->name, d->description)));
    }

    pcap_t* adapter = pcap_open(_alldevs->name,
                                65535,   // capture all data
                                PCAP_OPENFLAG_PROMISCUOUS,
                                1000,
                                nullptr, // remote auth off
                                errbuf);
    if (adapter == nullptr)
        std::cerr << "open fail" << std::endl;
    else
        std::cout << "find" << std::endl;

    return true;
}

const QList<QObject*> WinPcap::devices()
{
    return _devices;
}

bool WinPcap::captureStart(QString description, bool mixed, QString timeout)
{
    auto d = _alldevs;
    for (; description.compare(d->description); d = _alldevs->next) {
        // Continue until find the correct device
    }
    int mixedMode = mixed ? PCAP_OPENFLAG_PROMISCUOUS : 0;
    int timeOut = timeout.toInt();
    char errbuf[PCAP_ERRBUF_SIZE];

    pcap_t* adapter = pcap_open(d->name,
                                65535,   // capture all data
                                mixedMode,
                                timeOut,
                                nullptr, // remote auth off
                                errbuf);
    if (adapter == nullptr) {
        std::cerr << "ERROR::WinPcap::captureStart(QString, bool, QString): "
                  << errbuf << std::endl;
        return false;
    }
    return true;
}

bool WinPcap::captureStop()
{
    return true;
}
