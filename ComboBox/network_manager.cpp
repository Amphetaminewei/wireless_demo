#include "network_manager.h"
#include "netdata.h"

#include <QtDBus/QtDBus>
#include <QObject>

NetworkManager::NetworkManager(ComboBox* _combobox, QObject* parent):
    QObject(parent)
{
    //删
    this->box = _combobox;
    initNetList();
}
void NetworkManager::initNetList()
{
    //创建networkmanager的接口并拉取设备列表
    QDBusConnection bus = QDBusConnection::systemBus();
    QDBusInterface manager(NM, NM_PATH, NM, bus);

    QVector<QString> deviceList = parserDbusMsg(manager.call("GetDevices"));

    QDBusConnection::systemBus().connect(NM, NM_PATH, NM,
                                         "DeviceAdded", this,
                                         SLOT(addDevice(QDBusObjectPath)));
    QDBusConnection::systemBus().connect(NM, NM_PATH, NM,
                                         "DeviceRemoved", this,
                                         SLOT(removeDevice(QDBusObjectPath)));

    // 遍历搜索类型为无线网卡的设备，获取设备类型，设备类型为2的是无线网卡
    for(auto devicePath = deviceList.begin(); devicePath != deviceList.end(); ++devicePath)
    {
        QDBusInterface deviceInterface(NM, *devicePath, NM_DEVICE, bus);
        uint deviceType = deviceInterface.property("DeviceType").value<uint>();
        if(deviceType != DEVICE_TYPE_WIFI)
            continue;
        //删掉
        QDBusConnection::systemBus().connect(NM, *devicePath,
                                             NM_DEVICE_WIFI,
                                             "AccessPointAdded",
                                             this->box, SLOT(updateNetList()));
        //监听新AP
        QDBusConnection::systemBus().connect(NM, *devicePath, NM_DEVICE_WIFI,
                                             "AccessPointAdded", this,
                                             SLOT(addAccessPoint(QDBusObjectPath)));
        //删掉
        QDBusConnection::systemBus().connect(NM, *devicePath, NM_DEVICE_WIFI,
                                             "AccessPointRemoved", this,
                                             SLOT(removeAccessPoint(QDBusObjectPath)));

        //当前设备为无线网卡时，拉取ap列表
        QDBusInterface   wireless(NM, *devicePath, NM_DEVICE_WIFI, bus);
        QVector<QString> apList = parserDbusMsg(
                                  wireless.call("GetAccessPoints"));

        for(auto apPath = apList.begin(); apPath != apList.end(); ++apPath) {
            QDBusConnection::systemBus().connect(NM, *apPath, NM_AP,
                                                 "PropertiesChanged",
                                                 this->box, SLOT(updateNetList()));
            //创建连接监听ap强度的变化
            QDBusConnection::systemBus().connect(NM, *apPath, NM_AP,
                                                 "PropertiesChanged",
                                                 this, SLOT(apPropertyChanged(QVariantMap)));

            QDBusInterface ap(NM, *apPath, NM_AP, bus);

            //uchar类型不能直接转换成QString，我这里是将它先转为int再从int到QString
            unsigned char  str = ap.property("Strength").value<uchar>();
            int            strInint = (int)str;

            QString        ssid = ap.property("Ssid").value<QByteArray>();
            QString        strength = QString::number(strInint);
            QString        mac = ap.property("HwAddress").value<QString>();
            uint           wpa = ap.property("WpaFlags").value<uint>();
            uint           rsn = ap.property("RsnFlags").value<uint>();

            //保存所有的Ssid等信息，如果有相同的ssid，则保存信号最强那个
            if(netList.empty())
            {
                netList.push_back(NetData(ssid, strength, mac, *apPath,
                                          *devicePath, wpa, rsn));
                continue;
            }
            auto begin = netList.begin();
            for(; begin != netList.end(); ++begin) {
                if(begin->ssid == ssid) {
                    if(strength.toInt() <= begin->strength.toInt())
                        break;
                    else {
                        begin->strength = strength;
                        begin->mac = mac;
                        break;
                    }
                }
            }
            if(begin == netList.end())
                netList.push_back(NetData(ssid, strength, mac, *apPath,
                                          *devicePath, wpa, rsn));
        }

        //这里删掉
        for(auto begin = netList.begin(); begin != netList.end(); ++begin) {
            box->addWid(begin->ssid, begin->strength,
                        begin->mac, *devicePath, begin->apPath);
        }
        return;
    }
}

QVector<QString> NetworkManager::parserDbusMsg(const QDBusMessage& msg)
{
    /*
     * 解析收到的从dbus获取的device和ap，将其解析成QVector<QString>
     * 通过上面创建的interface接口来调用NetworkManager中的方法从而获取网卡设备
     * 但是这里拉取到的设备列表是QDBusMessage类型，这个类型保存的数据类似以下形式：
     *QDBusMessage(type=MethodReturn, service=":1.9", signature="ao",
     * contents=([Argument: ao {[ObjectPath: /org/freedesktop/
     * NetworkManager/Devices/6]}]) )
     * 属于套娃类型，而我们想要的设备信息被层层包裹在其中，通过QDBusMessage提供
     * 的arguments函数可以将其转化为QList<QVariant>类型，此时数据为以下形式：
     * (QVariant(QDBusArgument, ))
     * 我们关心的设备路径在QDBusArgument中，因此还要提取出QList中的QVariant，
     * 也就是列表中唯一的元素，再通过value来取得其中的QDBusArgument对象，也就是
     * 代码中的dbusArgs对象，通过其成员函数可以将其转为Array，并获取其中的ObjectPath
     * 而ObjectPath提供了path()成员来帮助我们取出其中的设备路径，并将其保存在vector中
     * 还可以使用类似这种形式来获取call返回的结果
     * QDBusReply<QVector<QString>> reply = manager.call("GetAllDevices");
     * 但是QDBusReply<QVector<QString>>中类型和返回结果的适配还有问题，我就没改
    */
    QList<QVariant>         variants = msg.arguments();
    const QVariant         &first = variants.at(0);
    const QDBusArgument    &dbusArgs = first.value<QDBusArgument>();
    QDBusObjectPath         path;
    QVector<QString>        pathList;

    dbusArgs.beginArray();
    for (int i = 0; !dbusArgs.atEnd(); ++i) {
        dbusArgs >> path;
        pathList.push_back(path.path());
    }
    dbusArgs.endArray();
    return pathList;
}

QVector<NetData> NetworkManager::getNetList()
{
    return netList;
}

void NetworkManager::addDevice(QDBusObjectPath newPath)
{
    QString path = newPath.path();
    emit deviceAdded(path);
}

void NetworkManager::addAccessPoint(QDBusObjectPath newPath)
{
    QString path = newPath.path();
    emit accessPointAdded(path);
}

void NetworkManager::removeDevice(QDBusObjectPath newPath)
{
    QString path = newPath.path();
    emit deviceRemove(path);
}

void NetworkManager::removeAccessPoint(QDBusObjectPath newPath)
{
    QString path = newPath.path();
    emit accessPointRemove(path);
}

void NetworkManager::apPropertyChanged(QVariantMap changes)
{
    QString key = changes.begin().key();

    if ( key == "Strength") {
        unsigned char str = changes.begin().value().value<uchar>();
        int           strInt = (int)str;
        QString       value = QString::number(strInt);

        emit propertyChanged(std::make_pair(key, value));
    }
    else {
        QString value = QString::number(
                    changes.begin().value().value<uint>());
        emit propertyChanged(std::make_pair(key, value));
    }
}
void NetworkManager::testSlots()
{
    qDebug() << "is ok";
}
