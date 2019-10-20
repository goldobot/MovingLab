#include "C_CoreSlamPF_Main.h"

C_CoreSlamPF_Main::C_CoreSlamPF_Main(uint32_t globalMapSquareSize__mm, uint32_t lidarMinReliableMeasuredDist__mm, uint32_t lidarMaxReliableMeasuredDist__mm, uint32_t lidarMinDistToAddVirtualMeasures__mm, uint32_t maxNbOfVirtualMeasuresAtMaxDist)
{
    // Init all estimators
    for(int index=0; index<MAX_NB_OF_MANAGED_MAP_ESTIMATOR; index++)
    {
        // Init the estimator
        m_tabMapEstimators[index].Init(globalMapSquareSize__mm);
        m_tabMapEstimators[index].ConnectSensorDataFlow(m_tabOfLidarMeasuresInCartesianRef_X__mm, m_tabOfLidarMeasuresInCartesianRef_Y__mm, &m_opti_nbOfMeasuresTakenIntoAccount_minus1);

        // Only mark 1 to be used at the begining
        if(index == 0) m_tabMapEstimatorsFreeSlotMarker[index] = false;
        else m_tabMapEstimatorsFreeSlotMarker[index] = true;
    }

    // The first slot is taken
    m_nbOfFreeSlots = MAX_NB_OF_MANAGED_MAP_ESTIMATOR - 1;
    m_bestEstimatorIndex = 0;

    // Precompute data for Angle err model
    for (int32_t i = 0; i < NB_OF_VALUES_OF_DANGLE_ERR_MODEL; i++)
    {
        m_tabOfDAngleErrModel__rad[i] = m_tabOfDAngleErrModel__rad[i] * MATHS_CONV_DEG_2_RAD;
        m_opti_cached_tabOfCosOfAngleErrModel[i] =  cos(m_tabOfDAngleErrModel__rad[i]);
        m_opti_cached_tabOfSinOfAngleErrModel[i] = sin(m_tabOfDAngleErrModel__rad[i]);
    }

    // Store sensor model
    m_lidarMinReliableMeasuredDist__mm = lidarMinReliableMeasuredDist__mm;
    m_lidarMinReliableMeasuredDist__pixel = m_lidarMinReliableMeasuredDist__mm * m_tabMapEstimators[0].GET_GlobalMap_CONV_MM_2_PIXEL();

    m_lidarMaxReliableMeasuredDist__mm = lidarMaxReliableMeasuredDist__mm;
    m_lidarMaxReliableMeasuredDist__pixel = m_lidarMaxReliableMeasuredDist__mm * m_tabMapEstimators[0].GET_GlobalMap_CONV_MM_2_PIXEL();

    m_lidarMinDistToAddVirtualMeasures__mm = lidarMinDistToAddVirtualMeasures__mm;
    m_lidarMinDistToAddVirtualMeasures__pixel = m_lidarMinDistToAddVirtualMeasures__mm * m_tabMapEstimators[0].GET_GlobalMap_CONV_MM_2_PIXEL();
    m_maxNbOfVirtualMeasuresAtMaxDist = maxNbOfVirtualMeasuresAtMaxDist;
    m_opti_maxNbOfVirtualMeasuresAtMaxDist_minus1 = m_maxNbOfVirtualMeasuresAtMaxDist - 1;

    m_lidarDistFromMinDistToAddVirtualMeasuresToMaxReliableMeasuredDist__mm = m_lidarMaxReliableMeasuredDist__mm - m_lidarMinDistToAddVirtualMeasures__mm;

    Reset();
}

C_CoreSlamPF_Main::~C_CoreSlamPF_Main()
{
}

void C_CoreSlamPF_Main::Reset()
{
    // Reset statistics
    m_nbMapUpdatePassSinceLastRead = 0;

    for(int index=0; index<MAX_NB_OF_MANAGED_MAP_ESTIMATOR; index++)
    {
        m_tabMapEstimators[index].Reset();

        // Only mark 1 to be used at the begining
        if(index == 0) m_tabMapEstimatorsFreeSlotMarker[index] = false;
        else m_tabMapEstimatorsFreeSlotMarker[index] = true;
    }

    // The first slot is taken
    m_nbOfFreeSlots = MAX_NB_OF_MANAGED_MAP_ESTIMATOR - 1;
    m_bestEstimatorIndex = 0;
}

