#include "C_PathFinder.h"

C_PathFinder::C_PathFinder(QWidget * ptParent, uint32_t mmPerPixel) :
    QMainWindow(ptParent)
{
    CONV_PIXEL_2_MM = (double)mmPerPixel;
    CONV_MM_2_PIXEL = 1.0 / CONV_PIXEL_2_MM;

    // Configure the HMI
    m_userInterface.setupUi(this);
    m_worldMapSize__pixel = (int32_t)((double)(GLOBAL_MAP_SIDE_SIZE__MM) * CONV_MM_2_PIXEL) + 1;

    m_ptWorldMapRawData = C_Tools_DataTable::AllocArrayU8(m_worldMapSize__pixel, m_worldMapSize__pixel,  0);

    m_coreAstar.SetMatrix(m_worldMapSize__pixel, m_worldMapSize__pixel);

    // Create the scene to show the scan
    m_ptMapGrScene = new MapScene(this);
    // Associate the scene to the graphic view
    m_userInterface.gv_Map->setScene(m_ptMapGrScene);

    m_worldMapImage = QImage(m_worldMapSize__pixel, m_worldMapSize__pixel , QImage::Format_RGB32);
    m_worldMapImage.fill(QColor(0,0,0));

    // Convert the grayscale from 8bits to 32 bits
    for (uint32_t i = 0; i < 256; i++)
    {
        /*
        if(i == NAV_MAP_OBSTACLE_PIXEL_VALUE)
            m_tabConvSlamMapPixelToRgbPixel[i] = 0xFFFF0000;
        else if (i == NAV_MAP_OBSTACLE_MARGIN_1_PIXEL_VALUE)
            m_tabConvSlamMapPixelToRgbPixel[i] = 0xFFFFFF00;
        else if (i == NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE)
            m_tabConvSlamMapPixelToRgbPixel[i] = 0xFF00FF00;
        else
        */
        m_tabConvSlamMapPixelToRgbPixel[i] = (0xFF000000 | (i << 16) | (i << 8) | i);
    }

    // Create a dummy image to activate centering
    m_ptMap = m_ptMapGrScene->addPixmap(QPixmap::fromImage(m_worldMapImage));

    // Init the map view windows
    on_btn_CenterMap_clicked();
    on_btn_ZoomDefaultMap_clicked();
    m_userInterface.chkB_FollowRobot->setChecked(true);

    connect(&m_TIMER_processNewMap, &QTimer::timeout, this, &C_PathFinder::SLOT_ProcessNewEstimation);

    // Statistics purpose
    m_estimationRateTimer.start();

    connect(&m_TIMER_positionRegulation, &QTimer::timeout, this, &C_PathFinder::SLOT_PositionRegulation);
    m_TIMER_positionRegulation.start(0);
}

void C_PathFinder::closeEvent (QCloseEvent * ptEvent)
{
    Q_UNUSED(ptEvent);

    // Send a signal to the parent
    emit SIG_ClosingWindow();
}


void C_PathFinder::on_btn_ZoomDefaultMap_clicked()
{
    m_userInterface.gv_Map->resetMatrix();
    m_userInterface.gv_Map->scale(3, 3);
}

void C_PathFinder::on_btn_ZoomOutMap_clicked()
{
    m_userInterface.gv_Map->scale(0.8, 0.8);
}

void C_PathFinder::on_btn_ZoomInMap_clicked()
{
    m_userInterface.gv_Map->scale(1.2, 1.2);
}

void C_PathFinder::on_btn_CenterMap_clicked()
{
    m_userInterface.chkB_FollowRobot->setChecked(false);

    m_mapViewCenterX = m_userInterface.gv_Map->sceneRect().center().x();
    m_mapViewCenterY = m_userInterface.gv_Map->sceneRect().center().y();
    m_userInterface.gv_Map->centerOn(m_mapViewCenterX, m_mapViewCenterY);
}

void C_PathFinder::on_btn_MoveRightMap_clicked()
{
    if(m_userInterface.chkB_FollowRobot->isChecked())
    {
        m_userInterface.chkB_FollowRobot->setChecked(false);
        m_mapViewCenterX = (int)m_robotPosX__pixel;
        m_mapViewCenterY = (int)m_robotPosY__pixel;
    }

    m_mapViewCenterX -= 2.0;
    m_userInterface.gv_Map->centerOn(m_mapViewCenterX, m_mapViewCenterY);
}

