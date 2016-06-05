#include "devicemodel.h"

DeviceModel::DeviceModel(QObject *parent)
    :QObject(parent)
{

}

DeviceModel::DeviceModel(const QString& name, const QString& description, QObject *parent)
    :QObject(parent)
{
    _name = name;
    _description = description;
}

QString DeviceModel::name() const
{
    return _name;
}

QString DeviceModel::description() const
{
    return _description;
}
