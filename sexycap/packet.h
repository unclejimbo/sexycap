#ifndef PACKET_H
#define PACKET_H

#include <pcap/pcap.h>

class Packet
{
public:
    Packet() = default;
    virtual ~Packet()
    {
        if (next != nullptr)
            free(next);
    }

    virtual bool parse(const u_char* pkt_data) = 0;
    Packet* next;
};

#endif // PACKET_H