void C_PathFinder::on_btn_MoveLeftMap_clicked()
{
    if(m_userInterface.chkB_FollowRobot->isChecked())
    {
        m_userInterface.chkB_FollowRobot->setChecked(false);
        m_mapViewCenterX = (int)m_robotPosX__pixel;
        m_mapViewCenterY = (int)m_robotPosY__pixel;
    }

    m_mapViewCenterX += 2.0;
    m_userInterface.gv_Map->centerOn(m_mapViewCenterX, m_mapViewCenterY);
}

void C_PathFinder::on_btn_MoveDownMap_clicked()
{
    if(m_userInterface.chkB_FollowRobot->isChecked())
    {
        m_userInterface.chkB_FollowRobot->setChecked(false);
        m_mapViewCenterX = (int)m_robotPosX__pixel;
        m_mapViewCenterY = (int)m_robotPosY__pixel;
    }

    m_mapViewCenterY -= 2.0;
    m_userInterface.gv_Map->centerOn(m_mapViewCenterX, m_mapViewCenterY);
}

void C_PathFinder::on_btn_MoveUpMap_clicked()
{
    if(m_userInterface.chkB_FollowRobot->isChecked())
    {
        m_userInterface.chkB_FollowRobot->setChecked(false);
        m_mapViewCenterX = (int)m_robotPosX__pixel;
        m_mapViewCenterY = (int)m_robotPosY__pixel;
    }

    m_mapViewCenterY += 2.0;
    m_userInterface.gv_Map->centerOn(m_mapViewCenterX, m_mapViewCenterY);
}

void C_PathFinder::SLOT_StoreNewEstimation(double posX__mm, double posY__mm, double posTheta__rad, uint8_t * mapData, uint32_t xMin, uint32_t xMax, uint32_t yMin, uint32_t yMax)
{
    // No pending previous data to be processed
    if(m_SEM_newWorldMapAvailable.available() == 0)
    {
        m_robotPosX__pixel = posX__mm * CONV_MM_2_PIXEL;
        m_robotPosY__pixel = posY__mm * CONV_MM_2_PIXEL;
        m_robotAngle__rad = posTheta__rad;

        // Store new scan data
        C_Tools_DataTable::CopyArrayU8(m_ptWorldMapRawData, mapData, m_worldMapSize__pixel, m_worldMapUpdatedZone_xMin__pixel = xMin, m_worldMapUpdatedZone_yMin__pixel = yMin, m_worldMapUpdatedZone_xMax__pixel = xMax, m_worldMapUpdatedZone_yMax__pixel = yMax);

        // Signal the available new data
        m_SEM_newWorldMapAvailable.release(1);

        // Avoid using emit because it chain to the SLOT and handle the CPU
        // Use of a timer which is an other thread
        m_TIMER_processNewMap.start(0);
    }
}



