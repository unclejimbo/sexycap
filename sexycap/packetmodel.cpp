#include "packetmodel.h"

void PacketModel::add_packet(Packet *packet, QString time, int length)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    _packets.append(packet);
    _timeStamps.append(time);
    _lengths.append(length);
    endInsertRows();
}

int PacketModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return _packets.size();
}

int PacketModel::columnCount(const QModelIndex& parent) const
{
    return 2 + AllRole - Qt::UserRole;
}

QVariant PacketModel::data(const QModelIndex& index, int role) const
{
    if (index.row() < 0 || index.row() >= _packets.size())
        return QVariant();

    Packet* packet = _packets.at(index.row());
    QVariant rtn;
    switch(role)
    {
    case NumRole:
        rtn = index.row();
        break;
    case TypeRole:
        while(packet->child != nullptr)
            packet = packet->child;
        rtn = packet->type();
        break;
    case TimeRole:
        rtn = _timeStamps[index.row()];
        break;
    case LenRole:
        rtn = _lengths[index.row()];
        break;
    case SrcRole:
        if (packet->child->type().compare("IPv4") == 0)
            packet = packet->child;
        rtn = packet->src();
        break;
    case DstRole:
        if (packet->child->type().compare("IPv4") == 0)
            packet = packet->child;
        rtn = packet->dst();
        break;
    case DscbRole:
        while(packet->child != nullptr)
            packet = packet->child;
        rtn = packet->description();
        break;
    default:
        rtn = QVariant();
    }
    return rtn;
}

QHash<int, QByteArray> PacketModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NumRole] = "no";
    roles[TypeRole] = "type";
    roles[TimeRole] = "time";
    roles[LenRole] = "len";
    roles[SrcRole] = "src";
    roles[DstRole] = "dst";
    roles[DscbRole] = "describe";
    return roles;
}
