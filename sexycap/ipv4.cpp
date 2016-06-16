#include "ipv4.h"
#include "protocols.h"
#include "udp.h"
#include "tcp.h"

bool Ipv4::parse(const u_char* pkt_data)
{
    auto hdr = reinterpret_cast<const ipv4_header*>(pkt_data);

    _version = (hdr->ver_hl & 0xf0) >> 4;
    _hdr_len = (hdr->ver_hl & 0x0f) * 4;
    _tlen = ntohs(hdr->tlen);
    auto flags_fo = ntohs(hdr->flags_fo);
    _df = flags_fo & 0x4000;
    _mf = flags_fo & 0x2000;
    _offset = flags_fo & 0x00ff;
    _ttl = hdr->ttl;
    _protocol = hdr->protocol;
    _saddr = ipv42qstr(hdr->saddr);
    _daddr = ipv42qstr(hdr->daddr);

    switch(_protocol) {
    case 0x01: // ICMP
    case 0x06: // TCP
        child = new Tcp(this);
        child->parse(pkt_data + _hdr_len);
        break;
    case 0x11: // UDP
        child = new Udp(this);
        child->parse(pkt_data + _hdr_len);
        break;
    default:
        child = nullptr;
    }

    return true;
}

QString Ipv4::type() const
{
    return QString("IPv4");
}

QString Ipv4::src() const
{
    return _saddr;
}

QString Ipv4::dst() const
{
    if (_daddr.compare("255:255:255:255") == 0)
        return "Broadcast";
    else
        return _daddr;
}

QString Ipv4::description() const
{
    return QString("IP datagram from %1 to %2")
            .arg(_saddr).arg(_daddr);
}

QString Ipv4::full_text() const
{
    QString str;
    str.append("IPv4 Header:\n");
    str.append("  Version: 4\n");
    str.append(QString("  Header Length: %1\n").arg(_hdr_len));
    str.append(QString("  Total Length: %1\n").arg(_tlen));
    str.append(QString("  Defragment: %1\n").arg(_df));
    str.append(QString("  More Fragments: %1\n").arg(_mf));
    str.append(QString("  Fragment Offset: %1\n").arg(_offset));
    str.append(QString("  Time to Live: %1\n").arg(_ttl));
    str.append(QString("  Protocol: %1\n").arg(_protocol));
    str.append(QString("  Source IP Address: %1\n").arg(_saddr));
    str.append(QString("  Destination IP Address: %1\n").arg(_daddr));

    if (child != nullptr)
        str.append(child->full_text());

    return str;
}


