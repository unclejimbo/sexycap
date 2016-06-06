#include "packet.h"

#include <QTextStream>

Packet::Packet(QObject *parent) : QObject(parent)
{

}

Packet::Packet(const pcap_pkthdr* header, const u_char* pkt_data):
    _header(header), _pkt_data(pkt_data)
{

}

void Packet::parse()
{
    // parse time
    time_t local_tv_sec = _header->ts.tv_sec;
    struct tm ltime;
    localtime_s(&ltime, &local_tv_sec);
    char timestr[16];
    strftime(timestr, sizeof(timestr), "%H:%M:%S", &ltime);
    QTextStream(&_timeStr) << timestr << "." << _header->ts.tv_usec;

    // parse header length
    _header_length = _header->len;

    // parse packet length
    _packet_length = _header->caplen;
}

QString Packet::time() const
{
    return _timeStr;
}

int Packet::headerLength() const
{
    return _header_length;
}

int Packet::packetLength() const
{
    return _packet_length;
}
