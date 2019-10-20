/********************************************************************************
** Form generated from reading UI file 'C_ScanseLidar.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_C_SCANSELIDAR_H
#define UI_C_SCANSELIDAR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_C_ScanseLidar
{
public:
    QWidget *centralwidget;
    QGraphicsView *gv_LdsScan;
    QPushButton *btn_ZoomDefault;
    QPushButton *btn_ZoomOut;
    QPushButton *btn_ZoomIn;
    QPushButton *btn_ShowComPort;
    QPushButton *btn_Connect;
    QPushButton *btn_CenterLdsScan;
    QPushButton *btn_MoveUpLdsScan;
    QPushButton *btn_MoveDownLdsScan;
    QPushButton *btn_MoveLeftLdsScan;
    QPushButton *btn_MoveRightLdsScan;
    QLabel *lbl_RefreshRate;

    void setupUi(QMainWindow *C_ScanseLidar)
    {
        if (C_ScanseLidar->objectName().isEmpty())
            C_ScanseLidar->setObjectName(QString::fromUtf8("C_ScanseLidar"));
        C_ScanseLidar->resize(419, 502);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(C_ScanseLidar->sizePolicy().hasHeightForWidth());
        C_ScanseLidar->setSizePolicy(sizePolicy);
        C_ScanseLidar->setMinimumSize(QSize(419, 502));
        C_ScanseLidar->setMaximumSize(QSize(419, 502));
        centralwidget = new QWidget(C_ScanseLidar);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gv_LdsScan = new QGraphicsView(centralwidget);
        gv_LdsScan->setObjectName(QString::fromUtf8("gv_LdsScan"));
        gv_LdsScan->setGeometry(QRect(10, 20, 400, 400));
        gv_LdsScan->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        gv_LdsScan->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        gv_LdsScan->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        btn_ZoomDefault = new QPushButton(centralwidget);
        btn_ZoomDefault->setObjectName(QString::fromUtf8("btn_ZoomDefault"));
        btn_ZoomDefault->setGeometry(QRect(100, 450, 23, 23));
        btn_ZoomOut = new QPushButton(centralwidget);
        btn_ZoomOut->setObjectName(QString::fromUtf8("btn_ZoomOut"));
        btn_ZoomOut->setGeometry(QRect(120, 450, 23, 23));
        btn_ZoomIn = new QPushButton(centralwidget);
        btn_ZoomIn->setObjectName(QString::fromUtf8("btn_ZoomIn"));
        btn_ZoomIn->setGeometry(QRect(80, 450, 23, 23));
        btn_ShowComPort = new QPushButton(centralwidget);
        btn_ShowComPort->setObjectName(QString::fromUtf8("btn_ShowComPort"));
        btn_ShowComPort->setGeometry(QRect(310, 440, 101, 23));
        btn_Connect = new QPushButton(centralwidget);
        btn_Connect->setObjectName(QString::fromUtf8("btn_Connect"));
        btn_Connect->setGeometry(QRect(310, 470, 101, 23));
        btn_CenterLdsScan = new QPushButton(centralwidget);
        btn_CenterLdsScan->setObjectName(QString::fromUtf8("btn_CenterLdsScan"));
        btn_CenterLdsScan->setGeometry(QRect(30, 450, 23, 23));
        btn_MoveUpLdsScan = new QPushButton(centralwidget);
        btn_MoveUpLdsScan->setObjectName(QString::fromUtf8("btn_MoveUpLdsScan"));
        btn_MoveUpLdsScan->setGeometry(QRect(30, 470, 23, 23));
        btn_MoveDownLdsScan = new QPushButton(centralwidget);
        btn_MoveDownLdsScan->setObjectName(QString::fromUtf8("btn_MoveDownLdsScan"));
        btn_MoveDownLdsScan->setGeometry(QRect(30, 430, 23, 23));
        btn_MoveLeftLdsScan = new QPushButton(centralwidget);
        btn_MoveLeftLdsScan->setObjectName(QString::fromUtf8("btn_MoveLeftLdsScan"));
        btn_MoveLeftLdsScan->setGeometry(QRect(50, 450, 23, 23));
        btn_MoveRightLdsScan = new QPushButton(centralwidget);
        btn_MoveRightLdsScan->setObjectName(QString::fromUtf8("btn_MoveRightLdsScan"));
        btn_MoveRightLdsScan->setGeometry(QRect(10, 450, 23, 23));
        lbl_RefreshRate = new QLabel(centralwidget);
        lbl_RefreshRate->setObjectName(QString::fromUtf8("lbl_RefreshRate"));
        lbl_RefreshRate->setGeometry(QRect(10, 0, 191, 16));
        C_ScanseLidar->setCentralWidget(centralwidget);

        retranslateUi(C_ScanseLidar);

        QMetaObject::connectSlotsByName(C_ScanseLidar);
    } // setupUi

    void retranslateUi(QMainWindow *C_ScanseLidar)
    {
        C_ScanseLidar->setWindowTitle(QApplication::translate("C_ScanseLidar", "Scanse Lidar Interface", nullptr));
        btn_ZoomDefault->setText(QApplication::translate("C_ScanseLidar", "O", nullptr));
        btn_ZoomOut->setText(QApplication::translate("C_ScanseLidar", "-", nullptr));
        btn_ZoomIn->setText(QApplication::translate("C_ScanseLidar", "+", nullptr));
        btn_ShowComPort->setText(QApplication::translate("C_ScanseLidar", "Show COM port", nullptr));
        btn_Connect->setText(QApplication::translate("C_ScanseLidar", "Connect", nullptr));
        btn_CenterLdsScan->setText(QApplication::translate("C_ScanseLidar", "X", nullptr));
        btn_MoveUpLdsScan->setText(QApplication::translate("C_ScanseLidar", "v", nullptr));
        btn_MoveDownLdsScan->setText(QApplication::translate("C_ScanseLidar", "^", nullptr));
        btn_MoveLeftLdsScan->setText(QApplication::translate("C_ScanseLidar", ">", nullptr));
        btn_MoveRightLdsScan->setText(QApplication::translate("C_ScanseLidar", "<", nullptr));
        lbl_RefreshRate->setText(QApplication::translate("C_ScanseLidar", "lbl_RefreshRate", nullptr));
    } // retranslateUi

};

namespace Ui {
    class C_ScanseLidar: public Ui_C_ScanseLidar {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_C_SCANSELIDAR_H
