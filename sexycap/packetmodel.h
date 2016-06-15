#ifndef PACKETMODEL_H
#define PACKETMODEL_H

#include <QAbstractTableModel>
#include "packet.h"

class PacketModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    enum PacketRoles {
        NumRole = Qt::UserRole + 1,
        TypeRole,
        TimeRole,
        LenRole,
        SrcRole,
        DstRole,
        DscbRole,
        AllRole
    };

    explicit PacketModel(QObject* parent = 0): QAbstractTableModel(parent){}
    ~PacketModel() = default;

    void add_packet(Packet* packet, QString time, int length);
    Packet* at(int index);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role) const override;

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    QVector<Packet*> _packets;
    QVector<QString> _timeStamps;
    QVector<int> _lengths;
};

#endif // PACKETMODEL_H
