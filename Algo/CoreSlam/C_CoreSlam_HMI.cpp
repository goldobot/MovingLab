#include "C_CoreSlam_HMI.h"

C_CoreSlam_HMI::C_CoreSlam_HMI(QWidget * ptParent, C_ScanseLidar * ptScanse, C_Slamware * ptSlamware) :
    QMainWindow(ptParent)
{
    m_ptScanse = ptScanse;
    m_ptSlamware = ptSlamware;

    // Configure the HMI
    m_userInterface.setupUi(this);

    // Init CoreSlam module
    m_ptCoreSlam = new C_CoreSlamRealAngle_8bppMap(GLOBAL_MAP_SIDE_SIZE__MM, LIDAR_MIN_RELIABLE_MESURED_DISTANCE__MM, LIDAR_MAX_RELIABLE_MESURED_DISTANCE__MM, LIDAR_MIN_DIST_TO_ADD_VIRTUAL_MEASURES__MM, LIDAR_MAX_NB_OF_VIRTUAL_MEASURES_AT_MAX_DIST);

    // Configure the CoreSlam

    // Lidar 0
    // Describe how to use the lidar data
    C_CoreSlamRealAngle_8bppMap::struct_ParamsForUsingLidar param;
    param.lidarPosOffsetX__mm = SCANSE_LIDAR_OFFSET_X__mm;
    param.lidarPosOffsetY__mm = SCANSE_LIDAR_OFFSET_Y__mm;
    param.estimationType = C_CoreSlamRealAngle_8bppMap::COMPLET_POS;
    param.mapIntegrationWeight = 0;
    m_ptCoreSlam->AddSensorModel(SCANSE_LIDAR_ID, param);

    // Lidar 1
    // Describe how to use the lidar data
    param.lidarPosOffsetX__mm = SLAMWARE_LIDAR_OFFSET_X__mm;
    param.lidarPosOffsetY__mm = SLAMWARE_LIDAR_OFFSET_Y__mm;
    param.estimationType = C_CoreSlamRealAngle_8bppMap::COMPLET_POS;
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

    QRectF rect2 = QRectF(half_w-ROBOT_BASE_RADIUS__MM/10,half_w-ROBOT_BASE_RADIUS__MM/10,ROBOT_BASE_RADIUS__MM/5,ROBOT_BASE_RADIUS__MM/5);

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

        m_tabConvSlamMapPixelToClearMapRgbPixel[i] = (0xFF000000 | (color << 16) | (color << 8) | color);
        m_tabConvSlamMapPixelToRgbPixel[i] = (0xFF000000 | (i << 16) | (i << 8) | i);
    }

    // Init the map view windows
    on_btn_CenterMap_clicked();
    on_btn_ZoomDefaultMap_clicked();
    m_userInterface.chkB_FollowRobot->setChecked(true);

    // Date flow connection
    connect(m_ptScanse->GetProtocol(), &C_ScanseLidar_Protocol::SIG_NewLidarData, this, &C_CoreSlam_HMI::SLOT_StoreNewScanData);
    connect(m_ptSlamware->GetProtocol(), &C_Slamware_Protocol::SIG_NewLidarData, this, &C_CoreSlam_HMI::SLOT_StoreNewScanData);

    connect(&m_TIMER_processNewScanData, &QTimer::timeout, this, &C_CoreSlam_HMI::SLOT_ProcessNewScanData);

    // Statistics purpose
    m_estimationRateTimer.start();

    // Reset the HMI
    on_btn_ResetSlam_clicked();
}

C_CoreSlam_HMI::~C_CoreSlam_HMI()
{
    delete m_ptCoreSlam;
    delete m_ptMapGrScene;
}

void C_CoreSlam_HMI::closeEvent (QCloseEvent * ptEvent)
{
    Q_UNUSED(ptEvent);

    // Send a signal to the parent
    emit SIG_ClosingWindow();
}

void C_CoreSlam_HMI::SLOT_StoreNewScanData(int sensorId, uint32_t * tabOfMeasures__mm, double * tabOfMeasures__cos, double * tabOfMeasures__sin, uint32_t nbOfMeasures)
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

void C_CoreSlam_HMI::SLOT_ProcessNewScanData(void)
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
        m_ptCoreSlam->GET_lastNavMapUpgradedZone(&xMin, &xMax, &yMin, &yMax);
        emit SIG_NewEstimation(m_ptCoreSlam->GET_currentPosX__mm() , m_ptCoreSlam->GET_currentPosY__mm(), m_ptCoreSlam->GET_currentPosAngle__rad(), m_ptCoreSlam->GET_ptNavMap8bpp(), xMin, xMax, yMin, yMax);

        // Show the new estimation
        UpdateHMI();

        // Signal the data has been processed
        m_SEM_measuresAvailable.acquire();
    }
}