void C_CoreSlamPF_Main::IntegrateNewSensorData(uint32_t * tabOfDistMeasures__mm, double * tabOfAngleMeasures__cos, double * tabOfAngleMeasures__sin, uint32_t nbOfMeasures, int paramIndex)
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
        //TODO : Delete all the aberant estimator


        // Estimate new robot position by all map estimator
        if(EstimateNewPosition(m_paramsForUsingLidar[paramIndex].estimationType))
        {
            // Update the map with new sensor data
            // For each estimator, do update the map with new sensor data
            for(int estimatorIndex=0; estimatorIndex < MAX_NB_OF_MANAGED_MAP_ESTIMATOR; estimatorIndex++)
            {
                m_tabMapEstimators[estimatorIndex].UpdateMap();
            }

            // Statistic purpose : Nb of map computation pass since last time the value is requested
            m_nbMapUpdatePassSinceLastRead++;
        }
    }

    // Protect from launching severals times
    m_isBusy = false;
}

/*
bool C_CoreSlamPF_Main::EstimateNewPosition(enum_EstimationType estimationType)
{
    // No need to estimate position
    if(estimationType == NONE) return true;

    // Read the current robot position
    C_CoreSlamPF_RealAngle_8bppMap::struct_EstimatedRobotPosition estimatedRobotPos;
    m_mapEstimator->GetRobotPosition(&estimatedRobotPos);


    // Current position on the global map
    double currentPosX__mm = estimatedRobotPos.currentPosX__mm;
    double currentPosY__mm = estimatedRobotPos.currentPosY__mm;
    double currentPosAngle__rad = estimatedRobotPos.currentPosAngle__rad;

    // Optimization
    double opti_currentPosAngle__cos = estimatedRobotPos.opti_currentPosAngle__cos;
    double opti_currentPosAngle__sin = estimatedRobotPos.opti_currentPosAngle__sin;


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

    double appliedDxErrValue__mm = 0.0;
    double appliedDyErrValue__mm = 0.0;
    double appliedDangleErrValue__rad = 0.0;


    int32_t nbOfValuesOfDxErrModel = NB_OF_VALUES_OF_DX_ERR_MODEL;
    int32_t nbOfValuesOfDyErrModel = NB_OF_VALUES_OF_DY_ERR_MODEL;

    // Only need to estimate Theta
    if(estimationType == THETA_ONLY)
    {
        nbOfValuesOfDxErrModel = nbOfValuesOfDyErrModel = 1;
    }

    // Search of best position by looping on Delta Angle, X, Y
    // Using the Move Error Model
    //**********************************************************************

    // Pointer to the angle error model
    double * ptAngleErrModel__rad = (double *) m_tabOfDAngleErrModel__rad;

#ifdef ENABLE_ESTIMATION
    for (int32_t i = 0; i < NB_OF_VALUES_OF_DANGLE_ERR_MODEL; i++)
#else
    for (int32_t i = 0; i < 1; i++)
#endif
    {
        // Optimize : Avoid cos, sin computation
        bool angleErrModelValueChanged = true;

        // Compute once the cos, sin
        angleErrModel__cos = m_opti_cached_tabOfCosOfAngleErrModel[i];
        angleErrModel__sin = m_opti_cached_tabOfSinOfAngleErrModel[i];

        // Pointer to the pos X error model
        double * ptDxErrModel__mm = (double*)m_tabOfDxErrModel__mm;

#ifdef ENABLE_ESTIMATION
        for (int32_t j = 0; j < nbOfValuesOfDxErrModel; j++)
#else
        for (int32_t j = 0; j < 1; j++)
#endif
        {
            // Compute an possible posX (to be checked)
            checkingPosX__mm = currentPosX__mm + (*ptDxErrModel__mm);

            // Pointer to the pos Y error model
            double* ptDyErrModel__mm = (double*)m_tabOfDyErrModel__mm;

#ifdef ENABLE_ESTIMATION
            for (int32_t k = 0; k < nbOfValuesOfDyErrModel; k++)
#else
            for (int32_t k = 0; k < 1; k++)
#endif
            {
                // Compute an possible posY (to be checked)
                checkingPosY__mm = currentPosY__mm + (*ptDyErrModel__mm);

                if (angleErrModelValueChanged)
                {
                    matchingQualityValue = m_mapEstimator->ComputeMatching(checkingPosX__mm, checkingPosY__mm, opti_currentPosAngle__cos * angleErrModel__cos - opti_currentPosAngle__sin * angleErrModel__sin, opti_currentPosAngle__sin * angleErrModel__cos + opti_currentPosAngle__cos * angleErrModel__sin);
                    angleErrModelValueChanged = false;
                }
                else
                {
                    matchingQualityValue = m_mapEstimator->Opti_ComputeMatching(checkingPosX__mm, checkingPosY__mm);
                }

                // Best position found
                if (matchingQualityValue < currentBestMatchingQualityValue)
                {
                    // Store the new best position
                    currentBestMatchingQualityValue = matchingQualityValue;

                    currentBestPosX__mm = checkingPosX__mm;
                    currentBestPosY__mm = checkingPosY__mm;
                    currentBestPosAngle__rad = currentPosAngle__rad + (*ptAngleErrModel__rad);

                    // Debug purpose only
                    appliedDxErrValue__mm = (*ptDxErrModel__mm);
                    appliedDyErrValue__mm = (*ptDyErrModel__mm);
                    appliedDangleErrValue__rad = (*ptAngleErrModel__rad);
                }

                ptDyErrModel__mm++;
            }

            ptDxErrModel__mm++;
        }

        ptAngleErrModel__rad++;
    }

    // Has at least one estimation
    if(currentBestMatchingQualityValue < UINT64_MAX)
    {
        // Angle normalize [-Pi; Pi]
        while (currentBestPosAngle__rad > MATHS_PI) currentBestPosAngle__rad -= MATHS_2PI;
        while (currentBestPosAngle__rad < MATHS_MINUS_PI) currentBestPosAngle__rad += MATHS_2PI;

        // Store the best of all position found
        m_mapEstimator->SetRobotPosition(currentBestPosX__mm, currentBestPosY__mm, currentBestPosAngle__rad, appliedDxErrValue__mm, appliedDyErrValue__mm, appliedDangleErrValue__rad, currentBestMatchingQualityValue);

        return true;
    }

    return false;
}
*/

