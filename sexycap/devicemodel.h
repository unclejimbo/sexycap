#ifndef DEVICEMODEL_H
#define DEVICEMODEL_H

#include <QObject>

class DeviceModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name)
    Q_PROPERTY(QString description READ description)

public:
    DeviceModel(QObject* parent = 0);
    DeviceModel(const QString& name, const QString& description, QObject* parent = 0);

    QString name() const;
    void setName(const QString& name);

    QString description() const;
    void setDescription(const QString& description);

private:
    QString _name;
    QString _description;
};

#endif // DEVICEMODEL_H
