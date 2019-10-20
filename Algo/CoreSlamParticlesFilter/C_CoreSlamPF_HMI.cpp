#include "C_CoreSlamPF_HMI.h"

C_CoreSlamPF_HMI::C_CoreSlamPF_HMI(QWidget * ptParent, C_ScanseLidar * ptScanse, C_Slamware * ptSlamware) :
    QMainWindow(ptParent)
{
    m_ptScanse = ptScanse;
    m_ptSlamware = ptSlamware;

    // Configure the HMI
    m_userInterface.setupUi(this);

    // Init CoreSlam module
    m_ptCoreSlam = new C_CoreSlamPF_Main(GLOBAL_MAP_SIDE_SIZE__MM, ROBOT_BASE_RADIUS__MM, LIDAR_MAX_RELIABLE_MESURED_DISTANCE__MM, LIDAR_MIN_DIST_TO_ADD_VIRTUAL_MEASURES__MM, LIDAR_MAX_NB_OF_VIRTUAL_MEASURES_AT_MAX_DIST);

    // Configure the CoreSlam

    // Lidar 0
    // Describe how to use the lidar data
    struct_ParamsForUsingLidar param;
    param.lidarPosOffsetX__mm = SCANSE_LIDAR_OFFSET_X__mm;
    param.lidarPosOffsetY__mm = SCANSE_LIDAR_OFFSET_Y__mm;
    param.estimationType = COMPLET_POS;
    param.mapIntegrationWeight = 0;
    m_ptCoreSlam->AddSensorModel(SCANSE_LIDAR_ID, param);

    // Lidar 1
    // Describe how to use the lidar data
    param.lidarPosOffsetX__mm = SLAMWARE_LIDAR_OFFSET_X__mm;
    param.lidarPosOffsetY__mm = SLAMWARE_LIDAR_OFFSET_Y__mm;
    param.estimationType = COMPLET_POS;
    param.mapIntegrationWeight = 0;
    m_ptCoreSlam->AddSensorModel(SLAMWARE_LIDAR_ID, param);

    // Create the scene to show the scan
    m_ptMapGrScene = new QGraphicsScene(this);
    // Associate the scene to the graphic view
    m_userInterface.gv_Map->setScene(m_ptMapGrScene);



    m_Lidar = QImage(600, 600 , QImage::Format_RGB32);

    // Create a dummy image to activate centering
    m_ptLidar = m_ptMapGrScene->addPixmap(QPixmap::fromImage(m_Lidar));



    int w = m_ptCoreSlam->GET_globalMapSquareSize__pixel();
    int half_w = w / 2;

    m_coreSlamMap = QImage(m_ptCoreSlam->GET_globalMapSquareSize__pixel(), m_ptCoreSlam->GET_globalMapSquareSize__pixel() , QImage::Format_RGB32);

    // Create a dummy image to activate centering
    m_ptMap = m_ptMapGrScene->addPixmap(QPixmap::fromImage(m_coreSlamMap));

    m_lastX = half_w;
    m_lastY = half_w;

    QRectF rect2 = QRectF(half_w-21,half_w-21,42,42);

    QPolygonF Triangle2;
    Triangle2.append(QPointF(half_w,half_w-20));
    //Triangle2.append(QPointF(half_w+12,half_w+12));
    //Triangle2.append(QPointF(half_w-12,half_w+12));
    Triangle2.append(QPointF(half_w+20,half_w));
    Triangle2.append(QPointF(half_w-20,half_w));

    m_ptRect = m_ptMapGrScene->addRect(rect2, QPen(QColor(255,0,255)));
    m_ptRect->setTransformOriginPoint( m_ptRect->rect().center());

    m_ptRobotBase = m_ptMapGrScene->addEllipse(rect2, QPen(QColor(255,0,255)), QBrush(QColor(0,255,0)));
    m_ptRobotBase->setTransformOriginPoint( m_ptRobotBase->rect().center());

    m_ptPoly = m_ptMapGrScene->addPolygon(Triangle2, QPen(QColor(0,0,255)), QBrush(QColor(150,150,150)));
    m_ptPoly->setTransformOriginPoint( m_ptRobotBase->rect().center());


    // Convert the color dynamic from D1 to D2
    double deltaColor = 255.0 / 160.0;
    for (uint32_t i = 0; i < 255; i++)
    {
        uint32_t color = deltaColor * i;
        if(color > 255) color = 255;

        m_tabConvSlamMapPixelToRgbPixel[i] = (0xFF000000 | (color << 16) | (color << 8) | color);
    }

    on_btn_CenterMap_clicked();

    // Set default zoom
    on_btn_ZoomDefaultMap_clicked();

    // Date flow connection
    connect(m_ptScanse->GetProtocol(), &C_ScanseLidar_Protocol::SIG_NewLidarData, this, &C_CoreSlamPF_HMI::SLOT_StoreNewScanData);
    connect(m_ptSlamware->GetProtocol(), &C_Slamware_Protocol::SIG_NewLidarData, this, &C_CoreSlamPF_HMI::SLOT_StoreNewScanData);

    connect(&m_TIMER_processNewScanData, &QTimer::timeout, this, &C_CoreSlamPF_HMI::SLOT_ProcessNewScanData);

    // Statistics purpose
    m_estimationRateTimer.start();

    // Reset the HMI
    on_btn_ResetSlam_clicked();
}

