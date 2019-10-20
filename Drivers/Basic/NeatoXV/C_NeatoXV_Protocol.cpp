#include "C_NeatoXV_Protocol.h"

bool C_NeatoXV_Protocol::Connect(void)
{
    // Open the serial port
    if(m_ptComPort != nullptr)
    {
        if(m_ptComPort->Connect())
        {
            m_needToTerminate = false;

            // Init the device mode
            AddCommand("testmode on", C_NeatoXV_Protocol::HIGH_PRIORITY_MANUAL_CMD);

            // Enable LDS sensor
            AddCommand("setldsrotation on", C_NeatoXV_Protocol::HIGH_PRIORITY_MANUAL_CMD);

            // Immediate start the cmd manager
            m_manageConnectionTimer.start(0);

            return true;
        }
    }

    // No connection, it is an error
    return false;
}

bool C_NeatoXV_Protocol::Disconnect(void)
{
    if(m_ptComPort->IsConnected())
    {
        // Before disconnecting, shall finalizing stuff

        // Init the device mode
        AddCommand("testmode on", C_NeatoXV_Protocol::HIGH_PRIORITY_MANUAL_CMD);

        // Disable the LDS sensor
        AddCommand("setldsrotation off", C_NeatoXV_Protocol::HIGH_PRIORITY_MANUAL_CMD);

        // Ask for terminating
        m_needToTerminate = true;
    }

    // Never fails
    return true;
}

void C_NeatoXV_Protocol::SLOT_ManageConnection()
{
    // Stop the current timeout
    m_manageConnectionTimer.stop();

    // Connection done
    if(m_ptComPort->IsConnected())
    {
        // The command to execute
        QByteArray cmdToExecute;

        // Read the current command (if exist)
        // Currently sending a command, but timeout
        if(!m_currentCmd.isEmpty())
        {
            // Currently executing something, so it is a timeout
            m_respTimeoutCounter++;
            m_ptComPort->ShowError(tr("Resp. timeout counter : %1").arg(m_respTimeoutCounter));

            // Redo the same command
            cmdToExecute = m_currentCmd;
        }
        else
        {
            // No current command, so read the next command
            cmdToExecute = GetNextCmdOrCloseConnection();
        }

        // Execute the command
        TryExecuteCmd(cmdToExecute);
    }
    else
    {
        // No connection, just wait a bit
        m_manageConnectionTimer.start(250);
    }
}

void C_NeatoXV_Protocol::SLOT_ProcessReceivedData(const QByteArray &data)
{
    // Check wether the response is completed
    if(AddDataAndCheckMsgCompleted(data))
    {
        // Stop the timeout timer
        m_manageConnectionTimer.stop();

        // Decode the received response

        // Convert into string
        QString dataStr(m_storedData);

        // Split into strings chunck
        QStringList listChunckStr =  dataStr.split("\r\n", QString::SkipEmptyParts);

        if(((QString)listChunckStr.value(0)).startsWith("GETLD", Qt::CaseInsensitive))
        {
            // Send a signal to the parent
            DecodeLidarData(listChunckStr);
        }

        // Before executing the next command, wait the specified time for the previous cmd
        C_Tools_System::delay__ms(m_currentCmdDelay);

        // Execute the next command
        TryExecuteCmd(GetNextCmdOrCloseConnection());
    }
}

bool C_NeatoXV_Protocol::AddDataAndCheckMsgCompleted(const QByteArray &newData)
{
    // Add new data to the previous data
    m_storedData.append(newData);

    // Check if the whole message is completed
    int indexOfEndMsg = m_storedData.indexOf(m_END_MSG_MARKER);

    // Marker found
    if(indexOfEndMsg >=0)
    {
        // Only keep the data before the marker
        m_storedData.truncate(indexOfEndMsg);

        return true;
    }

    return false;
}

// Add a command to be executed
bool C_NeatoXV_Protocol::AddCommand(QString cmdStr, enum_CmdType cmdType, int cmdDelay__ms)
{
    bool result = true;

    switch(cmdType)
    {
    case AUTO:
        m_listAutoCmd.append(cmdStr);
        m_listAutoCmdDelay.append(cmdDelay__ms);
        break;

    case NORMAL_PRIORITY_MANUAL_CMD:
        m_listNormalPriorityManualCmd.append(cmdStr);
        m_listNormalPriorityManualCmdDelay.append(cmdDelay__ms);
        break;

    case HIGH_PRIORITY_MANUAL_CMD:
        m_listHighPriorityManualCmd.append(cmdStr);
        m_listHighPriorityManualCmdDelay.append(cmdDelay__ms);
        break;

    default:
        result = false;
    }

    return result;
}

