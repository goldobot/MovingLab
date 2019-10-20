#include "C_CoreSlamPF_RealAngle_8bppMap.h"


void C_CoreSlamPF_RealAngle_8bppMap::Init(uint32_t globalMapSquareSize__mm)
{
    m_allMapSquareSize__mm = globalMapSquareSize__mm;

    // Map 1 model
    m_globalMap.initMapPixelValue = 128;

    m_globalMap.mmPerPixel = 10;
    m_globalMap.convPixel2Mm = (double)m_globalMap.mmPerPixel;
    m_globalMap.convMm2Pixel = 1.0 / m_globalMap.convPixel2Mm;
    m_globalMap.currentPosX__pixel = 0;
    m_globalMap.currentPosY__pixel = 0;

    m_globalMap.opti_mapUpdateZoneXmin__pixel = 0;
    m_globalMap.opti_mapUpdateZoneXmax__pixel = 0;
    m_globalMap.opti_mapUpdateZoneYmin__pixel = 0;
    m_globalMap.opti_mapUpdateZoneYmax__pixel = 0;

    m_globalMap.obstaclesWidth__mm = 150;
    m_globalMap.obstaclesHalfWidth__pixel = (uint32_t)((double)(m_globalMap.obstaclesWidth__mm) * m_globalMap.convMm2Pixel) / 2;

    m_globalMap.opti_mapSquareSize__pixel = 0;

    m_globalMap.rayTraceAlphaModel = 50;
    m_globalMap.opti_256MinusAlphaModel = 256 - m_globalMap.rayTraceAlphaModel;


    // Map 2 model
    m_thumbnailMap.initMapPixelValue = 0;

    m_thumbnailMap.mmPerPixel = 47;
    m_thumbnailMap.convPixel2Mm = (double)m_thumbnailMap.mmPerPixel;
    m_thumbnailMap.convMm2Pixel = 1.0 / m_thumbnailMap.convPixel2Mm;
    m_thumbnailMap.currentPosX__pixel = 0;
    m_thumbnailMap.currentPosY__pixel = 0;

    m_thumbnailMap.opti_mapUpdateZoneXmin__pixel = 0;
    m_thumbnailMap.opti_mapUpdateZoneXmax__pixel = 0;
    m_thumbnailMap.opti_mapUpdateZoneYmin__pixel = 0;
    m_thumbnailMap.opti_mapUpdateZoneYmax__pixel = 0;

    m_thumbnailMap.obstaclesWidth__mm = 100;
    m_thumbnailMap.obstaclesHalfWidth__pixel = (uint32_t)((double)(m_thumbnailMap.obstaclesWidth__mm) * m_thumbnailMap.convMm2Pixel) / 2;

    m_thumbnailMap.opti_mapSquareSize__pixel = 0;

    m_thumbnailMap.rayTraceAlphaModel = 50;
    m_thumbnailMap.opti_256MinusAlphaModel = 256 - m_thumbnailMap.rayTraceAlphaModel;


    // Precomputed usefull data
    m_globalMap.opti_mapSideSize_minus1__pixel = (int32_t)((double)m_allMapSquareSize__mm * m_globalMap.convMm2Pixel);
    m_globalMap.opti_mapSquareSize__pixel = m_globalMap.opti_mapSideSize_minus1__pixel + 1;
    m_globalMap.opti_minus_mapSideSize__pixel = -m_globalMap.opti_mapSquareSize__pixel;

    m_thumbnailMap.opti_mapSideSize_minus1__pixel = (int32_t)((double)m_allMapSquareSize__mm * m_thumbnailMap.convMm2Pixel);
    m_thumbnailMap.opti_mapSquareSize__pixel = m_thumbnailMap.opti_mapSideSize_minus1__pixel + 1;
    m_thumbnailMap.opti_minus_mapSideSize__pixel = -m_thumbnailMap.opti_mapSquareSize__pixel;
}

