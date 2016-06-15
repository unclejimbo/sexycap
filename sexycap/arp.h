#ifndef ARP_H
#define ARP_H

#include <QString>
#include "packet.h"

class Arp : public Packet
{
public:
    explicit Arp(Packet* p): Packet(p){}
    ~Arp() = default;

    bool parse(const u_char *pkt_data) override;

    QString type() const override;
    QString src() const override;
    QString dst() const override;
    QString description() const override;
    QString full_text() const override;

private:
    u_short _htype;
    u_short _ptype;
    u_char _hlen;
    u_char _plen;
    u_short _operation;
    QString _sha;
    QString _spa;
    QString _tha;
    QString _tpa;
};

#endif // ARP_H
