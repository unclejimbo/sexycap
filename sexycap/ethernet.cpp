#include "ethernet.h"
#include "protocols.h"
#include "ipv4.h"
#include "arp.h"

bool Ethernet::parse(const u_char *pkt_data)
{
    auto hdr = reinterpret_cast<const ethernet_header*>(pkt_data);
    _saddr = mac2qstr(hdr->saddr);
    _daddr = mac2qstr(hdr->daddr);
    _tof = ntohs(hdr->tof);

    switch(_tof) {
    case 0x0800: // IPv4
        child = new Ipv4(this);
        child->parse(pkt_data + 14);
        break;
    case 0x0806: // ARP
        child = new Arp(this);
        child->parse(pkt_data + 14);
        break;
    default:
        child = nullptr;
    }

    return true;
}

QString Ethernet::type() const
{
    return QString("Ethernet10MB");
}

QString Ethernet::src() const
{
    return _saddr;
}

QString Ethernet::dst() const
{
    return _daddr;
}

QString Ethernet::description() const
{
    return QString("Data frame from %1 to %2")
            .arg(_saddr).arg(_daddr);
}
