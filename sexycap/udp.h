#ifndef UDP_H
#define UDP_H

#include <QString>
#include "packet.h"

class Udp : public Packet
{
public:
    explicit Udp(Packet* p): Packet(p){}
    ~Udp() = default;

    bool parse(const u_char *pkt_data) override;

    QString type() const override;
    QString src() const override;
    QString dst() const override;
    QString description() const override;
    QString full_text() const override;

private:
    u_short _sport;
    u_short _dport;
    u_short _len;
};

#endif // UDP_H