C_CoreSlamPF_HMI::~C_CoreSlamPF_HMI()
{
    delete m_ptCoreSlam;
    delete m_ptMapGrScene;
}

void C_CoreSlamPF_HMI::closeEvent (QCloseEvent * ptEvent)
{
    Q_UNUSED(ptEvent);

    // Send a signal to the parent
    emit SIG_ClosingWindow();
}

void C_CoreSlamPF_HMI::SLOT_StoreNewScanData(int sensorId, uint32_t * tabOfMeasures__mm, double * tabOfMeasures__cos, double * tabOfMeasures__sin, uint32_t nbOfMeasures)
{
    // No pending previous data to be processed
    if(m_SEM_measuresAvailable.available() == 0)
    {
        // Store new scan data
        // Store the measures for internal uses
        m_nbOfScanseMeasures = nbOfMeasures;
        memcpy(m_tabScanseMeasures__mm, tabOfMeasures__mm, sizeof(uint32_t) * m_nbOfScanseMeasures);
        memcpy(m_tabScanseMeasures__cos, tabOfMeasures__cos, sizeof(double) * m_nbOfScanseMeasures);
        memcpy(m_tabScanseMeasures__sin, tabOfMeasures__sin, sizeof(double) * m_nbOfScanseMeasures);
        m_sensorId = sensorId;


        // Signal the available new data
        m_SEM_measuresAvailable.release(1);

        // Avoid using emit because it chain to the SLOT and handle the CPU
        // Use of a timer which is an other thread
        m_TIMER_processNewScanData.start(0);
    }
}

void C_CoreSlamPF_HMI::SLOT_ProcessNewScanData(void)
{
    m_TIMER_processNewScanData.stop();

    // Wait for new available data to process
    if(m_SEM_measuresAvailable.available() > 0)
    {
        // Now process the data

        // Do one position estimation step
        m_ptCoreSlam->IntegrateNewSensorData(m_tabScanseMeasures__mm, m_tabScanseMeasures__cos, m_tabScanseMeasures__sin, m_nbOfScanseMeasures, m_sensorId);

        // Signal the new estimation
        uint32_t xMin, xMax, yMin, yMax;
        m_ptCoreSlam->GET_lastThnlGlobalMapUpgradedZone(&xMin, &xMax, &yMin, &yMax);
        emit SIG_NewEstimation(m_ptCoreSlam->GET_currentPosX__mm() , m_ptCoreSlam->GET_currentPosY__mm(), m_ptCoreSlam->GET_currentPosAngle__rad(), m_ptCoreSlam->GET_ptThnlGlobalMap8bpp(), xMin, xMax, yMin, yMax);

        // Show the new estimation
        UpdateHMI();

        // Signal the data has been processed
        m_SEM_measuresAvailable.acquire();
    }
}

