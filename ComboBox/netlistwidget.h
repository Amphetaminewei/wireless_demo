#ifndef NETLISTWIDGET_H
#define NETLISTWIDGET_H

#include <QObject>
#include <QWidget>
#include <QListWidget>

class QPushbutton;

class NetListWidget : public QListWidget
{
    Q_OBJECT
public:
    NetListWidget(QWidget* parent = nullptr);
private:
//    QListWidget* listWidget;
    QPushbutton* addOther;
};

#endif // NETLISTWIDGET_H
