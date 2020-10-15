#include "netlistcombobox.h"

#include <QDebug>

NetListComboBox::NetListComboBox(QWidget *parent):
    QWidget(parent), Ui::Form()
{
    setupUi(this);
    showButton->setFixedSize(40, 40);
    listWidget->hide();
    otherButton->hide();

    widget->installEventFilter(this);
    //label->installEventFilter(this);
    connect(showButton, &QPushButton::clicked,
            this, &NetListComboBox::clickShow);
}

bool NetListComboBox::eventFilter (QObject *watched, QEvent *event)
{
    if(event->type() == QEvent::MouseButtonPress) {
        if(watched == widget) {
            showOrHide();
            return true;
        }
    }
    return QWidget::eventFilter(watched, event);
}

void NetListComboBox::clickShow()
{
    showOrHide();
}

void NetListComboBox::setCheckTest(QString text)
{
    label->setText(text);
}

void NetListComboBox::showOrHide()
{
    if (listWidget->isHidden()) {
        listWidget->show();
        otherButton->show();
    }
    else {
        listWidget->hide();
        otherButton->hide();
    }
}
