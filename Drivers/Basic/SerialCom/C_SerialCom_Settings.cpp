#include "C_SerialCom_Settings.h"


C_SerialCom_Settings::C_SerialCom_Settings(QWidget *parent) :
    QDialog(parent)
{
    // Configure the HMI
    m_userInterface.setupUi(this);

    m_userInterface.baudRateBox->setInsertPolicy(QComboBox::NoInsert);

    connect(m_userInterface.applyButton, &QPushButton::clicked,
            this, &C_SerialCom_Settings::SLOT_ApplySettings);
    connect(m_userInterface.serialPortInfoListBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &C_SerialCom_Settings::SLOT_ShowPortInfo);
    connect(m_userInterface.baudRateBox,  QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &C_SerialCom_Settings::SLOT_CheckCustomBaudRatePolicy);
    connect(m_userInterface.serialPortInfoListBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &C_SerialCom_Settings::SLOT_CheckCustomDevicePathPolicy);

    FillPortsParameters();
    FillPortsInfo();
    UpdateSettings();
}

// Scan th whole list of detected port and take the one of the given name
bool C_SerialCom_Settings::SetComPortName(const QString & comPortName)
{

    int indexOfPortName = m_userInterface.serialPortInfoListBox->findText(comPortName);

    if(indexOfPortName >= 0)
    {
        m_userInterface.serialPortInfoListBox->setCurrentIndex(indexOfPortName);
        UpdateSettings();
        return true;
    }

    return false;
}

void C_SerialCom_Settings::SLOT_ShowPortInfo(int idx)
{
    if (idx == -1)
        return;

    const QStringList list = m_userInterface.serialPortInfoListBox->itemData(idx).toStringList();
    m_userInterface.descriptionLabel->setText(tr("Description: %1").arg(list.count() > 1 ? list.at(1) : tr(SerialCom_blankString)));
    m_userInterface.manufacturerLabel->setText(tr("Manufacturer: %1").arg(list.count() > 2 ? list.at(2) : tr(SerialCom_blankString)));
    m_userInterface.serialNumberLabel->setText(tr("Serial number: %1").arg(list.count() > 3 ? list.at(3) : tr(SerialCom_blankString)));
    m_userInterface.locationLabel->setText(tr("Location: %1").arg(list.count() > 4 ? list.at(4) : tr(SerialCom_blankString)));
    m_userInterface.vidLabel->setText(tr("Vendor Identifier: %1").arg(list.count() > 5 ? list.at(5) : tr(SerialCom_blankString)));
    m_userInterface.pidLabel->setText(tr("Product Identifier: %1").arg(list.count() > 6 ? list.at(6) : tr(SerialCom_blankString)));
}


void C_SerialCom_Settings::SLOT_CheckCustomBaudRatePolicy(int idx)
{
    const bool isCustomBaudRate = !m_userInterface.baudRateBox->itemData(idx).isValid();
    if (isCustomBaudRate)
    {
        if(m_userInterface.baudRateBox->currentIndex() > 4)
        {
            m_userInterface.baudRateBox->setEditable(isCustomBaudRate);
            m_userInterface.baudRateBox->clearEditText();
            QLineEdit *edit = m_userInterface.baudRateBox->lineEdit();

            edit->setValidator(new QIntValidator(0, 4000000));
        }
    }
}

void C_SerialCom_Settings::SLOT_CheckCustomDevicePathPolicy(int idx)
{
    const bool isCustomPath = !m_userInterface.serialPortInfoListBox->itemData(idx).isValid();
    m_userInterface.serialPortInfoListBox->setEditable(isCustomPath);
    if (isCustomPath)
        m_userInterface.serialPortInfoListBox->clearEditText();
}