void C_CoreSlamPF_RealAngle_8bppMap::Copy(C_CoreSlamPF_RealAngle_8bppMap * ptMapEstimator)
{
    // No need to copy when the data does not change

    //m_allMapSquareSize__mm = ptMapEstimator->m_allMapSquareSize__mm;

    memcpy(m_globalMap.ptMap8bpp, ptMapEstimator->m_globalMap.ptMap8bpp, m_globalMap.opti_mapSquareSize__pixel * m_globalMap.opti_mapSquareSize__pixel);
    //m_globalMap.initMapPixelValue = ptMapEstimator->m_globalMap.initMapPixelValue;
    //m_globalMap.mmPerPixel = ptMapEstimator->m_globalMap.mmPerPixel;
    //m_globalMap.convPixel2Mm = ptMapEstimator->m_globalMap.convPixel2Mm;
    //m_globalMap.convMm2Pixel = ptMapEstimator->m_globalMap.convMm2Pixel;
    //m_globalMap.currentPosX__pixel = ptMapEstimator->m_globalMap.currentPosX__pixel;
    //m_globalMap.currentPosY__pixel = ptMapEstimator->m_globalMap.currentPosY__pixel;
    //m_globalMap.obstaclesWidth__mm = ptMapEstimator->m_globalMap.obstaclesWidth__mm;
    //m_globalMap.obstaclesHalfWidth__pixel = ptMapEstimator->m_globalMap.obstaclesHalfWidth__pixel;
    //m_globalMap.opti_mapUpdateZoneXmin__pixel = ptMapEstimator->m_globalMap.opti_mapUpdateZoneXmin__pixel;
    //m_globalMap.opti_mapUpdateZoneXmax__pixel = ptMapEstimator->m_globalMap.opti_mapUpdateZoneXmax__pixel;
    //m_globalMap.opti_mapUpdateZoneYmin__pixel = ptMapEstimator->m_globalMap.opti_mapUpdateZoneYmin__pixel;
    //m_globalMap.opti_mapUpdateZoneYmax__pixel = ptMapEstimator->m_globalMap.opti_mapUpdateZoneYmax__pixel;
    //m_globalMap.opti_mapSquareSize__pixel = ptMapEstimator->m_globalMap.opti_mapSquareSize__pixel;
    //m_globalMap.opti_minus_mapSideSize__pixel = ptMapEstimator->m_globalMap.opti_minus_mapSideSize__pixel;
    //m_globalMap.opti_mapSideSize_minus1__pixel = ptMapEstimator->m_globalMap.opti_mapSideSize_minus1__pixel;
    //m_globalMap.rayTraceAlphaModel = ptMapEstimator->m_globalMap.rayTraceAlphaModel;
    //m_globalMap.opti_256MinusAlphaModel = ptMapEstimator->m_globalMap.opti_256MinusAlphaModel;


    memcpy(m_thumbnailMap.ptMap8bpp, ptMapEstimator->m_thumbnailMap.ptMap8bpp, m_thumbnailMap.opti_mapSquareSize__pixel * m_thumbnailMap.opti_mapSquareSize__pixel);
    //m_thumbnailMap.initMapPixelValue = ptMapEstimator->m_thumbnailMap.initMapPixelValue;
    //m_thumbnailMap.mmPerPixel = ptMapEstimator->m_thumbnailMap.mmPerPixel;
    //m_thumbnailMap.convPixel2Mm = ptMapEstimator->m_thumbnailMap.convPixel2Mm;
    //m_thumbnailMap.convMm2Pixel = ptMapEstimator->m_thumbnailMap.convMm2Pixel;
    //m_thumbnailMap.currentPosX__pixel = ptMapEstimator->m_thumbnailMap.currentPosX__pixel;
    //m_thumbnailMap.currentPosY__pixel = ptMapEstimator->m_thumbnailMap.currentPosY__pixel;
    //m_thumbnailMap.obstaclesWidth__mm = ptMapEstimator->m_thumbnailMap.obstaclesWidth__mm;
    //m_thumbnailMap.obstaclesHalfWidth__pixel = ptMapEstimator->m_thumbnailMap.obstaclesHalfWidth__pixel;
    //m_thumbnailMap.opti_mapUpdateZoneXmin__pixel = ptMapEstimator->m_thumbnailMap.opti_mapUpdateZoneXmin__pixel;
    //m_thumbnailMap.opti_mapUpdateZoneXmax__pixel = ptMapEstimator->m_thumbnailMap.opti_mapUpdateZoneXmax__pixel;
    //m_thumbnailMap.opti_mapUpdateZoneYmin__pixel = ptMapEstimator->m_thumbnailMap.opti_mapUpdateZoneYmin__pixel;
    //m_thumbnailMap.opti_mapUpdateZoneYmax__pixel = ptMapEstimator->m_thumbnailMap.opti_mapUpdateZoneYmax__pixel;
    //m_thumbnailMap.opti_mapSquareSize__pixel = ptMapEstimator->m_thumbnailMap.opti_mapSquareSize__pixel;
    //m_thumbnailMap.opti_minus_mapSideSize__pixel = ptMapEstimator->m_thumbnailMap.opti_minus_mapSideSize__pixel;
    //m_thumbnailMap.opti_mapSideSize_minus1__pixel = ptMapEstimator->m_thumbnailMap.opti_mapSideSize_minus1__pixel;
    //m_thumbnailMap.rayTraceAlphaModel = ptMapEstimator->m_thumbnailMap.rayTraceAlphaModel;
    //m_thumbnailMap.opti_256MinusAlphaModel = ptMapEstimator->m_thumbnailMap.opti_256MinusAlphaModel;

    //m_estimatedRobotPosition.currentPosX__mm = ptMapEstimator->m_estimatedRobotPosition.currentPosX__mm;
    //m_estimatedRobotPosition.currentPosY__mm = ptMapEstimator->m_estimatedRobotPosition.currentPosY__mm;
    //m_estimatedRobotPosition.currentPosAngle__rad = ptMapEstimator->m_estimatedRobotPosition.currentPosAngle__rad ;
    //m_estimatedRobotPosition.currentPosAngle__deg = ptMapEstimator->m_estimatedRobotPosition.currentPosAngle__deg;
    //m_estimatedRobotPosition.opti_currentPosAngle__cos = ptMapEstimator->m_estimatedRobotPosition.opti_currentPosAngle__cos;
    //m_estimatedRobotPosition.opti_currentPosAngle__sin = ptMapEstimator->m_estimatedRobotPosition.opti_currentPosAngle__sin;
    //m_estimatedRobotPosition.matchingQuality = ptMapEstimator->m_estimatedRobotPosition.matchingQuality;
    //m_estimatedRobotPosition.appliedDxErr__mm = ptMapEstimator->m_estimatedRobotPosition.appliedDxErr__mm;
    //m_estimatedRobotPosition.appliedDyErr__mm = ptMapEstimator->m_estimatedRobotPosition.appliedDyErr__mm;
    //m_estimatedRobotPosition.appliedDangleErr__rad = ptMapEstimator->m_estimatedRobotPosition.appliedDangleErr__rad;
    //m_estimatedRobotPosition.appliedDangleErr__deg = ptMapEstimator->m_estimatedRobotPosition.appliedDangleErr__deg;

    //m_tabOfLidarMeasuresInCartesianRef_X__mm = ptMapEstimator->m_tabOfLidarMeasuresInCartesianRef_X__mm;
    //m_tabOfLidarMeasuresInCartesianRef_Y__mm = ptMapEstimator->m_tabOfLidarMeasuresInCartesianRef_Y__mm;
    //m_pt_opti_nbOfMeasuresTakenIntoAccount_minus1 = ptMapEstimator->m_pt_opti_nbOfMeasuresTakenIntoAccount_minus1;

    //memcpy(m_opti_computeMatching_cached_X, ptMapEstimator->m_opti_computeMatching_cached_X, LIDAR_MAX_NB_OF_VIRTUAL_MEASURES_AT_MAX_DIST * LIDAR_MAX_NB_MEASURES_PER_REVOLUTION * sizeof(double));
    //memcpy(m_opti_computeMatching_cached_Y, ptMapEstimator->m_opti_computeMatching_cached_Y, LIDAR_MAX_NB_OF_VIRTUAL_MEASURES_AT_MAX_DIST * LIDAR_MAX_NB_MEASURES_PER_REVOLUTION * sizeof(double));
}


