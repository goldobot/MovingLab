/********************************************************************************
** Form generated from reading UI file 'C_SerialCom.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_C_SERIALCOM_H
#define UI_C_SERIALCOM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_C_SerialCom
{
public:
    QAction *actionAbout;
    QAction *actionAboutQt;
    QAction *actionConnect;
    QAction *actionDisconnect;
    QAction *actionConfigure;
    QAction *actionClear;
    QAction *actionQuit;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *C_SerialCom)
    {
        if (C_SerialCom->objectName().isEmpty())
            C_SerialCom->setObjectName(QString::fromUtf8("C_SerialCom"));
        C_SerialCom->resize(642, 477);
        C_SerialCom->setMaximumSize(QSize(642, 477));
        actionAbout = new QAction(C_SerialCom);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionAboutQt = new QAction(C_SerialCom);
        actionAboutQt->setObjectName(QString::fromUtf8("actionAboutQt"));
        actionConnect = new QAction(C_SerialCom);
        actionConnect->setObjectName(QString::fromUtf8("actionConnect"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/connect.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionConnect->setIcon(icon);
        actionDisconnect = new QAction(C_SerialCom);
        actionDisconnect->setObjectName(QString::fromUtf8("actionDisconnect"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/disconnect.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDisconnect->setIcon(icon1);
        actionConfigure = new QAction(C_SerialCom);
        actionConfigure->setObjectName(QString::fromUtf8("actionConfigure"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images/settings.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionConfigure->setIcon(icon2);
        actionClear = new QAction(C_SerialCom);
        actionClear->setObjectName(QString::fromUtf8("actionClear"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/images/clear.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionClear->setIcon(icon3);
        actionQuit = new QAction(C_SerialCom);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/images/application-exit.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionQuit->setIcon(icon4);
        centralWidget = new QWidget(C_SerialCom);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        C_SerialCom->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(C_SerialCom);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        C_SerialCom->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(C_SerialCom);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        C_SerialCom->setStatusBar(statusBar);

        mainToolBar->addAction(actionConnect);
        mainToolBar->addAction(actionDisconnect);
        mainToolBar->addAction(actionConfigure);
        mainToolBar->addAction(actionClear);

        retranslateUi(C_SerialCom);

        QMetaObject::connectSlotsByName(C_SerialCom);
    } // setupUi

    void retranslateUi(QMainWindow *C_SerialCom)
    {
        C_SerialCom->setWindowTitle(QApplication::translate("C_SerialCom", "Serial communication", nullptr));
        actionAbout->setText(QApplication::translate("C_SerialCom", "&About", nullptr));
#ifndef QT_NO_TOOLTIP
        actionAbout->setToolTip(QApplication::translate("C_SerialCom", "About program", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionAbout->setShortcut(QApplication::translate("C_SerialCom", "Alt+A", nullptr));
#endif // QT_NO_SHORTCUT
        actionAboutQt->setText(QApplication::translate("C_SerialCom", "About Qt", nullptr));
        actionConnect->setText(QApplication::translate("C_SerialCom", "C&onnect", nullptr));
#ifndef QT_NO_TOOLTIP
        actionConnect->setToolTip(QApplication::translate("C_SerialCom", "Connect to serial port", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionConnect->setShortcut(QApplication::translate("C_SerialCom", "Ctrl+O", nullptr));
#endif // QT_NO_SHORTCUT
        actionDisconnect->setText(QApplication::translate("C_SerialCom", "&Disconnect", nullptr));
#ifndef QT_NO_TOOLTIP
        actionDisconnect->setToolTip(QApplication::translate("C_SerialCom", "Disconnect from serial port", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionDisconnect->setShortcut(QApplication::translate("C_SerialCom", "Ctrl+D", nullptr));
#endif // QT_NO_SHORTCUT
        actionConfigure->setText(QApplication::translate("C_SerialCom", "&Configure", nullptr));
#ifndef QT_NO_TOOLTIP
        actionConfigure->setToolTip(QApplication::translate("C_SerialCom", "Configure serial port", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionConfigure->setShortcut(QApplication::translate("C_SerialCom", "Alt+C", nullptr));
#endif // QT_NO_SHORTCUT
        actionClear->setText(QApplication::translate("C_SerialCom", "C&lear", nullptr));
#ifndef QT_NO_TOOLTIP
        actionClear->setToolTip(QApplication::translate("C_SerialCom", "Clear data", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionClear->setShortcut(QApplication::translate("C_SerialCom", "Alt+L", nullptr));
#endif // QT_NO_SHORTCUT
        actionQuit->setText(QApplication::translate("C_SerialCom", "&Quit", nullptr));
#ifndef QT_NO_SHORTCUT
        actionQuit->setShortcut(QApplication::translate("C_SerialCom", "Ctrl+Q", nullptr));
#endif // QT_NO_SHORTCUT
    } // retranslateUi

};

namespace Ui {
    class C_SerialCom: public Ui_C_SerialCom {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_C_SERIALCOM_H
