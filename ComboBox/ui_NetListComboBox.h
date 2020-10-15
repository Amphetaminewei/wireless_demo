/********************************************************************************
** Form generated from reading UI file 'NetListComboBox.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NETLISTCOMBOBOX_H
#define UI_NETLISTCOMBOBOX_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QWidget     *widget;
    QHBoxLayout *horizontalLayout;
    QLabel      *label;
    QPushButton *showButton;
    QWidget     *widFillList;
    QListWidget *listWidget;
    QPushButton *otherButton;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QString::fromUtf8("Form"));
        Form->resize(400, 300);
        verticalLayout_2 = new QVBoxLayout(Form);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        widget = new QWidget(Form);
        widget->setObjectName(QString::fromUtf8("widget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        widget->setStyleSheet(QString::fromUtf8("background-color: rgb(238, 238, 238);"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        label->setMaximumSize(QSize(178, 16777215));
        label->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(label);

        showButton = new QPushButton(widget);
        showButton->setObjectName(QString::fromUtf8("showButton"));

        horizontalLayout->addWidget(showButton);


        verticalLayout->addWidget(widget);

        widFillList = new QWidget(Form);
        widFillList->setObjectName(QString::fromUtf8("widFillList"));

        verticalLayout->addWidget(widFillList);

        listWidget = new QListWidget(Form);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(listWidget->sizePolicy().hasHeightForWidth());
        listWidget->setSizePolicy(sizePolicy2);

        verticalLayout->addWidget(listWidget);


        verticalLayout_2->addLayout(verticalLayout);

        otherButton = new QPushButton(Form);
        otherButton->setObjectName(QString::fromUtf8("otherButton"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(otherButton->sizePolicy().hasHeightForWidth());
        otherButton->setSizePolicy(sizePolicy3);

        verticalLayout_2->addWidget(otherButton);


        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QApplication::translate("Form", "Form", nullptr));
        label->setText(QApplication::translate("Form", "\350\257\267\351\200\211\346\213\251\347\275\221\347\273\234", nullptr));
        showButton->setText(QApplication::translate("Form", "show", nullptr));
        otherButton->setText(QApplication::translate("Form", "\345\212\240\345\205\245\345\205\266\345\256\203\347\275\221\347\273\234", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NETLISTCOMBOBOX_H
