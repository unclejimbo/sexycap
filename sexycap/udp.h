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

private:
};

#endif // UDP_H
