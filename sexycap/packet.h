#ifndef PACKET_H
#define PACKET_H

#include <QObject>
#include <pcap.h>

class Packet : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString time READ time)
    Q_PROPERTY(int len READ len)
    Q_PROPERTY(QString src READ src)
    Q_PROPERTY(QString dst READ dst)
    Q_PROPERTY(QString info READ info)

public:
    Packet(const QString& timestr, int len, QObject* parent = 0);
    virtual ~Packet();

    QString time() const;
    int len() const;
    QString src() const;
    QString dst() const;
    virtual QString info() const = 0;

    Packet* next;

    virtual void parse(const u_char* pkt_data) = 0;

protected:
    QString _timestr;
    int _len;
    QString _src;
    QString _dst;
};

#endif // PACKET_H
