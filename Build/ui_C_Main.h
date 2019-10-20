/********************************************************************************
** Form generated from reading UI file 'C_Main.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_C_MAIN_H
#define UI_C_MAIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_C_Main
{
public:
    QWidget *centralWidget;
    QPushButton *btn_ShowCoreSlam;
    QPushButton *btn_ShowCommand;
    QPushButton *btn_ShowScanseLidar;
    QPushButton *btn_ShowPathFinder;
    QPushButton *btn_ShowSlamwareLidar;
    QPushButton *btn_ShowCoreSlamPF;

    void setupUi(QMainWindow *C_Main)
    {
        if (C_Main->objectName().isEmpty())
            C_Main->setObjectName(QString::fromUtf8("C_Main"));
        C_Main->resize(201, 196);
        centralWidget = new QWidget(C_Main);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        btn_ShowCoreSlam = new QPushButton(centralWidget);
        btn_ShowCoreSlam->setObjectName(QString::fromUtf8("btn_ShowCoreSlam"));
        btn_ShowCoreSlam->setGeometry(QRect(10, 70, 181, 23));
        btn_ShowCommand = new QPushButton(centralWidget);
        btn_ShowCommand->setObjectName(QString::fromUtf8("btn_ShowCommand"));
        btn_ShowCommand->setGeometry(QRect(10, 130, 181, 23));
        btn_ShowScanseLidar = new QPushButton(centralWidget);
        btn_ShowScanseLidar->setObjectName(QString::fromUtf8("btn_ShowScanseLidar"));
        btn_ShowScanseLidar->setGeometry(QRect(10, 10, 181, 23));
        btn_ShowPathFinder = new QPushButton(centralWidget);
        btn_ShowPathFinder->setObjectName(QString::fromUtf8("btn_ShowPathFinder"));
        btn_ShowPathFinder->setGeometry(QRect(10, 160, 181, 23));
        btn_ShowSlamwareLidar = new QPushButton(centralWidget);
        btn_ShowSlamwareLidar->setObjectName(QString::fromUtf8("btn_ShowSlamwareLidar"));
        btn_ShowSlamwareLidar->setGeometry(QRect(10, 40, 181, 23));
        btn_ShowCoreSlamPF = new QPushButton(centralWidget);
        btn_ShowCoreSlamPF->setObjectName(QString::fromUtf8("btn_ShowCoreSlamPF"));
        btn_ShowCoreSlamPF->setGeometry(QRect(10, 100, 181, 23));
        C_Main->setCentralWidget(centralWidget);

        retranslateUi(C_Main);

        QMetaObject::connectSlotsByName(C_Main);
    } // setupUi

    void retranslateUi(QMainWindow *C_Main)
    {
        C_Main->setWindowTitle(QApplication::translate("C_Main", "MovingLab", nullptr));
        btn_ShowCoreSlam->setText(QApplication::translate("C_Main", "Show CoreSlam HMI", nullptr));
        btn_ShowCommand->setText(QApplication::translate("C_Main", "Show Commands", nullptr));
        btn_ShowScanseLidar->setText(QApplication::translate("C_Main", "Show Scanse Lidar", nullptr));
        btn_ShowPathFinder->setText(QApplication::translate("C_Main", "Show Path Finder", nullptr));
        btn_ShowSlamwareLidar->setText(QApplication::translate("C_Main", "Show Slamware Lidar", nullptr));
        btn_ShowCoreSlamPF->setText(QApplication::translate("C_Main", "Show CoreSlamPF HMI", nullptr));
    } // retranslateUi

};

namespace Ui {
    class C_Main: public Ui_C_Main {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_C_MAIN_H