void C_SerialCom_Settings::FillPortsParameters()
{
    m_userInterface.baudRateBox->addItem(QStringLiteral("9600"), QSerialPort::Baud9600);
    m_userInterface.baudRateBox->addItem(QStringLiteral("19200"), QSerialPort::Baud19200);
    m_userInterface.baudRateBox->addItem(QStringLiteral("38400"), QSerialPort::Baud38400);
    m_userInterface.baudRateBox->addItem(QStringLiteral("115200"), QSerialPort::Baud115200);
    m_userInterface.baudRateBox->addItem(tr("250000"));
    m_userInterface.baudRateBox->addItem(tr("Custom"));
    m_userInterface.baudRateBox->setCurrentIndex(3);

    m_userInterface.dataBitsBox->addItem(QStringLiteral("5"), QSerialPort::Data5);
    m_userInterface.dataBitsBox->addItem(QStringLiteral("6"), QSerialPort::Data6);
    m_userInterface.dataBitsBox->addItem(QStringLiteral("7"), QSerialPort::Data7);
    m_userInterface.dataBitsBox->addItem(QStringLiteral("8"), QSerialPort::Data8);
    m_userInterface.dataBitsBox->setCurrentIndex(3);

    m_userInterface.parityBox->addItem(tr("None"), QSerialPort::NoParity);
    m_userInterface.parityBox->addItem(tr("Even"), QSerialPort::EvenParity);
    m_userInterface.parityBox->addItem(tr("Odd"), QSerialPort::OddParity);
    m_userInterface.parityBox->addItem(tr("Mark"), QSerialPort::MarkParity);
    m_userInterface.parityBox->addItem(tr("Space"), QSerialPort::SpaceParity);
    m_userInterface.parityBox->setCurrentIndex(0);

    m_userInterface.stopBitsBox->addItem(QStringLiteral("1"), QSerialPort::OneStop);
#ifdef Q_OS_WIN
    m_userInterface.stopBitsBox->addItem(tr("1.5"), QSerialPort::OneAndHalfStop);
#endif
    m_userInterface.stopBitsBox->addItem(QStringLiteral("2"), QSerialPort::TwoStop);
    m_userInterface.stopBitsBox->setCurrentIndex(0);

    m_userInterface.flowControlBox->addItem(tr("None"), QSerialPort::NoFlowControl);
    m_userInterface.flowControlBox->addItem(tr("RTS/CTS"), QSerialPort::HardwareControl);
    m_userInterface.flowControlBox->addItem(tr("XON/XOFF"), QSerialPort::SoftwareControl);
    m_userInterface.flowControlBox->setCurrentIndex(0);
}

void C_SerialCom_Settings::FillPortsInfo()
{
    m_userInterface.serialPortInfoListBox->clear();
    QString description;
    QString manufacturer;
    QString serialNumber;
    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos) {
        QStringList list;
        description = info.description();
        manufacturer = info.manufacturer();
        serialNumber = info.serialNumber();
        list << info.portName()
             << (!description.isEmpty() ? description : SerialCom_blankString)
             << (!manufacturer.isEmpty() ? manufacturer : SerialCom_blankString)
             << (!serialNumber.isEmpty() ? serialNumber : SerialCom_blankString)
             << info.systemLocation()
             << (info.vendorIdentifier() ? QString::number(info.vendorIdentifier(), 16) : SerialCom_blankString)
             << (info.productIdentifier() ? QString::number(info.productIdentifier(), 16) : SerialCom_blankString);

        m_userInterface.serialPortInfoListBox->addItem(list.first(), list);
    }

    m_userInterface.serialPortInfoListBox->addItem(tr("Custom"));
}

void C_SerialCom_Settings::UpdateSettings()
{
    m_currentSettings.name = m_userInterface.serialPortInfoListBox->currentText();

    if (m_userInterface.baudRateBox->currentIndex() >= 4) {
        m_currentSettings.baudRate = m_userInterface.baudRateBox->currentText().toInt();
    } else {
        m_currentSettings.baudRate = static_cast<QSerialPort::BaudRate>(
                    m_userInterface.baudRateBox->itemData(m_userInterface.baudRateBox->currentIndex()).toInt());
    }
    m_currentSettings.stringBaudRate = QString::number(m_currentSettings.baudRate);

    m_currentSettings.dataBits = static_cast<QSerialPort::DataBits>(
                m_userInterface.dataBitsBox->itemData(m_userInterface.dataBitsBox->currentIndex()).toInt());
    m_currentSettings.stringDataBits = m_userInterface.dataBitsBox->currentText();

    m_currentSettings.parity = static_cast<QSerialPort::Parity>(
                m_userInterface.parityBox->itemData(m_userInterface.parityBox->currentIndex()).toInt());
    m_currentSettings.stringParity = m_userInterface.parityBox->currentText();

    m_currentSettings.stopBits = static_cast<QSerialPort::StopBits>(
                m_userInterface.stopBitsBox->itemData(m_userInterface.stopBitsBox->currentIndex()).toInt());
    m_currentSettings.stringStopBits = m_userInterface.stopBitsBox->currentText();

    m_currentSettings.flowControl = static_cast<QSerialPort::FlowControl>(
                m_userInterface.flowControlBox->itemData(m_userInterface.flowControlBox->currentIndex()).toInt());
    m_currentSettings.stringFlowControl = m_userInterface.flowControlBox->currentText();

    m_currentSettings.localEchoEnabled = m_userInterface.localEchoCheckBox->isChecked();
}


#include "moc_C_SerialCom_Settings.cpp"
