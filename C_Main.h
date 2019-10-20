#ifndef C_MAIN_H
#define C_MAIN_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QMessageBox>

#include "ui_C_Main.h"

#include "C_ScanseLidar.h"
#include "C_Slamware.h"
#include "C_CoreSlam_HMI.h"
#include "C_CoreSlamPF_HMI.h"
#include "C_TwoWheelsBase.h"
#include "C_PathFinder.h"

class C_Main : public QMainWindow
{
    Q_OBJECT

public:
    // Constructor
    explicit C_Main(QWidget * ptParent = nullptr);

    // Destructor
    ~C_Main()
    {
        delete m_ptCoreSlamHMI;
        //delete m_ptCoreSlamPFHMI;
        delete m_ptPathFinder;
    }

private:
    // The UI of the object
    Ui::C_Main m_userInterface;

    C_ScanseLidar m_scanseLidar;
    C_Slamware m_slamwareLidar;

    C_CoreSlam_HMI * m_ptCoreSlamHMI = nullptr;
    //C_CoreSlamPF_HMI * m_ptCoreSlamPFHMI = nullptr;

    C_TwoWheelsBase m_twoWheelsBase;
    C_PathFinder * m_ptPathFinder = nullptr;


    // Timer only used when exiting the software
    QTimer * m_ptExitConditionsTimer;

private slots:
    // User slots
    //***********************************************************************************
    // Closing the child windows
    void SLOT_ClosingScanseLidarWindow(void);
    void SLOT_ClosingSlamwareLidarWindow(void);
    void SLOT_ClosingCoreSlamHMIWindow(void);
    void SLOT_ClosingCoreSlamPFHMIWindow(void);
    void SLOT_ClosingCommandsWindow(void);
    void SLOT_ClosingPathFinderWindow(void);

    // Check the exit conditions
    // When exit conditions are met, do exit
    void SLOT_PeriodicCheckExitConditionsThenExit();

    // Standard slots
    //***********************************************************************************
    // Show or hide the sensor UI
    void on_btn_ShowScanseLidar_clicked();
    void on_btn_ShowSlamwareLidar_clicked();
    void on_btn_ShowCoreSlam_clicked();
    void on_btn_ShowCommand_clicked();
    void on_btn_ShowPathFinder_clicked();

    // Closing the window
    void closeEvent (QCloseEvent * ptEvent);
    void on_btn_ShowCoreSlamPF_clicked();
};

#endif // C_MAIN_H
