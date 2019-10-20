#include "C_CoreSlamRealAngle_8bppMap.h"


C_CoreSlamRealAngle_8bppMap::C_CoreSlamRealAngle_8bppMap(uint32_t globalMapSquareSize__mm, uint32_t lidarMinReliableMeasuredDist__mm, uint32_t lidarMaxReliableMeasuredDist__mm, uint32_t lidarMinDistToAddVirtualMeasures__mm, uint32_t maxNbOfVirtualMeasuresAtMaxDist)
{
    // Map 1 model
    m_globalMap.INIT_MAP_PIXEL_VALUE = 128;

    m_globalMap.MM_PER_PIXEL = 10;
    m_globalMap.CONV_PIXEL_2_MM = (double)m_globalMap.MM_PER_PIXEL;
    m_globalMap.CONV_MM_2_PIXEL = 1.0 / m_globalMap.CONV_PIXEL_2_MM;
    m_globalMap.m_currentPosX__pixel = 0;
    m_globalMap.m_currentPosY__pixel = 0;

    m_globalMap.m_opti_globalMapUpdateZoneXmin__pixel = 0;
    m_globalMap.m_opti_globalMapUpdateZoneXmax__pixel = 0;
    m_globalMap.m_opti_globalMapUpdateZoneYmin__pixel = 0;
    m_globalMap.m_opti_globalMapUpdateZoneYmax__pixel = 0;

    m_globalMap.OBSTACLES_WIDTH__MM = 150;
    m_globalMap.OBSTACLES_HALF_WIDTH__PIXEL = (uint32_t)((double)(m_globalMap.OBSTACLES_WIDTH__MM) * m_globalMap.CONV_MM_2_PIXEL) / 2;

    m_globalMap.m_opti_globalMapSquareSize__pixel = 0;

    // The bigger the value is, the faster the obstacle is marked on map
    m_globalMap.RAY_TRACE_ALPHA_MODEL = 50;
    m_globalMap.m_opti_256MinusAlphaModel = 256 - m_globalMap.RAY_TRACE_ALPHA_MODEL;


    // Map 2 model
    m_navMap.INIT_MAP_PIXEL_VALUE = NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE;

    m_navMap.MM_PER_PIXEL = 40;
    m_navMap.CONV_PIXEL_2_MM = (double)m_navMap.MM_PER_PIXEL;
    m_navMap.CONV_MM_2_PIXEL = 1.0 / m_navMap.CONV_PIXEL_2_MM;
    m_navMap.m_currentPosX__pixel = 0;
    m_navMap.m_currentPosY__pixel = 0;

    m_navMap.m_opti_globalMapUpdateZoneXmin__pixel = 0;
    m_navMap.m_opti_globalMapUpdateZoneXmax__pixel = 0;
    m_navMap.m_opti_globalMapUpdateZoneYmin__pixel = 0;
    m_navMap.m_opti_globalMapUpdateZoneYmax__pixel = 0;

    m_navMap.OBSTACLES_WIDTH__MM = 90;
    m_navMap.OBSTACLES_HALF_WIDTH__PIXEL = (uint32_t)((double)(m_navMap.OBSTACLES_WIDTH__MM) * m_navMap.CONV_MM_2_PIXEL) / 2;

    m_navMap.m_opti_globalMapSquareSize__pixel = 0;

    m_navMap.RAY_TRACE_ALPHA_MODEL = 5;
    m_navMap.m_opti_256MinusAlphaModel = 256 - m_navMap.RAY_TRACE_ALPHA_MODEL;


    // Store the map size
    m_globalMapSquareSize__mm = globalMapSquareSize__mm;

    // Precomputed usefull data
    m_globalMap.m_opti_globalMapSideSize_minus1__pixel = (int32_t)((double)m_globalMapSquareSize__mm * m_globalMap.CONV_MM_2_PIXEL);
    m_globalMap.m_opti_globalMapSquareSize__pixel = m_globalMap.m_opti_globalMapSideSize_minus1__pixel + 1;
    m_globalMap.m_opti_minus_globalMapSideSize__pixel = -m_globalMap.m_opti_globalMapSquareSize__pixel;

    m_navMap.m_opti_globalMapSideSize_minus1__pixel = (int32_t)((double)m_globalMapSquareSize__mm * m_navMap.CONV_MM_2_PIXEL);
    m_navMap.m_opti_globalMapSquareSize__pixel = m_navMap.m_opti_globalMapSideSize_minus1__pixel + 1;
    m_navMap.m_opti_minus_globalMapSideSize__pixel = -m_navMap.m_opti_globalMapSquareSize__pixel;


    // Precompute data for Angle err model
    for (int32_t i = 0; i < NB_OF_VALUES_OF_L1_DTHETA_ERR_MODEL; i++)
    {
        m_tabOfL1DThetaErrModel__rad[i] = m_tabOfL1DThetaErrModel__rad[i] * MATHS_CONV_DEG_2_RAD;
        m_opti_cached_tabOfCosOfL1ThetaErrModel[i] = cos(m_tabOfL1DThetaErrModel__rad[i]);
        m_opti_cached_tabOfSinOfL1ThetaErrModel[i] = sin(m_tabOfL1DThetaErrModel__rad[i]);
    }
    for (int32_t i = 0; i < NB_OF_VALUES_OF_L2_DTHETA_ERR_MODEL; i++)
    {
        m_tabOfL2DThetaErrModel__rad[i] = m_tabOfL2DThetaErrModel__rad[i] * MATHS_CONV_DEG_2_RAD;
        m_opti_cached_tabOfCosOfL2ThetaErrModel[i] = cos(m_tabOfL2DThetaErrModel__rad[i]);
        m_opti_cached_tabOfSinOfL2ThetaErrModel[i] = sin(m_tabOfL2DThetaErrModel__rad[i]);
    }
    for (int32_t i = 0; i < NB_OF_VALUES_OF_L3_DTHETA_ERR_MODEL; i++)
    {
        m_tabOfL3DThetaErrModel__rad[i] = m_tabOfL3DThetaErrModel__rad[i] * MATHS_CONV_DEG_2_RAD;
        m_opti_cached_tabOfCosOfL3ThetaErrModel[i] = cos(m_tabOfL3DThetaErrModel__rad[i]);
        m_opti_cached_tabOfSinOfL3ThetaErrModel[i] = sin(m_tabOfL3DThetaErrModel__rad[i]);
    }

    // Store sensor model
    //m_lidarMinReliableMeasuredDist__mm = lidarMinReliableMeasuredDist__mm;
    m_opti_squareOf_lidarMinReliableMeasuredDist__mm = lidarMinReliableMeasuredDist__mm;
    m_opti_squareOf_lidarMinReliableMeasuredDist__mm = m_opti_squareOf_lidarMinReliableMeasuredDist__mm * m_opti_squareOf_lidarMinReliableMeasuredDist__mm;
    //m_lidarMinReliableMeasuredDist__pixel = m_lidarMinReliableMeasuredDist__mm * m_globalMap.CONV_MM_2_PIXEL;

    //m_lidarMaxReliableMeasuredDist__mm = lidarMaxReliableMeasuredDist__mm;
    m_opti_squareOf_lidarMaxReliableMeasuredDist__mm = lidarMaxReliableMeasuredDist__mm;
    m_opti_squareOf_lidarMaxReliableMeasuredDist__mm = m_opti_squareOf_lidarMaxReliableMeasuredDist__mm * m_opti_squareOf_lidarMaxReliableMeasuredDist__mm;
    //m_lidarMaxReliableMeasuredDist__pixel = m_lidarMaxReliableMeasuredDist__mm * m_globalMap.CONV_MM_2_PIXEL;

    //m_lidarMinDistToAddVirtualMeasures__mm = lidarMinDistToAddVirtualMeasures__mm;
    //m_lidarMinDistToAddVirtualMeasures__pixel = m_lidarMinDistToAddVirtualMeasures__mm * m_globalMap.CONV_MM_2_PIXEL;
    //m_maxNbOfVirtualMeasuresAtMaxDist = maxNbOfVirtualMeasuresAtMaxDist;
    //m_opti_maxNbOfVirtualMeasuresAtMaxDist_minus1 = m_maxNbOfVirtualMeasuresAtMaxDist - 1;

    //m_lidarDistFromMinDistToAddVirtualMeasuresToMaxReliableMeasuredDist__mm = m_lidarMaxReliableMeasuredDist__mm - m_lidarMinDistToAddVirtualMeasures__mm;

    Reset();
}


C_CoreSlamRealAngle_8bppMap::~C_CoreSlamRealAngle_8bppMap()
{
    // Clear all malloc stuff
    free(m_globalMap.m_ptRawPixelMatrix_8bpp);
    free(m_navMap.m_ptRawPixelMatrix_8bpp);
    free(m_navMap.m_ptModifiedPixelMatrix_8bpp);
}


