#ifndef C_SERIALCOM_H
#define C_SERIALCOM_H

#include <QMessageBox>

#include "ui_C_SerialCom.h"
#include "C_SerialCom_Settings.h"
#include "C_SerialCom_Console.h"


class C_SerialCom : public QMainWindow
{
    Q_OBJECT

public:
    // Constructor
    explicit C_SerialCom(QWidget * ptParent = nullptr);

    bool SetComPortName(const QString & comPortName)
    {
        return m_settingsPanel.SetComPortName(comPortName);
    }

    // Do the connection
    bool Connect(void)
    {
        // Not connected, so connect
        if(!m_serialPort.isOpen()) SLOT_Connect();

        return m_serialPort.isOpen();
    }

    // Do the disconnection
    bool Disconnect(void)
    {
        // Connected, so disconnect
        if(m_serialPort.isOpen()) SLOT_Disconnect();

        return !(m_serialPort.isOpen());
    }

    bool SetWindowTitle(const QString &txt)
    {
        this->setWindowTitle(txt);
        return true;
    }

    // Is connected
    bool IsConnected(void)
    {
        return m_serialPort.isOpen();
    }

    bool WriteData(const QByteArray &data)
    {
        m_serialPort.write(data);
        return true;
    }

    int ReadData(void * dest, int nbMaxOfBytesToRead)
    {
        char buff[4096];

        int nbOfReadBytes = m_serialPort.read(buff, nbMaxOfBytesToRead);

        if(nbOfReadBytes > 0)
        {
            memcpy(dest, buff, nbOfReadBytes);
        }

        return nbOfReadBytes;
    }

    bool Flush()
    {
        m_serialPort.flush();
        return true;
    }

    void ShowError(const QString &message)
    {
        m_errorLabel.setText(message);
    }

signals:
    // Closing the window
    void SIG_ClosingWindow(void);

    // Closing the window
    void SIG_NewDataReceived(const QByteArray &data);

private :
    // The UI of the object
    Ui::C_SerialCom m_userInterface;

    // Physical serial port
    QSerialPort m_serialPort;

    // Setting window
    C_SerialCom_Settings m_settingsPanel;

    // Console window
    C_SerialCom_Console m_consolePanel;

    // Status
    void ShowStatus(const QString &message)
    {
        m_statusLabel.setText(message);
    }
    QLabel m_statusLabel;

    // Statistics
    void ShowPerf(const QString &message)
    {
        m_perfLabel.setText(message);
    }
    QLabel m_perfLabel;
    uint64_t m_nbBytesReceived = 0;

    // Error
    QLabel m_errorLabel;

private slots:
    // User slots
    //***********************************************************************************
    // Button on the HMI
    void SLOT_Connect();
    void SLOT_Disconnect();

    // Hardware management
    void SLOT_ReadDataFromPort();
    void SLOT_HandlePortError(QSerialPort::SerialPortError error);

    void SLOT_WriteDataToPort(const QByteArray &data)
    {
        m_serialPort.write(data);
    }

    // Standard slots
    //***********************************************************************************
    // Closing the window event
    void closeEvent (QCloseEvent * ptEvent);
};

#endif // C_SERIALCOM_H
