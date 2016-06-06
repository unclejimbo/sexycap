#include "ipv4.h"

Ipv4::Ipv4(const QString &timestr, int len, QObject *parent):
    Packet(timestr, len, parent)
{

}

QString Ipv4::info() const
{
    return QString();
}

void Ipv4::parse(const u_char* pkt_data)
{

}