void C_CoreSlamRealAngle_8bppMap::Reset()
{
    // Put the robot to the midle of the map
    m_currentPosX__mm = m_globalMapSquareSize__mm / 2;
    m_currentPosY__mm = m_globalMapSquareSize__mm / 2;
    m_currentPosAngle__rad = 0.0;
    m_opti_currentPosAngle__cos = cos(m_currentPosAngle__rad);
    m_opti_currentPosAngle__sin = sin(m_currentPosAngle__rad);

    // Init the probability map
    m_globalMap.m_ptRawPixelMatrix_8bpp = C_Tools_DataTable::AllocArrayU8(m_globalMap.m_opti_globalMapSquareSize__pixel, m_globalMap.m_opti_globalMapSquareSize__pixel,  m_globalMap.INIT_MAP_PIXEL_VALUE);
    // Init the drawing zone to the whole map
    m_globalMap.m_opti_globalMapUpdateZoneXmin__pixel = 0;
    m_globalMap.m_opti_globalMapUpdateZoneXmax__pixel = m_globalMap.m_opti_globalMapSideSize_minus1__pixel;
    m_globalMap.m_opti_globalMapUpdateZoneYmin__pixel = 0;
    m_globalMap.m_opti_globalMapUpdateZoneYmax__pixel = m_globalMap.m_opti_globalMapSideSize_minus1__pixel;

    m_globalMap.m_currentPosX__pixel = C_Tools_Maths::Opti_round(m_currentPosX__mm * m_globalMap.CONV_MM_2_PIXEL);
    m_globalMap.m_currentPosY__pixel = C_Tools_Maths::Opti_round(m_currentPosY__mm * m_globalMap.CONV_MM_2_PIXEL);

    // Init the probability map
    m_navMap.m_ptRawPixelMatrix_8bpp = C_Tools_DataTable::AllocArrayU8(m_navMap.m_opti_globalMapSquareSize__pixel, m_navMap.m_opti_globalMapSquareSize__pixel,  m_navMap.INIT_MAP_PIXEL_VALUE);
    m_navMap.m_ptModifiedPixelMatrix_8bpp = C_Tools_DataTable::AllocArrayU8(m_navMap.m_opti_globalMapSquareSize__pixel, m_navMap.m_opti_globalMapSquareSize__pixel,  m_navMap.INIT_MAP_PIXEL_VALUE);
    // Init the drawing zone to the whole map
    m_navMap.m_opti_globalMapUpdateZoneXmin__pixel = 0;
    m_navMap.m_opti_globalMapUpdateZoneXmax__pixel = m_navMap.m_opti_globalMapSideSize_minus1__pixel;
    m_navMap.m_opti_globalMapUpdateZoneYmin__pixel = 0;
    m_navMap.m_opti_globalMapUpdateZoneYmax__pixel = m_navMap.m_opti_globalMapSideSize_minus1__pixel;

    m_navMap.m_currentPosX__pixel = C_Tools_Maths::Opti_round(m_currentPosX__mm * m_navMap.CONV_MM_2_PIXEL);
    m_navMap.m_currentPosY__pixel = C_Tools_Maths::Opti_round(m_currentPosY__mm * m_navMap.CONV_MM_2_PIXEL);

    // Reset error model
    m_appliedDxErrValue__mm = 0;
    m_appliedDyErrValue__mm = 0;
    m_appliedDangleErrValue__rad = 0;

    // Reset statistics
    m_nbMapUpdatePassSinceLastRead = 0;
}


void C_CoreSlamRealAngle_8bppMap::IntegrateNewSensorData(uint32_t * tabOfDistMeasures__mm, double * tabOfAngleMeasures__cos, double * tabOfAngleMeasures__sin, uint32_t nbOfMeasures, int paramIndex)
{
    // Protect from launching severals times
    if(m_isBusy)
    {
        return;
    }
    m_isBusy = true;

    // Store new sensor data
    // Lidar measures
    m_tabOfLidarMeasures__mm = tabOfDistMeasures__mm;
    m_tabOfLidarMeasures__cos = tabOfAngleMeasures__cos;
    m_tabOfLidarMeasures__sin = tabOfAngleMeasures__sin;
    m_nbOfMeasures = nbOfMeasures;

    // Adapt lidar data to the good format
    if(ProcessLidarData(m_paramsForUsingLidar[paramIndex].lidarPosOffsetX__mm, m_paramsForUsingLidar[paramIndex].lidarPosOffsetY__mm))
    {
        // Reset the last estimation
        m_appliedDxErrValue__mm = 0;
        m_appliedDyErrValue__mm = 0;
        m_appliedDangleErrValue__rad = 0;

        // Fast estimate new robot position
        if(EstimateNewPosition(1, m_paramsForUsingLidar[paramIndex].estimationType))
        {
            // Refine estimation
            if(EstimateNewPosition(2, m_paramsForUsingLidar[paramIndex].estimationType))
            {
                // Refine more estimation
                if(EstimateNewPosition(3, m_paramsForUsingLidar[paramIndex].estimationType))
                {
                    // Update the map with new sensor data
                    UpdateMap(&m_globalMap);

                    // Update the map with new sensor data
                    // Use cached data from the previous UpdateMap
                    UpdateMap_Opti(&m_navMap);

                    // Add margin to the obstacles
                    UpdateModifiedMap(&m_navMap);
                    AddMarginToModifiedMap(&m_navMap);

                    // Statistic purpose : Nb of map computation pass since last time the value is requested
                    m_nbMapUpdatePassSinceLastRead++;
                }
            }
        }
    }

    // Protect from launching severals times
    m_isBusy = false;
}


