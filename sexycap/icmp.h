#ifndef ICMP_H
#define ICMP_H

#include <QString>
#include "packet.h"

class Icmp : public Packet
{
public:
    explicit Icmp(Packet* p): Packet(p){}
    ~Icmp() = default;

    bool parse(const u_char* pkt_data) override;

    QString type() const override;
    QString src() const override;
    QString dst() const override;
    QString description() const override;
    QString full_text() const override;

private:
    u_char _type;
    u_char _code;
};

#endif // ICMP_H
