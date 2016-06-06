#ifndef ETHERNET_H
#define ETHERNET_H

#include "packet.h"

class Ethernet : public Packet
{
    Q_OBJECT

public:
    Ethernet(const QString& timeStr, int len, QObject* parent = 0);
    ~Ethernet();

    QString info() const override;
    void parse(const u_char *pkt_data) override;
};

#endif // ETHERNET_H
