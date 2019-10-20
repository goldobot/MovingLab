#include "C_ScanseLidar_Protocol.h"

bool C_ScanseLidar_Protocol::Connect(void)
{
    // Open the serial port
    if(m_ptComPort != nullptr)
    {
        if(m_ptComPort->Connect())
        {
            m_needToTerminate = false;

            // Start scanning
            AddStartScanningSequence();

            // Immediate start the cmd manager
            m_manageConnectionTimer.start(0);

            return true;
        }
    }

    // No connection, it is an error
    return false;
}

bool C_ScanseLidar_Protocol::Disconnect(void)
{
    if(m_ptComPort->IsConnected())
    {
        // Not scanning anymore
        m_scanningInProgress = false;

        // Before disconnecting, shall finalizing stuff

        // Stop scanning
        AddCommand("DX", C_ScanseLidar_Protocol::HIGH_PRIORITY_MANUAL_CMD);

        // Stop the motor
        AddCommand("MS00", C_ScanseLidar_Protocol::HIGH_PRIORITY_MANUAL_CMD);

        // Ask for terminating
        m_needToTerminate = true;
    }

    // Never fails
    return true;
}

void C_ScanseLidar_Protocol::SLOT_ManageConnection()
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
        if((!m_currentCmd.isEmpty()) && (m_currentCmdDelay >= 0))
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


bool C_ScanseLidar_Protocol::FilterMeasures(void)
{
    int32_t dist_2 = 0;
    int32_t dist_1 = 0;
    int32_t dist_0 = 0;

    double angle_2 = 0.0;
    double angle_1 = 0.0;
    double angle_0 = 0.0;

    int cumulPoint = 0;

    int writeIndex = 0;

    // Read the whole table
    // Do 3 points average
    for(int readIndex = 0; readIndex < m_nbOfMeasures; readIndex++)
    {
        // Shift register mecanism
        dist_2 = dist_1;
        dist_1 = dist_0;
        dist_0 = m_tabDistMeasures__mm[readIndex];

        angle_2 = angle_1;
        angle_1 = angle_0;
        angle_0 = m_tabAngleMeasures__rad[readIndex];

        cumulPoint++;

        // First point
        if(cumulPoint == 1)
        {
            m_tabDistMeasures__mm[writeIndex++] = dist_0;
        }

        // At least 2 measures cumulated
        if(cumulPoint >= 2)
        {
            // The 2 points are so differents
            if((abs(angle_1 - angle_0) > 2.54) || (abs(dist_1 - dist_0) > 200))
            {
                // Store the cumulated measures
                if(cumulPoint > 2) m_tabDistMeasures__mm[writeIndex++] = dist_1;
                m_tabDistMeasures__mm[writeIndex++] = dist_0;

                cumulPoint = 0;
            }
        }

        // At least 3 measures cumulated (and they are near from each to the others)
        if(cumulPoint > 2)
        {
            m_tabDistMeasures__mm[writeIndex++] = (dist_2 + dist_1 + dist_0) / 3;
        }
    }


    // There remains cumulated point
    if(cumulPoint >= 2)
    {
        m_tabDistMeasures__mm[writeIndex++] = dist_0;
    }

    return true;
}

