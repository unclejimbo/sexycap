#include "ethernet.h"
#include "protocols.h"
#include "ipv4.h"
#include "arp.h"

bool Ethernet::parse(const u_char *pkt_data)
{
    auto hdr = reinterpret_cast<const ethernet_header*>(pkt_data);
    _saddr = mac2qstr(hdr->saddr);
    _daddr = mac2qstr(hdr->daddr);
    _tof = ntohs(hdr->tof);

    switch(_tof) {
    case 0x0800: // IPv4
        next = new Ipv4();
        next->parse(pkt_data + 14);
        break;
    case 0x0806: // ARP
        next = new Arp();
        next->parse(pkt_data + 14);
        break;
    default:
        next = nullptr;
    }

    return true;
}
