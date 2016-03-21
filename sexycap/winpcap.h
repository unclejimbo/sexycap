#ifndef WINPCAP_H
#define WINPCAP_H

#include <QObject>

#include "devicemodel.h"

class WinPcap : public QObject
{
    Q_OBJECT

public:
    WinPcap(QObject* parent = 0);

    void readDevices();
    const QList<QObject*> devices();

private:
    QList<QObject*> _devices;
};

#endif // WINPCAP_H
