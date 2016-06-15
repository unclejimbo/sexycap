#include "udp.h"

bool Udp::parse(const u_char *pkt_data)
{
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
    return QString();
}