void C_PathFinder::SLOT_ProcessNewEstimation(void)
{
    m_TIMER_processNewMap.stop();

    // Wait for new available data to process
    if(m_SEM_newWorldMapAvailable.available() > 0)
    {
        int screenWidth = m_worldMapImage.size().width();

        uint8_t * ptWorldMapRawDataSrc = m_ptWorldMapRawData + m_worldMapUpdatedZone_yMin__pixel * screenWidth + m_worldMapUpdatedZone_xMin__pixel;

        // First pass, re copy map data
        for(uint32_t y = m_worldMapUpdatedZone_yMin__pixel; y < m_worldMapUpdatedZone_yMax__pixel; y++)
        {
            uint32_t * ptWorldMapImage = (uint32_t *) m_worldMapImage.scanLine(y) + m_worldMapUpdatedZone_xMin__pixel;
            uint8_t * ptWorldMapRawData = ptWorldMapRawDataSrc;

            for(uint32_t x = m_worldMapUpdatedZone_xMin__pixel; x < m_worldMapUpdatedZone_xMax__pixel; x++)
            {
                *ptWorldMapImage = m_tabConvSlamMapPixelToRgbPixel[*ptWorldMapRawData];

                ptWorldMapRawData++;
                ptWorldMapImage++;
            }

            ptWorldMapRawDataSrc += screenWidth;
        }

        // Update the internal Astar data
        ptWorldMapRawDataSrc = m_ptWorldMapRawData + m_worldMapUpdatedZone_yMin__pixel * screenWidth + m_worldMapUpdatedZone_xMin__pixel;

        // First pass, re copy map data
        for(uint32_t y = m_worldMapUpdatedZone_yMin__pixel; y < m_worldMapUpdatedZone_yMax__pixel; y++)
        {
            uint8_t * ptWorldMapRawData = ptWorldMapRawDataSrc;

            for(uint32_t x = m_worldMapUpdatedZone_xMin__pixel; x < m_worldMapUpdatedZone_xMax__pixel; x++)
            {
                if((*ptWorldMapRawData) > NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE)
                {
                    m_coreAstar.SetWay(x,y,NAV_MAP_NO_OBSTACLE_EXPAND_COST);
                }
                else if((*ptWorldMapRawData) < NAV_MAP_OBSTACLE_MARGIN_1_PIXEL_VALUE)
                {
                    m_coreAstar.SetWall(x,y);
                }
                else if((*ptWorldMapRawData) < NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE)
                {
                    m_coreAstar.SetWay(x,y,NAV_MAP_OBSTACLE_MARGIN_1_EXPAND_COST);
                }
                else
                {
                    m_coreAstar.SetWay(x,y,NAV_MAP_OBSTACLE_MARGIN_2_EXPAND_COST);
                }

                /*
                switch(*ptWorldMapRawData)
                {
                case NAV_MAP_OBSTACLE_PIXEL_VALUE:
                    m_coreAstar.SetWall(x,y);
                    break;

                case NAV_MAP_OBSTACLE_MARGIN_1_PIXEL_VALUE:
                    m_coreAstar.SetWay(x,y,NAV_MAP_OBSTACLE_MARGIN_1_EXPAND_COST);
                    break;

                case NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE:
                    m_coreAstar.SetWay(x,y,NAV_MAP_OBSTACLE_MARGIN_2_EXPAND_COST);
                    break;

                default:
                    m_coreAstar.SetWay(x,y,NAV_MAP_NO_OBSTACLE_EXPAND_COST);
                    break;
                }
                */

                ptWorldMapRawData++;
            }

            ptWorldMapRawDataSrc += screenWidth;
        }

        // The robot pos is of course free space
        /*
        m_coreAstar.SetWay((int)m_robotPosX__pixel - 1, (int)m_robotPosY__pixel - 1, 1);
        m_coreAstar.SetWay((int)m_robotPosX__pixel, (int)m_robotPosY__pixel - 1, 1);
        m_coreAstar.SetWay((int)m_robotPosX__pixel + 1, (int)m_robotPosY__pixel - 1, 1);

        m_coreAstar.SetWay((int)m_robotPosX__pixel - 1, (int)m_robotPosY__pixel, 1);
        m_coreAstar.SetWay((int)m_robotPosX__pixel, (int)m_robotPosY__pixel, 1);
        m_coreAstar.SetWay((int)m_robotPosX__pixel + 1, (int)m_robotPosY__pixel, 1);

        m_coreAstar.SetWay((int)m_robotPosX__pixel - 1, (int)m_robotPosY__pixel + 1, 1);
        m_coreAstar.SetWay((int)m_robotPosX__pixel, (int)m_robotPosY__pixel + 1, 1);
        m_coreAstar.SetWay((int)m_robotPosX__pixel + 1, (int)m_robotPosY__pixel + 1, 1);
*/

        // Drive the robot
        DriveTheRobot();

        // Refresh the HMI
        UpdateHMI();

        // Signal the data has been processed
        m_SEM_newWorldMapAvailable.acquire();
    }
}


