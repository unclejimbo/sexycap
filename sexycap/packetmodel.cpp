#include "packetmodel.h"

PacketModel::PacketModel(QString& time, int len, Packet* pkt, QObject* parent):
    _time(time), _len(len), _pkt(pkt), QObject(parent)
{

}

PacketModel::~PacketModel()
{
    free(_pkt);
}

QString PacketModel::time() const
{
    return QString();
}

int PacketModel::len() const
{
    return 0;
}

QString PacketModel::src() const
{
    return QString();
}

QString PacketModel::dst() const
{
    return QString();
}

QString PacketModel::type() const
{
    return QString();
}

QString PacketModel::info() const
{
    return QString();
}

QString PacketModel::display() const
{
    return QString();
}
