#include "combobox.h"
#include "widget.h"
#include "network_manager.h"

#include <QComboBox>
#include <QObject>
#include <QListWidget>
#include <QListWidgetItem>


ComboBox::ComboBox(QWidget *parent) : QComboBox(parent)
{

    listWidget = new QListWidget(this);
    this->setModel(listWidget->model());
    this->setView(listWidget);
    this->resize(400, 100);
    //listWidget->setStyleSheet("QListWidget{color:rgb(255,255,255)}");

    //加入其它网络的按钮
    QPushButton*         addOther = new QPushButton(this);
    QListWidgetItem*     item0 = new QListWidgetItem();
    addOther->setText("加入其它网络");
    listWidget->addItem(item0);
    item0->setSizeHint(QSize(item0->sizeHint().width(), 60));
    listWidget->setItemWidget(item0, addOther);

  /*//重载一下widget的mousePressEvent，让他发一个信号，这边建一个信号连接，然后改显示的文字
    connect(this, QOverload<int>::of(&QComboBox::currentIndexChanged),
          [=](int index){

    });*/

    NetworkManager* manager = new NetworkManager(this);

    QObject::connect(manager, &NetworkManager::deviceAdded,
                     this,    &ComboBox::testSig);
    QObject::connect(manager, &NetworkManager::accessPointAdded,
                     this,    &ComboBox::testSig);
    QObject::connect(manager, &NetworkManager::deviceRemove,
                     this,    &ComboBox::testSig);
    QObject::connect(manager, &NetworkManager::accessPointRemove,
                     this,    &ComboBox::testSig);

    QObject::connect(manager, &NetworkManager::propertyChanged,
                     this,    &ComboBox::testSignal);

    /*
    //在构建manager前设置text会被覆盖掉
    this->setEditable(true);
    QLineEdit* p=this->lineEdit();
    p->setFocusPolicy(Qt::NoFocus);
    p->setText("请选择网络");
    */
}

void ComboBox::testSig(QString data)
{
    qDebug() << data;
}

void ComboBox::testSignal(std::pair<QString, QString> data)
{
    qDebug() << data;
}

void ComboBox::updateNetList()
{
    //qDebug()<<"befor："<<listWidget->count();
    while(listWidget->count() != 1)
    {
        listWidget->takeItem(0);
    }
    //qDebug()<<"after："<<listWidget->count();
    NetworkManager warpper(this);
}

QListWidget* ComboBox::getListWidget()
{
    return listWidget;
}

void ComboBox::addWid(QString ssid, QString strength, QString mac, QString devicePath, QString apPath)
{
    NetWidget* wid = new NetWidget(this->listWidget, this);
    wid->setSsid(ssid);
    wid->setStrength(strength);
    wid->setMAC(mac);
    wid->setDevicePath(devicePath);
    wid->setApPath(apPath);
    QListWidgetItem* item = new QListWidgetItem();
    listWidget->insertItem(listWidget->count() - 1, item);
    item->setSizeHint(QSize(item->sizeHint().width(), 80));
    listWidget->setItemWidget(item, wid);
    //这个只有在item都加完之后才有效,所以应该在外面调用比较好
    //this->setCurrentIndex(-1);
}
