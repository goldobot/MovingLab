#include "C_Main.h"

C_Main::C_Main(QWidget * ptParent) :
    QMainWindow(ptParent)
{
    // Configure the HMI
    m_userInterface.setupUi(this);

    // Objects config
    if(m_scanseLidar.SetComPortName("COM5")) m_scanseLidar.Connect();

    m_ptCoreSlamHMI = new C_CoreSlam_HMI(nullptr, &m_scanseLidar, &m_slamwareLidar);
    //m_ptCoreSlamPFHMI = new C_CoreSlamPF_HMI(nullptr, &m_scanseLidar, &m_slamwareLidar);

    if(m_twoWheelsBase.SetComPortName("COM13", "COM7")) m_twoWheelsBase.Connect();

    m_ptPathFinder = new C_PathFinder(0, m_ptCoreSlamHMI->GET_ThnlGlobalMapScale__mmPerPixel());
    //m_ptPathFinder = new C_PathFinder(0, m_ptCoreSlamPFHMI->GET_ThnlGlobalMapScale__mmPerPixel());


    // Date flow connection
    connect(m_ptPathFinder, &C_PathFinder::SIG_ExecuteCmd, &m_twoWheelsBase, &C_TwoWheelsBase::SLOT_StoreNewCmd);
    connect(m_ptCoreSlamHMI, &C_CoreSlam_HMI::SIG_NewEstimation, m_ptPathFinder, &C_PathFinder::SLOT_StoreNewEstimation);
    //connect(m_ptCoreSlamPFHMI, &C_CoreSlamPF_HMI::SIG_NewEstimation, m_ptPathFinder, &C_PathFinder::SLOT_StoreNewEstimation);

    // Closing windows management
    connect(&m_scanseLidar, &C_ScanseLidar::SIG_ClosingWindow, this, &C_Main::SLOT_ClosingScanseLidarWindow);
    connect(&m_slamwareLidar, &C_Slamware::SIG_ClosingWindow, this, &C_Main::SLOT_ClosingSlamwareLidarWindow);
    connect(m_ptCoreSlamHMI, &C_CoreSlam_HMI::SIG_ClosingWindow, this, &C_Main::SLOT_ClosingCoreSlamHMIWindow);
    //connect(m_ptCoreSlamPFHMI, &C_CoreSlamPF_HMI::SIG_ClosingWindow, this, &C_Main::SLOT_ClosingCoreSlamPFHMIWindow);
    connect(&m_twoWheelsBase, &C_TwoWheelsBase::SIG_ClosingWindow, this, &C_Main::SLOT_ClosingCommandsWindow);
    connect(m_ptPathFinder, &C_PathFinder::SIG_ClosingWindow, this, &C_Main::SLOT_ClosingPathFinderWindow);
}

void C_Main::on_btn_ShowScanseLidar_clicked()
{
    // Is hidden, so show the window
    if(m_scanseLidar.isHidden())
    {
        m_scanseLidar.show();
        m_userInterface.btn_ShowScanseLidar->setText("Hide Scanse Lidar");
    }
    else
    {
        // Is shown, so hide the window
        m_scanseLidar.hide();
        m_userInterface.btn_ShowScanseLidar->setText("Show Scanse Lidar");
    }
}

void C_Main::on_btn_ShowSlamwareLidar_clicked()
{
    // Is hidden, so show the window
    if(m_slamwareLidar.isHidden())
    {
        m_slamwareLidar.show();
        m_userInterface.btn_ShowSlamwareLidar->setText("Hide Slamware Lidar");
    }
    else
    {
        // Is shown, so hide the window
        m_slamwareLidar.hide();
        m_userInterface.btn_ShowSlamwareLidar->setText("Show Slamware Lidar");
    }
}


void C_Main::on_btn_ShowCoreSlam_clicked()
{
    // Is hidden, so show the window
    if(m_ptCoreSlamHMI->isHidden())
    {
        m_ptCoreSlamHMI->show();
        m_userInterface.btn_ShowCoreSlam->setText("Hide CoreSlam MHI");
    }
    else
    {
        // Is shown, so hide the window
        m_ptCoreSlamHMI->hide();
        m_userInterface.btn_ShowCoreSlam->setText("Show CoreSlam MHI");
    }
}


