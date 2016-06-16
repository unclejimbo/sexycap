#ifndef DNS_H
#define DNS_H

#include "packet.h"

class Dns : public Packet
{
public:
    explicit Dns(Packet* p): Packet(p){}
    ~Dns() = default;

    bool parse(const u_char* pkt_data) override;

    QString type() const override;
    QString src() const override;
    QString dst() const override;
    QString description() const override;
    QString full_text() const override;

private:
    u_short _id;
    bool _qr;
    u_char _opcode;
    bool _aa;
    bool _tc;
    bool _rd;
    bool _ra;
    u_char _rcode;
    u_short _nq;
    u_short _na;
    u_short _nauth_rrs;
    u_short _naddt_rrs;
    u_int _qname;
    u_short _qtype;
    u_short _qclass;
};

#endif // DNS_H
