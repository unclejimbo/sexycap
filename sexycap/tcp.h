#ifndef TCP_H
#define TCP_H

#include <QString>
#include "packet.h"

class Tcp : public Packet
{
public:
    explicit Tcp(Packet* p): Packet(p){}
    ~Tcp() = default;

    bool parse(const u_char *pkt_data) override;

    QString type() const override;
    QString src() const override;
    QString dst() const override;
    QString description() const override;
    QString full_text() const override;

private:
    u_short _sport;
    u_short _dport;
    u_int _seq_num;
    u_int _ack_num;
    u_char _offset;
    bool _urg;
    bool _ack;
    bool _psh;
    bool _rst;
    bool _syn;
    bool _fin;
    u_short _win;
};

#endif // TCP_H
