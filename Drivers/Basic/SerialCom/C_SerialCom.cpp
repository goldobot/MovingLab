#include "C_SerialCom.h"

C_SerialCom::C_SerialCom(QWidget * ptParent) : QMainWindow(ptParent)
{
    // Configure the HMI
    m_userInterface.setupUi(this);

    m_consolePanel.setEnabled(false);
    setCentralWidget(&m_consolePanel);

    m_userInterface.actionConnect->setEnabled(true);
    m_userInterface.actionDisconnect->setEnabled(false);
    m_userInterface.actionQuit->setEnabled(true);
    m_userInterface.actionConfigure->setEnabled(true);

    m_userInterface.statusBar->addWidget(&m_statusLabel);

    //m_ptErrorStatus = new QLabel;
    m_userInterface.statusBar->addWidget(&m_errorLabel);

    //m_ptPerf = new QLabel;
    m_userInterface.statusBar->addWidget(&m_perfLabel);

    connect(m_userInterface.actionConnect, &QAction::triggered, this, &C_SerialCom::SLOT_Connect);
    connect(m_userInterface.actionDisconnect, &QAction::triggered, this, &C_SerialCom::SLOT_Disconnect);
    connect(m_userInterface.actionQuit, &QAction::triggered, this, &C_SerialCom::close);
    connect(m_userInterface.actionConfigure, &QAction::triggered, &m_settingsPanel, &C_SerialCom_Settings::show);
    connect(m_userInterface.actionClear, &QAction::triggered, &m_consolePanel, &C_SerialCom_Console::clear);

    // Hardware management
    connect(&m_serialPort, &QSerialPort::readyRead, this, &C_SerialCom::SLOT_ReadDataFromPort);
    connect(&m_consolePanel, &C_SerialCom_Console::SIG_ReadDataFromScreen, this, &C_SerialCom::SLOT_WriteDataToPort);
    connect(&m_serialPort, &QSerialPort::errorOccurred, this, &C_SerialCom::SLOT_HandlePortError);
}


void C_SerialCom::closeEvent (QCloseEvent * ptEvent)
{
    Q_UNUSED(ptEvent);

    // Send a signal to the parent
    emit SIG_ClosingWindow();
}

void C_SerialCom::SLOT_Connect()
{
    const C_SerialCom_Settings::Settings p = m_settingsPanel.settings();
    m_serialPort.setPortName(p.name);
    m_serialPort.setBaudRate(p.baudRate);
    m_serialPort.setDataBits(p.dataBits);
    m_serialPort.setParity(p.parity);
    m_serialPort.setStopBits(p.stopBits);
    m_serialPort.setFlowControl(p.flowControl);

    if (m_serialPort.open(QIODevice::ReadWrite))
    {
        m_consolePanel.setEnabled(true);
        m_consolePanel.SetLocalEcho(p.localEchoEnabled);
        m_userInterface.actionConnect->setEnabled(false);
        m_userInterface.actionDisconnect->setEnabled(true);
        m_userInterface.actionConfigure->setEnabled(false);
        ShowStatus(tr("Connected to %1 : %2, %3, %4, %5, %6")
                   .arg(p.name).arg(p.stringBaudRate).arg(p.stringDataBits)
                   .arg(p.stringParity).arg(p.stringStopBits).arg(p.stringFlowControl));
    }
    else
    {
        QMessageBox::critical(this, tr("Error"), m_serialPort.errorString());

        ShowStatus(tr("Open error"));
    }

    m_nbBytesReceived = 0;
    ShowPerf(tr("Bytes received : %1").arg(m_nbBytesReceived));
}

void C_SerialCom::SLOT_Disconnect()
{
    if (m_serialPort.isOpen())
    {
        m_serialPort.close();
    }

    m_consolePanel.setEnabled(false);
    m_userInterface.actionConnect->setEnabled(true);
    m_userInterface.actionDisconnect->setEnabled(false);
    m_userInterface.actionConfigure->setEnabled(true);

    ShowStatus(tr("Disconnected"));
}


void C_SerialCom::SLOT_ReadDataFromPort()
{
    // New data received
    QByteArray data = m_serialPort.readAll();

    // Cosmetic
    m_consolePanel.WriteDataToScreen(data);
    m_nbBytesReceived += (uint64_t)data.size();
    ShowPerf(tr("Bytes received : %1").arg(m_nbBytesReceived));

    emit SIG_NewDataReceived(data);
}

void C_SerialCom::SLOT_HandlePortError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        //QMessageBox::critical(this, tr("Critical Error"), m_serialPort.errorString());
        SLOT_Disconnect();
        SLOT_Connect();
    }
}

#include "moc_C_SerialCom.cpp"
