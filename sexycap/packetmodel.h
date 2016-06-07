#ifndef PACKETMODEL_H
#define PACKETMODEL_H

#include <QObject>
#include "packet.h"

class PacketModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString time READ time)
    Q_PROPERTY(int len READ len)
    Q_PROPERTY(QString src READ src)
    Q_PROPERTY(QString dst READ dst)
    Q_PROPERTY(QString type READ type)
    Q_PROPERTY(QString info READ info)
    Q_PROPERTY(QString display READ display)

public:
    PacketModel(QString& time, int len, Packet* pkt, QObject* parent = 0);
    ~PacketModel();

    QString time() const;
    int len() const;
    QString src() const;
    QString dst() const;
    QString type() const;
    QString info() const;
    QString display() const;

private:
    QString _time;
    int _len;
    Packet* _pkt;
};

#endif // PACKETMODEL_H
