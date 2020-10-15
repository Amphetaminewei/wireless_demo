#ifndef NM_H
#define NM_H
#include <QtDBus/QtDBus>
#include <QObject>
#include <QString>

#include "combobox.h"
#include "netdata.h"

#define DEVICE_TYPE_WIFI 2
#define NM  "org.freedesktop.NetworkManager"
#define NM_PATH  "/org/freedesktop/NetworkManager"
#define NM_DEVICE  "org.freedesktop.NetworkManager.Device"
#define NM_DEVICE_WIFI  "org.freedesktop.NetworkManager.Device.Wireless"
#define NM_AP  "org.freedesktop.NetworkManager.AccessPoint"

class NetworkManager : public QObject
{
    Q_OBJECT
public:
    NetworkManager(ComboBox*, QObject* parent = nullptr);

    void             initNetList();
    QString          devicePath;
    QString          apPath;
    QVector<NetData> getNetList();

public slots:
    void addDevice(QDBusObjectPath);
    void addAccessPoint(QDBusObjectPath);
    void removeDevice(QDBusObjectPath);
    void removeAccessPoint(QDBusObjectPath);
    void apPropertyChanged(QVariantMap);
    void testSlots();

private:
    QVector<NetData> netList;
    ComboBox        *box;
    QVector<QString> parserDbusMsg(const QDBusMessage& msg);

signals:
    void deviceAdded(QString);
    void accessPointAdded(QString);
    void deviceRemove(QString);
    void accessPointRemove(QString);
    void propertyChanged(std::pair<QString, QString>);
};

#endif // NM_H
