#ifndef NETLISTCOMBOBOX_H
#define NETLISTCOMBOBOX_H

#include <QObject>
#include <QWidget>
#include "ui_NetListComboBox.h"
#include "netdata.h"

class NetListComboBox : public QWidget, public Ui::Form
{
    Q_OBJECT
public:
    explicit NetListComboBox(QWidget *parent = nullptr);
    void initList(NetData);
    void addAp(QString);
    void removeAp(QString);
    void propertyChange(std::pair<QString, QString>);
private slots:
    void clickShow();
    void setCheckTest(QString);
private:
    void showOrHide();
protected:
    bool eventFilter(QObject *watched, QEvent *event);
signals:

};

#endif // NETLISTCOMBOBOX_H
