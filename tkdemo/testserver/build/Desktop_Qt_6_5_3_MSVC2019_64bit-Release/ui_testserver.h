/********************************************************************************
** Form generated from reading UI file 'testserver.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TESTSERVER_H
#define UI_TESTSERVER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_testserver
{
public:
    QWidget *centralwidget;
    QWidget *widget;
    QFormLayout *formLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *startServer;
    QPushButton *stopServer;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *testserver)
    {
        if (testserver->objectName().isEmpty())
            testserver->setObjectName("testserver");
        testserver->resize(1000, 500);
        testserver->setMinimumSize(QSize(1000, 500));
        testserver->setMaximumSize(QSize(1000, 500));
        centralwidget = new QWidget(testserver);
        centralwidget->setObjectName("centralwidget");
        widget = new QWidget(centralwidget);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(90, 100, 700, 350));
        widget->setMinimumSize(QSize(700, 350));
        widget->setMaximumSize(QSize(700, 350));
        formLayout = new QFormLayout(widget);
        formLayout->setObjectName("formLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        startServer = new QPushButton(widget);
        startServer->setObjectName("startServer");

        horizontalLayout->addWidget(startServer);

        stopServer = new QPushButton(widget);
        stopServer->setObjectName("stopServer");

        horizontalLayout->addWidget(stopServer);


        formLayout->setLayout(0, QFormLayout::FieldRole, horizontalLayout);

        testserver->setCentralWidget(centralwidget);
        menubar = new QMenuBar(testserver);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1000, 24));
        testserver->setMenuBar(menubar);
        statusbar = new QStatusBar(testserver);
        statusbar->setObjectName("statusbar");
        testserver->setStatusBar(statusbar);

        retranslateUi(testserver);

        QMetaObject::connectSlotsByName(testserver);
    } // setupUi

    void retranslateUi(QMainWindow *testserver)
    {
        testserver->setWindowTitle(QCoreApplication::translate("testserver", "testserver", nullptr));
        startServer->setText(QCoreApplication::translate("testserver", "\345\274\200\345\247\213", nullptr));
        stopServer->setText(QCoreApplication::translate("testserver", "\347\273\223\346\235\237", nullptr));
    } // retranslateUi

};

namespace Ui {
    class testserver: public Ui_testserver {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TESTSERVER_H
