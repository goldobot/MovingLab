#include "C_Slamware.h"

C_Slamware::C_Slamware(QWidget * ptParent) : QMainWindow(ptParent)
{
    // Configure the HMI
    m_userInterface.setupUi(this);

    m_lidarProtocol.SetComPort(&m_comPort);

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

    // Date flow connection
    connect(&m_lidarProtocol, &C_Slamware_Protocol::SIG_NewLidarData, this, &C_Slamware::SLOT_StoreNewScanData);

    // Activate modules monitoring
    connect(&m_monitoringTimer, &QTimer::timeout, this, &C_Slamware::SLOT_PeriodicCheckModulesMalFunction);
    m_monitoringTimer.start(3000);

    connect(&m_TIMER_processNewScanData, &QTimer::timeout, this, &C_Slamware::SLOT_ProcessNewScanData);
}


void C_Slamware::SLOT_StoreNewScanData(int sensorId, uint32_t * tabOfMeasures__mm, double * tabOfMeasures__cos, double * tabOfMeasures__sin, uint32_t nbOfMeasures)
{
    Q_UNUSED(sensorId)

    // No pending previous data to be processed
    if(m_SEM_measuresAvailable.available() == 0)
    {
        // Store new scan data
        m_nbOfMeasures = nbOfMeasures;
        memcpy(m_tabMeasures__mm, tabOfMeasures__mm, sizeof (uint32_t) * m_nbOfMeasures);
        memcpy(m_tabMeasures__cos, tabOfMeasures__cos, sizeof (double) * m_nbOfMeasures);
        memcpy(m_tabMeasures__sin, tabOfMeasures__sin, sizeof (double) * m_nbOfMeasures);

        // Signal the available new data
        m_SEM_measuresAvailable.release(1);

        // Avoid using emit because it chain to the SLOT and handle the CPU
        // Use of a timer which is an other thread
        m_TIMER_processNewScanData.start(0);
    }
}

void C_Slamware::SLOT_ProcessNewScanData(void)
{
    m_TIMER_processNewScanData.stop();

    // Wait for new available data to process
    if(m_SEM_measuresAvailable.available() > 0)
    {
        // Now process the data

        // Show the scan
        DrawLidarScans();

        // Statistics
        m_nbOfScreenRefresh++;

        // Signal the data has been processed
        m_SEM_measuresAvailable.acquire();
    }
}


void C_Slamware::DrawLidarScans(void)
{
    // Create the new scan image
    m_lidarScanImage.fill(QColor(0,0,0));

    int screenWidth = m_lidarScanImage.size().width();
    int screenHeight = m_lidarScanImage.size().height();
    int screenCenterX =  screenWidth / 2;
    int screenCenterY = screenHeight / 2;

    uint32_t * ptDist = m_tabMeasures__mm;
    double * ptAngle__cos = m_tabMeasures__cos;
    double * ptAngle__sin = m_tabMeasures__sin;

    int x;
    int y;

    // Set pixel in the image
    for(int i = 0; i < m_nbOfMeasures; i++)
    {
        x = static_cast <int>((* ptAngle__cos) * (*ptDist) * CONV_MM_2_PIXEL) + screenCenterX + SLAMWARE_LIDAR_OFFSET_X__pixel;
        y = static_cast <int>((* ptAngle__sin) * (*ptDist) * CONV_MM_2_PIXEL) + screenCenterY + SLAMWARE_LIDAR_OFFSET_Y__pixel;

        if((x >=0) && (x < screenWidth) && (y >= 0) && (y < screenHeight))
        {
            (*( reinterpret_cast <uint32_t *>(m_lidarScanImage.scanLine(y)) + x)) = 0xFFFF0000;
        }

        ptDist++;
        ptAngle__cos++;
        ptAngle__sin++;
    }

    // Show the image
    m_ptDirectAccessToLidarScanImage->setPixmap(QPixmap::fromImage(m_lidarScanImage.transformed(QMatrix().rotate(-90.0))));
}

void C_Slamware::on_btn_ShowComPort_clicked()
{
    /*
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
    */
}

void C_Slamware::on_btn_Connect_clicked()
{
    /*
    if(m_comPort.IsConnected())
    {
        m_lidarProtocol.Disconnect();
        m_userInterface.btn_Connect->setText("Connect");
    }
    else
    {
        m_lidarProtocol.Connect();
        m_userInterface.btn_Connect->setText("Disconnect");
    }
    */
}

void C_Slamware::on_btn_MoveDownLdsScan_clicked()
{
    m_viewCenterY -= 10.0;
    m_userInterface.gv_LdsScan->centerOn(m_viewCenterX, m_viewCenterY);
}

void C_Slamware::on_btn_MoveUpLdsScan_clicked()
{
    m_viewCenterY += 10.0;
    m_userInterface.gv_LdsScan->centerOn(m_viewCenterX, m_viewCenterY);
}

void C_Slamware::on_btn_MoveLeftLdsScan_clicked()
{
    m_viewCenterX += 10.0;
    m_userInterface.gv_LdsScan->centerOn(m_viewCenterX, m_viewCenterY);
}

void C_Slamware::on_btn_MoveRightLdsScan_clicked()
{
    m_viewCenterX -= 10.0;
    m_userInterface.gv_LdsScan->centerOn(m_viewCenterX, m_viewCenterY);
}

void C_Slamware::on_btn_CenterLdsScan_clicked()
{
    m_viewCenterX = m_userInterface.gv_LdsScan->sceneRect().center().x();
    m_viewCenterY = m_userInterface.gv_LdsScan->sceneRect().center().y();
    m_userInterface.gv_LdsScan->centerOn(m_viewCenterX, m_viewCenterY);
}


void C_Slamware::on_btn_ZoomIn_clicked()
{
    m_userInterface.gv_LdsScan->scale(1.1, 1.1);
}

void C_Slamware::on_btn_ZoomOut_clicked()
{
    m_userInterface.gv_LdsScan->scale(0.9, 0.9);
}

void C_Slamware::on_btn_ZoomDefault_clicked()
{
    m_userInterface.gv_LdsScan->resetMatrix();
    m_userInterface.gv_LdsScan->scale(2.0, 2.0);
}


void C_Slamware::closeEvent (QCloseEvent * ptEvent)
{
    Q_UNUSED(ptEvent);

    // Send a signal to the parent
    emit SIG_ClosingWindow();
}


void C_Slamware::SLOT_ClosingComPortWindow(void)
{
    m_userInterface.btn_ShowComPort->setText("Show COM port");
}

void C_Slamware::SLOT_PeriodicCheckModulesMalFunction()
{
    m_userInterface.lbl_RefreshRate->setText(QString("Refreshing rate : %1 fps").arg(1000 * m_nbOfScreenRefresh / m_monitoringTimer.interval()));
    m_nbOfScreenRefresh = 0;
}

#include "moc_C_Slamware.cpp"
