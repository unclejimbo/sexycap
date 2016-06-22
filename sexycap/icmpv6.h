#ifndef ICMPV6_H
#define ICMPV6_H

#include <QString>
#include "packet.h"

class Icmpv6 : public Packet
{
public:
    explicit Icmpv6(Packet* p): Packet(p){}
    ~Icmpv6() = default;

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

#endif // ICMPV6_H