void C_CoreSlam_HMI::UpdateHMI()
{
    // Show infos
    float posX = m_ptCoreSlam->GET_currentPosX__mm();
    float posY = m_ptCoreSlam->GET_currentPosY__mm();
    float posT = m_ptCoreSlam->GET_currentPosAngle__deg();
    m_userInterface.lbl_coreSlamPos->setText(QString("Estimated position : X = %1 mm : Y = %2 mm : θ = %3 deg").arg(posX).arg(posY).arg(posT));

    float errX = m_ptCoreSlam->GET_appliedPosCorrectionX__mm();
    float errY = m_ptCoreSlam->GET_appliedPosCorrectionY__mm();
    float errT = m_ptCoreSlam->GET_appliedPosCorrectionAngle__deg();
    m_userInterface.lbl_coreSlamErr->setText(QString("Estimation error : dx = %1 mm : dy = %2 mm : dθ = %3 deg").arg(errX).arg(errY).arg(errT));

    double elapsedTime__ms = m_estimationRateTimer.elapsed();
    if(elapsedTime__ms > 1000)
    {
        m_estimationRateTimer.restart();
        m_userInterface.lbl_coreSlamFrameRate->setText(QString("CoreSlam rate : %1 fps").arg(QString::number(m_ptCoreSlam->GET_nbMapUpdatePassSinceLastRead() * 1000.0 / elapsedTime__ms, 'f', 1)));
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
    m_ptPoly->setRotation(m_ptCoreSlam->GET_currentPosAngle__deg() + 90.0);

    m_ptRect->setRect(xMin, yMin, xMax-xMin, yMax - yMin);

    m_lastX = x;
    m_lastY = y;

    if(m_userInterface.chkB_FollowRobot->isChecked())
    {
        m_userInterface.gv_Map->centerOn(x, y);
    }
}

void C_CoreSlam_HMI::Draw8BppMap(uint8_t * mapData, uint32_t xMin, uint32_t xMax, uint32_t yMin, uint32_t yMax)
{
    // To conversion to do while showing the map
    uint32_t * tabConvSlamMapPixelToRgbPixelToUse = m_tabConvSlamMapPixelToClearMapRgbPixel;
    if(m_userInterface.chkB_ClearMap->isChecked() != true) tabConvSlamMapPixelToRgbPixelToUse = m_tabConvSlamMapPixelToRgbPixel;

    int screenWidth = m_coreSlamMap.size().width();

    uint8_t * ptSlamMapOrigine = mapData + yMin * screenWidth;

    for(uint32_t y = yMin; y < yMax; y++)
    {
        uint32_t * scan = (uint32_t *) m_coreSlamMap.scanLine(y) + xMin;
        uint8_t * ptSlamMap = ptSlamMapOrigine + xMin;

        for(uint32_t x = xMin; x < xMax; x++)
        {
            uint8_t val = * ptSlamMap;

            *scan = tabConvSlamMapPixelToRgbPixelToUse[val];

            ptSlamMap++;
            scan++;
        }

        ptSlamMapOrigine += screenWidth;
    }
}

void C_CoreSlam_HMI::on_btn_ZoomDefaultMap_clicked()
{
    m_userInterface.gv_Map->resetMatrix();
    m_userInterface.gv_Map->scale(0.5, 0.5);

}

void C_CoreSlam_HMI::on_btn_ZoomOutMap_clicked()
{
    m_userInterface.gv_Map->scale(0.8, 0.8);
}

void C_CoreSlam_HMI::on_btn_ZoomInMap_clicked()
{
    m_userInterface.gv_Map->scale(1.2, 1.2);
}

void C_CoreSlam_HMI::on_btn_CenterMap_clicked()
{
    m_userInterface.chkB_FollowRobot->setChecked(false);

    m_mapViewCenterX = m_userInterface.gv_Map->sceneRect().center().x();
    m_mapViewCenterY = m_userInterface.gv_Map->sceneRect().center().y();
    m_userInterface.gv_Map->centerOn(m_mapViewCenterX, m_mapViewCenterY);
}

void C_CoreSlam_HMI::on_btn_MoveRightMap_clicked()
{
    if(m_userInterface.chkB_FollowRobot->isChecked())
    {
        m_userInterface.chkB_FollowRobot->setChecked(false);
        m_mapViewCenterX = (int)m_lastX;
        m_mapViewCenterY = (int)m_lastY;
    }

    m_mapViewCenterX -= 20.0;
    m_userInterface.gv_Map->centerOn(m_mapViewCenterX, m_mapViewCenterY);
}

void C_CoreSlam_HMI::on_btn_MoveLeftMap_clicked()
{
    if(m_userInterface.chkB_FollowRobot->isChecked())
    {
        m_userInterface.chkB_FollowRobot->setChecked(false);
        m_mapViewCenterX = (int)m_lastX;
        m_mapViewCenterY = (int)m_lastY;
    }

    m_mapViewCenterX += 20.0;
    m_userInterface.gv_Map->centerOn(m_mapViewCenterX, m_mapViewCenterY);
}

void C_CoreSlam_HMI::on_btn_MoveDownMap_clicked()
{
    if(m_userInterface.chkB_FollowRobot->isChecked())
    {
        m_userInterface.chkB_FollowRobot->setChecked(false);
        m_mapViewCenterX = (int)m_lastX;
        m_mapViewCenterY = (int)m_lastY;
    }

    m_mapViewCenterY -= 20.0;
    m_userInterface.gv_Map->centerOn(m_mapViewCenterX, m_mapViewCenterY);
}

void C_CoreSlam_HMI::on_btn_MoveUpMap_clicked()
{
    if(m_userInterface.chkB_FollowRobot->isChecked())
    {
        m_userInterface.chkB_FollowRobot->setChecked(false);
        m_mapViewCenterX = (int)m_lastX;
        m_mapViewCenterY = (int)m_lastY;
    }

    m_mapViewCenterY += 20.0;
    m_userInterface.gv_Map->centerOn(m_mapViewCenterX, m_mapViewCenterY);
}

void C_CoreSlam_HMI::on_btn_ResetSlam_clicked()
{
    m_ptCoreSlam->Reset();
    uint32_t xMin, xMax, yMin, yMax;
    m_ptCoreSlam->GET_lastGlobalMapUpgradedZone(&xMin, &xMax, &yMin, &yMax);
    Draw8BppMap(m_ptCoreSlam->GET_ptGlobalMap8bpp(), xMin, xMax, yMin, yMax);
}

#include "moc_C_CoreSlam_HMI.cpp"