bool C_CoreSlamRealAngle_8bppMap::EstimateNewPosition(int optimizationLevel, enum_EstimationType estimationType)
{
    // No need to estimate position
    if(estimationType == NONE) return true;

    // Position to check
    double checkingPosX__mm = 0.0;
    double checkingPosY__mm = 0.0;

    double angleErrModel__cos;
    double angleErrModel__sin;

    // Position matching quality
    // The lower it is, the best it is
    uint64_t matchingQualityValue = 0;
    uint64_t currentBestMatchingQualityValue = UINT64_MAX;

    // Store the current best position
    double currentBestPosX__mm = 0.0;
    double currentBestPosY__mm = 0.0;
    double currentBestPosAngle__rad = 0.0;

    // Store the current best position correction
    double currentBestPosDx__mm = 0.0;
    double currentBestPosDy__mm = 0.0;
    double currentBestPosDTheta__rad = 0.0;


    int32_t nbOfValuesOfDxErrModel = NB_OF_VALUES_OF_L1_DX_ERR_MODEL;
    int32_t nbOfValuesOfDyErrModel = NB_OF_VALUES_OF_L1_DY_ERR_MODEL;
    int32_t nbOfValuesOfThetaErrModel = NB_OF_VALUES_OF_L1_DTHETA_ERR_MODEL;

    double * pt_tabOfDThetaErrModel__rad = m_tabOfL1DThetaErrModel__rad;
    double * pt_opti_cached_tabOfCosOfThetaErrModel = m_opti_cached_tabOfCosOfL1ThetaErrModel;
    double * pt_opti_cached_tabOfSinOfThetaErrModel = m_opti_cached_tabOfSinOfL1ThetaErrModel;

    // Depending on the optimization level, select the right parameters
    switch(optimizationLevel)
    {
    case 2:
        nbOfValuesOfDxErrModel = NB_OF_VALUES_OF_L2_DX_ERR_MODEL;
        nbOfValuesOfDyErrModel = NB_OF_VALUES_OF_L2_DY_ERR_MODEL;
        nbOfValuesOfThetaErrModel = NB_OF_VALUES_OF_L2_DTHETA_ERR_MODEL;

        pt_tabOfDThetaErrModel__rad = m_tabOfL2DThetaErrModel__rad;
        pt_opti_cached_tabOfCosOfThetaErrModel = m_opti_cached_tabOfCosOfL2ThetaErrModel;
        pt_opti_cached_tabOfSinOfThetaErrModel = m_opti_cached_tabOfSinOfL2ThetaErrModel;

        break;

    case 3:
        nbOfValuesOfDxErrModel = NB_OF_VALUES_OF_L3_DX_ERR_MODEL;
        nbOfValuesOfDyErrModel = NB_OF_VALUES_OF_L3_DY_ERR_MODEL;
        nbOfValuesOfThetaErrModel = NB_OF_VALUES_OF_L3_DTHETA_ERR_MODEL;

        pt_tabOfDThetaErrModel__rad = m_tabOfL3DThetaErrModel__rad;
        pt_opti_cached_tabOfCosOfThetaErrModel = m_opti_cached_tabOfCosOfL3ThetaErrModel;
        pt_opti_cached_tabOfSinOfThetaErrModel = m_opti_cached_tabOfSinOfL3ThetaErrModel;

        break;

    default: break;

    }

    // Only need to estimate Theta
    if(estimationType == THETA_ONLY)
    {
        nbOfValuesOfDxErrModel = nbOfValuesOfDyErrModel = 1;
    }

    // Search of best position by looping on Delta Angle, X, Y
    // Using the Move Error Model
    //**********************************************************************

#ifdef ENABLE_ESTIMATION
    for (int32_t i = 0; i < nbOfValuesOfThetaErrModel; i++)
#else
    for (int32_t i = 0; i < 1; i++)
#endif
    {
        // Optimize : Avoid cos, sin computation
        bool angleErrModelValueChanged = true;

        // Compute once the cos, sin
        angleErrModel__cos = pt_opti_cached_tabOfCosOfThetaErrModel[i];
        angleErrModel__sin = pt_opti_cached_tabOfSinOfThetaErrModel[i];

        // Pointer to the pos X error model
        double * pt_tabOfDxErrModel__mm = (double*) m_tabOfL1DxErrModel__mm;
        switch(optimizationLevel)
        {
        case 2:
            pt_tabOfDxErrModel__mm = (double*) m_tabOfL2DxErrModel__mm;
            break;

        case 3:
            pt_tabOfDxErrModel__mm = (double*) m_tabOfL3DxErrModel__mm;
            break;

        default: break;

        }


#ifdef ENABLE_ESTIMATION
        for (int32_t j = 0; j < nbOfValuesOfDxErrModel; j++)
#else
        for (int32_t j = 0; j < 1; j++)
#endif
        {
            // Compute an possible posX (to be checked)
            checkingPosX__mm = m_currentPosX__mm + (*pt_tabOfDxErrModel__mm);

            // Pointer to the pos Y error model
            double * pt_tabOfDyErrModel__mm = (double*) m_tabOfL1DyErrModel__mm;
            switch(optimizationLevel)
            {
            case 2:
                pt_tabOfDyErrModel__mm = (double*) m_tabOfL2DyErrModel__mm;
                break;

            case 3:
                pt_tabOfDyErrModel__mm = (double*) m_tabOfL3DyErrModel__mm;
                break;

            default: break;

            }

#ifdef ENABLE_ESTIMATION
            for (int32_t k = 0; k < nbOfValuesOfDyErrModel; k++)
#else
            for (int32_t k = 0; k < 1; k++)
#endif
            {
                // Compute an possible posY (to be checked)
                checkingPosY__mm = m_currentPosY__mm + (*pt_tabOfDyErrModel__mm);

                if (angleErrModelValueChanged)
                {
                    matchingQualityValue = ComputeMatching(checkingPosX__mm, checkingPosY__mm, m_opti_currentPosAngle__cos * angleErrModel__cos - m_opti_currentPosAngle__sin * angleErrModel__sin, m_opti_currentPosAngle__sin * angleErrModel__cos + m_opti_currentPosAngle__cos * angleErrModel__sin);
                    angleErrModelValueChanged = false;
                }
                else
                {
                    matchingQualityValue = Opti_ComputeMatching(checkingPosX__mm, checkingPosY__mm);
                }

                // Best position found
                if (matchingQualityValue < currentBestMatchingQualityValue)
                {
                    // Store the new best position
                    currentBestMatchingQualityValue = matchingQualityValue;

                    currentBestPosX__mm = checkingPosX__mm;
                    currentBestPosY__mm = checkingPosY__mm;
                    currentBestPosAngle__rad = m_currentPosAngle__rad + (*pt_tabOfDThetaErrModel__rad);

                    // Debug purpose only
                    currentBestPosDx__mm = (*pt_tabOfDxErrModel__mm);
                    currentBestPosDy__mm = (*pt_tabOfDyErrModel__mm);
                    currentBestPosDTheta__rad = (*pt_tabOfDThetaErrModel__rad);
                }

                pt_tabOfDyErrModel__mm++;
            }

            pt_tabOfDxErrModel__mm++;
        }

        pt_tabOfDThetaErrModel__rad++;
    }

    // Has at least one estimation
    if(currentBestMatchingQualityValue < UINT64_MAX)
    {
        // Angle normalize [-Pi; Pi]
        while (currentBestPosAngle__rad > MATHS_PI) currentBestPosAngle__rad -= MATHS_2PI;
        while (currentBestPosAngle__rad < MATHS_MINUS_PI) currentBestPosAngle__rad += MATHS_2PI;

        // Store the best of all position found
        m_currentPosX__mm = currentBestPosX__mm;

        // No need because we do the precise computation just after
        m_globalMap.m_currentPosX__pixel = C_Tools_Maths::Opti_round(m_currentPosX__mm * m_globalMap.CONV_MM_2_PIXEL);
        m_navMap.m_currentPosX__pixel = C_Tools_Maths::Opti_round(m_currentPosX__mm * m_navMap.CONV_MM_2_PIXEL);

        m_currentPosY__mm = currentBestPosY__mm;

        // No need because we do the precise computation just after
        m_globalMap.m_currentPosY__pixel = C_Tools_Maths::Opti_round(m_currentPosY__mm * m_globalMap.CONV_MM_2_PIXEL);
        m_navMap.m_currentPosY__pixel = C_Tools_Maths::Opti_round(m_currentPosY__mm * m_navMap.CONV_MM_2_PIXEL);

        m_currentPosAngle__rad = currentBestPosAngle__rad;
        m_opti_currentPosAngle__cos = qFastCos(currentBestPosAngle__rad);
        m_opti_currentPosAngle__sin = qFastSin(currentBestPosAngle__rad);


        m_appliedDxErrValue__mm += currentBestPosDx__mm;
        m_appliedDyErrValue__mm += currentBestPosDy__mm;
        m_appliedDangleErrValue__rad += currentBestPosDTheta__rad;

        return true;
    }

    return false;
}


bool C_CoreSlamRealAngle_8bppMap::ProcessLidarData(int offsetX__mm, int offsetY__mm)
{
    uint32_t nbOfPoints = 0;

    // Access lidar data
    uint32_t * ptReadOfLidarMeasures__mm = m_tabOfLidarMeasures__mm;
    double * ptReadOfLidarAngle__cos = m_tabOfLidarMeasures__cos;
    double * ptReadOfLidarAngle__sin = m_tabOfLidarMeasures__sin;

    // Tab of cartesian coordinates of detected points
    double * ptWriteOfMeasuresPosX__mm = m_tabOfLidarMeasuresInCartesianRef_X__mm;
    double * ptWriteOfMeasuresPosY__mm = m_tabOfLidarMeasuresInCartesianRef_Y__mm;

    // As the lidar is not at the exact center of the robot
    // This distance is the computed dist to the center of the robot
    double distFromObstacleToRobotCenter__mm = 0.0;

    // Current position
    double currentMeasuredPosX = 0.0;
    double currentMeasuredPosY = 0.0;

    // Computation loop on each detected points
    for(int32_t i = 0; i < m_nbOfMeasures; i++)
    {
        // Convert to cartesian coordinates
        currentMeasuredPosX = (*ptReadOfLidarMeasures__mm) * (*ptReadOfLidarAngle__cos) + offsetX__mm;
        currentMeasuredPosY = (*ptReadOfLidarMeasures__mm) * (*ptReadOfLidarAngle__sin) + offsetY__mm;

        distFromObstacleToRobotCenter__mm = currentMeasuredPosX * currentMeasuredPosX + currentMeasuredPosY * currentMeasuredPosY;

        // Take in account only valide points
        if ((distFromObstacleToRobotCenter__mm >= m_opti_squareOf_lidarMinReliableMeasuredDist__mm) && (distFromObstacleToRobotCenter__mm <= m_opti_squareOf_lidarMaxReliableMeasuredDist__mm))
        {
            // Add the current measure
            *ptWriteOfMeasuresPosX__mm = currentMeasuredPosX;
            *ptWriteOfMeasuresPosY__mm = currentMeasuredPosY;

            ptWriteOfMeasuresPosX__mm++;
            ptWriteOfMeasuresPosY__mm++;
            nbOfPoints++;
        }

        ptReadOfLidarMeasures__mm++;
        ptReadOfLidarAngle__cos++;
        ptReadOfLidarAngle__sin++;
    }

    m_nbOfMeasuresTakenIntoAccount = static_cast<int32_t>(nbOfPoints);
    m_opti_nbOfMeasuresTakenIntoAccount_minus1 = m_nbOfMeasuresTakenIntoAccount - 1;

    // Final status, only OK if enough usable points
    return (nbOfPoints >= MIN_NB_OF_POINTS_TO_ALLOW_POS_ESTIMATION);
}


