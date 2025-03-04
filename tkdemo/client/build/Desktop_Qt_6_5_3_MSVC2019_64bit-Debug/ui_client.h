/********************************************************************************
** Form generated from reading UI file 'client.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIENT_H
#define UI_CLIENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_client
{
public:
    QWidget *centralwidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLineEdit *portLineEdit;
    QLineEdit *hostLineEdit;
    QPushButton *connectButton;
    QPushButton *sendButton;
    QLineEdit *lineEdit_3;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *client)
    {
        if (client->objectName().isEmpty())
            client->setObjectName("client");
        client->resize(600, 600);
        client->setMinimumSize(QSize(600, 600));
        client->setMaximumSize(QSize(600, 600));
        centralwidget = new QWidget(client);
        centralwidget->setObjectName("centralwidget");
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(140, 110, 301, 261));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        portLineEdit = new QLineEdit(verticalLayoutWidget);
        portLineEdit->setObjectName("portLineEdit");

        verticalLayout->addWidget(portLineEdit);

        hostLineEdit = new QLineEdit(verticalLayoutWidget);
        hostLineEdit->setObjectName("hostLineEdit");

        verticalLayout->addWidget(hostLineEdit);

        connectButton = new QPushButton(verticalLayoutWidget);
        connectButton->setObjectName("connectButton");

        verticalLayout->addWidget(connectButton);

        sendButton = new QPushButton(verticalLayoutWidget);
        sendButton->setObjectName("sendButton");

        verticalLayout->addWidget(sendButton);

        lineEdit_3 = new QLineEdit(verticalLayoutWidget);
        lineEdit_3->setObjectName("lineEdit_3");

        verticalLayout->addWidget(lineEdit_3);

        client->setCentralWidget(centralwidget);
        menubar = new QMenuBar(client);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 600, 24));
        client->setMenuBar(menubar);
        statusbar = new QStatusBar(client);
        statusbar->setObjectName("statusbar");
        client->setStatusBar(statusbar);

        retranslateUi(client);

        QMetaObject::connectSlotsByName(client);
    } // setupUi

    void retranslateUi(QMainWindow *client)
    {
        client->setWindowTitle(QCoreApplication::translate("client", "client", nullptr));
        portLineEdit->setPlaceholderText(QCoreApplication::translate("client", "\350\276\223\345\205\245\346\234\215\345\212\241\345\231\250\345\234\260\345\235\200", nullptr));
        hostLineEdit->setPlaceholderText(QCoreApplication::translate("client", "\350\276\223\345\205\245\346\234\215\345\212\241\345\231\250\347\253\257\345\217\243", nullptr));
        connectButton->setText(QCoreApplication::translate("client", "\350\277\236\346\216\245", nullptr));
        sendButton->setText(QCoreApplication::translate("client", "\345\217\221\351\200\201", nullptr));
        lineEdit_3->setPlaceholderText(QCoreApplication::translate("client", "\350\276\223\345\205\245\350\246\201\345\217\221\351\200\201\347\232\204\346\266\210\346\201\257", nullptr));
    } // retranslateUi

};

namespace Ui {
    class client: public Ui_client {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENT_H
