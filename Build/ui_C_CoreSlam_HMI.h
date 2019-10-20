/********************************************************************************
** Form generated from reading UI file 'C_CoreSlam_HMI.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_C_CORESLAM_HMI_H
#define UI_C_CORESLAM_HMI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_C_CoreSlam_HMI
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
    QLabel *lbl_coreSlamErr;
    QLabel *lbl_coreSlamPos;
    QCheckBox *chkB_FollowRobot;
    QCheckBox *chkB_ClearMap;

    void setupUi(QMainWindow *C_CoreSlam_HMI)
    {
        if (C_CoreSlam_HMI->objectName().isEmpty())
            C_CoreSlam_HMI->setObjectName(QString::fromUtf8("C_CoreSlam_HMI"));
        C_CoreSlam_HMI->resize(770, 732);
        C_CoreSlam_HMI->setMinimumSize(QSize(770, 732));
        C_CoreSlam_HMI->setMaximumSize(QSize(770, 732));
        centralwidget = new QWidget(C_CoreSlam_HMI);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        lbl_coreSlamFrameRate = new QLabel(centralwidget);
        lbl_coreSlamFrameRate->setObjectName(QString::fromUtf8("lbl_coreSlamFrameRate"));
        lbl_coreSlamFrameRate->setGeometry(QRect(470, 0, 191, 20));
        lbl_coreSlamFrameRate->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        gv_Map = new QGraphicsView(centralwidget);
        gv_Map->setObjectName(QString::fromUtf8("gv_Map"));
        gv_Map->setGeometry(QRect(10, 20, 651, 651));
        gv_Map->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        gv_Map->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        gv_Map->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        btn_CenterMap = new QPushButton(centralwidget);
        btn_CenterMap->setObjectName(QString::fromUtf8("btn_CenterMap"));
        btn_CenterMap->setGeometry(QRect(700, 140, 23, 23));
        btn_MoveRightMap = new QPushButton(centralwidget);
        btn_MoveRightMap->setObjectName(QString::fromUtf8("btn_MoveRightMap"));
        btn_MoveRightMap->setGeometry(QRect(670, 140, 23, 23));
        btn_MoveLeftMap = new QPushButton(centralwidget);
        btn_MoveLeftMap->setObjectName(QString::fromUtf8("btn_MoveLeftMap"));
        btn_MoveLeftMap->setGeometry(QRect(730, 140, 23, 23));
        btn_MoveUpMap = new QPushButton(centralwidget);
        btn_MoveUpMap->setObjectName(QString::fromUtf8("btn_MoveUpMap"));
        btn_MoveUpMap->setGeometry(QRect(700, 170, 23, 23));
        btn_ZoomInMap = new QPushButton(centralwidget);
        btn_ZoomInMap->setObjectName(QString::fromUtf8("btn_ZoomInMap"));
        btn_ZoomInMap->setGeometry(QRect(670, 80, 23, 23));
        btn_MoveDownMap = new QPushButton(centralwidget);
        btn_MoveDownMap->setObjectName(QString::fromUtf8("btn_MoveDownMap"));
        btn_MoveDownMap->setGeometry(QRect(700, 110, 23, 23));
        btn_ZoomDefaultMap = new QPushButton(centralwidget);
        btn_ZoomDefaultMap->setObjectName(QString::fromUtf8("btn_ZoomDefaultMap"));
        btn_ZoomDefaultMap->setGeometry(QRect(700, 80, 23, 23));
        btn_ZoomOutMap = new QPushButton(centralwidget);
        btn_ZoomOutMap->setObjectName(QString::fromUtf8("btn_ZoomOutMap"));
        btn_ZoomOutMap->setGeometry(QRect(730, 80, 23, 23));
        btn_ResetSlam = new QPushButton(centralwidget);
        btn_ResetSlam->setObjectName(QString::fromUtf8("btn_ResetSlam"));
        btn_ResetSlam->setGeometry(QRect(670, 650, 81, 23));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 0, 101, 16));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label_2->setFont(font);
        lbl_coreSlamErr = new QLabel(centralwidget);
        lbl_coreSlamErr->setObjectName(QString::fromUtf8("lbl_coreSlamErr"));
        lbl_coreSlamErr->setGeometry(QRect(10, 700, 651, 20));
        lbl_coreSlamPos = new QLabel(centralwidget);
        lbl_coreSlamPos->setObjectName(QString::fromUtf8("lbl_coreSlamPos"));
        lbl_coreSlamPos->setGeometry(QRect(10, 680, 651, 20));
        chkB_FollowRobot = new QCheckBox(centralwidget);
        chkB_FollowRobot->setObjectName(QString::fromUtf8("chkB_FollowRobot"));
        chkB_FollowRobot->setGeometry(QRect(670, 50, 101, 17));
        chkB_FollowRobot->setChecked(true);
        chkB_ClearMap = new QCheckBox(centralwidget);
        chkB_ClearMap->setObjectName(QString::fromUtf8("chkB_ClearMap"));
        chkB_ClearMap->setGeometry(QRect(670, 30, 101, 17));
        chkB_ClearMap->setChecked(false);
        C_CoreSlam_HMI->setCentralWidget(centralwidget);

        retranslateUi(C_CoreSlam_HMI);

        QMetaObject::connectSlotsByName(C_CoreSlam_HMI);
    } // setupUi

    void retranslateUi(QMainWindow *C_CoreSlam_HMI)
    {
        C_CoreSlam_HMI->setWindowTitle(QApplication::translate("C_CoreSlam_HMI", "CoreSlam Interface", nullptr));
        lbl_coreSlamFrameRate->setText(QApplication::translate("C_CoreSlam_HMI", "lbl_coreSlamFrameRate", nullptr));
        btn_CenterMap->setText(QApplication::translate("C_CoreSlam_HMI", "X", nullptr));
        btn_MoveRightMap->setText(QApplication::translate("C_CoreSlam_HMI", "<", nullptr));
        btn_MoveLeftMap->setText(QApplication::translate("C_CoreSlam_HMI", ">", nullptr));
        btn_MoveUpMap->setText(QApplication::translate("C_CoreSlam_HMI", "v", nullptr));
        btn_ZoomInMap->setText(QApplication::translate("C_CoreSlam_HMI", "+", nullptr));
        btn_MoveDownMap->setText(QApplication::translate("C_CoreSlam_HMI", "^", nullptr));
        btn_ZoomDefaultMap->setText(QApplication::translate("C_CoreSlam_HMI", "O", nullptr));
        btn_ZoomOutMap->setText(QApplication::translate("C_CoreSlam_HMI", "-", nullptr));
        btn_ResetSlam->setText(QApplication::translate("C_CoreSlam_HMI", "Reset SLAM", nullptr));
        label_2->setText(QApplication::translate("C_CoreSlam_HMI", "World map", nullptr));
        lbl_coreSlamErr->setText(QApplication::translate("C_CoreSlam_HMI", "lbl_coreSlamErr", nullptr));
        lbl_coreSlamPos->setText(QApplication::translate("C_CoreSlam_HMI", "lbl_coreSlamPos", nullptr));
        chkB_FollowRobot->setText(QApplication::translate("C_CoreSlam_HMI", "Robot Tracking", nullptr));
        chkB_ClearMap->setText(QApplication::translate("C_CoreSlam_HMI", "Clear map", nullptr));
    } // retranslateUi

};

namespace Ui {
    class C_CoreSlam_HMI: public Ui_C_CoreSlam_HMI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_C_CORESLAM_HMI_H
