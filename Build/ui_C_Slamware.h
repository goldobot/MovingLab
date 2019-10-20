/********************************************************************************
** Form generated from reading UI file 'C_Slamware.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_C_SLAMWARE_H
#define UI_C_SLAMWARE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_C_Slamware
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

    void setupUi(QMainWindow *C_Slamware)
    {
        if (C_Slamware->objectName().isEmpty())
            C_Slamware->setObjectName(QString::fromUtf8("C_Slamware"));
        C_Slamware->resize(419, 502);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(C_Slamware->sizePolicy().hasHeightForWidth());
        C_Slamware->setSizePolicy(sizePolicy);
        C_Slamware->setMinimumSize(QSize(419, 502));
        C_Slamware->setMaximumSize(QSize(419, 502));
        centralwidget = new QWidget(C_Slamware);
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
        C_Slamware->setCentralWidget(centralwidget);

        retranslateUi(C_Slamware);

        QMetaObject::connectSlotsByName(C_Slamware);
    } // setupUi

    void retranslateUi(QMainWindow *C_Slamware)
    {
        C_Slamware->setWindowTitle(QApplication::translate("C_Slamware", "Slamware Interface", nullptr));
        btn_ZoomDefault->setText(QApplication::translate("C_Slamware", "O", nullptr));
        btn_ZoomOut->setText(QApplication::translate("C_Slamware", "-", nullptr));
        btn_ZoomIn->setText(QApplication::translate("C_Slamware", "+", nullptr));
        btn_ShowComPort->setText(QApplication::translate("C_Slamware", "Show COM port", nullptr));
        btn_Connect->setText(QApplication::translate("C_Slamware", "Connect", nullptr));
        btn_CenterLdsScan->setText(QApplication::translate("C_Slamware", "X", nullptr));
        btn_MoveUpLdsScan->setText(QApplication::translate("C_Slamware", "v", nullptr));
        btn_MoveDownLdsScan->setText(QApplication::translate("C_Slamware", "^", nullptr));
        btn_MoveLeftLdsScan->setText(QApplication::translate("C_Slamware", ">", nullptr));
        btn_MoveRightLdsScan->setText(QApplication::translate("C_Slamware", "<", nullptr));
        lbl_RefreshRate->setText(QApplication::translate("C_Slamware", "lbl_RefreshRate", nullptr));
    } // retranslateUi

};

namespace Ui {
    class C_Slamware: public Ui_C_Slamware {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_C_SLAMWARE_H
