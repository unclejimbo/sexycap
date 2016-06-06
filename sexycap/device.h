#ifndef DEVICEMODEL_H
#define DEVICEMODEL_H

#include <QObject>

class Device : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name)
    Q_PROPERTY(QString description READ description)

public:
    Device(QObject* parent = 0);
    Device(const QString& name, const QString& description, QObject* parent = 0);

    QString name() const;

    QString description() const;

private:
    QString _name;
    QString _description;
};

#endif // DEVICEMODEL_H
