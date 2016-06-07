#ifndef PROTOCOLS_H
#define PROTOCOLS_H

#include <QString>
#include <pcap/pcap.h>

typedef struct mac_address {
    u_char byte1;
    u_char byte2;
    u_char byte3;
    u_char byte4;
    u_char byte5;
    u_char byte6;
}mac_address;

inline QString mac2qstr(mac_address mac)
{
    return QString("%1:%2:%3:%4:%5:%6")
            .arg(mac.byte1, 2, 16, QLatin1Char('0'))
            .arg(mac.byte2, 2, 16, QLatin1Char('0'))
            .arg(mac.byte3, 2, 16, QLatin1Char('0'))
            .arg(mac.byte4, 2, 16, QLatin1Char('0'))
            .arg(mac.byte5, 2, 16, QLatin1Char('0'))
            .arg(mac.byte6, 2, 16, QLatin1Char('0'));
}

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

inline QString ipv42qstr(ipv4_address ip)
{
    return QString("%1%2%3%4")
            .arg(ip.byte1)
            .arg(ip.byte2)
            .arg(ip.byte3)
            .arg(ip.byte4);
}

typedef struct ipv4_header {
    u_char       ver_hl;         // version(4 bits) + header length(4bits)
    u_char       tos;            // type of service
    u_short      tlen;           // total length(header + data)
    u_short      identification; // identification
    u_short      flags_fo;       // flags(3 bits) + fragment offset(13 bits)
    u_char       ttl;            // time-to-live
    u_char       protocol;       // transport-layer protocol
    u_short      crc;            // header checksum
    ipv4_address saddr;          // source address
    ipv4_address daddr;          // destination address
    u_int        op_pad;         // option + padding
}ipv4_header;


typedef struct arp_header {
    u_short      htype;     // hardware type
    u_short      ptype;     // protocol type
    u_char       hlen;      // hardware address length
    u_char       plen;      // protocol address length
    u_short      operation; // operation code
    mac_address  sha;       // sender hardware address
    ipv4_address spa;       // sender protocol address
    mac_address  tha;       // target hardware address
    ipv4_address tpa;       // target protocol address
}arp_header;

typedef struct icmp_header {
    u_char  type; // type of the icmp
    u_char  code; // code for sending the icmp
    u_short crc;  // checksum
    u_int   rest; // rest of the header
}icmp_header;

typedef struct udp_header {
    u_short sport; // source port
    u_short dport; // destination port
    u_short len;   // datagram length
    u_short crc;   // checksum
}upd_header;

typedef struct tcp_header {
    u_short sport;   // source port
    u_short dport;   // destination port
    u_int   seq_num; // sequence number
    u_int   ack_num; // acknowledgment number
    u_char  offset;  // data offset
    u_char  byte1;   // reserved
    u_short ctrl;    // control bits
    u_short win;     // window size
    u_short crc;     // checksum
}tcp_header;

#endif // PROTOCOLS_H