// Compute the matching quality of the detected points set
// For each detected point, read on the probability map if the point is probable or not
// Smallest is the best
uint64_t C_CoreSlamRealAngle_8bppMap::ComputeMatching(double posX__mm, double posY__mm, double preComputedCos, double preComputedSin)
{
#ifdef ENABLE_MAP_BOUNDARIES_CHECK
    uint32_t nbOfPoints = 0;
#endif

    int32_t x, y = 0;
    uint64_t sum = 0;

    double cos_x_CONV_MM_2_PIXEL = preComputedCos * m_globalMap.CONV_MM_2_PIXEL;
    double sin_x_CONV_MM_2_PIXEL = preComputedSin * m_globalMap.CONV_MM_2_PIXEL;

    double posX__pixel = posX__mm * m_globalMap.CONV_MM_2_PIXEL;
    double posY__pixel = posY__mm * m_globalMap.CONV_MM_2_PIXEL;

    int32_t i = m_opti_nbOfMeasuresTakenIntoAccount_minus1;
    double * ptX = m_tabOfLidarMeasuresInCartesianRef_X__mm + i;
    double * ptY = m_tabOfLidarMeasuresInCartesianRef_Y__mm + i;
    double * ptCachedX = m_opti_computeMatching_cached_X + i;
    double * ptCachedY = m_opti_computeMatching_cached_Y + i;

    // Translate and rotate scan to robot currentPosition
    // and compute the CalcDistance
    while (i >= 0)
    {
        (*ptCachedX) = cos_x_CONV_MM_2_PIXEL * (*ptX) - sin_x_CONV_MM_2_PIXEL * (*ptY) + 0.5;
        (*ptCachedY) = sin_x_CONV_MM_2_PIXEL * (*ptX) + cos_x_CONV_MM_2_PIXEL * (*ptY) + 0.5;

        x = C_Tools_Maths::Opti_floor(posX__pixel + (*ptCachedX));
        y = C_Tools_Maths::Opti_floor(posY__pixel + (*ptCachedY));

        // Check boundaries
#ifdef ENABLE_MAP_BOUNDARIES_CHECK
        if ((x >= 0) && (x < m_globalMap.m_opti_globalMapSquareSize__pixel) && (y >= 0) && (y < m_globalMap.m_opti_globalMapSquareSize__pixel))
#endif
        {
            sum += m_globalMap.m_ptRawPixelMatrix_8bpp[y * m_globalMap.m_opti_globalMapSquareSize__pixel + x];

#ifdef ENABLE_MAP_BOUNDARIES_CHECK
            nbOfPoints++;
#endif
        }

        i--; ptX--; ptY--; ptCachedX--; ptCachedY--;
    }

#ifdef ENABLE_MAP_BOUNDARIES_CHECK
    if (nbOfPoints > MIN_NB_OF_POINTS_TO_ALLOW_POS_ESTIMATION)
    {
        sum = (sum << 10) / nbOfPoints;
    }
    else
    {
        sum = UINT64_MAX;
    }

    return sum;
    
#else
    return ((sum << 10) / m_nbOfMeasuresTakenIntoAccount);
#endif
}


//Calculer la ressemblance entre le scan et la carte
uint64_t C_CoreSlamRealAngle_8bppMap::Opti_ComputeMatching(double xInMm, double yInMm)
{
#ifdef ENABLE_MAP_BOUNDARIES_CHECK
    uint32_t nb_points = 0;
#endif

    int32_t x, y = 0;
    uint64_t sum = 0;

    double xInPixel = xInMm * m_globalMap.CONV_MM_2_PIXEL;
    double yInPixel = yInMm * m_globalMap.CONV_MM_2_PIXEL;

    int32_t i = m_opti_nbOfMeasuresTakenIntoAccount_minus1;
    double * ptCachedX = m_opti_computeMatching_cached_X + i;
    double * ptCachedY = m_opti_computeMatching_cached_Y + i;

    // Translate and rotate scan to robot currentPosition
    // and compute the CalcDistance
    while (i >= 0)
    {
        x = C_Tools_Maths::Opti_floor(xInPixel + (*ptCachedX));
        y = C_Tools_Maths::Opti_floor(yInPixel + (*ptCachedY));

        // Check boundaries
#ifdef ENABLE_MAP_BOUNDARIES_CHECK
        if ((x >= 0) && (x < m_globalMap.m_opti_globalMapSquareSize__pixel) && (y >= 0) && (y < m_globalMap.m_opti_globalMapSquareSize__pixel))
#endif
        {
            sum += m_globalMap.m_ptRawPixelMatrix_8bpp[y * m_globalMap.m_opti_globalMapSquareSize__pixel + x];

#ifdef ENABLE_MAP_BOUNDARIES_CHECK
            nb_points++;
#endif
        }

        i--; ptCachedX--; ptCachedY--;
    }

#ifdef ENABLE_MAP_BOUNDARIES_CHECK
    if (nb_points > MIN_NB_OF_POINTS_TO_ALLOW_POS_ESTIMATION)
    {
        sum = (sum << 10) / nb_points;
    }
    else
    {
        sum = UINT64_MAX;
    }

    return sum;
    
#else
    return ((sum << 10) / m_nbOfMeasuresTakenIntoAccount);
#endif

}


void C_CoreSlamRealAngle_8bppMap::UpdateMap(struct_Map * ptMap)
{
    double x2p, y2p;
    int32_t x2, y2, xp, yp;
    double add;

    double conv_mm_2_pixel = ptMap->CONV_MM_2_PIXEL;

    double currentX__pixel = ptMap->m_currentPosX__pixel + 0.5;
    double currentY__pixel = ptMap->m_currentPosY__pixel + 0.5;

    uint32_t xmin__pixel = ptMap->m_currentPosX__pixel;
    uint32_t xmax__pixel = xmin__pixel;
    uint32_t ymin__pixel = ptMap->m_currentPosY__pixel;
    uint32_t ymax__pixel = ymin__pixel;

    int32_t mapSize__pixel = ptMap->m_opti_globalMapSquareSize__pixel;

    double obstaclesHalfWidth__pixel = (double)(ptMap->OBSTACLES_HALF_WIDTH__PIXEL) / conv_mm_2_pixel;

    int32_t x1 = C_Tools_Maths::Opti_floor(currentX__pixel);
    int32_t y1 = C_Tools_Maths::Opti_floor(currentY__pixel);

    int32_t i = m_opti_nbOfMeasuresTakenIntoAccount_minus1;
    double* ptX = m_tabOfLidarMeasuresInCartesianRef_X__mm + i;
    double* ptY = m_tabOfLidarMeasuresInCartesianRef_Y__mm + i;

    double *opti_var1 = m_opti_UpdateMap_var1 + i;
    double *opti_var2 = m_opti_UpdateMap_var2 + i;
    double *opti_var3 = m_opti_UpdateMap_var3 + i;

    while (i >= 0)
    {
        *opti_var1 = m_opti_currentPosAngle__cos * (*ptX) - m_opti_currentPosAngle__sin * (*ptY);
        *opti_var2 = m_opti_currentPosAngle__sin * (*ptX) + m_opti_currentPosAngle__cos * (*ptY);
        *opti_var3 = 1.0 / C_Tools_Maths::sqrt1((*opti_var1) * (*opti_var1) + (*opti_var2) * (*opti_var2));

        x2p = conv_mm_2_pixel * (*opti_var1);
        y2p = conv_mm_2_pixel * (*opti_var2);

        xp = C_Tools_Maths::Opti_floor(currentX__pixel + x2p);
        yp = C_Tools_Maths::Opti_floor(currentY__pixel + y2p);

        x2p *= (add = 1.0 + (obstaclesHalfWidth__pixel * (*opti_var3)));
        y2p *= add;

        x2 = C_Tools_Maths::Opti_floor(currentX__pixel + x2p);
        y2 = C_Tools_Maths::Opti_floor(currentY__pixel + y2p);

        UpdateMapWithASingleMeasuredPoint(ptMap, x1, y1, x2, y2, xp, yp);

        i--; ptX--; ptY--; opti_var1--; opti_var2--; opti_var3--;

        // Store the modification zone
        if((x2 > 0) && (x2 < mapSize__pixel))
        {
            if((uint32_t)x2 > xmax__pixel)
            {
                xmax__pixel = x2;
            }
            if((uint32_t)x2 < xmin__pixel)
            {
                xmin__pixel = x2;
            }
        }

        if((y2 > 0) && (y2 < mapSize__pixel))
        {
            if((uint32_t)y2 > ymax__pixel)
            {
                ymax__pixel = y2;
            }
            if((uint32_t)y2 < ymin__pixel)
            {
                ymin__pixel = y2;
            }
        }
    }

    ptMap->m_opti_globalMapUpdateZoneXmin__pixel = xmin__pixel;
    ptMap->m_opti_globalMapUpdateZoneXmax__pixel = xmax__pixel;
    ptMap->m_opti_globalMapUpdateZoneYmin__pixel = ymin__pixel;
    ptMap->m_opti_globalMapUpdateZoneYmax__pixel = ymax__pixel;

}


