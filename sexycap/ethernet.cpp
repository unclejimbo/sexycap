#include "ethernet.h"
#include <pcap.h>
#include <QTextStream>
#include "protocols.h"
#include "ipv4.h"

Ethernet::Ethernet(const QString &timestr, int len, QObject *parent):
    Packet(timestr, len, parent)
{

}

Ethernet::~Ethernet()
{
    if (next != nullptr)
        free(next);
}

QString Ethernet::info() const
{
    return QString();
}

void Ethernet::parse(const u_char *pkt_data)
{
    auto eth_hdr = reinterpret_cast<const ethernet_header*>(pkt_data);
    _src = QString("%1:%2:%3:%4:%5:%6")
            .arg(eth_hdr->saddr.byte1, 2, 16, QLatin1Char('0'))
            .arg(eth_hdr->saddr.byte2, 2, 16, QLatin1Char('0'))
            .arg(eth_hdr->saddr.byte3, 2, 16, QLatin1Char('0'))
            .arg(eth_hdr->saddr.byte4, 2, 16, QLatin1Char('0'))
            .arg(eth_hdr->saddr.byte5, 2, 16, QLatin1Char('0'))
            .arg(eth_hdr->saddr.byte6, 2, 16, QLatin1Char('0'));
    _dst = QString("%1:%2:%3:%4:%5:%6")
            .arg(eth_hdr->daddr.byte1, 2, 16, QLatin1Char('0'))
            .arg(eth_hdr->daddr.byte2, 2, 16, QLatin1Char('0'))
            .arg(eth_hdr->daddr.byte3, 2, 16, QLatin1Char('0'))
            .arg(eth_hdr->daddr.byte4, 2, 16, QLatin1Char('0'))
            .arg(eth_hdr->daddr.byte5, 2, 16, QLatin1Char('0'))
            .arg(eth_hdr->daddr.byte6, 2, 16, QLatin1Char('0'));

    switch(ntohs(eth_hdr->tof)) {
    case 0x0800: // ipv4
        next = new Ipv4(_timestr, _len);
        next->parse(pkt_data + 14);
        break;
    default:
        next = nullptr;
        break;
    }
}
