#include "C_Vesc.h"

C_Vesc::C_Vesc(QWidget * ptParent) :
    QMainWindow(ptParent)
{
    // Configure the HMI
    m_userInterface.setupUi(this);

    // COM port used to connect to the VESC
    m_comPort.SetWindowTitle("VESC COM port");

    connect(&m_comPort, &C_SerialCom::SIG_NewDataReceived, this, &C_Vesc::SLOT_ProcessReceivedData);

    connect(&m_comPort, &C_SerialCom::SIG_ClosingWindow, this, &C_Vesc::SLOT_ClosingComPortWindow);

    // Send timeout management
    connect(&m_manageAliveTimer, &QTimer::timeout, this, &C_Vesc::SLOT_ManagePeriodicPolling);
    m_manageAliveTimer.start(300);
}

void C_Vesc::on_btn_ShowComPort_clicked()
{
    // Is hidden, so show the window
    if(m_comPort.isHidden())
    {
        m_comPort.show();
        m_userInterface.btn_ShowComPort->setText("Hide COM port");
    }
    else
    {
        // Is shown, so hide the window
        m_comPort.hide();
        m_userInterface.btn_ShowComPort->setText("Show COM port");
    }
}

void C_Vesc::closeEvent (QCloseEvent * ptEvent)
{
    Q_UNUSED(ptEvent);

    // Send a signal to the parent
    emit SIG_ClosingWindow();
}

void C_Vesc::SLOT_ClosingComPortWindow(void)
{
    m_userInterface.btn_ShowComPort->setText("Show COM port");
}

void C_Vesc::SLOT_ManagePeriodicPolling()
{
    if(m_comPort.IsConnected())
    {
        GetVescValues();

        m_userInterface.lbl_avgMotorCurrent->setText(QString("avgMotorCurrent : %1 A").arg(data.avgMotorCurrent));
        m_userInterface.lbl_avgInputCurrent->setText(QString("avgInputCurrent : %1 A").arg(data.avgInputCurrent));
        m_userInterface.lbl_dutyCycleNow->setText(QString("dutyCycleNow : %1 %").arg(data.dutyCycleNow));
        m_userInterface.lbl_rpm->setText(QString("rpm : %1 rpm").arg(data.rpm));
        m_userInterface.lbl_inpVoltage->setText(QString("inpVoltage : %1 V").arg(data.inpVoltage));
        m_userInterface.lbl_ampHours->setText(QString("ampHours : %1 Ah").arg(data.ampHours));
        m_userInterface.lbl_ampHoursCharged->setText(QString("ampHoursCharged : %1 Ah").arg(data.ampHoursCharged));
        m_userInterface.lbl_tachometer->setText(QString("tachometer : %1 tics").arg(data.tachometer));
        m_userInterface.lbl_tachometerAbs->setText(QString("tachometerAbs : %1 tics").arg(data.tachometerAbs));
    }
}

void C_Vesc::SLOT_ProcessReceivedData(const QByteArray &data)
{
    // Read the bytes
    QByteArray allBytes = QByteArray(data);
    uint8_t readBytes[1024];
    C_Tools_System::ExtractU8(allBytes, readBytes, data.length());

    // Decode the bytes
    if(readBytes[0] == 2)
    {
        uint16_t endMessage = readBytes[1] + 5; //Payload size + 2 for sice + 3 for SRC and End.
        uint16_t lenPayload = readBytes[1];

        uint8_t payloadReceived[1024];
        if(UnpackPayload(readBytes, endMessage, payloadReceived))
        {
            if (lenPayload > 55)
            {
                ProcessReadPacket(payloadReceived); //returns true if sucessful
            }
        }
    }
}

bool C_Vesc::UnpackPayload(uint8_t * message, int lenMes, uint8_t * payload) {

    uint16_t crcMessage = 0;
    uint16_t crcPayload = 0;

    // Rebuild crc:
    crcMessage = message[lenMes - 3] << 8;
    crcMessage &= 0xFF00;
    crcMessage += message[lenMes - 2];


    // Extract payload:
    memcpy(payload, &message[2], message[1]);

    crcPayload = crc16(payload, message[1]);


    if (crcPayload == crcMessage) {

        return true;
    }else{
        return false;
    }
}