int C_NeatoXV_Protocol::GetNbCmdToExecute(enum_CmdType cmdType)
{
    int nbCmd = 0;

    switch(cmdType)
    {
    case AUTO:
        nbCmd = m_listAutoCmd.count();
        break;

    case NORMAL_PRIORITY_MANUAL_CMD:
        nbCmd = m_listNormalPriorityManualCmd.count();
        break;

    case HIGH_PRIORITY_MANUAL_CMD:
        nbCmd = m_listHighPriorityManualCmd.count();
        break;

    default:
        break;
    }

    return nbCmd;
}

QByteArray C_NeatoXV_Protocol::GetNextCmd(void)
{
    // Clear the current command
    m_currentCmd.clear();

    // Now read the next command if exists
    if(!m_listHighPriorityManualCmd.isEmpty())
    {
        m_currentCmd = m_listHighPriorityManualCmd.takeFirst().toUtf8();
        m_currentCmdDelay = m_listHighPriorityManualCmdDelay.takeFirst();
    }
    else if(!m_listNormalPriorityManualCmd.isEmpty())
    {
        m_currentCmd = m_listNormalPriorityManualCmd.takeFirst().toUtf8();
        m_currentCmdDelay = m_listNormalPriorityManualCmdDelay.takeFirst();
    }
    else if(!m_listAutoCmd.isEmpty())
    {
        m_currentCmd = m_listAutoCmd[m_autoCmdCurrentIndex].toUtf8();
        m_currentCmdDelay = m_listAutoCmdDelay[m_autoCmdCurrentIndex];

        m_autoCmdCurrentIndex = (m_autoCmdCurrentIndex + 1) % m_listAutoCmd.size();
    }

    return m_currentCmd;
}

QByteArray C_NeatoXV_Protocol:: GetNextCmdOrCloseConnection(void)
{
    // The command to execute
    QByteArray cmdToExecute;

    // Normal case
    if(!m_needToTerminate)
    {
        // Try to read the next command to execute
        cmdToExecute = GetNextCmd();
    }
    else
    {
        // We are not allow to connect
        // But there are high priority cmd
        // So do it
        if(GetNbCmdToExecute(C_NeatoXV_Protocol::HIGH_PRIORITY_MANUAL_CMD) > 0)
        {
            cmdToExecute = GetNextCmd();
        }
        else
        {
            // Nothing important remained, can close the connection
            m_ptComPort->Disconnect();
        }
    }

    return cmdToExecute;
}

void C_NeatoXV_Protocol::TryExecuteCmd(QByteArray cmdToExecute)
{
    // Nothing to send, wait a bit
    if(cmdToExecute.isEmpty())
    {
        m_manageConnectionTimer.start(100);
    }
    else
    {
        // Prepare the next reception
        m_storedData.clear();

        // Send the command
        m_ptComPort->WriteData(cmdToExecute);
        m_ptComPort->WriteData("\n");
        m_ptComPort->Flush();

        // Allow an amount of execution time
        m_manageConnectionTimer.start(1000);
    }
}

void C_NeatoXV_Protocol::DecodeLidarData(QStringList data)
{
    // The size shall be exactly 363
    if(data.count() == 363)
    {
        // Decode each data line

        // By default, no measure
        uint32_t tabDistMeasures__mm[LIDAR_NB_MEASURES_PER_REVOLUTION] = {0};

        // Forget the 1st line : it is the command name
        // Forget the 2nd line : it is the data header
        // Forget the last line : it is the motor speed
        for(int index = 2, angle = 179; index < 362; index++, angle--)
        {
            if(angle < 0)
            {
                angle = 359;
            }

            // Separate data fields
            QStringList measure = data[index].split(',');

            // Check the number of fields is exactly 4
            if (measure.count() == 4)
            {
                // Check the error code
                if ( measure[3].toInt() == 0)
                {
                    tabDistMeasures__mm[angle] = measure[1].toUInt();
                }
            }
        }

        // Get the Lds rotation speed
        QStringList motorSpeed = data[362].split(',');

        double lidarMotorSpeed = 0.0;

        if (motorSpeed.count() == 2)
        {
            lidarMotorSpeed = motorSpeed[1].replace(',','.').toDouble();
        }

        // Send a signal to the parent
        emit SIG_NewLidarData(tabDistMeasures__mm, lidarMotorSpeed);
    }
}


#include "moc_C_NeatoXV_Protocol.cpp"
