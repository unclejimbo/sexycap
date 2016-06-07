#include "arp.h"
#include "protocols.h"

bool Arp::parse(const u_char *pkt_data)
{
    auto hdr = reinterpret_cast<const arp_header*>(pkt_data);

    _htype = ntohs(hdr->htype);
    _ptype = ntohs(hdr->ptype);
    _hlen = hdr->hlen;
    _plen = hdr->plen;
    _operation = ntohs(hdr->operation);
    _sha = mac2qstr(hdr->sha);
    _spa = ipv42qstr(hdr->spa);
    _tha = mac2qstr(hdr->tha);
    _tpa = ipv42qstr(hdr->tpa);

    next = nullptr;

    return true;
}
