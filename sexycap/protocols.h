#ifndef PROTOCOLS_H
#define PROTOCOLS_H

#include <pcap.h>

typedef struct mac_address {
    u_char byte1;
    u_char byte2;
    u_char byte3;
    u_char byte4;
    u_char byte5;
    u_char byte6;
}mac_address;

typedef struct ethernet_header {
    mac_address saddr; // source mac address
    mac_address daddr; // destination mac address
    u_short     tof;   // type of frame
}ethernet_header;

typedef struct ipv4_address {
    u_char byte1;
    u_char byte2;
    u_char byte3;
    u_char byte4;
}ipv4_address;

typedef struct ipv4_header {
    u_char     ver_hl;         // version(4 bits) + header length(4bits)
    u_char     tos;            // type of service
    u_short    tlen;           // total length(header + data)
    u_short    identification; // identification
    u_short    flags_fo;       // flags(3 bits) + fragment offset(13 bits)
    u_char     ttl;            // time-to-live
    u_char     protocal;       // transport-layer protocol
    u_short    crc;            // header checksum
    ipv4_address saddr;          // source address
    ipv4_address daddr;          // destination address
    u_int      op_pad;         // option + padding
}ipv4_header;

typedef struct udp_header {
    u_short sport; // source port
    u_short dport; // destination port
    u_short len;   // datagram length
    u_short crc;   // checksum
}upd_header;

#endif // PROTOCOLS_H
