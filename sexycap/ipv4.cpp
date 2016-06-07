#include "ipv4.h"
#include "protocols.h"
#include <iostream>

bool Ipv4::parse(const u_char* pkt_data)
{
    auto hdr = reinterpret_cast<const ipv4_header*>(pkt_data);

    _version = (hdr->ver_hl & 0xf0) >> 4;
    _hdr_len = hdr->ver_hl & 0x0f;
    _tlen = ntohs(hdr->tlen);
    _df = hdr->flags_fo & 0x4000;
    _mf = hdr->flags_fo & 0x2000;
    _ttl = hdr->ttl;
    _protocol = hdr->protocol;
    _saddr = ipv42qstr(hdr->saddr);
    _daddr = ipv42qstr(hdr->daddr);

    switch(_protocol) {
    case 0x01: // ICMP
    case 0x06: // TCP
    case 0x11: // UDP
        break;
    default:
        next = nullptr;
    }

    return true;
}