void C_PathFinder::DriveTheRobot(void)
{
    if(m_needPathComputation)
    {
        if(m_userInterface.chkB_DynamicMargin->isChecked())
        {
            bool isPathValid = m_coreAstar.GetNextTarget((int32_t)m_robotPosX__pixel, (int32_t)m_robotPosY__pixel, &m_currentPathPointId, &m_pathSize, &m_wantedPosX, &m_wantedPosY, &m_isLastTarget);
            m_needPositionRegulation = m_needPathComputationLast = true;
            //m_needPathComputationLast = true;

            if(!isPathValid)
            {
                // Do a new path search from the current position
                m_coreAstar.SetStart((int)m_robotPosX__pixel, (int)m_robotPosY__pixel);
                m_coreAstar.SearchPath();
            }
        }
    }
    else
    {
        if(m_needPathComputationLast)
        {
            // To be sure
            emit SIG_ExecuteCmd(C_TwoWheelsBase::STOP);

            m_needPositionRegulation = m_needPathComputationLast = false;
        }
    }
}

void C_PathFinder::SLOT_PositionRegulation(void)
{
    m_TIMER_positionRegulation.stop();

    static int posReachedCounter = 0;

    if(m_needPositionRegulation)
    {
        // Add 0.5 pixel to target the center of the pixel
        double targetX__pixel = ((double)m_wantedPosX) + 0.5;
        double targetY__pixel = ((double)m_wantedPosY) + 0.5;

        // Compute the angle to go from the current pos to the target
        double angle = C_Tools_Maths::ComputeAngle(m_robotPosX__pixel, m_robotPosY__pixel, targetX__pixel, targetY__pixel);

        // Compute the distance diff
        double dx = targetX__pixel - m_robotPosX__pixel;
        double dy = targetY__pixel - m_robotPosY__pixel;
        double distance__mm = C_Tools_Maths::sqrt7(dx * dx + dy * dy) * CONV_PIXEL_2_MM;

        if(m_pathSize)
            m_userInterface.lbl_nextPos->setText(QString("Target (%1/%2) : X = %3 mm : Y = %4 mm : θ = %5 deg").arg(m_currentPathPointId + 1).arg(m_pathSize).arg(targetX__pixel * CONV_PIXEL_2_MM).arg(targetY__pixel * CONV_PIXEL_2_MM).arg(angle * MATHS_CONV_RAD_2_DEG));
        else
            m_userInterface.lbl_nextPos->setText("No path found");

        // Position is good
        // When the position is previously not good, we need to go closer to the target
        // When the position is previously good, we let a margin to the target
        if((!m_wantedPosReached && (distance__mm < 70.0)) || (m_wantedPosReached && (distance__mm <= 200.0)))
        {
            // To go from not reached to reached, need wait a bit
            if(!m_wantedPosReached)
            {
                if(posReachedCounter++ > 10)
                {
                    m_wantedPosReached = m_isLastTarget;
                    posReachedCounter = 0;
                }
            }
            else
            {
                m_wantedPosReached = m_isLastTarget;
            }

            m_LastSpeed = 100.0;
            emit SIG_ExecuteCmd(C_TwoWheelsBase::STOP);
        }
        else
        {
            // Reset the pos reached flag
            m_wantedPosReached = false;
            posReachedCounter = 0;

            // Speed to use for movement
            float speed = 0.0;

            // Compute the action to do to get the robot to the right angle
            // Compute angle diff
            angle -= m_robotAngle__rad;
            while (angle > MATHS_PI) angle -= MATHS_2PI;
            while (angle < MATHS_MINUS_PI) angle += MATHS_2PI;

            // Convert to deg
            double angleAbs = abs(angle * MATHS_CONV_RAD_2_DEG);

            // The angle is not OK
            if(angleAbs > 70.0)
            {
                speed = CalcSpeed(300.0);

                if(angle > 0.0)
                {
                    emit SIG_ExecuteCmd(C_TwoWheelsBase::TURN_RIGHT, speed);
                }
                else
                {
                    emit SIG_ExecuteCmd(C_TwoWheelsBase::TURN_LEFT, speed);
                }
            }
            else if(angleAbs > 40.0)
            {
                speed = CalcSpeed(200.0);

                if(angle > 0.0)
                {
                    emit SIG_ExecuteCmd(C_TwoWheelsBase::TURN_RIGHT, speed);
                }
                else
                {
                    emit SIG_ExecuteCmd(C_TwoWheelsBase::TURN_LEFT, speed);
                }
            }
            else if(angleAbs > 25.0)
            {
                speed = 100;
                /*
                if(distance__mm <= 250)
                {
                    speed = 100;
                }*/

                // The angle is nearly good, begin to move forward
                if(angle > 0.0)
                {
                    emit SIG_ExecuteCmd(C_TwoWheelsBase::FORWARD_RIGHT, speed, 1.0 + angleAbs * 0.5);
                }
                else
                {
                    emit SIG_ExecuteCmd(C_TwoWheelsBase::FORWARD_LEFT, speed, 1.0 + angleAbs * 0.5);
                }

                /*
                if(angle > 0.0)
                {
                    emit SIG_ExecuteCmd(C_TwoWheelsBase::TURN_RIGHT, speed);
                }
                else
                {
                    emit SIG_ExecuteCmd(C_TwoWheelsBase::TURN_LEFT, speed);
                }
                */
            }
            else if(angleAbs > 5.0)
            {
                speed = 350;
                if(distance__mm <= 250)
                {
                    // Last target, go slowly
                    if(m_isLastTarget)
                    {
                        speed = 150;
                    }

                    // Not last target, keep go faster for target chaining
                    else speed = 250;
                }

                // The angle is nearly good, begin to move forward
                if(angle > 0.0)
                {
                    emit SIG_ExecuteCmd(C_TwoWheelsBase::FORWARD_RIGHT, speed, 1.0 + angleAbs * 0.078);
                }
                else
                {
                    emit SIG_ExecuteCmd(C_TwoWheelsBase::FORWARD_LEFT, speed, 1.0 + angleAbs * 0.078);
                }
            }
            else
            {
                /*
                speed = distance__mm;
                bool force = false;
                if(speed <= 250)
                {
                    // Last target, go slowly
                    if(m_isLastTarget)
                    {
                        speed = 150;
                        force = true;
                    }

                    // Not last target, keep go faster for target chaining
                    else speed = 250;
                }
                else if(speed >= 500) speed = 500;
                */

                speed = 400;
                bool force = false;
                if(distance__mm <= 250)
                {
                    // Last target, go slowly
                    if(m_isLastTarget)
                    {
                        speed = 150;
                        force = true;
                    }

                    // Not last target, keep go faster for target chaining
                    else speed = 300;
                }


                speed = CalcSpeed(speed, force);

                // Angle is OK, just go forward
                emit SIG_ExecuteCmd(C_TwoWheelsBase::FORWARD, speed);
            }
        }
    }

    // 10Hz position regulation
    m_TIMER_positionRegulation.start(100);
}