void C_CoreSlamRealAngle_8bppMap::UpdateMap_Opti(struct_Map * ptMap)
{
    double x2p, y2p;
    int32_t x2, y2, xp, yp;
    double add;

    double conv_mm_2_pixel = ptMap->CONV_MM_2_PIXEL;

    double currentX__pixel = ptMap->m_currentPosX__pixel + 0.5;
    double currentY__pixel = ptMap->m_currentPosY__pixel + 0.5;

    uint32_t xmin__pixel = ptMap->m_currentPosX__pixel;
    uint32_t xmax__pixel = xmin__pixel;
    uint32_t ymin__pixel = ptMap->m_currentPosY__pixel;
    uint32_t ymax__pixel = ymin__pixel;

    int32_t mapSize__pixel = ptMap->m_opti_globalMapSquareSize__pixel;

    double obstaclesHalfWidth__pixel = (double)(ptMap->OBSTACLES_HALF_WIDTH__PIXEL) / conv_mm_2_pixel;

    int32_t x1 = C_Tools_Maths::Opti_floor(currentX__pixel);
    int32_t y1 = C_Tools_Maths::Opti_floor(currentY__pixel);

    int32_t i = m_opti_nbOfMeasuresTakenIntoAccount_minus1;
    double* ptX = m_tabOfLidarMeasuresInCartesianRef_X__mm + i;
    double* ptY = m_tabOfLidarMeasuresInCartesianRef_Y__mm + i;

    double *opti_var1 = m_opti_UpdateMap_var1 + i;
    double *opti_var2 = m_opti_UpdateMap_var2 + i;
    double *opti_var3 = m_opti_UpdateMap_var3 + i;

    while (i >= 0)
    {
        x2p = conv_mm_2_pixel * (*opti_var1);
        y2p = conv_mm_2_pixel * (*opti_var2);

        xp = C_Tools_Maths::Opti_floor(currentX__pixel + x2p);
        yp = C_Tools_Maths::Opti_floor(currentY__pixel + y2p);

        x2p *= (add = 1.0 + (obstaclesHalfWidth__pixel * (*opti_var3)));
        y2p *= add;

        x2 = C_Tools_Maths::Opti_floor(currentX__pixel + x2p);
        y2 = C_Tools_Maths::Opti_floor(currentY__pixel + y2p);

        UpdateMapWithASingleMeasuredPointForceBlack(ptMap, x1, y1, x2, y2, xp, yp);

        i--; ptX--; ptY--; opti_var1--; opti_var2--; opti_var3--;

        // Store the modification zone
        if((x2 > 0) && (x2 < mapSize__pixel))
        {
            if((uint32_t)x2 > xmax__pixel)
            {
                xmax__pixel = x2;
            }
            if((uint32_t)x2 < xmin__pixel)
            {
                xmin__pixel = x2;
            }
        }

        if((y2 > 0) && (y2 < mapSize__pixel))
        {
            if((uint32_t)y2 > ymax__pixel)
            {
                ymax__pixel = y2;
            }
            if((uint32_t)y2 < ymin__pixel)
            {
                ymin__pixel = y2;
            }
        }
    }

    ptMap->m_opti_globalMapUpdateZoneXmin__pixel = xmin__pixel;
    ptMap->m_opti_globalMapUpdateZoneXmax__pixel = xmax__pixel;
    ptMap->m_opti_globalMapUpdateZoneYmin__pixel = ymin__pixel;
    ptMap->m_opti_globalMapUpdateZoneYmax__pixel = ymax__pixel;

}


void C_CoreSlamRealAngle_8bppMap::UpdateModifiedMap(struct_Map * ptMap)
{
    int32_t mapSize__pixel = ptMap->m_opti_globalMapSquareSize__pixel;
    int32_t ymin = ptMap->m_opti_globalMapUpdateZoneYmin__pixel;
    int32_t ymax = ptMap->m_opti_globalMapUpdateZoneYmax__pixel;

    int offsetY = ymin * mapSize__pixel + ptMap->m_opti_globalMapUpdateZoneXmin__pixel;
    uint8_t * ptMapSrcRawData = (ptMap->m_ptRawPixelMatrix_8bpp) + offsetY;
    uint8_t * ptMapDstRawData = (ptMap->m_ptModifiedPixelMatrix_8bpp) + offsetY;

    uint32_t nbCol = (ptMap->m_opti_globalMapUpdateZoneXmax__pixel) - (ptMap->m_opti_globalMapUpdateZoneXmin__pixel);

    // First pass, re copy map data
    for(int32_t y = ymin; y < ymax; y++)
    {
        memcpy(ptMapDstRawData, ptMapSrcRawData, nbCol);
        ptMapSrcRawData += mapSize__pixel;
        ptMapDstRawData += mapSize__pixel;
    }
}


void C_CoreSlamRealAngle_8bppMap::AddMarginToModifiedMap(struct_Map * ptMap)
{
    int32_t ymin = ptMap->m_opti_globalMapUpdateZoneYmin__pixel;
    int32_t ymax = ptMap->m_opti_globalMapUpdateZoneYmax__pixel;
    int32_t xmin = ptMap->m_opti_globalMapUpdateZoneXmin__pixel;
    int32_t xmax = ptMap->m_opti_globalMapUpdateZoneXmax__pixel;
    int32_t mapSize__pixel = ptMap->m_opti_globalMapSquareSize__pixel;

    uint8_t * ptMapRawDataOrigine = (ptMap->m_ptRawPixelMatrix_8bpp) + ymin * mapSize__pixel + xmin;

    // First pass, re copy map data
    for(int32_t y = ymin; y < ymax; y++)
    {
        uint8_t * ptMapRawData = ptMapRawDataOrigine;

        for(int32_t x = xmin; x < xmax; x++)
        {
            if(*ptMapRawData < NAV_MAP_OBSTACLE_MARGIN_1_PIXEL_VALUE) AddMarginToPoint(ptMap, x,  y);

            ptMapRawData++;
        }

        ptMapRawDataOrigine += mapSize__pixel;
    }
}


void C_CoreSlamRealAngle_8bppMap::UpdateMapWithASingleMeasuredPoint(struct_Map * ptMap, int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t xp, int32_t yp)
{
#ifdef WALL_HALF_SIZE_ON_MAP
    // Generating the half V profil
    int32_t x2c = xp;
    int32_t y2c = yp;
#else
    // Generating V profil for the detected obstacle
    int32_t x2c = x2;
    int32_t y2c = y2;
#endif

    int32_t dx, dy, dxc, dyc, error, errorv, derrorv, x;

    int32_t incv = 0;
    int32_t incptrx, incptry, pixval, horiz, diago;

#ifdef ENABLE_MAP_BOUNDARIES_CHECK
    if ((x1 < 0) || (x1 >= (ptMap->m_opti_globalMapSquareSize__pixel)) || (y1 < 0) || (y1 >= (ptMap->m_opti_globalMapSquareSize__pixel)))
    {
        return; // Robot is out of data
    }
#endif

    // Clipping
    if (x2c < 0)
    {
        if (x2c == x1)
        {
            return;
        }

        y2c += (x2c * (y1 - y2c)) / (x2c - x1);
        x2c = 0;
    }

#ifdef ENABLE_MAP_BOUNDARIES_CHECK
    else if (x2c >= (ptMap->m_opti_globalMapSquareSize__pixel))
    {
        if (x1 == x2c)
        {
            return;
        }

        y2c += (y2c - y1) * ((ptMap->m_opti_globalMapSideSize_minus1__pixel) - x2c) / (x2c - x1);
        x2c = (ptMap->m_opti_globalMapSideSize_minus1__pixel);
    }
#endif

    if (y2c < 0)
    {
        if (y1 == y2c)
        {
            return;
        }

        x2c += (y2c * (x2c - x1)) / (y1 - y2c);
        y2c = 0;
    }

#ifdef ENABLE_MAP_BOUNDARIES_CHECK
    else if (y2c >= (ptMap->m_opti_globalMapSquareSize__pixel))
    {
        if (y1 == y2c)
        {
            return;
        }

        x2c += (x1 - x2c) * ((ptMap->m_opti_globalMapSideSize_minus1__pixel) - y2c) / (y1 - y2c);
        y2c = (ptMap->m_opti_globalMapSideSize_minus1__pixel);
    }
#endif

    dxc = C_Tools_Maths::Opti_abs(x2c - x1);
    dyc = C_Tools_Maths::Opti_abs(y2c - y1);

    if (x2 > x1)
    {
        dx = x2 - x1;
        incptrx = 1;
    }
    else
    {
        dx = x1 - x2;
        incptrx = -1;
    }

    if (y2 > y1)
    {
        dy = y2 - y1;
        incptry = (ptMap->m_opti_globalMapSquareSize__pixel);
    }
    else
    {
        dy = y1 - y2;
        incptry = (ptMap->m_opti_minus_globalMapSideSize__pixel);
    }

    if (dx > dy)
    {
        derrorv = C_Tools_Maths::Opti_abs(xp - x2);
    }
    else
    {
        //Swap(ref dx, ref dy);
        int32_t temp = dx;
        dx = dy;
        dy = temp;

        //Swap(ref dxc, ref dyc);
        temp = dxc;
        dxc = dyc;
        dyc = temp;

        //Swap(ref incptrx, ref incptry);
        temp = incptrx;
        incptrx = incptry;
        incptry = temp;

        derrorv = C_Tools_Maths::Opti_abs(yp - y2);
    }

    // Protection
    if(derrorv == 0) return;

    horiz = dyc + dyc;
    error = horiz - dxc;
    diago = error - dxc;

    errorv = derrorv / 2;

    incv = -255 / derrorv;

    pixval = 255;

    int32_t dx_minus_derrorv = dx - derrorv;
    int32_t dx_minus_2_derrorv = dx_minus_derrorv - derrorv;

    uint8_t * ptD = (ptMap->m_ptRawPixelMatrix_8bpp) + y1 * (ptMap->m_opti_globalMapSquareSize__pixel) + x1;

    x = 0;
    while (x <= dxc)
    {
        if (x > dx_minus_2_derrorv)
        {
            if (x <= dx_minus_derrorv)
            {
                pixval += incv;
                if (errorv > derrorv)
                {
                    pixval--;
                    errorv -= derrorv;
                }
            }
            else
            {
                pixval -= incv;
                if (errorv < 0)
                {
                    pixval++;
                    errorv += derrorv;
                }
            }
        }

        // Integration into the data
        uint16_t newMapPixelValue = (((uint16_t)(*ptD) * 768) + ((uint16_t)((ptMap->m_opti_256MinusAlphaModel) * (*ptD) + (ptMap->RAY_TRACE_ALPHA_MODEL) * pixval))) / 1024;

        if(newMapPixelValue > 255) (*ptD) = 255;
        else (*ptD) = (uint8_t)newMapPixelValue;


        if (error > 0)
        {
            ptD += incptry;
            error += diago;
        }
        else
        {
            error += horiz;
        }

        x++; ptD += incptrx;
    }
}