C_CoreSlamPF_RealAngle_8bppMap::~C_CoreSlamPF_RealAngle_8bppMap()
{
    // Clear all malloc stuff
    free(m_globalMap.ptMap8bpp);
    free(m_thumbnailMap.ptMap8bpp);
}


void C_CoreSlamPF_RealAngle_8bppMap::Reset()
{
    // Put the robot to the midle of the map
    m_estimatedRobotPosition.currentPosX__mm = m_allMapSquareSize__mm / 2;
    m_estimatedRobotPosition.currentPosY__mm = m_allMapSquareSize__mm / 2;
    m_estimatedRobotPosition.currentPosAngle__rad = 0.0;
    m_estimatedRobotPosition.opti_currentPosAngle__cos = cos(m_estimatedRobotPosition.currentPosAngle__rad);
    m_estimatedRobotPosition.opti_currentPosAngle__sin = sin(m_estimatedRobotPosition.currentPosAngle__rad);

    // Reset error model
    m_estimatedRobotPosition.appliedDxErr__mm = 0;
    m_estimatedRobotPosition.appliedDyErr__mm = 0;
    m_estimatedRobotPosition.appliedDangleErr__rad = 0;

    // Init the probability map
    m_globalMap.ptMap8bpp = C_Tools_DataTable::AllocArrayU8(m_globalMap.opti_mapSquareSize__pixel, m_globalMap.opti_mapSquareSize__pixel,  m_globalMap.initMapPixelValue);
    // Init the drawing zone to the whole map
    m_globalMap.opti_mapUpdateZoneXmin__pixel = 0;
    m_globalMap.opti_mapUpdateZoneXmax__pixel = m_globalMap.opti_mapSideSize_minus1__pixel;
    m_globalMap.opti_mapUpdateZoneYmin__pixel = 0;
    m_globalMap.opti_mapUpdateZoneYmax__pixel = m_globalMap.opti_mapSideSize_minus1__pixel;

    m_globalMap.currentPosX__pixel = C_Tools_Maths::Opti_round(m_estimatedRobotPosition.currentPosX__mm * m_globalMap.convMm2Pixel);
    m_globalMap.currentPosY__pixel = C_Tools_Maths::Opti_round(m_estimatedRobotPosition.currentPosY__mm * m_globalMap.convMm2Pixel);

    // Init the probability map
    m_thumbnailMap.ptMap8bpp = C_Tools_DataTable::AllocArrayU8(m_thumbnailMap.opti_mapSquareSize__pixel, m_thumbnailMap.opti_mapSquareSize__pixel,  m_thumbnailMap.initMapPixelValue);
    // Init the drawing zone to the whole map
    m_thumbnailMap.opti_mapUpdateZoneXmin__pixel = 0;
    m_thumbnailMap.opti_mapUpdateZoneXmax__pixel = m_thumbnailMap.opti_mapSideSize_minus1__pixel;
    m_thumbnailMap.opti_mapUpdateZoneYmin__pixel = 0;
    m_thumbnailMap.opti_mapUpdateZoneYmax__pixel = m_thumbnailMap.opti_mapSideSize_minus1__pixel;

    m_thumbnailMap.currentPosX__pixel = C_Tools_Maths::Opti_round(m_estimatedRobotPosition.currentPosX__mm * m_thumbnailMap.convMm2Pixel);
    m_thumbnailMap.currentPosY__pixel = C_Tools_Maths::Opti_round(m_estimatedRobotPosition.currentPosY__mm * m_thumbnailMap.convMm2Pixel);
}


