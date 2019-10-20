/********************************************************************************
** Form generated from reading UI file 'C_CoreSlamPF_HMI.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_C_CORESLAMPF_HMI_H
#define UI_C_CORESLAMPF_HMI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_C_CoreSlamPF_HMI
{
public:
    QWidget *centralwidget;
    QLabel *lbl_coreSlamFrameRate;
    QGraphicsView *gv_Map;
    QPushButton *btn_CenterMap;
    QPushButton *btn_MoveRightMap;
    QPushButton *btn_MoveLeftMap;
    QPushButton *btn_MoveUpMap;
    QPushButton *btn_ZoomInMap;
    QPushButton *btn_MoveDownMap;
    QPushButton *btn_ZoomDefaultMap;
    QPushButton *btn_ZoomOutMap;
    QPushButton *btn_ResetSlam;
    QLabel *label_2;
    QLabel *lbl_coreSlamErrX;
    QLabel *lbl_coreSlamErrY;
    QLabel *lbl_coreSlamErrAngle;
    QLabel *lbl_coreSlamPosY;
    QLabel *lbl_coreSlamPosAngle;
    QLabel *lbl_coreSlamPosX;
    QCheckBox *chkB_FollowRobot;
    QLabel *lbl_coreSlamPosQuality;
    QLabel *lbl_coreSlamEstimatorIndex;

    void setupUi(QMainWindow *C_CoreSlamPF_HMI)
    {
        if (C_CoreSlamPF_HMI->objectName().isEmpty())
            C_CoreSlamPF_HMI->setObjectName(QString::fromUtf8("C_CoreSlamPF_HMI"));
        C_CoreSlamPF_HMI->resize(520, 483);
        C_CoreSlamPF_HMI->setMinimumSize(QSize(520, 483));
        centralwidget = new QWidget(C_CoreSlamPF_HMI);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        lbl_coreSlamFrameRate = new QLabel(centralwidget);
        lbl_coreSlamFrameRate->setObjectName(QString::fromUtf8("lbl_coreSlamFrameRate"));
        lbl_coreSlamFrameRate->setGeometry(QRect(220, 0, 191, 20));
        lbl_coreSlamFrameRate->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        gv_Map = new QGraphicsView(centralwidget);
        gv_Map->setObjectName(QString::fromUtf8("gv_Map"));
        gv_Map->setGeometry(QRect(10, 20, 400, 400));
        gv_Map->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        gv_Map->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        gv_Map->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        btn_CenterMap = new QPushButton(centralwidget);
        btn_CenterMap->setObjectName(QString::fromUtf8("btn_CenterMap"));
        btn_CenterMap->setGeometry(QRect(460, 110, 23, 23));
        btn_MoveRightMap = new QPushButton(centralwidget);
        btn_MoveRightMap->setObjectName(QString::fromUtf8("btn_MoveRightMap"));
        btn_MoveRightMap->setGeometry(QRect(430, 110, 23, 23));
        btn_MoveLeftMap = new QPushButton(centralwidget);
        btn_MoveLeftMap->setObjectName(QString::fromUtf8("btn_MoveLeftMap"));
        btn_MoveLeftMap->setGeometry(QRect(490, 110, 23, 23));
        btn_MoveUpMap = new QPushButton(centralwidget);
        btn_MoveUpMap->setObjectName(QString::fromUtf8("btn_MoveUpMap"));
        btn_MoveUpMap->setGeometry(QRect(460, 140, 23, 23));
        btn_ZoomInMap = new QPushButton(centralwidget);
        btn_ZoomInMap->setObjectName(QString::fromUtf8("btn_ZoomInMap"));
        btn_ZoomInMap->setGeometry(QRect(430, 50, 23, 23));
        btn_MoveDownMap = new QPushButton(centralwidget);
        btn_MoveDownMap->setObjectName(QString::fromUtf8("btn_MoveDownMap"));
        btn_MoveDownMap->setGeometry(QRect(460, 80, 23, 23));
        btn_ZoomDefaultMap = new QPushButton(centralwidget);
        btn_ZoomDefaultMap->setObjectName(QString::fromUtf8("btn_ZoomDefaultMap"));
        btn_ZoomDefaultMap->setGeometry(QRect(460, 50, 23, 23));
        btn_ZoomOutMap = new QPushButton(centralwidget);
        btn_ZoomOutMap->setObjectName(QString::fromUtf8("btn_ZoomOutMap"));
        btn_ZoomOutMap->setGeometry(QRect(490, 50, 23, 23));
        btn_ResetSlam = new QPushButton(centralwidget);
        btn_ResetSlam->setObjectName(QString::fromUtf8("btn_ResetSlam"));
        btn_ResetSlam->setGeometry(QRect(430, 400, 81, 23));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 0, 101, 16));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label_2->setFont(font);
        lbl_coreSlamErrX = new QLabel(centralwidget);
        lbl_coreSlamErrX->setObjectName(QString::fromUtf8("lbl_coreSlamErrX"));
        lbl_coreSlamErrX->setGeometry(QRect(280, 420, 131, 20));
        lbl_coreSlamErrY = new QLabel(centralwidget);
        lbl_coreSlamErrY->setObjectName(QString::fromUtf8("lbl_coreSlamErrY"));
        lbl_coreSlamErrY->setGeometry(QRect(280, 440, 131, 20));
        lbl_coreSlamErrAngle = new QLabel(centralwidget);
        lbl_coreSlamErrAngle->setObjectName(QString::fromUtf8("lbl_coreSlamErrAngle"));
        lbl_coreSlamErrAngle->setGeometry(QRect(280, 460, 131, 20));
        lbl_coreSlamPosY = new QLabel(centralwidget);
        lbl_coreSlamPosY->setObjectName(QString::fromUtf8("lbl_coreSlamPosY"));
        lbl_coreSlamPosY->setGeometry(QRect(160, 440, 121, 20));
        lbl_coreSlamPosAngle = new QLabel(centralwidget);
        lbl_coreSlamPosAngle->setObjectName(QString::fromUtf8("lbl_coreSlamPosAngle"));
        lbl_coreSlamPosAngle->setGeometry(QRect(160, 460, 121, 20));
        lbl_coreSlamPosX = new QLabel(centralwidget);
        lbl_coreSlamPosX->setObjectName(QString::fromUtf8("lbl_coreSlamPosX"));
        lbl_coreSlamPosX->setGeometry(QRect(160, 420, 121, 20));
        chkB_FollowRobot = new QCheckBox(centralwidget);
        chkB_FollowRobot->setObjectName(QString::fromUtf8("chkB_FollowRobot"));
        chkB_FollowRobot->setGeometry(QRect(420, 20, 101, 17));
        chkB_FollowRobot->setChecked(true);
        lbl_coreSlamPosQuality = new QLabel(centralwidget);
        lbl_coreSlamPosQuality->setObjectName(QString::fromUtf8("lbl_coreSlamPosQuality"));
        lbl_coreSlamPosQuality->setGeometry(QRect(10, 440, 131, 20));
        lbl_coreSlamEstimatorIndex = new QLabel(centralwidget);
        lbl_coreSlamEstimatorIndex->setObjectName(QString::fromUtf8("lbl_coreSlamEstimatorIndex"));
        lbl_coreSlamEstimatorIndex->setGeometry(QRect(10, 420, 131, 20));
        C_CoreSlamPF_HMI->setCentralWidget(centralwidget);

        retranslateUi(C_CoreSlamPF_HMI);

        QMetaObject::connectSlotsByName(C_CoreSlamPF_HMI);
    } // setupUi

    void retranslateUi(QMainWindow *C_CoreSlamPF_HMI)
    {
        C_CoreSlamPF_HMI->setWindowTitle(QApplication::translate("C_CoreSlamPF_HMI", "CoreSlam Particles Filter Interface", nullptr));
        lbl_coreSlamFrameRate->setText(QApplication::translate("C_CoreSlamPF_HMI", "lbl_coreSlamFrameRate", nullptr));
        btn_CenterMap->setText(QApplication::translate("C_CoreSlamPF_HMI", "X", nullptr));
        btn_MoveRightMap->setText(QApplication::translate("C_CoreSlamPF_HMI", "<", nullptr));
        btn_MoveLeftMap->setText(QApplication::translate("C_CoreSlamPF_HMI", ">", nullptr));
        btn_MoveUpMap->setText(QApplication::translate("C_CoreSlamPF_HMI", "v", nullptr));
        btn_ZoomInMap->setText(QApplication::translate("C_CoreSlamPF_HMI", "+", nullptr));
        btn_MoveDownMap->setText(QApplication::translate("C_CoreSlamPF_HMI", "^", nullptr));
        btn_ZoomDefaultMap->setText(QApplication::translate("C_CoreSlamPF_HMI", "O", nullptr));
        btn_ZoomOutMap->setText(QApplication::translate("C_CoreSlamPF_HMI", "-", nullptr));
        btn_ResetSlam->setText(QApplication::translate("C_CoreSlamPF_HMI", "Reset SLAM", nullptr));
        label_2->setText(QApplication::translate("C_CoreSlamPF_HMI", "World map", nullptr));
        lbl_coreSlamErrX->setText(QApplication::translate("C_CoreSlamPF_HMI", "lbl_coreSlamErrX", nullptr));
        lbl_coreSlamErrY->setText(QApplication::translate("C_CoreSlamPF_HMI", "lbl_coreSlamErrY", nullptr));
        lbl_coreSlamErrAngle->setText(QApplication::translate("C_CoreSlamPF_HMI", "lbl_coreSlamErrAngle", nullptr));
        lbl_coreSlamPosY->setText(QApplication::translate("C_CoreSlamPF_HMI", "lbl_coreSlamPosY", nullptr));
        lbl_coreSlamPosAngle->setText(QApplication::translate("C_CoreSlamPF_HMI", "lbl_coreSlamPosAngle", nullptr));
        lbl_coreSlamPosX->setText(QApplication::translate("C_CoreSlamPF_HMI", "lbl_coreSlamPosX", nullptr));
        chkB_FollowRobot->setText(QApplication::translate("C_CoreSlamPF_HMI", "Robot Tracking", nullptr));
        lbl_coreSlamPosQuality->setText(QApplication::translate("C_CoreSlamPF_HMI", "lbl_coreSlamPosQuality", nullptr));
        lbl_coreSlamEstimatorIndex->setText(QApplication::translate("C_CoreSlamPF_HMI", "lbl_coreSlamEstimatorIndex", nullptr));
    } // retranslateUi

};

namespace Ui {
    class C_CoreSlamPF_HMI: public Ui_C_CoreSlamPF_HMI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_C_CORESLAMPF_HMI_H
