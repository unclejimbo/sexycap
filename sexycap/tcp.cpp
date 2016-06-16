#include "tcp.h"
#include "protocols.h"

bool Tcp::parse(const u_char *pkt_data)
{
    auto hdr = reinterpret_cast<const tcp_header*>(pkt_data);

    _sport = ntohs(hdr->sport);
    _dport = ntohs(hdr->dport);
    _seq_num = ntohl(hdr->seq_num);
    _ack_num = ntohl(hdr->ack_num);
    _offset = hdr->offset;
    _urg = hdr->ctrl & 0x20;
    _ack = hdr->ctrl & 0x10;
    _psh = hdr->ctrl & 0x08;
    _rst = hdr->ctrl & 0x04;
    _syn = hdr->ctrl & 0x02;
    _fin = hdr->ctrl & 0x01;
    _win = ntohs(hdr->win);

    switch(_dport) {
    case 80: // HTTP
    default:
        child = nullptr;
    }

    return true;
}

QString Tcp::type() const
{
    return "TCP";
}

QString Tcp::src() const
{
    return parent->src();
}

QString Tcp::dst() const
{
    return parent->dst();
}

QString Tcp::description() const
{
    return QString("TCP Message from %1 to %2")
            .arg(src().append(":").append(QString::number(_sport)))
            .arg(dst().append(":").append(QString::number(_dport)));
}

QString Tcp::full_text() const
{
    QString str;
    str.append("TCP Header:\n");
    str.append(QString("  Source Port: %1\n").arg(_sport));
    str.append(QString("  Destination Port: %1\n").arg(_dport));
    str.append(QString("  Sequence Number: %1\n").arg(_seq_num));
    str.append(QString("  Acknowledge Number: %1\n").arg(_ack_num));
    str.append(QString("  Offset: %1\n").arg(_offset));
    str.append(QString("  URG: %1\n").arg(_urg));
    str.append(QString("  ACK: %1\n").arg(_ack));
    str.append(QString("  PSH: %1\n").arg(_psh));
    str.append(QString("  RST: %1\n").arg(_rst));
    str.append(QString("  SYN: %1\n").arg(_syn));
    str.append(QString("  FIN: %1\n").arg(_fin));
    str.append(QString("  Window Size: %1\n").arg(_win));

    if (child != nullptr)
        str.append(child->full_text());

    return str;
}
