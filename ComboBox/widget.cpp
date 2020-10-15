#include "widget.h"
#include "network_manager.h"

#include <QMessageBox>
#include <QtDBus/QtDBus>
#include <QDebug>

NetWidget::NetWidget(QWidget *parent, ComboBox *box) : QWidget(parent)
{
    parentBox =     box;
    ssidLabel =     new QLabel(this);
    strengthLabel = new QLabel(this);
    macLabel =      new QLabel(this);
    connectBtn =    new QPushButton(this);
    connBtnPwd =    new QPushButton(this);
    pwdEdit =       new QLineEdit(this);

    labelLayout = new QVBoxLayout;
    btnLayout =   new QVBoxLayout;
    layout =      new QHBoxLayout;

    pwdEdit->setEchoMode(QLineEdit::Password);

    strengthLabel->hide();
    macLabel->hide();
    connBtnPwd->hide();
    pwdEdit->hide();

    labelLayout->addWidget(ssidLabel);
    labelLayout->addWidget(strengthLabel);
    labelLayout->addWidget(macLabel);
    labelLayout->addWidget(pwdEdit);

    btnLayout->addWidget(connectBtn);
    btnLayout->addWidget(connBtnPwd);

    layout->addLayout(labelLayout);
    layout->addLayout(btnLayout);

    this->setLayout(layout);

    QObject::connect(NetWidget::connectBtn, &QPushButton::clicked, this, &NetWidget::connBtn);
    QObject::connect(NetWidget::connBtnPwd, &QPushButton::clicked, this, &NetWidget::connBtnWithPwd);

    connectBtn->setText("加入网络");
    connBtnPwd->setText("连接");
    connectBtn->setFixedWidth(80);
    connBtnPwd->setFixedWidth(80);
}

void NetWidget::mouseReleaseEvent(QMouseEvent*){}

void NetWidget::mousePressEvent(QMouseEvent*)
{
    macLabel->hide();
    connectBtn->hide();
    strengthLabel->hide();
    pwdEdit->show();
    connBtnPwd->show();
}

void NetWidget::leaveEvent(QEvent *event)
{
    strengthLabel->hide();
    macLabel->hide();
    pwdEdit->hide();
    connBtnPwd->hide();
    connectBtn->show();
    QDBusConnection::systemBus().connect(NM, ap,
                                         NM_AP,
                                         "PropertiesChanged",
                                         this->getParentBox(),
                                         SLOT(updateNetList()));
    QDBusConnection::systemBus().connect(NM, device,
                                         NM_DEVICE_WIFI,
                                         "AccessPointAdded",
                                         this->getParentBox(), SLOT(updateNetList()));

}

void NetWidget::enterEvent(QEvent *event)
{
    strengthLabel->show();
    macLabel->show();
    QDBusConnection::systemBus().disconnect(NM, ap,
                                           NM_AP,
                                           "PropertiesChanged",
                                           this->getParentBox(),
                                           SLOT(updateNetList()));
    QDBusConnection::systemBus().disconnect(NM, device,
                                         NM_DEVICE_WIFI,
                                         "AccessPointAdded",
                                         this->getParentBox(), SLOT(updateNetList()));
}

void NetWidget::connBtn()
{
    macLabel->hide();
    connectBtn->hide();
    strengthLabel->hide();
    pwdEdit->show();
    connBtnPwd->show();
}

void NetWidget::connBtnWithPwd()
{
    connectBtn->show();
    connBtnPwd->hide();
    pwdEdit->hide();
    QByteArray ssid = ssidLabel->text().toLatin1();
    QByteArray pwd = pwdEdit->text().toLatin1();
    int results = system("nmcli dev wifi connect \"" +
                         ssid + "\" password " + pwd);
    if(results != 0)
    {
        QMessageBox error;
        error.critical(this, "Connect failde", "password error");
    }
}

void NetWidget::setSsid(QString _ssid)
{
    ssidLabel->setText(_ssid);
}

void NetWidget::setMAC(QString _MAC)
{
    macLabel->setText("物理地址："+_MAC);
}

void NetWidget::setStrength(QString _strength)
{
    strengthLabel->setText("信号强度："+_strength);
}

void NetWidget::setDevicePath(QString _devicePath)
{
    device = _devicePath;
}

void NetWidget::setApPath(QString _apPath)
{
    ap = _apPath;
}

QString NetWidget::getSsid()
{
    return ssidLabel->text();
}

ComboBox* NetWidget::getParentBox()
{
    return parentBox;
}
