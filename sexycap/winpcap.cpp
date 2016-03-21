#include "winpcap.h"

#include <pcap/pcap.h>
#include <iostream>

WinPcap::WinPcap(QObject *parent)
    :QObject(parent)
{

}

void WinPcap::readDevices()
{
    pcap_if_t *alldevs;
    char errbuf[PCAP_ERRBUF_SIZE];

    if (pcap_findalldevs_ex(const_cast<char*>(PCAP_SRC_IF_STRING), NULL, &alldevs, errbuf) == -1) {
        std::cerr << "ERROR::pcap_findalldevs_ex: " << errbuf << std::endl;
        exit(1);
    }

    for(auto d= alldevs; d != NULL; d= d->next) {
        std::cout << d->name << std::endl;
    }

    for (auto d = alldevs; d != nullptr; d = d->next) {
        _devices.append(std::move(new DeviceModel(d->name, d->description)));
    }

    pcap_freealldevs(alldevs);
}

const QList<QObject*> WinPcap::devices()
{
    return _devices;
}