void C_CoreSlamRealAngle_8bppMap::UpdateMapWithASingleMeasuredPointForceBlack(struct_Map * ptMap, int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t xp, int32_t yp)
{
#ifdef WALL_HALF_SIZE_ON_MAP
    // Generating the half V profil
    int32_t x2c = xp;
    int32_t y2c = yp;
#else
    // Generating V profil for the detected obstacle
    int32_t x2c = x2;
    int32_t y2c = y2;
#endif

    int32_t dx, dy, dxc, dyc, error, errorv, derrorv, x;

    int32_t incv = 0;
    int32_t incptrx, incptry, pixval, horiz, diago;

#ifdef ENABLE_MAP_BOUNDARIES_CHECK
    if ((x1 < 0) || (x1 >= (ptMap->m_opti_globalMapSquareSize__pixel)) || (y1 < 0) || (y1 >= (ptMap->m_opti_globalMapSquareSize__pixel)))
    {
        return; // Robot is out of data
    }
#endif

    // Clipping
    if (x2c < 0)
    {
        if (x2c == x1)
        {
            return;
        }

        y2c += (x2c * (y1 - y2c)) / (x2c - x1);
        x2c = 0;
    }

#ifdef ENABLE_MAP_BOUNDARIES_CHECK
    else if (x2c >= (ptMap->m_opti_globalMapSquareSize__pixel))
    {
        if (x1 == x2c)
        {
            return;
        }

        y2c += (y2c - y1) * ((ptMap->m_opti_globalMapSideSize_minus1__pixel) - x2c) / (x2c - x1);
        x2c = (ptMap->m_opti_globalMapSideSize_minus1__pixel);
    }
#endif

    if (y2c < 0)
    {
        if (y1 == y2c)
        {
            return;
        }

        x2c += (y2c * (x2c - x1)) / (y1 - y2c);
        y2c = 0;
    }

#ifdef ENABLE_MAP_BOUNDARIES_CHECK
    else if (y2c >= (ptMap->m_opti_globalMapSquareSize__pixel))
    {
        if (y1 == y2c)
        {
            return;
        }

        x2c += (x1 - x2c) * ((ptMap->m_opti_globalMapSideSize_minus1__pixel) - y2c) / (y1 - y2c);
        y2c = (ptMap->m_opti_globalMapSideSize_minus1__pixel);
    }
#endif

    dxc = C_Tools_Maths::Opti_abs(x2c - x1);
    dyc = C_Tools_Maths::Opti_abs(y2c - y1);

    if (x2 > x1)
    {
        dx = x2 - x1;
        incptrx = 1;
    }
    else
    {
        dx = x1 - x2;
        incptrx = -1;
    }

    if (y2 > y1)
    {
        dy = y2 - y1;
        incptry = (ptMap->m_opti_globalMapSquareSize__pixel);
    }
    else
    {
        dy = y1 - y2;
        incptry = (ptMap->m_opti_minus_globalMapSideSize__pixel);
    }

    if (dx > dy)
    {
        derrorv = C_Tools_Maths::Opti_abs(xp - x2);
    }
    else
    {
        //Swap(ref dx, ref dy);
        int32_t temp = dx;
        dx = dy;
        dy = temp;

        //Swap(ref dxc, ref dyc);
        temp = dxc;
        dxc = dyc;
        dyc = temp;

        //Swap(ref incptrx, ref incptry);
        temp = incptrx;
        incptrx = incptry;
        incptry = temp;

        derrorv = C_Tools_Maths::Opti_abs(yp - y2);
    }

    // Protection
    if(derrorv == 0) return;

    horiz = dyc + dyc;
    error = horiz - dxc;
    diago = error - dxc;

    errorv = derrorv / 2;

    incv = -255 / derrorv;

    pixval = 255;

    int32_t dx_minus_derrorv = dx - derrorv;
    int32_t dx_minus_2_derrorv = dx_minus_derrorv - derrorv;

    uint8_t * ptD = (ptMap->m_ptRawPixelMatrix_8bpp) + y1 * (ptMap->m_opti_globalMapSquareSize__pixel) + x1;

    x = 0;
    while (x <= dxc)
    {
        if (x > dx_minus_2_derrorv)
        {
            if (x <= dx_minus_derrorv)
            {
                pixval += incv;
                if (errorv > derrorv)
                {
                    pixval--;
                    errorv -= derrorv;
                }
            }
            else
            {
                pixval -= incv;
                if (errorv < 0)
                {
                    pixval++;
                    errorv += derrorv;
                }
            }
        }

        // Integration into the data

        uint16_t newMapPixelValue = (uint16_t)pixval;

        // If the new value means free space, we do an average with the value on map
        // Else if the new value means obstacle, we instant take the new value
        if(pixval > (*ptD))
        {
            newMapPixelValue = ((uint16_t)((ptMap->m_opti_256MinusAlphaModel) * (*ptD) + (ptMap->RAY_TRACE_ALPHA_MODEL) * pixval)) >> 8;
        }

        if(newMapPixelValue > 255) (*ptD) = 255;
        else (*ptD) = (uint8_t)newMapPixelValue;


        if (error > 0)
        {
            ptD += incptry;
            error += diago;
        }
        else
        {
            error += horiz;
        }

        x++; ptD += incptrx;
    }
}


