#ifndef IPV4_H
#define IPV4_H

#include <QString>
#include "packet.h"

class Ipv4 : public Packet
{
public:
    explicit Ipv4(Packet* p): Packet(p){}
    ~Ipv4() = default;

    bool parse(const u_char* pkt_data) override;

    QString type() const override;
    QString src() const override;
    QString dst() const override;
    QString description() const override;
    QString full_text() const override;

private:
    u_char _version;
    u_char _hdr_len;
    u_short _tlen;
    bool _df;
    bool _mf;
    u_short _offset;
    u_char _ttl;
    u_char _protocol;
    QString _saddr;
    QString _daddr;
};

#endif // IPV4_H