void C_CoreSlamPF_HMI::UpdateHMI()
{
    int bestEstimatorIndex = m_ptCoreSlam->GET_bestEstimatorIndex();

    struct_EstimatedRobotPosition estimatedRobotPos;
    m_ptCoreSlam->GetRobotPosition(&estimatedRobotPos);


    // Show infos
    m_userInterface.lbl_coreSlamEstimatorIndex->setText(QString("Estimator ID : %1").arg(bestEstimatorIndex));
    m_userInterface.lbl_coreSlamPosQuality->setText(QString("Quality : %1").arg(estimatedRobotPos.matchingQuality));
    m_userInterface.lbl_coreSlamPosX->setText(QString("X : %1 mm").arg(estimatedRobotPos.currentPosX__mm));
    m_userInterface.lbl_coreSlamPosY->setText(QString("Y : %1 mm").arg(estimatedRobotPos.currentPosY__mm));
    m_userInterface.lbl_coreSlamPosAngle->setText(QString("Angle : %1 deg").arg(QString::number(estimatedRobotPos.currentPosAngle__deg, 'f', 1)));
    m_userInterface.lbl_coreSlamErrX->setText(QString("Err X : %1 mm").arg(estimatedRobotPos.appliedDxErr__mm));
    m_userInterface.lbl_coreSlamErrY->setText(QString("Err Y : %1 mm").arg(estimatedRobotPos.appliedDyErr__mm));
    m_userInterface.lbl_coreSlamErrAngle->setText(QString("Err Angle : %1 deg").arg(QString::number(estimatedRobotPos.appliedDangleErr__deg, 'f', 1)));


    double elapsedTime__ms = m_estimationRateTimer.restart();
    if(elapsedTime__ms > 0)
    {
        m_userInterface.lbl_coreSlamFrameRate->setText(QString("CoreSlam rate : %1 fps").arg(1000.0 / elapsedTime__ms));
    }


    // Show the estimated map
    // Show the robot
    int x = m_ptCoreSlam->GET_currentPosX__pixel();
    int y = m_ptCoreSlam->GET_currentPosY__pixel();

    uint32_t xMin, xMax, yMin, yMax;
    m_ptCoreSlam->GET_lastGlobalMapUpgradedZone(&xMin, &xMax, &yMin, &yMax);

    if((x-xMin) > 200) xMin = x - 200;
    if((xMax - x) > 200) xMax = x + 200;
    if((y-yMin) > 200) yMin = y - 200;
    if((yMax - y) > 200) yMax = y + 200;

    Draw8BppMap(m_ptCoreSlam->GET_ptGlobalMap8bpp(), xMin, xMax, yMin, yMax);

    // Show the map
    m_ptMap->setPixmap(QPixmap::fromImage(m_coreSlamMap));

    // Show the robot
    m_ptRobotBase->moveBy(x- m_lastX, y - m_lastY);
    m_ptPoly->moveBy(x- m_lastX, y - m_lastY);
    m_ptPoly->setRotation(estimatedRobotPos.currentPosAngle__deg + 90.0);

    m_ptRect->setRect(xMin, yMin, xMax-xMin, yMax - yMin);


    m_lastX = x;
    m_lastY = y;

    if(m_userInterface.chkB_FollowRobot->isChecked())
    {
        m_userInterface.gv_Map->centerOn(x, y);
    }

    // Show the current lidar scan
    //DrawLidarScans();
}