int C_Vesc::PackSendPayload(uint8_t * payload, int lenPay) {

    uint16_t crcPayload = crc16(payload, lenPay);
    int count = 0;
    uint8_t messageSend[256];

    if (lenPay <= 256)
    {
        messageSend[count++] = 2;
        messageSend[count++] = lenPay;
    }
    else
    {
        messageSend[count++] = 3;
        messageSend[count++] = (uint8_t)(lenPay >> 8);
        messageSend[count++] = (uint8_t)(lenPay & 0xFF);
    }

    memcpy(&messageSend[count], payload, lenPay);

    count += lenPay;
    messageSend[count++] = (uint8_t)(crcPayload >> 8);
    messageSend[count++] = (uint8_t)(crcPayload & 0xFF);
    messageSend[count++] = 3;
    messageSend[count] = '\0';

    QByteArray bytesToSend =  C_Tools_System::ConvToQByteArray(messageSend, count);

    // Sending package
    m_comPort.WriteData(bytesToSend);
    m_comPort.Flush();

    // Returns number of send bytes
    return count;
}

bool C_Vesc::ProcessReadPacket(uint8_t * message) {

    COMM_PACKET_ID packetId;
    int32_t ind = 0;

    packetId = (COMM_PACKET_ID)message[0];
    message++; // Removes the packetId from the actual message (payload)

    switch (packetId){
    case COMM_GET_VALUES: // Structure defined here: https://github.com/vedderb/bldc/blob/43c3bbaf91f5052a35b75c2ff17b5fe99fad94d1/commands.c#L164

        ind = 4; // Skip the first 4 bytes
        data.avgMotorCurrent 	= buffer_get_float32(message, 100.0, &ind);
        data.avgInputCurrent 	= buffer_get_float32(message, 100.0, &ind);
        ind += 8; // Skip the next 8 bytes

        //data.dutyCycleNow 		= buffer_get_float16(message, 1000.0, &ind);
        // Direct read in %
        data.dutyCycleNow 		= buffer_get_float16(message, 10.0, &ind);

        data.rpm 				= buffer_get_int32(message, &ind);
        data.inpVoltage 		= buffer_get_float16(message, 10.0, &ind);
        data.ampHours 			= buffer_get_float32(message, 10000.0, &ind);
        data.ampHoursCharged 	= buffer_get_float32(message, 10000.0, &ind);
        ind += 8; // Skip the next 8 bytes
        data.tachometer 		= buffer_get_int32(message, &ind);
        data.tachometerAbs 		= buffer_get_int32(message, &ind);
        return true;

        break;

    default:
        return false;
        break;
    }
}

bool C_Vesc::GetVescValues(void) {

    uint8_t command[1] = { COMM_GET_VALUES };
    PackSendPayload(command, 1);

    return true;
}


void C_Vesc::SetCurrent(float current_A) {
    int32_t index = 0;
    uint8_t payload[5];

    payload[index++] = COMM_SET_CURRENT;
    buffer_append_int32(payload, (int32_t)(current_A * 1000), &index);

    PackSendPayload(payload, 5);
}

void C_Vesc::SetBrakeCurrent(float brakeCurrent) {
    int32_t index = 0;
    uint8_t payload[5];

    payload[index++] = COMM_SET_CURRENT_BRAKE;
    buffer_append_int32(payload, (int32_t)(brakeCurrent * 1000), &index);

    PackSendPayload(payload, 5);
}

void C_Vesc::SetRpm(float rpm)
{
    // Protection
    if(rpm >= 100)
    {
        if(rpm > 500) rpm = 500;
    }
    else if(rpm <= -100)
    {
        if(rpm < -500) rpm = -500;
    }
    // Too low speed is zero
    else rpm = 0;

    // Hack
    //SetDuty(rpm / 2000.0);
    //return;


    int32_t index = 0;
    uint8_t payload[5];

    payload[index++] = COMM_SET_RPM ;
    buffer_append_int32(payload, (int32_t)(rpm), &index);

    PackSendPayload(payload, 5);
}

void C_Vesc::SetDuty(float duty) {
    int32_t index = 0;
    uint8_t payload[5];

    payload[index++] = COMM_SET_DUTY;
    buffer_append_int32(payload, (int32_t)(duty * 100000), &index);

    PackSendPayload(payload, 5);
}

