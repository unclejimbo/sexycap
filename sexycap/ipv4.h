#ifndef IPV4_H
#define IPV4_H

#include "packet.h"

class Ipv4 : public Packet
{
    Q_OBJECT

public:
    Ipv4(const QString& timestr, int len, QObject* parent = 0);

    QString info() const override;
    void parse(const u_char* pkt_data) override;
};

#endif // IPV4_H