// Compute the matching quality of the detected points set
// For each detected point, read on the probability map if the point is probable or not
// Smallest is the best
uint64_t C_CoreSlamPF_RealAngle_8bppMap::ComputeMatching(double posX__mm, double posY__mm, double preComputedCos, double preComputedSin)
{
#ifdef ENABLE_MAP_BOUNDARIES_CHECK
    uint32_t nbOfPoints = 0;
#endif

    int32_t x, y = 0;
    uint64_t sum = 0;

    double cos_x_CONV_MM_2_PIXEL = preComputedCos * m_globalMap.convMm2Pixel;
    double sin_x_CONV_MM_2_PIXEL = preComputedSin * m_globalMap.convMm2Pixel;

    double posX__pixel = posX__mm * m_globalMap.convMm2Pixel;
    double posY__pixel = posY__mm * m_globalMap.convMm2Pixel;

    int32_t i = *m_pt_opti_nbOfMeasuresTakenIntoAccount_minus1;
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
        if ((x >= 0) && (x < m_globalMap.opti_mapSquareSize__pixel) && (y >= 0) && (y < m_globalMap.opti_mapSquareSize__pixel))
#endif
        {
            sum += m_globalMap.ptMap8bpp[y * m_globalMap.opti_mapSquareSize__pixel + x];

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
        // Minus 1 to avoid UINT64_MAX limit pb in the others alog which use UINT64_MAX
        sum = UINT64_MAX;
    }

    return sum;
    
#else
    return ((sum << 10) / m_nbOfMeasuresTakenIntoAccount);
#endif
}