float C_PathFinder::CalcSpeed(float desiredSpeed, bool force)
{
    return desiredSpeed;

    if(force)
    {
        m_LastSpeed = desiredSpeed;
    }
    else
    {
        float accelDown = 5.0;
        float accelUp = 10.0;

        if(desiredSpeed < m_LastSpeed)
        {
            m_LastSpeed -= accelDown;
            if(m_LastSpeed < desiredSpeed)
            {
                m_LastSpeed = desiredSpeed;
            }
        }
        else if(desiredSpeed > m_LastSpeed)
        {
            m_LastSpeed += accelUp;
            if(m_LastSpeed > desiredSpeed)
            {
                m_LastSpeed = desiredSpeed;
            }
        }
    }

    return m_LastSpeed;
}


void C_PathFinder::DrawPath(QPainter * qPainter, AStarPathType pathType, QColor color, bool drawLine)
{
    // Prepare the surface for drawing
    //QPainter qPainter(image);
    qPainter->setBrush(color);
    qPainter->setPen(color);

    // Get the path
    list<pair<UINT, UINT>> path = m_coreAstar.GetPath(pathType);
    if(path.size() > 0)
    {
        list<pair<UINT, UINT>>::iterator pathIter = path.begin();

        int x0 = pathIter->first;
        int y0 = pathIter->second;

        int x1;
        int y1;

        pathIter++;
        for (; pathIter != path.end(); pathIter++)
        {
            x1 = pathIter->first;
            y1 = pathIter->second;

            if(drawLine)
            {
                qPainter->drawLine(x0, y0, x1, y1);
            }
            else
            {
                qPainter->drawPoint(x0, y0);
            }

            x0 = x1;
            y0 = y1;
        }

        // Draw the last point
        if(!drawLine)
        {
            qPainter->drawPoint(x0, y0);
        }
    }
}


