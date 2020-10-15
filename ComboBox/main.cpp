#include "widget.h"
#include "combobox.h"
#include "network_manager.h"
#include "netlistcombobox.h"

#include <QApplication>

#include <string>
#include <QObject>
#include <QtDBus>
#include <QListWidget>
#include <QListWidgetItem>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    QVBoxLayout layout;
    QWidget     wid;
    ComboBox*   box = new ComboBox(&wid);

    layout.addWidget(box);
    //NetListComboBox wid;
    wid.setLayout(&layout);

    wid.show();
    return a.exec();
}
/*
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    QVBoxLayout layout;
    //QWidget     wid;
    //ComboBox*   box = new ComboBox(&wid);
    //addBtn      addItemBtn;

    //layout.addWidget(box);
    //layout.addWidget(&addItemBtn);
    NetListComboBox wid;
    wid.setLayout(&layout);

    wid.show();
    return a.exec();
}
*/
