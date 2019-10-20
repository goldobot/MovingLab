#ifndef C_NEATO_XV_PROTOCOL_H
#define C_NEATO_XV_PROTOCOL_H

#include "constants.h"
#include "C_SerialCom.h"
#include "C_Tools_System.h"

// This class manages the communication with the Neato XV
class C_NeatoXV_Protocol: public QObject
{
    Q_OBJECT

public:
    // Constructor
    C_NeatoXV_Protocol(void)
    {
        // Build the list of commands for auto play
        AddCommand("GETLD", enum_CmdType::AUTO, 100);

        // Send timeout management
        connect(&m_manageConnectionTimer, &QTimer::timeout, this, &C_NeatoXV_Protocol::SLOT_ManageConnection);

        //m_listAutoCmd.append("GETMO");
        //m_listAutoCmd.append("GETCHARGER");
        //m_listAutoCmd.append("GETACCEL");
        //m_listAutoCmd.append("GETANA");
        //m_listAutoCmd.append("GETBUTT");
    }

    // Set the COM port
    void SetComPort(C_SerialCom * ptComPort)
    {
        m_ptComPort = ptComPort;
        connect(m_ptComPort, &C_SerialCom::SIG_NewDataReceived, this, &C_NeatoXV_Protocol::SLOT_ProcessReceivedData);
    }

    // Connect to the device
    bool Connect(void);

    // Disconnect from the device
    bool Disconnect(void);

    // Do the reset Lidar reset sequence
    // Sometime the motor goes so fast (> 5.5 rps)
    bool ResetLidar(void)
    {
        // Disable the LDS sensor
        AddCommand("setldsrotation off", C_NeatoXV_Protocol::HIGH_PRIORITY_MANUAL_CMD, 1000);

        // Disable the LDS sensor
        AddCommand("setldsrotation on", C_NeatoXV_Protocol::HIGH_PRIORITY_MANUAL_CMD);

        return true;
    }

signals:
    // New Lds Data
    void SIG_NewLidarData(uint32_t tabOfMeasures__mm[LIDAR_NB_MEASURES_PER_REVOLUTION], double scanFreq);

private:
    // Need to terminate the current connection (if any)
    bool m_needToTerminate = false;

    // The COM port used for connecting to the device
    C_SerialCom * m_ptComPort = nullptr;

    // Type of command management
    enum enum_CmdType
    {
        AUTO, NORMAL_PRIORITY_MANUAL_CMD, HIGH_PRIORITY_MANUAL_CMD
    };

    // Add a command to be executed
    bool AddCommand(QString cmdStr, enum_CmdType cmdType = NORMAL_PRIORITY_MANUAL_CMD, int cmdDelay__ms=0);

    // Get the nb of cmd to execute
    int GetNbCmdToExecute(enum_CmdType cmdType);

    // Get next command (auto or manual)
    QByteArray GetNextCmd(void);

    // Get the next command or close the connection when asked
    QByteArray GetNextCmdOrCloseConnection(void);

    // Try to execute a given cmd
    void TryExecuteCmd(QByteArray cmdToExecute);

    // Add data to the previous data
    // then check if the message is completed
    bool AddDataAndCheckMsgCompleted(const QByteArray &data);

    // Decode the Lidar data received from the device
    void DecodeLidarData(QStringList data);

    // Cumulated data
    QByteArray m_storedData;

    // End message marker
    QByteArray m_END_MSG_MARKER = QByteArray("\x0D\x0A\x1A", 3);

    // Timer which invokes a connection management function
    QTimer m_manageConnectionTimer;

    // Statistics
    int m_respTimeoutCounter = 0;

    // Auto commands management
    //*************************
    // List of auto commands
    QList<QString> m_listAutoCmd;
    QList<int> m_listAutoCmdDelay;
    int m_autoCmdCurrentIndex = 0;

    // Manual commands management
    //***************************
    QList<QString> m_listNormalPriorityManualCmd;
    QList<int> m_listNormalPriorityManualCmdDelay;

    // High priority Manual commands management
    //*****************************************
    QList<QString> m_listHighPriorityManualCmd;
    QList<int> m_listHighPriorityManualCmdDelay;

    // Current command to execute
    QByteArray m_currentCmd;
    int m_currentCmdDelay;


private slots:
    // User slots
    //***********************************************************************************

    // Timeout management and connection
    void SLOT_ManageConnection();

    // Process the received data
    void SLOT_ProcessReceivedData(const QByteArray &data);

};

#endif // C_NEATO_XV_PROTOCOL_H
