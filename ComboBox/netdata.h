#ifndef NETDATA_H
#define NETDATA_H

#include <QString>

class NetData
{
public:
    QString ssid;
    QString strength;
    QString mac;
    QString apPath;
    QString devicePath;
    uint    wpa;
    uint    rsn;
    NetData (QString _ssid, QString _strength, QString _mac, QString _apPath,
             QString _devicePath, uint _wpa, uint _rsn) :
        ssid(_ssid), strength(_strength), mac(_mac), apPath(_apPath),
        devicePath(_devicePath), wpa(_wpa), rsn(_rsn){}

    NetData():ssid(""), strength(""), mac(""),
        apPath(""), devicePath(""), wpa(0), rsn(0){}
};

#endif // NETDATA_H