bool C_CoreSlamPF_Main::EstimateNewPosition(enum_EstimationType estimationType)
{
    // No need to estimate position
    if(estimationType == NO_CALC) return true;

    // Mark the estimator which are already refreshed
    bool estimatorsAlreadyRefreshed[MAX_NB_OF_MANAGED_MAP_ESTIMATOR];
    for(int estimatorIndex=0; estimatorIndex < MAX_NB_OF_MANAGED_MAP_ESTIMATOR; estimatorIndex++) estimatorsAlreadyRefreshed[estimatorIndex] = false;

    // Index of the best found estimator
    int bestEstimatorIndex = 0;

    // For each estimator, do the estimation
    for(int estimatorIndex=0; estimatorIndex < MAX_NB_OF_MANAGED_MAP_ESTIMATOR; estimatorIndex++)
    {
        // The slot has an estimator
        if((m_tabMapEstimatorsFreeSlotMarker[estimatorIndex] != true) && (estimatorsAlreadyRefreshed[estimatorIndex] != true))
        {
            // Reset the ordering list from the last estimation
            m_listOfBestMatchPos.Clear();

            C_CoreSlamPF_RealAngle_8bppMap * mapEstimator = &m_tabMapEstimators[estimatorIndex];

            // Read the current robot position
            struct_EstimatedRobotPosition estimatedRobotPos;
            mapEstimator->GetRobotPosition(&estimatedRobotPos);

            // Current position on the global map
            double currentPosX__mm = estimatedRobotPos.currentPosX__mm;
            double currentPosY__mm = estimatedRobotPos.currentPosY__mm;
            double currentPosAngle__rad = estimatedRobotPos.currentPosAngle__rad;

            // Optimization
            double opti_currentPosAngle__cos = estimatedRobotPos.opti_currentPosAngle__cos;
            double opti_currentPosAngle__sin = estimatedRobotPos.opti_currentPosAngle__sin;

            // Position to check
            double checkingPosX__mm = 0.0;
            double checkingPosY__mm = 0.0;

            double angleErrModel__cos;
            double angleErrModel__sin;

            // Position matching quality
            // The lower it is, the best it is
            uint64_t matchingQualityValue = 0;

            // Best matching quality ever
            uint64_t bestMatchingQualityValue = UINT64_MAX;

            int32_t nbOfValuesOfDxErrModel = NB_OF_VALUES_OF_DX_ERR_MODEL;
            int32_t nbOfValuesOfDyErrModel = NB_OF_VALUES_OF_DY_ERR_MODEL;

            // Only need to estimate Theta
            if(estimationType == THETA_ONLY)
            {
                nbOfValuesOfDxErrModel = nbOfValuesOfDyErrModel = 1;
            }

            // Search of best position by looping on Delta Angle, X, Y
            // Using the Move Error Model
            //**********************************************************************

            // Pointer to the angle error model
            double * ptAngleErrModel__rad = (double *) m_tabOfDAngleErrModel__rad;

#ifdef ENABLE_ESTIMATION
            for (int32_t i = 0; i < NB_OF_VALUES_OF_DANGLE_ERR_MODEL; i++)
#else
            for (int32_t i = 0; i < 1; i++)
#endif
            {
                // Optimize : Avoid cos, sin computation
                bool angleErrModelValueChanged = true;

                // Compute once the cos, sin
                angleErrModel__cos = m_opti_cached_tabOfCosOfAngleErrModel[i];
                angleErrModel__sin = m_opti_cached_tabOfSinOfAngleErrModel[i];

                // Pointer to the pos X error model
                double * ptDxErrModel__mm = (double*)m_tabOfDxErrModel__mm;

#ifdef ENABLE_ESTIMATION
                for (int32_t j = 0; j < nbOfValuesOfDxErrModel; j++)
#else
                for (int32_t j = 0; j < 1; j++)
#endif
                {
                    // Compute an possible posX (to be checked)
                    checkingPosX__mm = currentPosX__mm + (*ptDxErrModel__mm);

                    // Pointer to the pos Y error model
                    double* ptDyErrModel__mm = (double*)m_tabOfDyErrModel__mm;

#ifdef ENABLE_ESTIMATION
                    for (int32_t k = 0; k < nbOfValuesOfDyErrModel; k++)
#else
                    for (int32_t k = 0; k < 1; k++)
#endif
                    {
                        // Compute an possible posY (to be checked)
                        checkingPosY__mm = currentPosY__mm + (*ptDyErrModel__mm);

                        if (angleErrModelValueChanged)
                        {
                            matchingQualityValue = mapEstimator->ComputeMatching(checkingPosX__mm, checkingPosY__mm, opti_currentPosAngle__cos * angleErrModel__cos - opti_currentPosAngle__sin * angleErrModel__sin, opti_currentPosAngle__sin * angleErrModel__cos + opti_currentPosAngle__cos * angleErrModel__sin);
                            angleErrModelValueChanged = false;
                        }
                        else
                        {
                            matchingQualityValue = mapEstimator->Opti_ComputeMatching(checkingPosX__mm, checkingPosY__mm);
                        }

                        //Add the match pos to the data base
                        if(matchingQualityValue < UINT64_MAX)
                        {
                            struct_MatchPos newMatchPos = {estimatorIndex, matchingQualityValue, checkingPosX__mm, checkingPosY__mm, currentPosAngle__rad + (*ptAngleErrModel__rad), (*ptDxErrModel__mm), (*ptDyErrModel__mm), (*ptAngleErrModel__rad), nullptr};
                            m_listOfBestMatchPos.Add(&newMatchPos);
                        }

                        ptDyErrModel__mm++;
                    }

                    ptDxErrModel__mm++;
                }

                ptAngleErrModel__rad++;
            }

            // Now we have the list of all the estimated position
            // Order the match pos list from best to worst
            m_listOfBestMatchPos.OrderLowToHigh();

            // Get the head of the list (the best)
            struct_MatchPos * bestMatchPos = m_listOfBestMatchPos.GetNext();

            // Angle normalize [-Pi; Pi]
            double currentBestPosAngle__rad = bestMatchPos->posAngle__rad;
            while (currentBestPosAngle__rad > MATHS_PI) currentBestPosAngle__rad -= MATHS_2PI;
            while (currentBestPosAngle__rad < MATHS_MINUS_PI) currentBestPosAngle__rad += MATHS_2PI;

            // Update the estimator
            m_tabMapEstimators[estimatorIndex].SetRobotPosition(bestMatchPos->posX__mm, bestMatchPos->posY__mm, currentBestPosAngle__rad, bestMatchPos->posErrX__mm, bestMatchPos->posErrY__mm, bestMatchPos->posErrAngle__rad, bestMatchPos->matchingQuality);
            estimatorsAlreadyRefreshed[estimatorIndex] = true;

            // Store the best estimator index
            if( bestMatchPos->matchingQuality < bestMatchingQualityValue)
            {
                bestMatchingQualityValue = bestMatchPos->matchingQuality;
                bestEstimatorIndex = estimatorIndex;
            }

            // Now if there is room to duplicate the current estimator
            while(m_nbOfFreeSlots > 0)
            {
                // Search the free slot
                int freeSlotIndex = -1;
                for(int index=0; (index < MAX_NB_OF_MANAGED_MAP_ESTIMATOR) && (freeSlotIndex < 0); index++)
                {
                    if(m_tabMapEstimatorsFreeSlotMarker[index]) freeSlotIndex = index;
                }

                // Duplicate the best to the free slot
                // Copy the estimator data
                m_tabMapEstimators[freeSlotIndex].Copy(&m_tabMapEstimators[estimatorIndex]);

                // Get the next best estimated position
                bestMatchPos = m_listOfBestMatchPos.GetNext(bestMatchPos);

                // Angle normalize [-Pi; Pi]
                double currentBestPosAngle__rad = bestMatchPos->posAngle__rad;
                while (currentBestPosAngle__rad > MATHS_PI) currentBestPosAngle__rad -= MATHS_2PI;
                while (currentBestPosAngle__rad < MATHS_MINUS_PI) currentBestPosAngle__rad += MATHS_2PI;

                // Update the estimator
                m_tabMapEstimators[freeSlotIndex].SetRobotPosition(bestMatchPos->posX__mm, bestMatchPos->posY__mm, currentBestPosAngle__rad, bestMatchPos->posErrX__mm, bestMatchPos->posErrY__mm, bestMatchPos->posErrAngle__rad, bestMatchPos->matchingQuality);
                estimatorsAlreadyRefreshed[freeSlotIndex] = true;

                // Mark the taken slot
                m_tabMapEstimatorsFreeSlotMarker[freeSlotIndex] = false;
                m_nbOfFreeSlots--;
            }
        }
    }

    // Store the best index to be used
    m_bestEstimatorIndex = bestEstimatorIndex;

    return true;
}