void C_CoreSlamPF_HMI::DrawLidarScans(void)
{
    /*
    // Create the new scan image
    m_Lidar.fill(QColor(0,0,0));

    int screenWidth = m_Lidar.size().width();
    int screenHeight = m_Lidar.size().height();
    int screenCenterX =  screenWidth / 2;
    int screenCenterY = screenHeight / 2;

    uint32_t * ptScanseDist = m_tabScanseMeasures__mm;
    double * ptScanseAngle = m_tabScanseMeasures__rad;

    double dist;
    double angle;

    int x;
    int y;

    // Set pixel in the image
    for(int32_t i = 0; i < m_nbOfScanseMeasures; i++)
    {
        // Scanse data
        dist = (*ptScanseDist);
        angle = (*ptScanseAngle);

        x = (int)(cos(angle) * dist) + screenCenterX + SCANSE_LIDAR_OFFSET_X__scaled;
        y = (int)(sin(angle) * dist) + screenCenterY + SCANSE_LIDAR_OFFSET_Y__scaled;

        if((x >=0) && (x < screenWidth) && (y >= 0) && (y < screenHeight))
        {
            (*( reinterpret_cast <uint32_t *>(m_Lidar.scanLine(y)) + x)) = 0xFFFF0000;
        }

        ptScanseDist++;
        ptScanseAngle++;
    }

    // Show the image
    m_ptLidar->setPixmap(QPixmap::fromImage(m_Lidar.transformed(QMatrix().rotate(-90.0))));
    */
}

void C_CoreSlamPF_HMI::Draw8BppMap(uint8_t * mapData, uint32_t xMin, uint32_t xMax, uint32_t yMin, uint32_t yMax)
{
    int screenWidth = m_coreSlamMap.size().width();
    //int screenWidth = 546;

    int offsetY = yMin * screenWidth;

    for(uint32_t y = yMin; y < yMax; y++)
    {
        uint32_t * scan = (uint32_t *) m_coreSlamMap.scanLine(y) + xMin;
        uint8_t * ptSlamMap = mapData + offsetY + xMin;

        for(uint32_t x = xMin; x < xMax; x++)
        {
            uint8_t val = * ptSlamMap;
            *scan = m_tabConvSlamMapPixelToRgbPixel[val];

            ptSlamMap++;
            scan++;
        }

        offsetY += screenWidth;
    }
}

void C_CoreSlamPF_HMI::on_btn_ZoomDefaultMap_clicked()
{
    m_userInterface.gv_Map->resetMatrix();
    m_userInterface.gv_Map->scale(0.5, 0.5);

}

void C_CoreSlamPF_HMI::on_btn_CenterMap_clicked()
{
    m_mapViewCenterX = m_userInterface.gv_Map->sceneRect().center().x();
    m_mapViewCenterY = m_userInterface.gv_Map->sceneRect().center().y();
    m_userInterface.gv_Map->centerOn(m_mapViewCenterX, m_mapViewCenterY);
}

void C_CoreSlamPF_HMI::on_btn_ZoomOutMap_clicked()
{
    m_userInterface.gv_Map->scale(0.8, 0.8);
}

void C_CoreSlamPF_HMI::on_btn_ZoomInMap_clicked()
{
    m_userInterface.gv_Map->scale(1.2, 1.2);
}

void C_CoreSlamPF_HMI::on_btn_MoveRightMap_clicked()
{
    m_mapViewCenterX -= 20.0;
    m_userInterface.gv_Map->centerOn(m_mapViewCenterX, m_mapViewCenterY);
}

void C_CoreSlamPF_HMI::on_btn_MoveLeftMap_clicked()
{
    m_mapViewCenterX += 20.0;
    m_userInterface.gv_Map->centerOn(m_mapViewCenterX, m_mapViewCenterY);
}

void C_CoreSlamPF_HMI::on_btn_MoveDownMap_clicked()
{
    m_mapViewCenterY -= 20.0;
    m_userInterface.gv_Map->centerOn(m_mapViewCenterX, m_mapViewCenterY);
}

void C_CoreSlamPF_HMI::on_btn_MoveUpMap_clicked()
{
    m_mapViewCenterY += 20.0;
    m_userInterface.gv_Map->centerOn(m_mapViewCenterX, m_mapViewCenterY);
}

void C_CoreSlamPF_HMI::on_btn_ResetSlam_clicked()
{
    m_ptCoreSlam->Reset();
    uint32_t xMin, xMax, yMin, yMax;
    m_ptCoreSlam->GET_lastGlobalMapUpgradedZone(&xMin, &xMax, &yMin, &yMax);
    Draw8BppMap(m_ptCoreSlam->GET_ptGlobalMap8bpp(), xMin, xMax, yMin, yMax);
}

#include "moc_C_CoreSlamPF_HMI.cpp"
