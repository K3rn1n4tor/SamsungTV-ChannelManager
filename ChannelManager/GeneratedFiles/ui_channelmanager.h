/********************************************************************************
** Form generated from reading UI file 'channelmanager.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHANNELMANAGER_H
#define UI_CHANNELMANAGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChannelManagerClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ChannelManagerClass)
    {
        if (ChannelManagerClass->objectName().isEmpty())
            ChannelManagerClass->setObjectName(QStringLiteral("ChannelManagerClass"));
        ChannelManagerClass->resize(600, 400);
        menuBar = new QMenuBar(ChannelManagerClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        ChannelManagerClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ChannelManagerClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        ChannelManagerClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(ChannelManagerClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        ChannelManagerClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(ChannelManagerClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ChannelManagerClass->setStatusBar(statusBar);

        retranslateUi(ChannelManagerClass);

        QMetaObject::connectSlotsByName(ChannelManagerClass);
    } // setupUi

    void retranslateUi(QMainWindow *ChannelManagerClass)
    {
        ChannelManagerClass->setWindowTitle(QApplication::translate("ChannelManagerClass", "ChannelManager", 0));
    } // retranslateUi

};

namespace Ui {
    class ChannelManagerClass: public Ui_ChannelManagerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHANNELMANAGER_H
