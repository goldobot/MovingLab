#ifndef C_SCANSE_LIDAR_PROTOCOL_H
#define C_SCANSE_LIDAR_PROTOCOL_H

#include <math.h>
#include <QSemaphore>

#include "Constants.h"
#include "C_SerialCom.h"
#include "C_Tools_System.h"
#include "C_Tools_Maths.h"

// This class manages the communication with the ScanseLidar
class C_ScanseLidar_Protocol: public QObject
{
    Q_OBJECT

public:
    // Constructor
    C_ScanseLidar_Protocol(void)
    {
        // Send timeout management
        connect(&m_manageConnectionTimer, &QTimer::timeout, this, &C_ScanseLidar_Protocol::SLOT_ManageConnection);
    }

    // Set the COM port
    void SetComPort(C_SerialCom * ptComPort)
    {
        m_ptComPort = ptComPort;
        connect(m_ptComPort, &C_SerialCom::SIG_NewDataReceived, this, &C_ScanseLidar_Protocol::SLOT_ProcessReceivedData);
    }

    // Connect to the device
    bool Connect(void);

    // Disconnect from the device
    bool Disconnect(void);

    // Do the reset Lidar reset sequence
    bool ResetLidar(void)
    {
        // Not scanning anymore
        m_scanningInProgress = false;

        // Do reset
        AddCommand("RR", HIGH_PRIORITY_MANUAL_CMD, 10000);

        // Restart scanning
        AddStartScanningSequence();

        return true;
    }

    bool AddStartScanningSequence(void)
    {
        // Init the device scan rate (1000 Hz)
        AddCommand("LR03", C_ScanseLidar_Protocol::HIGH_PRIORITY_MANUAL_CMD);

        // Init the device scan speed (6 rps)
        AddCommand("MS06", C_ScanseLidar_Protocol::HIGH_PRIORITY_MANUAL_CMD, 8000);

        // Start scanning
        AddCommand("DS", C_ScanseLidar_Protocol::NORMAL_PRIORITY_MANUAL_CMD);

        return true;
    }

signals:
    // New Lds Data
    void SIG_NewLidarData(int sensorId, uint32_t * tabOfMeasures__mm, double * tabOfMeasures__cos, double * tabOfMeasures__sin, uint32_t nbOfMeasures);

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

    bool ClearAllCommands(void)
    {
        m_listNormalPriorityManualCmd.clear();
        m_listNormalPriorityManualCmdDelay.clear();
        m_listHighPriorityManualCmd.clear();
        m_listHighPriorityManualCmdDelay.clear();
        m_currentCmd.clear();
        m_currentCmdDelay = 0;

        return true;
    }

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
    //void DecodeLidarData(QStringList data);

    // Cumulated data
    QByteArray m_storedData;

    // End message marker
    QByteArray m_END_MSG_MARKER = QByteArray("\x30\x30\x50\x0A", 4);
    QByteArray m_END_MSG_ERROR_MARKER = QByteArray("13T\x0A", 4);
    QByteArray m_ACK_SCAN_CMD_MARKER = QByteArray("DS00P\n", 6);

    // Timer which invokes a connection management function
    QTimer m_manageConnectionTimer;

    // Statistics
    int m_respTimeoutCounter = 0;

    // Auto commands management
    //*************************
    // List of auto commands
    QList<QString> m_listAutoCmd;

    // >= 0 : Wait the reply then the timeout
    // < 0 : No wait (neither reply nor timeout)
    QList<int> m_listAutoCmdDelay;
    int m_autoCmdCurrentIndex = 0;

    // Manual commands management
    //***************************
    QList<QString> m_listNormalPriorityManualCmd;

    // >= 0 : Wait the reply then the timeout
    // < 0 : No wait (neither reply nor timeout)
    QList<int> m_listNormalPriorityManualCmdDelay;

    // High priority Manual commands management
    //*****************************************
    QList<QString> m_listHighPriorityManualCmd;

    // >= 0 : Wait the reply then the timeout
    // < 0 : No wait (neither reply nor timeout)
    QList<int> m_listHighPriorityManualCmdDelay;

    // Current command to execute
    QByteArray m_currentCmd;

    // >= 0 : Wait the reply then the timeout
    // < 0 : No wait (neither reply nor timeout)
    int m_currentCmdDelay;

    // True if the device is currently scanning
    bool m_scanningInProgress = false;
    uint32_t m_tabDistMeasures__mm[LIDAR_MAX_NB_MEASURES_PER_REVOLUTION] = {0};
    double m_tabAngleMeasures__rad[LIDAR_MAX_NB_MEASURES_PER_REVOLUTION] = {0};
    double m_tabAngleMeasures__cos[LIDAR_MAX_NB_MEASURES_PER_REVOLUTION] = {0};
    double m_tabAngleMeasures__sin[LIDAR_MAX_NB_MEASURES_PER_REVOLUTION] = {0};
    uint32_t m_nbOfMeasures = 0;

    bool FilterMeasures(void);

private slots:
    // User slots
    //***********************************************************************************

    // Timeout management and connection
    void SLOT_ManageConnection();

    // Process the received data
    void SLOT_ProcessReceivedData(const QByteArray &data);

};

#endif // C_SCANSE_LIDAR_PROTOCOL_H
