#ifndef OMBOBOX_H
#define OMBOBOX_H

#include "widget.h"

#include <QComboBox>
#include <QObject>
#include <QtDBus>

class QListWidget;
class QPushButton;
class ComboBox : public QComboBox
{
    Q_OBJECT
public:
    ComboBox(QWidget *parent = nullptr);
    //~combobox();
    QListWidget *getListWidget();
    void         addWid(QString, QString, QString, QString, QString);
    void         testSig(QString);
    void         testSignal(std::pair<QString, QString>);
public slots:
    void         updateNetList();
private:
    QListWidget* listWidget;
};

#endif // OMBOBOX_H
