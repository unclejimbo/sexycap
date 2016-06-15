#ifndef ETHERNET_H
#define ETHERNET_H

#include <QString>
#include "packet.h"

class Ethernet : public Packet
{
public:
    explicit Ethernet(Packet* p): Packet(p){}
    ~Ethernet() = default;

    bool parse(const u_char *pkt_data) override;

    QString type() const override;
    QString src() const override;
    QString dst() const override;
    QString description() const override;
    QString full_text() const override;

private:
    QString _saddr;
    QString _daddr;
    u_short _tof;
};

#endif // ETHERNET_H
