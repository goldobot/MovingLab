#include "C_NeatoXV.h"

C_NeatoXV::C_NeatoXV(QWidget * ptParent) : QMainWindow(ptParent)
{
    // Precompute data structure for optimization
    InitPrecomputedData();

    // Configure the HMI
    m_userInterface.setupUi(this);
    m_comPort.SetWindowTitle("Neato XV COM port");

    m_protocol.SetComPort(&m_comPort);

    // Create the scene to show the scan
    m_ptLdsScanGrScene = new QGraphicsScene(this);
    // Associate the scene to the graphic view
    m_userInterface.gv_LdsScan->setScene(m_ptLdsScanGrScene);

    // Create a dummy image to activate centering
    m_lidarScanImage = QImage(600, 600 , QImage::Format_RGB32);
    m_ptDirectAccessToLidarScanImage = m_ptLdsScanGrScene->addPixmap(QPixmap::fromImage(m_lidarScanImage));

    // Illustrate the robot
    QRectF rect1 = QRectF(300-11,300-11,22,22);
    QPolygonF Triangle1;
    Triangle1.append(QPointF(300,300-10));
    Triangle1.append(QPointF(300+10,300));
    Triangle1.append(QPointF(300-10,300));

    // Draw the robot
    m_ptLdsScanGrScene->addEllipse(rect1, QPen(QColor(255,0,255)), QBrush(QColor(0,255,0)));
    m_ptLdsScanGrScene->addPolygon(Triangle1, QPen(QColor(0,0,255)), QBrush(QColor(150,150,150)));

    // Center on the robot
    on_btn_CenterLdsScan_clicked();

    // Set default zoom
    on_btn_ZoomDefault_clicked();

    // Closing windows event
    connect(&m_comPort, &C_SerialCom::SIG_ClosingWindow, this, &C_NeatoXV::SLOT_ClosingComPortWindow);

    // Date flow connection
    connect(&m_protocol, &C_NeatoXV_Protocol::SIG_NewLidarData, this, &C_NeatoXV::SLOT_StoreNewScanData);

    // Activate modules monitoring
    connect(&m_monitoringTimer, &QTimer::timeout, this, &C_NeatoXV::SLOT_PeriodicCheckModulesMalFunction);
    m_monitoringTimer.start(3000);
}

void C_NeatoXV::InitPrecomputedData(void)
{
    // Precompute the Cos/Sin table
    for(int angleDeg = 0; angleDeg < LIDAR_NB_MEASURES_PER_REVOLUTION; angleDeg++)
    {
        // The Lidar rotation is not at the SI rotation
        double rad = MATHS_CONV_DEG_2_RAD * static_cast <double>(angleDeg);

        m_tabCosAngle[angleDeg] = cos(rad) * 0.06;
        m_tabSinAngle[angleDeg] = sin(rad) * 0.06;
    }
}

void C_NeatoXV::SLOT_StoreNewScanData(uint32_t tabOfMeasures__mm[LIDAR_NB_MEASURES_PER_REVOLUTION], double scanFreq)
{
    // Store the scan
    memcpy(m_tabLidarDistMeasures__mm, tabOfMeasures__mm, sizeof (uint32_t) * LIDAR_NB_MEASURES_PER_REVOLUTION);
    m_lidarMotorSpeed = scanFreq;

    // Show the scan
    DrawLidarScans();

    m_nbOfScreenRefresh++;
}


void C_NeatoXV::DrawLidarScans(void)
{
    // Create the new scan image
    m_lidarScanImage.fill(QColor(0,0,0));

    int screenWidth = m_lidarScanImage.size().width();
    int screenHeight = m_lidarScanImage.size().height();
    int screenCenterX =  screenWidth / 2;
    int screenCenterY = screenHeight / 2;

    double * ptCosAngle = m_tabCosAngle;
    double * ptSinAngle = m_tabSinAngle;
    uint32_t * ptLidarDist = m_tabLidarDistMeasures__mm;
    double dist;

    int x;
    int y;

    // Set pixel in the image
    for(int angle = 0; angle < LIDAR_NB_MEASURES_PER_REVOLUTION; angle++)
    {
        // Neato data
        dist = (*ptLidarDist);
        x = static_cast <int>((*ptCosAngle) * dist) + screenCenterX + NEATO_LIDAR_OFFSET_X__scaled;
        y = static_cast <int>((*ptSinAngle) * dist) + screenCenterY + NEATO_LIDAR_OFFSET_Y__scaled;

        if((x >=0) && (x < screenWidth) && (y >= 0) && (y < screenHeight))
        {
            (*( reinterpret_cast <uint32_t *>(m_lidarScanImage.scanLine(y)) + x)) = 0xFFFF0000;
        }

        ptCosAngle++;
        ptSinAngle++;
        ptLidarDist++;
    }

    // Show the image
    m_ptDirectAccessToLidarScanImage->setPixmap(QPixmap::fromImage(m_lidarScanImage.transformed(QMatrix().rotate(-90.0))));
}

