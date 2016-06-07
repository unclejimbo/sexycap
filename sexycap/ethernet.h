#ifndef ETHERNET_H
#define ETHERNET_H

#include <QString>
#include "packet.h"

class Ethernet : public Packet
{
public:
    Ethernet() = default;
    ~Ethernet() = default;

    bool parse(const u_char *pkt_data) override;

private:
    QString _saddr;
    QString _daddr;
    u_short _tof;
};

#endif // ETHERNET_H
