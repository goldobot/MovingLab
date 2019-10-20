/********************************************************************************
** Form generated from reading UI file 'C_TwoWheelsBase.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_C_TWOWHEELSBASE_H
#define UI_C_TWOWHEELSBASE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_C_TwoWheelsBase
{
public:
    QWidget *centralwidget;
    QPushButton *btn_ShowLeftMotor;
    QPushButton *btn_ShowRightMotor;
    QPushButton *btn_Backward;
    QPushButton *btn_Forward;
    QPushButton *btn_TurnRight;
    QPushButton *btn_TurnLeft;
    QPushButton *btn_Stop;
    QPushButton *btn_ForwardRight;
    QPushButton *btn_ForwardLeft;
    QPushButton *btn_BackwardRight;
    QPushButton *btn_BackwardLeft;

    void setupUi(QMainWindow *C_TwoWheelsBase)
    {
        if (C_TwoWheelsBase->objectName().isEmpty())
            C_TwoWheelsBase->setObjectName(QString::fromUtf8("C_TwoWheelsBase"));
        C_TwoWheelsBase->resize(289, 270);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(C_TwoWheelsBase->sizePolicy().hasHeightForWidth());
        C_TwoWheelsBase->setSizePolicy(sizePolicy);
        C_TwoWheelsBase->setMaximumSize(QSize(419, 450));
        centralwidget = new QWidget(C_TwoWheelsBase);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        btn_ShowLeftMotor = new QPushButton(centralwidget);
        btn_ShowLeftMotor->setObjectName(QString::fromUtf8("btn_ShowLeftMotor"));
        btn_ShowLeftMotor->setGeometry(QRect(10, 10, 121, 23));
        btn_ShowRightMotor = new QPushButton(centralwidget);
        btn_ShowRightMotor->setObjectName(QString::fromUtf8("btn_ShowRightMotor"));
        btn_ShowRightMotor->setGeometry(QRect(160, 10, 121, 23));
        btn_Backward = new QPushButton(centralwidget);
        btn_Backward->setObjectName(QString::fromUtf8("btn_Backward"));
        btn_Backward->setGeometry(QRect(110, 190, 71, 71));
        btn_Forward = new QPushButton(centralwidget);
        btn_Forward->setObjectName(QString::fromUtf8("btn_Forward"));
        btn_Forward->setGeometry(QRect(110, 50, 71, 71));
        btn_TurnRight = new QPushButton(centralwidget);
        btn_TurnRight->setObjectName(QString::fromUtf8("btn_TurnRight"));
        btn_TurnRight->setGeometry(QRect(180, 120, 71, 71));
        btn_TurnLeft = new QPushButton(centralwidget);
        btn_TurnLeft->setObjectName(QString::fromUtf8("btn_TurnLeft"));
        btn_TurnLeft->setGeometry(QRect(40, 120, 71, 71));
        btn_Stop = new QPushButton(centralwidget);
        btn_Stop->setObjectName(QString::fromUtf8("btn_Stop"));
        btn_Stop->setGeometry(QRect(110, 120, 71, 71));
        btn_ForwardRight = new QPushButton(centralwidget);
        btn_ForwardRight->setObjectName(QString::fromUtf8("btn_ForwardRight"));
        btn_ForwardRight->setGeometry(QRect(180, 50, 71, 71));
        btn_ForwardLeft = new QPushButton(centralwidget);
        btn_ForwardLeft->setObjectName(QString::fromUtf8("btn_ForwardLeft"));
        btn_ForwardLeft->setGeometry(QRect(40, 50, 71, 71));
        btn_BackwardRight = new QPushButton(centralwidget);
        btn_BackwardRight->setObjectName(QString::fromUtf8("btn_BackwardRight"));
        btn_BackwardRight->setGeometry(QRect(180, 190, 71, 71));
        btn_BackwardLeft = new QPushButton(centralwidget);
        btn_BackwardLeft->setObjectName(QString::fromUtf8("btn_BackwardLeft"));
        btn_BackwardLeft->setGeometry(QRect(40, 190, 71, 71));
        C_TwoWheelsBase->setCentralWidget(centralwidget);

        retranslateUi(C_TwoWheelsBase);

        QMetaObject::connectSlotsByName(C_TwoWheelsBase);
    } // setupUi

    void retranslateUi(QMainWindow *C_TwoWheelsBase)
    {
        C_TwoWheelsBase->setWindowTitle(QApplication::translate("C_TwoWheelsBase", "Two wheels base", nullptr));
        btn_ShowLeftMotor->setText(QApplication::translate("C_TwoWheelsBase", "Show Left Motor", nullptr));
        btn_ShowRightMotor->setText(QApplication::translate("C_TwoWheelsBase", "Show Right Motor", nullptr));
        btn_Backward->setText(QApplication::translate("C_TwoWheelsBase", "Backward", nullptr));
        btn_Forward->setText(QApplication::translate("C_TwoWheelsBase", "Forward", nullptr));
        btn_TurnRight->setText(QApplication::translate("C_TwoWheelsBase", "Turn Right", nullptr));
        btn_TurnLeft->setText(QApplication::translate("C_TwoWheelsBase", "Turn Left", nullptr));
        btn_Stop->setText(QApplication::translate("C_TwoWheelsBase", "Stop", nullptr));
        btn_ForwardRight->setText(QApplication::translate("C_TwoWheelsBase", "Fwd Right", nullptr));
        btn_ForwardLeft->setText(QApplication::translate("C_TwoWheelsBase", "Fwd Left", nullptr));
        btn_BackwardRight->setText(QApplication::translate("C_TwoWheelsBase", "Back Right", nullptr));
        btn_BackwardLeft->setText(QApplication::translate("C_TwoWheelsBase", "Back Left", nullptr));
    } // retranslateUi

};

namespace Ui {
    class C_TwoWheelsBase: public Ui_C_TwoWheelsBase {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_C_TWOWHEELSBASE_H