void C_NeatoXV::on_btn_ShowComPort_clicked()
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

void C_NeatoXV::on_btn_Connect_clicked()
{
    if(m_comPort.IsConnected())
    {
        m_protocol.Disconnect();
        m_userInterface.btn_Connect->setText("Connect");
    }
    else
    {
        m_protocol.Connect();
        m_userInterface.btn_Connect->setText("Disconnect");
    }
}

void C_NeatoXV::on_btn_MoveDownLdsScan_clicked()
{
    m_viewCenterY -= 10.0;
    m_userInterface.gv_LdsScan->centerOn(m_viewCenterX, m_viewCenterY);
}

void C_NeatoXV::on_btn_MoveUpLdsScan_clicked()
{
    m_viewCenterY += 10.0;
    m_userInterface.gv_LdsScan->centerOn(m_viewCenterX, m_viewCenterY);
}

void C_NeatoXV::on_btn_MoveLeftLdsScan_clicked()
{
    m_viewCenterX += 10.0;
    m_userInterface.gv_LdsScan->centerOn(m_viewCenterX, m_viewCenterY);
}

void C_NeatoXV::on_btn_MoveRightLdsScan_clicked()
{
    m_viewCenterX -= 10.0;
    m_userInterface.gv_LdsScan->centerOn(m_viewCenterX, m_viewCenterY);
}

void C_NeatoXV::on_btn_CenterLdsScan_clicked()
{
    m_viewCenterX = m_userInterface.gv_LdsScan->sceneRect().center().x();
    m_viewCenterY = m_userInterface.gv_LdsScan->sceneRect().center().y();
    m_userInterface.gv_LdsScan->centerOn(m_viewCenterX, m_viewCenterY);
}


void C_NeatoXV::on_btn_ZoomIn_clicked()
{
    m_userInterface.gv_LdsScan->scale(1.1, 1.1);
}

void C_NeatoXV::on_btn_ZoomOut_clicked()
{
    m_userInterface.gv_LdsScan->scale(0.9, 0.9);
}

void C_NeatoXV::on_btn_ZoomDefault_clicked()
{
    m_userInterface.gv_LdsScan->resetMatrix();
    m_userInterface.gv_LdsScan->scale(2.0, 2.0);
}


void C_NeatoXV::closeEvent (QCloseEvent * ptEvent)
{
    Q_UNUSED(ptEvent);

    // Send a signal to the parent
    emit SIG_ClosingWindow();
}


void C_NeatoXV::SLOT_ClosingComPortWindow(void)
{
    m_userInterface.btn_ShowComPort->setText("Show COM port");
}

void C_NeatoXV::SLOT_PeriodicCheckModulesMalFunction()
{
    // The device is connected
    if(m_comPort.IsConnected())
    {
        m_userInterface.lbl_LdsRotSpeed->setText(QString("LDS rotation speed : %1 rps").arg(m_lidarMotorSpeed));

        // And the scanner goes so fast
        if(m_lidarMotorSpeed > 6)
        {
            m_lidarMotorSpeed = 0;
            m_protocol.ResetLidar();
        }
    }
    else
    {
        m_userInterface.lbl_LdsRotSpeed->setText(QString("LDS rotation speed : - rps"));
    }

    // Update the button name
    if(m_comPort.IsConnected())
    {
        m_userInterface.btn_Connect->setText("Disconnect");
    }
    else
    {
        m_userInterface.btn_Connect->setText("Connect");
    }

    m_userInterface.lbl_RefreshRate->setText(QString("Refreshing rate : %1 fps").arg(1000 * m_nbOfScreenRefresh / m_monitoringTimer.interval()));
    m_nbOfScreenRefresh = 0;
}

#include "moc_C_NeatoXV.cpp"