void C_ScanseLidar_Protocol::SLOT_ProcessReceivedData(const QByteArray &data)
{
    // Check wether the response is completed
    if(AddDataAndCheckMsgCompleted(data))
    {
        // Stop the timeout timer
        m_manageConnectionTimer.stop();

        // Before executing the next command, wait the specified time for the previous cmd
        C_Tools_System::delay__ms(m_currentCmdDelay);

        // Execute the next command
        TryExecuteCmd(GetNextCmdOrCloseConnection());
    }

    // We are scanning
    if(m_scanningInProgress)
    {
        uint8_t oneScan[7] = {0};

        while(C_Tools_System::ExtractU8(m_storedData, oneScan, sizeof (oneScan)))
        {
            // TODO: validate receipt
            uint8_t i = 0;

            // SYNC BIT : Special case where we got the first scan of the current rotation
            if(oneScan[i++] & 0x01)
            {
                // Filter the measurements
                FilterMeasures();

                // For optimization purpose, compute the sin and cos because everyone need cos and sin
                double * ptAngle__rad = m_tabAngleMeasures__rad;
                double * ptAngle__cos = m_tabAngleMeasures__cos;
                double * ptAngle__sin = m_tabAngleMeasures__sin;

                for(int i = 0; i < m_nbOfMeasures; i++)
                {
                    *ptAngle__cos = cos(*ptAngle__rad);
                    *ptAngle__sin = sin(*ptAngle__rad);

                    ptAngle__rad++; ptAngle__cos++; ptAngle__sin++;
                }


                // Publish the previous measures
                emit SIG_NewLidarData(SCANSE_LIDAR_ID, m_tabDistMeasures__mm, m_tabAngleMeasures__cos, m_tabAngleMeasures__sin, m_nbOfMeasures);

                // Reset the current measures
                m_nbOfMeasures = 0;
            }

            // read raw fixed point azimuth value
            uint16_t rawAngle_lsb = oneScan[i++];
            uint16_t rawAngle_msb = oneScan[i++] << 8;
            double angleDeg = (double)(rawAngle_lsb + rawAngle_msb) / 16.0;

            // read distance value
            uint16_t distance_lsb = oneScan[i++];
            uint16_t distance_msb = oneScan[i++] << 8;
            uint16_t distance = 10 * (distance_lsb + distance_msb) - 145;

            // read signal strength value
            uint8_t signalStrength = oneScan[i++];

            // Copy the decoded data
            if((signalStrength > 60) && (angleDeg >= 0) && (angleDeg <= 360.0) && (distance >= 300))
            {
                m_tabDistMeasures__mm[m_nbOfMeasures] = distance;
                m_tabAngleMeasures__rad[m_nbOfMeasures] = (360.0 - angleDeg) * MATHS_CONV_DEG_2_RAD;
                m_nbOfMeasures++;
            }
        }
    }
}

bool C_ScanseLidar_Protocol::AddDataAndCheckMsgCompleted(const QByteArray &newData)
{
    // Add new data to the previous data
    m_storedData.append(newData);

    if(!m_scanningInProgress)
    {
        // Check if the whole message contains error
        int indexOfEndMsg = m_storedData.indexOf(m_END_MSG_ERROR_MARKER);

        // Marker found
        if(indexOfEndMsg >=0)
        {
            // Restart all
            ClearAllCommands();

            // CLear all previous received data
            m_storedData.clear();

            // Reset the lidar
            ResetLidar();

            return false;
        }


        // Special case where we got the start of scan
        indexOfEndMsg = m_storedData.indexOf(m_ACK_SCAN_CMD_MARKER);

        // Marker found
        if(indexOfEndMsg >=0)
        {
            // CLear all data before the marker
            // Because only what incoming after the marker is interesting

            m_scanningInProgress = true;

            // Reset the current cmd (because it is the scan cmd and we got it)
            m_currentCmd.clear();
            m_currentCmdDelay = 0;

            m_storedData.remove(0, indexOfEndMsg + m_ACK_SCAN_CMD_MARKER.length());

            return false;
        }


        // Check if the whole message is completed
        indexOfEndMsg = m_storedData.indexOf(m_END_MSG_MARKER);

        // Marker found
        if(indexOfEndMsg >=0)
        {
            // Only keep the data before the marker
            m_storedData.truncate(indexOfEndMsg);

            return true;
        }
    }

    return false;
}

// Add a command to be executed
bool C_ScanseLidar_Protocol::AddCommand(QString cmdStr, enum_CmdType cmdType, int cmdDelay__ms)
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

int C_ScanseLidar_Protocol::GetNbCmdToExecute(enum_CmdType cmdType)
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

QByteArray C_ScanseLidar_Protocol::GetNextCmd(void)
{
    // Clear the current command
    m_currentCmd.clear();
    m_currentCmdDelay = 0;

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

QByteArray C_ScanseLidar_Protocol:: GetNextCmdOrCloseConnection(void)
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
        if(GetNbCmdToExecute(C_ScanseLidar_Protocol::HIGH_PRIORITY_MANUAL_CMD) > 0)
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

void C_ScanseLidar_Protocol::TryExecuteCmd(QByteArray cmdToExecute)
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

#include "moc_C_ScanseLidar_Protocol.cpp"
