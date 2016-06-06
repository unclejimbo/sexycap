#ifndef PACKET_H
#define PACKET_H

#include <QObject>
#include <pcap/pcap.h>

class Packet : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString time READ time)
    Q_PROPERTY(int headerLength READ headerLength)
    Q_PROPERTY(int packetLength READ packetLength)

public:
    explicit Packet(QObject *parent = 0);
    Packet(const pcap_pkthdr* header, const u_char* pkt_data);

    virtual void parse();

    QString time() const;
    int headerLength() const;
    int packetLength() const;

private:
    const pcap_pkthdr* _header;
    const u_char* _pkt_data;
    QString _timeStr;
    int _header_length;
    int _packet_length;
};

#endif // PACKET_H
