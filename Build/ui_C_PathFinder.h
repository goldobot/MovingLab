/********************************************************************************
** Form generated from reading UI file 'C_PathFinder.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_C_PATHFINDER_H
#define UI_C_PATHFINDER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_C_PathFinder
{
public:
    QWidget *centralwidget;
    QGraphicsView *gv_Map;
    QPushButton *btn_CenterMap;
    QPushButton *btn_MoveRightMap;
    QPushButton *btn_MoveLeftMap;
    QPushButton *btn_MoveUpMap;
    QPushButton *btn_ZoomInMap;
    QPushButton *btn_MoveDownMap;
    QPushButton *btn_ZoomDefaultMap;
    QPushButton *btn_ZoomOutMap;
    QLabel *label_2;
    QCheckBox *chkB_FollowRobot;
    QLabel *lbl_coreSlamPos;
    QLabel *lbl_nextPos;
    QLabel *lbl_frameRate;
    QCheckBox *chkB_DynamicMargin;

    void setupUi(QMainWindow *C_PathFinder)
    {
        if (C_PathFinder->objectName().isEmpty())
            C_PathFinder->setObjectName(QString::fromUtf8("C_PathFinder"));
        C_PathFinder->resize(769, 723);
        C_PathFinder->setMinimumSize(QSize(769, 723));
        C_PathFinder->setMaximumSize(QSize(769, 723));
        centralwidget = new QWidget(C_PathFinder);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gv_Map = new QGraphicsView(centralwidget);
        gv_Map->setObjectName(QString::fromUtf8("gv_Map"));
        gv_Map->setGeometry(QRect(10, 20, 651, 651));
        gv_Map->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        gv_Map->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        gv_Map->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        btn_CenterMap = new QPushButton(centralwidget);
        btn_CenterMap->setObjectName(QString::fromUtf8("btn_CenterMap"));
        btn_CenterMap->setGeometry(QRect(700, 120, 23, 23));
        btn_MoveRightMap = new QPushButton(centralwidget);
        btn_MoveRightMap->setObjectName(QString::fromUtf8("btn_MoveRightMap"));
        btn_MoveRightMap->setGeometry(QRect(670, 120, 23, 23));
        btn_MoveLeftMap = new QPushButton(centralwidget);
        btn_MoveLeftMap->setObjectName(QString::fromUtf8("btn_MoveLeftMap"));
        btn_MoveLeftMap->setGeometry(QRect(730, 120, 23, 23));
        btn_MoveUpMap = new QPushButton(centralwidget);
        btn_MoveUpMap->setObjectName(QString::fromUtf8("btn_MoveUpMap"));
        btn_MoveUpMap->setGeometry(QRect(700, 150, 23, 23));
        btn_ZoomInMap = new QPushButton(centralwidget);
        btn_ZoomInMap->setObjectName(QString::fromUtf8("btn_ZoomInMap"));
        btn_ZoomInMap->setGeometry(QRect(670, 60, 23, 23));
        btn_MoveDownMap = new QPushButton(centralwidget);
        btn_MoveDownMap->setObjectName(QString::fromUtf8("btn_MoveDownMap"));
        btn_MoveDownMap->setGeometry(QRect(700, 90, 23, 23));
        btn_ZoomDefaultMap = new QPushButton(centralwidget);
        btn_ZoomDefaultMap->setObjectName(QString::fromUtf8("btn_ZoomDefaultMap"));
        btn_ZoomDefaultMap->setGeometry(QRect(700, 60, 23, 23));
        btn_ZoomOutMap = new QPushButton(centralwidget);
        btn_ZoomOutMap->setObjectName(QString::fromUtf8("btn_ZoomOutMap"));
        btn_ZoomOutMap->setGeometry(QRect(730, 60, 23, 23));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 0, 101, 16));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label_2->setFont(font);
        chkB_FollowRobot = new QCheckBox(centralwidget);
        chkB_FollowRobot->setObjectName(QString::fromUtf8("chkB_FollowRobot"));
        chkB_FollowRobot->setGeometry(QRect(670, 30, 101, 17));
        chkB_FollowRobot->setChecked(true);
        lbl_coreSlamPos = new QLabel(centralwidget);
        lbl_coreSlamPos->setObjectName(QString::fromUtf8("lbl_coreSlamPos"));
        lbl_coreSlamPos->setGeometry(QRect(10, 680, 651, 20));
        lbl_nextPos = new QLabel(centralwidget);
        lbl_nextPos->setObjectName(QString::fromUtf8("lbl_nextPos"));
        lbl_nextPos->setGeometry(QRect(10, 700, 651, 20));
        lbl_frameRate = new QLabel(centralwidget);
        lbl_frameRate->setObjectName(QString::fromUtf8("lbl_frameRate"));
        lbl_frameRate->setGeometry(QRect(470, 0, 191, 20));
        lbl_frameRate->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        chkB_DynamicMargin = new QCheckBox(centralwidget);
        chkB_DynamicMargin->setObjectName(QString::fromUtf8("chkB_DynamicMargin"));
        chkB_DynamicMargin->setGeometry(QRect(560, 680, 101, 17));
        chkB_DynamicMargin->setChecked(true);
        C_PathFinder->setCentralWidget(centralwidget);

        retranslateUi(C_PathFinder);

        QMetaObject::connectSlotsByName(C_PathFinder);
    } // setupUi

    void retranslateUi(QMainWindow *C_PathFinder)
    {
        C_PathFinder->setWindowTitle(QApplication::translate("C_PathFinder", "Path Finder Interface", nullptr));
        btn_CenterMap->setText(QApplication::translate("C_PathFinder", "X", nullptr));
        btn_MoveRightMap->setText(QApplication::translate("C_PathFinder", "<", nullptr));
        btn_MoveLeftMap->setText(QApplication::translate("C_PathFinder", ">", nullptr));
        btn_MoveUpMap->setText(QApplication::translate("C_PathFinder", "v", nullptr));
        btn_ZoomInMap->setText(QApplication::translate("C_PathFinder", "+", nullptr));
        btn_MoveDownMap->setText(QApplication::translate("C_PathFinder", "^", nullptr));
        btn_ZoomDefaultMap->setText(QApplication::translate("C_PathFinder", "O", nullptr));
        btn_ZoomOutMap->setText(QApplication::translate("C_PathFinder", "-", nullptr));
        label_2->setText(QApplication::translate("C_PathFinder", "World map", nullptr));
        chkB_FollowRobot->setText(QApplication::translate("C_PathFinder", "Robot Tracking", nullptr));
        lbl_coreSlamPos->setText(QApplication::translate("C_PathFinder", "lbl_coreSlamPos", nullptr));
        lbl_nextPos->setText(QApplication::translate("C_PathFinder", "lbl_nextPos", nullptr));
        lbl_frameRate->setText(QApplication::translate("C_PathFinder", "lbl_frameRate", nullptr));
        chkB_DynamicMargin->setText(QApplication::translate("C_PathFinder", "Dynamic Margin", nullptr));
    } // retranslateUi

};

namespace Ui {
    class C_PathFinder: public Ui_C_PathFinder {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_C_PATHFINDER_H
