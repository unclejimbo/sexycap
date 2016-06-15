#include "arp.h"
#include "protocols.h"

bool Arp::parse(const u_char *pkt_data)
{
    auto hdr = reinterpret_cast<const arp_header*>(pkt_data);

    _htype = ntohs(hdr->htype);
    _ptype = ntohs(hdr->ptype);
    _hlen = hdr->hlen;
    _plen = hdr->plen;
    _operation = ntohs(hdr->operation);
    _sha = mac2qstr(hdr->sha);
    _spa = ipv42qstr(hdr->spa);
    _tha = mac2qstr(hdr->tha);
    _tpa = ipv42qstr(hdr->tpa);

    child = nullptr;

    return true;
}

QString Arp::type() const
{
    return QString("ARP");
}

QString Arp::src() const
{
    return parent->src();
}

QString Arp::dst() const
{
    return parent->dst();
}

QString Arp::description() const
{
    return QString();
}

QString Arp::full_text() const
{
    QString str;
    str.append("ARP Header:\n");
    str.append(QString("  ARP Type: %1\n").arg(type()));

    return str;
}
