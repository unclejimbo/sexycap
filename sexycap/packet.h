#ifndef PACKET_H
#define PACKET_H

#include <QString>
#include <pcap/pcap.h>

class Packet
{
public:
    explicit Packet(Packet* p):
        parent(p), child(nullptr)
    {

    }
    virtual ~Packet()
    {
        if (child != nullptr)
            delete child;
    }

    virtual bool parse(const u_char* pkt_data) = 0;

    virtual QString type() const = 0;
    virtual QString src() const = 0;
    virtual QString dst() const = 0;
    virtual QString description() const = 0;
    virtual QString full_text() const = 0;

    Packet* child;
    Packet* parent;
};

#endif // PACKET_H
