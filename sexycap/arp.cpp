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
    if (_operation == 1) { // Request
        return QString(_sha).append(" asks for mac address of ").append(_tpa);
    } else { // Response
        return QString(_tha).append(" I am ").append(_spa).append("and my mac address is ").append(_sha);
    }

}

QString Arp::full_text() const
{
    QString str;
    str.append("ARP Header:\n");
    str.append(QString("  Hardware Type: %1\n").arg(_htype));
    str.append(QString("  Protocol Type: %1\n").arg(_ptype));
    str.append(QString("  Hardware Address Length: %1\n").arg(_hlen));
    str.append(QString("  Protocol Address Length: %1\n").arg(_plen));
    if (_operation == 1)
        str.append("  Operation: Request\n");
    else
        str.append("  Operation: Responce\n");
    str.append(QString("  Sender Hardware Address: %1\n").arg(_sha));
    str.append(QString("  Sender Protocol Address: %1\n").arg(_spa));
    str.append(QString("  Target Hardware Address: %1\n").arg(_tha));
    str.append(QString("  Target Protocol Address: %1\n").arg(_tpa));

    return str;
}
