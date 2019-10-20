#ifndef C_SERIALCOM_SETTINGS_H
#define C_SERIALCOM_SETTINGS_H

#include <QSerialPort>
#include <QSerialPortInfo>

#include "ui_C_SerialCom_Settings.h"

class C_SerialCom_Settings : public QDialog
{
    Q_OBJECT

public:
    // Constructor
    explicit C_SerialCom_Settings(QWidget *parent = nullptr);

    struct Settings {
        QString name;
        qint32 baudRate;
        QString stringBaudRate;
        QSerialPort::DataBits dataBits;
        QString stringDataBits;
        QSerialPort::Parity parity;
        QString stringParity;
        QSerialPort::StopBits stopBits;
        QString stringStopBits;
        QSerialPort::FlowControl flowControl;
        QString stringFlowControl;
        bool localEchoEnabled;
    };

    bool SetComPortName(const QString & comPortName);

    Settings settings() const
    {
        return m_currentSettings;
    }

private:
    Ui::C_SerialCom_Settings m_userInterface;
    Settings m_currentSettings;

    void FillPortsParameters();
    void FillPortsInfo();
    void UpdateSettings();


private slots:
    // User slots
    //***********************************************************************************
    void SLOT_ShowPortInfo(int idx);

    void SLOT_ApplySettings()
    {
        UpdateSettings();
        hide();
    }

    void SLOT_CheckCustomBaudRatePolicy(int idx);
    void SLOT_CheckCustomDevicePathPolicy(int idx);

};

static const char SerialCom_blankString[] = QT_TRANSLATE_NOOP("SettingsDialog", "N/A");

#endif // C_SERIALCOM_SETTINGS_H