void C_PathFinder::UpdateHMI(void)
{
    // Do a copy so we can draw anything without affecting the original map
    QImage mapToShow = m_worldMapImage.copy();

    // Show the current robot position
    QPainter qPainter(&mapToShow);

    // Need path computation
    // So draw the path
    if(m_needPathComputation)
    {
        //DrawPath(&qPainter, AStarPathType::raw, QColor(255,0,0), true);
        //DrawPath(&qPainter, AStarPathType::margin, QColor(255,200,0), true);
        DrawPath(&qPainter, AStarPathType::direct, QColor(0,255,125), true);

        // Draw the target
        if(m_isLastTarget)
        {
            qPainter.setBrush(QColor(0,255,255));
            qPainter.setPen(QColor(0,255,255));
        }
        else
        {
            qPainter.setBrush(QColor(0,0,255));
            qPainter.setPen(QColor(0,0,255));
        }
        qPainter.drawRect(m_wantedPosX - 1, m_wantedPosY - 1, 2, 2);

        // Draw path with dots
        DrawPath(&qPainter, AStarPathType::direct, QColor(0,128,0), false);
    }


    // Draw the immediate direct path to the next target

    // Draw the robot
    qPainter.setBrush(QColor(255,0,255));
    qPainter.setPen(QColor(255,0,255));
    qPainter.drawEllipse(m_robotPosX__pixel - 1, m_robotPosY__pixel - 1, 2, 2);

    // Draw the robot direction
    qPainter.setBrush(QColor(255,0,0));
    qPainter.setPen(QColor(255,0,0));
    qPainter.drawPoint(m_robotPosX__pixel + 3 * qFastCos(m_robotAngle__rad), m_robotPosY__pixel + 3 * qFastSin(m_robotAngle__rad));


    // Show the map on the scene
    m_ptMap->setPixmap(QPixmap::fromImage(mapToShow));

    // Center the map on the robot if needed
    if(m_userInterface.chkB_FollowRobot->isChecked())
    {
        m_userInterface.gv_Map->centerOn((int)m_robotPosX__pixel, (int)m_robotPosY__pixel);
    }

    // Show the robot pos
    m_userInterface.lbl_coreSlamPos->setText(QString("Current robot position : X = %1 mm : Y = %2 mm : θ = %3 deg").arg(m_robotPosX__pixel * CONV_PIXEL_2_MM).arg(m_robotPosY__pixel * CONV_PIXEL_2_MM).arg(m_robotAngle__rad * MATHS_CONV_RAD_2_DEG));


    m_numberOfComputationCycles ++;
    double elapsedTime__ms = m_estimationRateTimer.elapsed();
    if(elapsedTime__ms > 1000)
    {
        m_estimationRateTimer.restart();
        m_userInterface.lbl_frameRate->setText(QString("A* rate : %1 fps").arg(QString::number(m_numberOfComputationCycles * 1000.0 / elapsedTime__ms, 'f', 1)));
        m_numberOfComputationCycles = 0;
    }
}


void C_PathFinder::MapScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    C_PathFinder * ptParent = (C_PathFinder *)m_ptParent;

    QPointF clickedPos;

    switch(event->button())
    {
    case Qt::LeftButton:
        clickedPos = event->buttonDownScenePos(Qt::LeftButton);
        ptParent->m_coreAstar.SetStart((int)(ptParent->m_robotPosX__pixel), (int)(ptParent->m_robotPosY__pixel));
        ptParent->m_coreAstar.SetEnd(clickedPos.x(), clickedPos.y());
        ptParent->m_coreAstar.SearchPath();
        ptParent->m_currentPathPointId = 0;
        ptParent->m_wantedPosReached = false;
        ptParent->m_needPathComputation = true;


        break;

    case Qt::RightButton:
        ptParent->m_needPathComputation = ptParent->m_needPositionRegulation = false;
        emit ptParent->SIG_ExecuteCmd(C_TwoWheelsBase::STOP, 0);
        ptParent->m_userInterface.lbl_nextPos->setText(QString("Target : undefined"));

        break;

    default:
        break;
    }
}


#include "moc_C_PathFinder.cpp"