void C_CoreSlamRealAngle_8bppMap::AddMarginToPoint(struct_Map * ptMap, int32_t xp, int32_t yp)
{
    int32_t mapSize__pixel = ptMap->m_opti_globalMapSquareSize__pixel;
    int32_t mapSize__pixel_x2 = mapSize__pixel * 2;
    int32_t mapSize__pixel_x3 = mapSize__pixel * 3;
    int32_t mapSize__pixel_x4 = mapSize__pixel * 4;
    int32_t mapSize__pixel_x5 = mapSize__pixel * 5;
    int32_t mapSize__pixel_x6 = mapSize__pixel * 6;

    uint8_t * ptOnCenter = (ptMap->m_ptModifiedPixelMatrix_8bpp) + yp * mapSize__pixel + xp;
    uint8_t * ptD1, * ptD2, * ptD3, * ptD4;

    // Of course the center is an obstacle
    *ptOnCenter = NAV_MAP_OBSTACLE_PIXEL_VALUE;

    // Draw the cross
    // **************
    ptD1 = ptD2 = ptD3 = ptD4 = ptOnCenter;
    for(int i = 0; i < 5; i++)
    {
        ptD1 += mapSize__pixel;
        ptD2 ++;
        ptD3 -= mapSize__pixel;
        ptD4 --;

        *ptD1 = *ptD2 = *ptD3 = *ptD4 = NAV_MAP_OBSTACLE_PIXEL_VALUE;
    }

    ptD1 += mapSize__pixel;
    ptD2 ++;
    ptD3 -= mapSize__pixel;
    ptD4 --;

    if(*ptD1 > NAV_MAP_OBSTACLE_MARGIN_1_PIXEL_VALUE) *ptD1 = NAV_MAP_OBSTACLE_MARGIN_1_PIXEL_VALUE;
    if(*ptD2 > NAV_MAP_OBSTACLE_MARGIN_1_PIXEL_VALUE) *ptD2 = NAV_MAP_OBSTACLE_MARGIN_1_PIXEL_VALUE;
    if(*ptD3 > NAV_MAP_OBSTACLE_MARGIN_1_PIXEL_VALUE) *ptD3 = NAV_MAP_OBSTACLE_MARGIN_1_PIXEL_VALUE;
    if(*ptD4 > NAV_MAP_OBSTACLE_MARGIN_1_PIXEL_VALUE) *ptD4 = NAV_MAP_OBSTACLE_MARGIN_1_PIXEL_VALUE;

    ptD1 += mapSize__pixel;
    ptD2 ++;
    ptD3 -= mapSize__pixel;
    ptD4 --;

    if(*ptD1 > NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE) *ptD1 = NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE;
    if(*ptD2 > NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE) *ptD2 = NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE;
    if(*ptD3 > NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE) *ptD3 = NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE;
    if(*ptD4 > NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE) *ptD4 = NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE;

    // Draw the Diag
    // **************
    ptD1 = ptD2 = ptD3 = ptD4 = ptOnCenter;
    for(int i = 0; i < 4; i++)
    {
        ptD1 += mapSize__pixel + 1;
        ptD2 += -mapSize__pixel + 1;
        ptD3 += -mapSize__pixel - 1;
        ptD4 += mapSize__pixel - 1;

        *ptD1 = *ptD2 = *ptD3 = *ptD4 = NAV_MAP_OBSTACLE_PIXEL_VALUE;
    }

    ptD1 += mapSize__pixel + 1;
    ptD2 += -mapSize__pixel + 1;
    ptD3 += -mapSize__pixel - 1;
    ptD4 += mapSize__pixel - 1;

    if(*ptD1 > NAV_MAP_OBSTACLE_MARGIN_1_PIXEL_VALUE) *ptD1 = NAV_MAP_OBSTACLE_MARGIN_1_PIXEL_VALUE;
    if(*ptD2 > NAV_MAP_OBSTACLE_MARGIN_1_PIXEL_VALUE) *ptD2 = NAV_MAP_OBSTACLE_MARGIN_1_PIXEL_VALUE;
    if(*ptD3 > NAV_MAP_OBSTACLE_MARGIN_1_PIXEL_VALUE) *ptD3 = NAV_MAP_OBSTACLE_MARGIN_1_PIXEL_VALUE;
    if(*ptD4 > NAV_MAP_OBSTACLE_MARGIN_1_PIXEL_VALUE) *ptD4 = NAV_MAP_OBSTACLE_MARGIN_1_PIXEL_VALUE;

    ptD1 += mapSize__pixel + 1;
    ptD2 += -mapSize__pixel + 1;
    ptD3 += -mapSize__pixel - 1;
    ptD4 += mapSize__pixel - 1;

    if(*ptD1 > NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE) *ptD1 = NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE;
    if(*ptD2 > NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE) *ptD2 = NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE;
    if(*ptD3 > NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE) *ptD3 = NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE;
    if(*ptD4 > NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE) *ptD4 = NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE;


    // Draw the Rest
    // **************
    uint8_t * ptD12, * ptD22, * ptD32, * ptD42;

    // Part 1
    //=======
    ptD1 = ptD12 = ptOnCenter + mapSize__pixel + 1;
    ptD2 = ptD22 = ptOnCenter - mapSize__pixel + 1;
    ptD3 = ptD32 = ptOnCenter - mapSize__pixel - 1;
    ptD4 = ptD42 = ptOnCenter + mapSize__pixel - 1;

    for(int i = 0; i < 4; i++)
    {
        ptD1 += mapSize__pixel;
        ptD12 ++;
        ptD2 ++;
        ptD22 -= mapSize__pixel;
        ptD3 -= mapSize__pixel;
        ptD32 --;
        ptD4 --;
        ptD42 += mapSize__pixel;

        *ptD1 = *ptD12 = *ptD2 = *ptD22 = *ptD3 = *ptD32 = *ptD4 = *ptD42 = NAV_MAP_OBSTACLE_PIXEL_VALUE;
    }

    ptD1 += mapSize__pixel;
    ptD12 ++;
    ptD2 ++;
    ptD22 -= mapSize__pixel;
    ptD3 -= mapSize__pixel;
    ptD32 --;
    ptD4 --;
    ptD42 += mapSize__pixel;

    if(*ptD1 > NAV_MAP_OBSTACLE_MARGIN_1_PIXEL_VALUE) *ptD1 = NAV_MAP_OBSTACLE_MARGIN_1_PIXEL_VALUE;
    if(*ptD12 > NAV_MAP_OBSTACLE_MARGIN_1_PIXEL_VALUE) *ptD12 = NAV_MAP_OBSTACLE_MARGIN_1_PIXEL_VALUE;
    if(*ptD2 > NAV_MAP_OBSTACLE_MARGIN_1_PIXEL_VALUE) *ptD2 = NAV_MAP_OBSTACLE_MARGIN_1_PIXEL_VALUE;
    if(*ptD22 > NAV_MAP_OBSTACLE_MARGIN_1_PIXEL_VALUE) *ptD22 = NAV_MAP_OBSTACLE_MARGIN_1_PIXEL_VALUE;
    if(*ptD3 > NAV_MAP_OBSTACLE_MARGIN_1_PIXEL_VALUE) *ptD3 = NAV_MAP_OBSTACLE_MARGIN_1_PIXEL_VALUE;
    if(*ptD32 > NAV_MAP_OBSTACLE_MARGIN_1_PIXEL_VALUE) *ptD32 = NAV_MAP_OBSTACLE_MARGIN_1_PIXEL_VALUE;
    if(*ptD4 > NAV_MAP_OBSTACLE_MARGIN_1_PIXEL_VALUE) *ptD4 = NAV_MAP_OBSTACLE_MARGIN_1_PIXEL_VALUE;
    if(*ptD42 > NAV_MAP_OBSTACLE_MARGIN_1_PIXEL_VALUE) *ptD42 = NAV_MAP_OBSTACLE_MARGIN_1_PIXEL_VALUE;

    ptD1 += mapSize__pixel;
    ptD12 ++;
    ptD2 ++;
    ptD22 -= mapSize__pixel;
    ptD3 -= mapSize__pixel;
    ptD32 --;
    ptD4 --;
    ptD42 += mapSize__pixel;

    if(*ptD1 > NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE) *ptD1 = NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE;
    if(*ptD12 > NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE) *ptD12 = NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE;
    if(*ptD2 > NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE) *ptD2 = NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE;
    if(*ptD22 > NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE) *ptD22 = NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE;
    if(*ptD3 > NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE) *ptD3 = NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE;
    if(*ptD32 > NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE) *ptD32 = NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE;
    if(*ptD4 > NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE) *ptD4 = NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE;
    if(*ptD42 > NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE) *ptD42 = NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE;

    // Part 2
    //=======
    ptD1 = ptD12 = ptOnCenter + mapSize__pixel_x2 + 2;
    ptD2 = ptD22 = ptOnCenter - mapSize__pixel_x2 + 2;
    ptD3 = ptD32 = ptOnCenter - mapSize__pixel_x2 - 2;
    ptD4 = ptD42 = ptOnCenter + mapSize__pixel_x2 - 2;

    for(int i = 0; i < 3; i++)
    {
        ptD1 += mapSize__pixel;
        ptD12 ++;
        ptD2 ++;
        ptD22 -= mapSize__pixel;
        ptD3 -= mapSize__pixel;
        ptD32 --;
        ptD4 --;
        ptD42 += mapSize__pixel;

        *ptD1 = *ptD12 = *ptD2 = *ptD22 = *ptD3 = *ptD32 = *ptD4 = *ptD42= NAV_MAP_OBSTACLE_PIXEL_VALUE;
    }

    ptD1 += mapSize__pixel;
    ptD12 ++;
    ptD2 ++;
    ptD22 -= mapSize__pixel;
    ptD3 -= mapSize__pixel;
    ptD32 --;
    ptD4 --;
    ptD42 += mapSize__pixel;

    if(*ptD1 > NAV_MAP_OBSTACLE_MARGIN_1_PIXEL_VALUE) *ptD1 = NAV_MAP_OBSTACLE_MARGIN_1_PIXEL_VALUE;
    if(*ptD12 > NAV_MAP_OBSTACLE_MARGIN_1_PIXEL_VALUE) *ptD12 = NAV_MAP_OBSTACLE_MARGIN_1_PIXEL_VALUE;
    if(*ptD2 > NAV_MAP_OBSTACLE_MARGIN_1_PIXEL_VALUE) *ptD2 = NAV_MAP_OBSTACLE_MARGIN_1_PIXEL_VALUE;
    if(*ptD22 > NAV_MAP_OBSTACLE_MARGIN_1_PIXEL_VALUE) *ptD22 = NAV_MAP_OBSTACLE_MARGIN_1_PIXEL_VALUE;
    if(*ptD3 > NAV_MAP_OBSTACLE_MARGIN_1_PIXEL_VALUE) *ptD3 = NAV_MAP_OBSTACLE_MARGIN_1_PIXEL_VALUE;
    if(*ptD32 > NAV_MAP_OBSTACLE_MARGIN_1_PIXEL_VALUE) *ptD32 = NAV_MAP_OBSTACLE_MARGIN_1_PIXEL_VALUE;
    if(*ptD4 > NAV_MAP_OBSTACLE_MARGIN_1_PIXEL_VALUE) *ptD4 = NAV_MAP_OBSTACLE_MARGIN_1_PIXEL_VALUE;
    if(*ptD42 > NAV_MAP_OBSTACLE_MARGIN_1_PIXEL_VALUE) *ptD42 = NAV_MAP_OBSTACLE_MARGIN_1_PIXEL_VALUE;

    ptD1 += mapSize__pixel;
    ptD12 ++;
    ptD2 ++;
    ptD22 -= mapSize__pixel;
    ptD3 -= mapSize__pixel;
    ptD32 --;
    ptD4 --;
    ptD42 += mapSize__pixel;

    if(*ptD1 > NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE) *ptD1 = NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE;
    if(*ptD12 > NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE) *ptD12 = NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE;
    if(*ptD2 > NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE) *ptD2 = NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE;
    if(*ptD22 > NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE) *ptD22 = NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE;
    if(*ptD3 > NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE) *ptD3 = NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE;
    if(*ptD32 > NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE) *ptD32 = NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE;
    if(*ptD4 > NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE) *ptD4 = NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE;
    if(*ptD42 > NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE) *ptD42 = NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE;


    // Part 3
    //=======
    ptD1 =  ptOnCenter + mapSize__pixel_x4 + 3;
    ptD12 = ptOnCenter + mapSize__pixel_x3 + 4;
    ptD2 = ptOnCenter - mapSize__pixel_x3 + 4;
    ptD22 = ptOnCenter - mapSize__pixel_x4 + 3;
    ptD3 = ptOnCenter - mapSize__pixel_x4 - 3;
    ptD32 = ptOnCenter - mapSize__pixel_x3 - 4;
    ptD4 = ptOnCenter + mapSize__pixel_x3 - 4;
    ptD42 = ptOnCenter + mapSize__pixel_x4 - 3;

    *ptD1 = *ptD12 = *ptD2 = *ptD22 = *ptD3 = *ptD32 = *ptD4 = *ptD42= NAV_MAP_OBSTACLE_PIXEL_VALUE;

    for(int i = 0; i < 2; i++)
    {
        ptD1 += mapSize__pixel;
        ptD12 ++;
        ptD2 ++;
        ptD22 -= mapSize__pixel;
        ptD3 -= mapSize__pixel;
        ptD32 --;
        ptD4 --;
        ptD42 += mapSize__pixel;

        if(*ptD1 > NAV_MAP_OBSTACLE_MARGIN_1_PIXEL_VALUE) *ptD1 = NAV_MAP_OBSTACLE_MARGIN_1_PIXEL_VALUE;
        if(*ptD12 > NAV_MAP_OBSTACLE_MARGIN_1_PIXEL_VALUE) *ptD12 = NAV_MAP_OBSTACLE_MARGIN_1_PIXEL_VALUE;
        if(*ptD2 > NAV_MAP_OBSTACLE_MARGIN_1_PIXEL_VALUE) *ptD2 = NAV_MAP_OBSTACLE_MARGIN_1_PIXEL_VALUE;
        if(*ptD22 > NAV_MAP_OBSTACLE_MARGIN_1_PIXEL_VALUE) *ptD22 = NAV_MAP_OBSTACLE_MARGIN_1_PIXEL_VALUE;
        if(*ptD3 > NAV_MAP_OBSTACLE_MARGIN_1_PIXEL_VALUE) *ptD3 = NAV_MAP_OBSTACLE_MARGIN_1_PIXEL_VALUE;
        if(*ptD32 > NAV_MAP_OBSTACLE_MARGIN_1_PIXEL_VALUE) *ptD32 = NAV_MAP_OBSTACLE_MARGIN_1_PIXEL_VALUE;
        if(*ptD4 > NAV_MAP_OBSTACLE_MARGIN_1_PIXEL_VALUE) *ptD4 = NAV_MAP_OBSTACLE_MARGIN_1_PIXEL_VALUE;
        if(*ptD42 > NAV_MAP_OBSTACLE_MARGIN_1_PIXEL_VALUE) *ptD42 = NAV_MAP_OBSTACLE_MARGIN_1_PIXEL_VALUE;
    }

    ptD1 += mapSize__pixel;
    ptD12 ++;
    ptD2 ++;
    ptD22 -= mapSize__pixel;
    ptD3 -= mapSize__pixel;
    ptD32 --;
    ptD4 --;
    ptD42 += mapSize__pixel;

    if(*ptD1 > NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE) *ptD1 = NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE;
    if(*ptD12 > NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE) *ptD12 = NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE;
    if(*ptD2 > NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE) *ptD2 = NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE;
    if(*ptD22 > NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE) *ptD22 = NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE;
    if(*ptD3 > NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE) *ptD3 = NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE;
    if(*ptD32 > NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE) *ptD32 = NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE;
    if(*ptD4 > NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE) *ptD4 = NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE;
    if(*ptD42 > NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE) *ptD42 = NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE;

    // Part 4
    //=======
    ptD1 = ptOnCenter + mapSize__pixel_x5 + 4;
    ptD12 = ptOnCenter + mapSize__pixel_x4 + 5;
    ptD2 = ptOnCenter - mapSize__pixel_x4 + 5;
    ptD22 = ptOnCenter - mapSize__pixel_x5 + 4;
    ptD3 = ptOnCenter - mapSize__pixel_x5 - 4;
    ptD32 = ptOnCenter - mapSize__pixel_x4 - 5;
    ptD4 = ptOnCenter + mapSize__pixel_x4 - 5;
    ptD42 = ptOnCenter + mapSize__pixel_x5 - 4;

    if(*ptD1 > NAV_MAP_OBSTACLE_MARGIN_1_PIXEL_VALUE) *ptD1 = NAV_MAP_OBSTACLE_MARGIN_1_PIXEL_VALUE;
    if(*ptD12 > NAV_MAP_OBSTACLE_MARGIN_1_PIXEL_VALUE) *ptD12 = NAV_MAP_OBSTACLE_MARGIN_1_PIXEL_VALUE;
    if(*ptD2 > NAV_MAP_OBSTACLE_MARGIN_1_PIXEL_VALUE) *ptD2 = NAV_MAP_OBSTACLE_MARGIN_1_PIXEL_VALUE;
    if(*ptD22 > NAV_MAP_OBSTACLE_MARGIN_1_PIXEL_VALUE) *ptD22 = NAV_MAP_OBSTACLE_MARGIN_1_PIXEL_VALUE;
    if(*ptD3 > NAV_MAP_OBSTACLE_MARGIN_1_PIXEL_VALUE) *ptD3 = NAV_MAP_OBSTACLE_MARGIN_1_PIXEL_VALUE;
    if(*ptD32 > NAV_MAP_OBSTACLE_MARGIN_1_PIXEL_VALUE) *ptD32 = NAV_MAP_OBSTACLE_MARGIN_1_PIXEL_VALUE;
    if(*ptD4 > NAV_MAP_OBSTACLE_MARGIN_1_PIXEL_VALUE) *ptD4 = NAV_MAP_OBSTACLE_MARGIN_1_PIXEL_VALUE;
    if(*ptD42 > NAV_MAP_OBSTACLE_MARGIN_1_PIXEL_VALUE) *ptD42 = NAV_MAP_OBSTACLE_MARGIN_1_PIXEL_VALUE;

    for(int i = 0; i < 2; i++)
    {
        ptD1 += mapSize__pixel;
        ptD12 ++;
        ptD2 ++;
        ptD22 -= mapSize__pixel;
        ptD3 -= mapSize__pixel;
        ptD32 --;
        ptD4 --;
        ptD42 += mapSize__pixel;

        if(*ptD1 > NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE) *ptD1 = NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE;
        if(*ptD12 > NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE) *ptD12 = NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE;
        if(*ptD2 > NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE) *ptD2 = NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE;
        if(*ptD22 > NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE) *ptD22 = NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE;
        if(*ptD3 > NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE) *ptD3 = NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE;
        if(*ptD32 > NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE) *ptD32 = NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE;
        if(*ptD4 > NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE) *ptD4 = NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE;
        if(*ptD42 > NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE) *ptD42 = NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE;
    }

    // Part 5
    //=======
    ptD1 = ptOnCenter + mapSize__pixel_x6 + 5;
    ptD12 = ptOnCenter + mapSize__pixel_x5 + 6;
    ptD2 = ptOnCenter - mapSize__pixel_x5 + 6;
    ptD22 = ptOnCenter - mapSize__pixel_x6 + 5;
    ptD3 = ptOnCenter - mapSize__pixel_x6 - 5;
    ptD32 = ptOnCenter - mapSize__pixel_x5 - 6;
    ptD4 = ptOnCenter + mapSize__pixel_x5 - 6;
    ptD42 = ptOnCenter + mapSize__pixel_x6 - 5;

    if(*ptD1 > NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE) *ptD1 = NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE;
    if(*ptD12 > NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE) *ptD12 = NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE;
    if(*ptD2 > NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE) *ptD2 = NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE;
    if(*ptD22 > NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE) *ptD22 = NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE;
    if(*ptD3 > NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE) *ptD3 = NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE;
    if(*ptD32 > NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE) *ptD32 = NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE;
    if(*ptD4 > NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE) *ptD4 = NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE;
    if(*ptD42 > NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE) *ptD42 = NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE;
}