//Calculer la ressemblance entre le scan et la carte
uint64_t C_CoreSlamPF_RealAngle_8bppMap::Opti_ComputeMatching(double xInMm, double yInMm)
{
#ifdef ENABLE_MAP_BOUNDARIES_CHECK
    uint32_t nb_points = 0;
#endif

    int32_t x, y = 0;
    uint64_t sum = 0;

    double xInPixel = xInMm * m_globalMap.convMm2Pixel;
    double yInPixel = yInMm * m_globalMap.convMm2Pixel;

    int32_t i = *m_pt_opti_nbOfMeasuresTakenIntoAccount_minus1;
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
        if ((x >= 0) && (x < m_globalMap.opti_mapSquareSize__pixel) && (y >= 0) && (y < m_globalMap.opti_mapSquareSize__pixel))
#endif
        {
            sum += m_globalMap.ptMap8bpp[y * m_globalMap.opti_mapSquareSize__pixel + x];

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


void C_CoreSlamPF_RealAngle_8bppMap::UpdateMap(struct_Map * ptMap)
{
    double x2p, y2p;
    int32_t x2, y2, xp, yp;
    double add;

    double currentCosOfPosAngle__pixel = m_estimatedRobotPosition.opti_currentPosAngle__cos * ptMap->convMm2Pixel;
    double currentSinOfPosAngle__pixel = m_estimatedRobotPosition.opti_currentPosAngle__sin * ptMap->convMm2Pixel;

    double currentX__pixel = ptMap->currentPosX__pixel;
    double currentY__pixel = ptMap->currentPosY__pixel;

    ptMap->opti_mapUpdateZoneXmin__pixel = ptMap->opti_mapUpdateZoneXmax__pixel = ptMap->currentPosX__pixel;
    ptMap->opti_mapUpdateZoneYmin__pixel = ptMap->opti_mapUpdateZoneYmax__pixel = ptMap->currentPosY__pixel;

    int32_t x1 = C_Tools_Maths::Opti_floor(currentX__pixel + 0.5);
    int32_t y1 = C_Tools_Maths::Opti_floor(currentY__pixel + 0.5);

    int32_t i = *m_pt_opti_nbOfMeasuresTakenIntoAccount_minus1;
    double* ptX = m_tabOfLidarMeasuresInCartesianRef_X__mm + i;
    double* ptY = m_tabOfLidarMeasuresInCartesianRef_Y__mm + i;

    while (i >= 0)
    {
        x2p = currentCosOfPosAngle__pixel * (*ptX) - currentSinOfPosAngle__pixel * (*ptY);
        y2p = currentSinOfPosAngle__pixel * (*ptX) + currentCosOfPosAngle__pixel * (*ptY);

        xp = C_Tools_Maths::Opti_floor(currentX__pixel + x2p + 0.5);
        yp = C_Tools_Maths::Opti_floor(currentY__pixel + y2p + 0.5);

        x2p *= (add = 1.0 + ((double)(ptMap->obstaclesHalfWidth__pixel) / sqrt((double)(x2p * x2p + y2p * y2p))));
        y2p *= add;

        x2 = C_Tools_Maths::Opti_floor(currentX__pixel + x2p + 0.5);
        y2 = C_Tools_Maths::Opti_floor(currentY__pixel + y2p + 0.5);

        RayTraceLidarData(ptMap, x1, y1, x2, y2, xp, yp);

        i--; ptX--; ptY--;

        // Store the modification zone
        if((x2 > 0) && (x2 < ptMap->opti_mapSquareSize__pixel))
        {
            if((uint32_t)x2 > (ptMap->opti_mapUpdateZoneXmax__pixel))
            {
                ptMap->opti_mapUpdateZoneXmax__pixel = x2;
            }
            if((uint32_t)x2 < (ptMap->opti_mapUpdateZoneXmin__pixel))
            {
                ptMap->opti_mapUpdateZoneXmin__pixel = x2;
            }
        }

        if((y2 > 0) && (y2 < ptMap->opti_mapSquareSize__pixel))
        {
            if((uint32_t)y2 > ptMap->opti_mapUpdateZoneYmax__pixel)
            {
                ptMap->opti_mapUpdateZoneYmax__pixel = y2;
            }
            if((uint32_t)y2 < ptMap->opti_mapUpdateZoneYmin__pixel)
            {
                ptMap->opti_mapUpdateZoneYmin__pixel = y2;
            }
        }
    }
}


void C_CoreSlamPF_RealAngle_8bppMap::RayTraceLidarData(struct_Map * ptMap, int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t xp, int32_t yp)
{
    int32_t x2c, y2c, dx, dy, dxc, dyc, error, errorv, derrorv, x;

    int32_t incv = 0;
    int32_t incptrx, incptry, pixval, horiz, diago;

#ifdef ENABLE_MAP_BOUNDARIES_CHECK
    if ((x1 < 0) || (x1 >= (ptMap->opti_mapSquareSize__pixel)) || (y1 < 0) || (y1 >= (ptMap->opti_mapSquareSize__pixel)))
    {
        return; // Robot is out of data
    }
#endif

    x2c = x2;
    y2c = y2;

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
    else if (x2c >= (ptMap->opti_mapSquareSize__pixel))
    {
        if (x1 == x2c)
        {
            return;
        }

        y2c += (y2c - y1) * ((ptMap->opti_mapSideSize_minus1__pixel) - x2c) / (x2c - x1);
        x2c = (ptMap->opti_mapSideSize_minus1__pixel);
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
    else if (y2c >= (ptMap->opti_mapSquareSize__pixel))
    {
        if (y1 == y2c)
        {
            return;
        }

        x2c += (x1 - x2c) * ((ptMap->opti_mapSideSize_minus1__pixel) - y2c) / (y1 - y2c);
        y2c = (ptMap->opti_mapSideSize_minus1__pixel);
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
        incptry = (ptMap->opti_mapSquareSize__pixel);
    }
    else
    {
        dy = y1 - y2;
        incptry = (ptMap->opti_minus_mapSideSize__pixel);
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

    uint8_t * ptD = (ptMap->ptMap8bpp) + y1 * (ptMap->opti_mapSquareSize__pixel) + x1;

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
        uint16_t val = (((uint16_t)(*ptD) * 768) + ((uint16_t)((ptMap->opti_256MinusAlphaModel) * (*ptD) + (ptMap->rayTraceAlphaModel) * pixval))) / 1024;

        if(val > 255) (*ptD) = 255;
        else (*ptD) = val;


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
