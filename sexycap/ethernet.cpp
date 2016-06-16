#include "ethernet.h"
#include "protocols.h"
#include "ipv4.h"
#include "arp.h"

bool Ethernet::parse(const u_char *pkt_data)
{
    auto hdr = reinterpret_cast<const ethernet_header*>(pkt_data);
    _daddr = mac2qstr(hdr->saddr);
    _saddr = mac2qstr(hdr->daddr);
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
    if (_daddr.compare("ff:ff:ff:ff:ff:ff") == 0)
        return "Broadcast";
    else
        return _daddr;
}

QString Ethernet::description() const
{
    return QString("Data frame from %1 to %2")
            .arg(_saddr).arg(_daddr);
}

QString Ethernet::full_text() const
{
    QString str;
    str.append("Ethernet10MB Header:\n");
    str.append(QString("  Source Mac Address: %1\n").arg(_saddr));
    str.append(QString("  Destination Mac Address: %1\n").arg(_daddr));

    QString service_type;
    switch(_tof) {
    case 0x0800:
        service_type = "IPv4";
        break;
    case 0x0806:
        service_type = "ARP";
        break;
    default:
        break;
    }
    str.append(QString("  Type of Service: %1(%2)\n").arg(service_type).arg(_tof));

    if(child != nullptr)
        str.append(child->full_text());

    return str;
}
