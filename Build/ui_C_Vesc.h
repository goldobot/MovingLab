/********************************************************************************
** Form generated from reading UI file 'C_Vesc.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_C_VESC_H
#define UI_C_VESC_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_C_Vesc
{
public:
    QWidget *centralwidget;
    QPushButton *btn_ShowComPort;
    QLabel *lbl_avgMotorCurrent;
    QLabel *lbl_avgInputCurrent;
    QLabel *lbl_dutyCycleNow;
    QLabel *lbl_rpm;
    QLabel *lbl_inpVoltage;
    QLabel *lbl_ampHours;
    QLabel *lbl_ampHoursCharged;
    QLabel *lbl_tachometer;
    QLabel *lbl_tachometerAbs;

    void setupUi(QMainWindow *C_Vesc)
    {
        if (C_Vesc->objectName().isEmpty())
            C_Vesc->setObjectName(QString::fromUtf8("C_Vesc"));
        C_Vesc->resize(210, 236);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(C_Vesc->sizePolicy().hasHeightForWidth());
        C_Vesc->setSizePolicy(sizePolicy);
        C_Vesc->setMaximumSize(QSize(419, 450));
        centralwidget = new QWidget(C_Vesc);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        btn_ShowComPort = new QPushButton(centralwidget);
        btn_ShowComPort->setObjectName(QString::fromUtf8("btn_ShowComPort"));
        btn_ShowComPort->setGeometry(QRect(40, 10, 131, 23));
        lbl_avgMotorCurrent = new QLabel(centralwidget);
        lbl_avgMotorCurrent->setObjectName(QString::fromUtf8("lbl_avgMotorCurrent"));
        lbl_avgMotorCurrent->setGeometry(QRect(10, 50, 191, 16));
        lbl_avgMotorCurrent->setAlignment(Qt::AlignCenter);
        lbl_avgInputCurrent = new QLabel(centralwidget);
        lbl_avgInputCurrent->setObjectName(QString::fromUtf8("lbl_avgInputCurrent"));
        lbl_avgInputCurrent->setGeometry(QRect(10, 70, 191, 16));
        lbl_avgInputCurrent->setAlignment(Qt::AlignCenter);
        lbl_dutyCycleNow = new QLabel(centralwidget);
        lbl_dutyCycleNow->setObjectName(QString::fromUtf8("lbl_dutyCycleNow"));
        lbl_dutyCycleNow->setGeometry(QRect(10, 90, 191, 16));
        lbl_dutyCycleNow->setAlignment(Qt::AlignCenter);
        lbl_rpm = new QLabel(centralwidget);
        lbl_rpm->setObjectName(QString::fromUtf8("lbl_rpm"));
        lbl_rpm->setGeometry(QRect(10, 110, 191, 16));
        lbl_rpm->setAlignment(Qt::AlignCenter);
        lbl_inpVoltage = new QLabel(centralwidget);
        lbl_inpVoltage->setObjectName(QString::fromUtf8("lbl_inpVoltage"));
        lbl_inpVoltage->setGeometry(QRect(10, 130, 191, 16));
        lbl_inpVoltage->setAlignment(Qt::AlignCenter);
        lbl_ampHours = new QLabel(centralwidget);
        lbl_ampHours->setObjectName(QString::fromUtf8("lbl_ampHours"));
        lbl_ampHours->setGeometry(QRect(10, 150, 191, 16));
        lbl_ampHours->setAlignment(Qt::AlignCenter);
        lbl_ampHoursCharged = new QLabel(centralwidget);
        lbl_ampHoursCharged->setObjectName(QString::fromUtf8("lbl_ampHoursCharged"));
        lbl_ampHoursCharged->setGeometry(QRect(10, 170, 191, 16));
        lbl_ampHoursCharged->setAlignment(Qt::AlignCenter);
        lbl_tachometer = new QLabel(centralwidget);
        lbl_tachometer->setObjectName(QString::fromUtf8("lbl_tachometer"));
        lbl_tachometer->setGeometry(QRect(10, 190, 191, 16));
        lbl_tachometer->setAlignment(Qt::AlignCenter);
        lbl_tachometerAbs = new QLabel(centralwidget);
        lbl_tachometerAbs->setObjectName(QString::fromUtf8("lbl_tachometerAbs"));
        lbl_tachometerAbs->setGeometry(QRect(10, 210, 191, 16));
        lbl_tachometerAbs->setAlignment(Qt::AlignCenter);
        C_Vesc->setCentralWidget(centralwidget);

        retranslateUi(C_Vesc);

        QMetaObject::connectSlotsByName(C_Vesc);
    } // setupUi

    void retranslateUi(QMainWindow *C_Vesc)
    {
        C_Vesc->setWindowTitle(QApplication::translate("C_Vesc", "Neato Lidar", nullptr));
        btn_ShowComPort->setText(QApplication::translate("C_Vesc", "Show COM port", nullptr));
        lbl_avgMotorCurrent->setText(QApplication::translate("C_Vesc", "lbl_avgMotorCurrent", nullptr));
        lbl_avgInputCurrent->setText(QApplication::translate("C_Vesc", "lbl_avgInputCurrent", nullptr));
        lbl_dutyCycleNow->setText(QApplication::translate("C_Vesc", "lbl_dutyCycleNow", nullptr));
        lbl_rpm->setText(QApplication::translate("C_Vesc", "lbl_rpm", nullptr));
        lbl_inpVoltage->setText(QApplication::translate("C_Vesc", "lbl_inpVoltage", nullptr));
        lbl_ampHours->setText(QApplication::translate("C_Vesc", "lbl_ampHours", nullptr));
        lbl_ampHoursCharged->setText(QApplication::translate("C_Vesc", "lbl_ampHoursCharged", nullptr));
        lbl_tachometer->setText(QApplication::translate("C_Vesc", "lbl_tachometer", nullptr));
        lbl_tachometerAbs->setText(QApplication::translate("C_Vesc", "lbl_tachometerAbs", nullptr));
    } // retranslateUi

};

namespace Ui {
    class C_Vesc: public Ui_C_Vesc {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_C_VESC_H
