#ifndef C_VESC_H
#define C_VESC_H

#include <stdio.h>
#include <string>

#include "ui_C_Vesc.h"
#include "C_SerialCom.h"


#include "datatypes.h"
#include "buffer.h"
#include "crc.h"

#include "C_Tools_System.h"


class C_Vesc : public QMainWindow
{
    Q_OBJECT

public:
    // Constructor
    explicit C_Vesc(QWidget * ptParent = nullptr);

    // COM port name to use to connect to the device
    bool SetComPortName(const QString & comPortName)
    {
        return m_comPort.SetComPortName(comPortName);
    }

    bool SetWindowTitle(const QString &txt)
    {
        this->setWindowTitle(txt);
        m_comPort.SetWindowTitle(txt + " : VESC COM port");

        return true;
    }

    // Connect to the device
    bool Connect(void)
    {
        return m_comPort.Connect();
    }

    // Disconnect from the device
    bool Disconnect(void)
    {
        return m_comPort.Disconnect();
    }

    // Is the device connected
    bool IsConnected(void)
    {
        return m_comPort.IsConnected();
    }

    // Set the rpm of the motor
    // rpm  - The desired RPM (actually eRPM = RPM * poles)
    void SetRpm(float rpm);

    // Set the duty of the motor
    // duty  - The desired duty (0.0-1.0)
    void SetDuty(float duty);

    // Set the current to drive the motor
    //current  - The current to apply
    void SetCurrent(float current_A);

    // Set the current to brake the motor
    // brakeCurrent  - The current to apply
    void SetBrakeCurrent(float brakeCurrent);


signals:
    // Closing the window
    void SIG_ClosingWindow(void);

private :
    // The UI of the object
    Ui::C_Vesc m_userInterface;

    // The COM port
    C_SerialCom m_comPort;


    // Struct to store the telemetry data returned by the VESC
    struct dataPackage {
        float avgMotorCurrent;
        float avgInputCurrent;
        float dutyCycleNow;
        long rpm;
        float inpVoltage;
        float ampHours;
        float ampHoursCharged;
        long tachometer;
        long tachometerAbs;
    };

    // Variabel to hold measurements returned from VESC
    dataPackage data;

    // Sends a command to VESC and stores the returned data
    bool GetVescValues(void);

    // Packs the payload and sends it over Serial
    // payload  - The payload as a unit8_t Array with length of int lenPayload
    // lenPay   - Length of payload
    // The number of bytes send
    int PackSendPayload(uint8_t * payload, int lenPay);

    // Verifies the message (CRC-16) and extracts the payload
    // message  - The received UART message
    // lenMes   - The lenght of the message
    // payload  - The final payload ready to extract data from
    // True if the process was a success
    bool UnpackPayload(uint8_t * message, int lenMes, uint8_t * payload);

    // Extracts the data from the received payload
    // message  - The payload to extract data from
    // True if the process was a success
    bool ProcessReadPacket(uint8_t * message);

    // Timer which invokes a connection management function
    QTimer m_manageAliveTimer;


private slots:
    // User slots
    //***********************************************************************************
    void SLOT_ClosingComPortWindow(void);
    // Process the received data
    void SLOT_ProcessReceivedData(const QByteArray &data);
    void SLOT_ManagePeriodicPolling();

    // Standard slots
    //***********************************************************************************
    // Closing the window
    void closeEvent (QCloseEvent * ptEvent);

    void on_btn_ShowComPort_clicked();
};

#endif // C_VESC_H