bool C_CoreSlamPF_Main::ProcessLidarData(int offsetX__mm, int offsetY__mm)
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

    // Last position
    double lastMeasuredPosX = 0.0;
    double lastMeasuredPosY = 0.0;

    // Used to compute distance from last measure to current measure
    double dx = 0.0;
    double dy = 0.0;

    // Computation loop on each detected points
    for(int32_t i = 0; i < m_nbOfMeasures; i++)
    {
        // Convert to cartesian coordinates
        currentMeasuredPosX = (*ptReadOfLidarMeasures__mm) * (*ptReadOfLidarAngle__cos) + offsetX__mm;
        currentMeasuredPosY = (*ptReadOfLidarMeasures__mm) * (*ptReadOfLidarAngle__sin) + offsetY__mm;

        distFromObstacleToRobotCenter__mm = sqrt(currentMeasuredPosX * currentMeasuredPosX + currentMeasuredPosY * currentMeasuredPosY);

        // Take in account only valide points
        if ((distFromObstacleToRobotCenter__mm >= m_lidarMinReliableMeasuredDist__mm) && (distFromObstacleToRobotCenter__mm <= m_lidarMaxReliableMeasuredDist__mm))
        {
            // Need add virtual measures points ?
            if(distFromObstacleToRobotCenter__mm >= m_lidarMinDistToAddVirtualMeasures__mm)
            {
                // Compute distance from the current and the last measure
                dx = currentMeasuredPosX - lastMeasuredPosX;
                dy = currentMeasuredPosY - lastMeasuredPosY;

                // Current and last measures are near
                if((dx * dx + dy * dy) < m_opti_SQUARE_OF_MAX_DIST_BETWEEN_MEASURES_TO_ADD_VIRTUAL_MEASURES__MM)
                {
                    // Compute the number of points to add
                    uint32_t div = m_opti_maxNbOfVirtualMeasuresAtMaxDist_minus1 * (distFromObstacleToRobotCenter__mm - m_lidarMinDistToAddVirtualMeasures__mm) / m_lidarDistFromMinDistToAddVirtualMeasuresToMaxReliableMeasuredDist__mm + 1;

                    // Compute the delta to add per point
                    dx = dx / ((double)div);
                    dy = dy / ((double)div);

                    // Adding virtual measures loop
                    for(uint32_t k = 1; k < div; k++)
                    {
                        *ptWriteOfMeasuresPosX__mm = lastMeasuredPosX + dx;
                        *ptWriteOfMeasuresPosY__mm = lastMeasuredPosY + dy;

                        dx += dx;
                        dy += dy;
                        ptWriteOfMeasuresPosX__mm++;
                        ptWriteOfMeasuresPosY__mm++;
                        nbOfPoints++;
                    }
                }
            }

            // Add the current measure
            *ptWriteOfMeasuresPosX__mm = currentMeasuredPosX;
            *ptWriteOfMeasuresPosY__mm = currentMeasuredPosY;

            ptWriteOfMeasuresPosX__mm++;
            ptWriteOfMeasuresPosY__mm++;
            nbOfPoints++;

            // Store the current measure for next computation
            lastMeasuredPosX = currentMeasuredPosX;
            lastMeasuredPosY = currentMeasuredPosY;
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
