#include "packet.h"

Packet::Packet(const QString& timestr, int len, QObject* parent):
    _timestr(timestr), _len(len), QObject(parent)
{

}

Packet::~Packet()
{

}

QString Packet::time() const
{
    return _timestr;
}

int Packet::len() const
{
    return _len;
}

QString Packet::src() const
{
    return _src;
}

QString Packet::dst() const
{
    return _dst;
}
