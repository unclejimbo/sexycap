#include "udp.h"
#include "protocols.h"
#include "dns.h"

bool Udp::parse(const u_char *pkt_data)
{
    auto hdr = reinterpret_cast<const udp_header*>(pkt_data);

    _sport = ntohs(hdr->sport);
    _dport = ntohs(hdr->dport);
    _len = ntohs(hdr->len);

    switch(_dport) {
    case 53: // DNS
        child = new Dns(this);
        child->parse(pkt_data + 8);
        break;
    default:
        child = nullptr;
    }

    return true;
}

QString Udp::type() const
{
    return QString("UDP");
}

QString Udp::src() const
{
    return parent->src();
}

QString Udp::dst() const
{
    return parent->dst();
}

QString Udp::description() const
{
    return QString("UDP Message from %1 to %2")
            .arg(src().append(":").append(QString::number(_sport)))
            .arg(dst().append(":").append(QString::number(_dport)));
}

QString Udp::full_text() const
{
    QString str;
    str.append("UDP Header:\n");
    str.append(QString("  Source Port: %1\n").arg(_sport));
    str.append(QString("  Destination Port: %1\n").arg(_dport));
    str.append(QString("  Length of UDP Header and Data: %1\n").arg(_len));

    if (child != nullptr)
        str.append(child->full_text());

    return str;
}