void C_Main::on_btn_ShowCoreSlamPF_clicked()
{
    /*
    // Is hidden, so show the window
    if(m_ptCoreSlamPFHMI->isHidden())
    {
        m_ptCoreSlamPFHMI->show();
        m_userInterface.btn_ShowCoreSlamPF->setText("Hide CoreSlamPF MHI");
    }
    else
    {
        // Is shown, so hide the window
        m_ptCoreSlamPFHMI->hide();
        m_userInterface.btn_ShowCoreSlamPF->setText("Show CoreSlamPF MHI");
    }
    */
}


void C_Main::on_btn_ShowCommand_clicked()
{
    // Is hidden, so show the window
    if(m_twoWheelsBase.isHidden())
    {
        m_twoWheelsBase.show();
        m_userInterface.btn_ShowCommand->setText("Hide Commands");
    }
    else
    {
        // Is shown, so hide the window
        m_twoWheelsBase.hide();
        m_userInterface.btn_ShowCommand->setText("Show Commands");
    }
}

void C_Main::on_btn_ShowPathFinder_clicked()
{
    // Is hidden, so show the window
    if(m_ptPathFinder->isHidden())
    {
        m_ptPathFinder->show();
        m_userInterface.btn_ShowPathFinder->setText("Hide Path Finder");
    }
    else
    {
        // Is shown, so hide the window
        m_ptPathFinder->hide();
        m_userInterface.btn_ShowPathFinder->setText("Show Path Finder");
    }
}

void C_Main::SLOT_ClosingScanseLidarWindow(void)
{
    m_userInterface.btn_ShowScanseLidar->setText("Show Scanse Lidar");
}

void C_Main::SLOT_ClosingSlamwareLidarWindow(void)
{
    m_userInterface.btn_ShowSlamwareLidar->setText("Show Slamware Lidar");
}

void C_Main::SLOT_ClosingCoreSlamHMIWindow(void)
{
    m_userInterface.btn_ShowCoreSlam->setText("Show CoreSlam MHI");
}

void C_Main::SLOT_ClosingCoreSlamPFHMIWindow(void)
{
    m_userInterface.btn_ShowCoreSlamPF->setText("Show CoreSlamPF MHI");
}

void C_Main::SLOT_ClosingCommandsWindow(void)
{
    m_userInterface.btn_ShowCommand->setText("Show Commands");
}

void C_Main::SLOT_ClosingPathFinderWindow(void)
{
    m_userInterface.btn_ShowPathFinder->setText("Show Path Finder");
}

void C_Main::closeEvent (QCloseEvent * ptEvent)
{
    // Ask for confirmation
    QMessageBox::StandardButton resBtn = QMessageBox::question( this, "Exiting confirmation...",
                                                                tr("Do you really want to exit ?"),
                                                                QMessageBox::No | QMessageBox::Yes,
                                                                QMessageBox::Yes);
    // Exit confirmed
    if (resBtn == QMessageBox::Yes)
    {
        // Disconnect from the Scanse
        m_scanseLidar.Disconnect();

        // Start the exiting procedure
        m_ptExitConditionsTimer = new QTimer(this);
        connect(m_ptExitConditionsTimer, &QTimer::timeout, this, &C_Main::SLOT_PeriodicCheckExitConditionsThenExit);

        // Start the exit procedure timer
        m_ptExitConditionsTimer->start(100);
    }

    // Ignore the event
    // Because the Checking exit function will do the effective exit (if needed)
    ptEvent->ignore();
}

void C_Main::SLOT_PeriodicCheckExitConditionsThenExit()
{
    // The robot is disconnected
    if(!m_scanseLidar.IsConnected())
    {
        // Delete myself
        delete this;
    }
}

#include "moc_C_Main.cpp"
