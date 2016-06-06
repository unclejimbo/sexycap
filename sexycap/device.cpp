#include "device.h"

Device::Device(QObject *parent)
    :QObject(parent)
{

}

Device::Device(const QString& name, const QString& description, QObject *parent)
    :QObject(parent)
{
    _name = name;
    _description = description;
}

QString Device::name() const
{
    return _name;
}

QString Device::description() const
{
    return _description;
}
