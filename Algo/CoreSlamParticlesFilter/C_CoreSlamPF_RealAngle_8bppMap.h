#ifndef C_CORESLAM_PF_REAL_ANGLE_8BPP_MAP_H
#define C_CORESLAM_PF_REAL_ANGLE_8BPP_MAP_H

#include "stdio.h"
#include "stdlib.h"
#include "stddef.h"
#include "stdint.h"
#include "math.h"
#include "string.h"

#include "Constants.h"
#include "C_Tools_DataTable.h"
#include "C_Tools_Maths.h"

#include "C_CoreSlamPF_DataStructDef.h"


// Disable boundary check to increase speed, but can be dangerous if map is too small
#define ENABLE_MAP_BOUNDARIES_CHECK

// This enable SLAM based on LIDAR Data
// For optimization on low power system, the algo use 8bpp map and lots of tweaks
// The main position estimation can work with or without odometry
class C_CoreSlamPF_RealAngle_8bppMap
{
public:
    // Constructor

    // No init (need init before use)
    C_CoreSlamPF_RealAngle_8bppMap(){}
    // Self Init
    C_CoreSlamPF_RealAngle_8bppMap(uint32_t globalMapSquareSize__mm){Init(globalMapSquareSize__mm);}
    // Init by recopy
    C_CoreSlamPF_RealAngle_8bppMap(C_CoreSlamPF_RealAngle_8bppMap * ptMapEstimator){Copy(ptMapEstimator);}

    // Destructor
    ~C_CoreSlamPF_RealAngle_8bppMap();

    void Init(uint32_t globalMapSquareSize__mm);
    void Copy(C_CoreSlamPF_RealAngle_8bppMap * ptMapEstimator);

    // Accessors
    // ======================================================================================

    uint8_t * GET_ptGlobalMap8bpp(void)
    {
        return m_globalMap.ptMap8bpp;
    }

    uint8_t * GET_ptThnlGlobalMap8bpp(void)
    {
        return m_thumbnailMap.ptMap8bpp;
    }

    uint32_t GET_GlobalMapScale__mmPerPixel(void)
    {
        return m_globalMap.mmPerPixel;
    }

    double GET_GlobalMap_CONV_PIXEL_2_MM(void)
    {
        return m_globalMap.convPixel2Mm;
    }

    double GET_GlobalMap_CONV_MM_2_PIXEL(void)
    {
        return m_globalMap.convMm2Pixel;
    }

    uint32_t GET_ThnlGlobalMapScale__mmPerPixel(void)
    {
        return m_thumbnailMap.mmPerPixel;
    }

    uint32_t GET_globalMapSquareSize__mm(void)
    {
        return m_allMapSquareSize__mm;
    }

    uint32_t GET_ThnlGlobalMapSquareSize__mm(void)
    {
        return m_allMapSquareSize__mm;
    }

    uint32_t GET_globalMapSquareSize__pixel(void)
    {
        return (uint32_t)m_globalMap.opti_mapSquareSize__pixel;
    }

    uint32_t GET_thnlGlobalMapSquareSize__pixel(void)
    {
        return (uint32_t)m_thumbnailMap.opti_mapSquareSize__pixel;
    }

    double GET_currentPosX__mm(void)
    {
        return m_estimatedRobotPosition.currentPosX__mm;
    }

    uint32_t GET_currentPosX__pixel(void)
    {
        return m_globalMap.currentPosX__pixel;
    }

    double GET_currentPosY__mm(void)
    {
        return m_estimatedRobotPosition.currentPosY__mm;
    }

    uint32_t GET_currentPosY__pixel(void)
    {
        return m_globalMap.currentPosY__pixel;
    }

    double GET_currentPosAngle__rad(void)
    {
        return m_estimatedRobotPosition.currentPosAngle__rad;
    }

    double GET_opti_currentPosAngle__cos(void)
    {
        return m_estimatedRobotPosition.opti_currentPosAngle__cos;
    }

    double GET_opti_currentPosAngle__sin(void)
    {
        return m_estimatedRobotPosition.opti_currentPosAngle__sin;
    }

    double GET_currentPosAngle__deg(void)
    {
        return m_estimatedRobotPosition.currentPosAngle__rad * MATHS_CONV_RAD_2_DEG;
    }

    void GET_lastGlobalMapUpgradedZone(uint32_t * xMin, uint32_t * xMax, uint32_t * yMin, uint32_t * yMax)
    {
        *xMin = m_globalMap.opti_mapUpdateZoneXmin__pixel;
        *xMax = m_globalMap.opti_mapUpdateZoneXmax__pixel;
        *yMin = m_globalMap.opti_mapUpdateZoneYmin__pixel;
        *yMax = m_globalMap.opti_mapUpdateZoneYmax__pixel;
    }

    void GET_lastThnlGlobalMapUpgradedZone(uint32_t * xMin, uint32_t * xMax, uint32_t * yMin, uint32_t * yMax)
    {
        *xMin = m_thumbnailMap.opti_mapUpdateZoneXmin__pixel;
        *xMax = m_thumbnailMap.opti_mapUpdateZoneXmax__pixel;
        *yMin = m_thumbnailMap.opti_mapUpdateZoneYmin__pixel;
        *yMax = m_thumbnailMap.opti_mapUpdateZoneYmax__pixel;
    }

    // Reset the algo
    void Reset();

    void ConnectSensorDataFlow(double * tabOfLidarMeasuresInCartesianRef_X__mm, double * tabOfLidarMeasuresInCartesianRef_Y__mm, int32_t * pt_opti_nbOfMeasuresTakenIntoAccount_minus1)
    {
        m_tabOfLidarMeasuresInCartesianRef_X__mm = tabOfLidarMeasuresInCartesianRef_X__mm;
        m_tabOfLidarMeasuresInCartesianRef_Y__mm = tabOfLidarMeasuresInCartesianRef_Y__mm;
        m_pt_opti_nbOfMeasuresTakenIntoAccount_minus1 = pt_opti_nbOfMeasuresTakenIntoAccount_minus1;
    }

    // Set the robot position
    void SetRobotPosition(double currentPosX__mm, double currentPosY__mm, double currentPosAngle__rad, double appliedDxErr__mm, double appliedDyErr__mm, double appliedDangleErr__rad, uint64_t matchingQuality)
    {
        m_estimatedRobotPosition.currentPosX__mm = currentPosX__mm;
        m_globalMap.currentPosX__pixel = C_Tools_Maths::Opti_round(currentPosX__mm * m_globalMap.convMm2Pixel);
        m_thumbnailMap.currentPosX__pixel = C_Tools_Maths::Opti_round(currentPosX__mm * m_thumbnailMap.convMm2Pixel);

        m_estimatedRobotPosition.currentPosY__mm = currentPosY__mm;
        m_globalMap.currentPosY__pixel = C_Tools_Maths::Opti_round(currentPosY__mm * m_globalMap.convMm2Pixel);
        m_thumbnailMap.currentPosY__pixel = C_Tools_Maths::Opti_round(currentPosY__mm * m_thumbnailMap.convMm2Pixel);

        m_estimatedRobotPosition.currentPosAngle__rad = currentPosAngle__rad;
        m_estimatedRobotPosition.currentPosAngle__deg = currentPosAngle__rad * MATHS_CONV_RAD_2_DEG;
        m_estimatedRobotPosition.opti_currentPosAngle__cos = cos(currentPosAngle__rad);
        m_estimatedRobotPosition.opti_currentPosAngle__sin = sin(currentPosAngle__rad);

        m_estimatedRobotPosition.matchingQuality = matchingQuality;

        m_estimatedRobotPosition.appliedDxErr__mm = appliedDxErr__mm;
        m_estimatedRobotPosition.appliedDyErr__mm = appliedDyErr__mm;
        m_estimatedRobotPosition.appliedDangleErr__rad = appliedDangleErr__rad;
        m_estimatedRobotPosition.appliedDangleErr__deg = appliedDangleErr__rad * MATHS_CONV_RAD_2_DEG;
    }

    // Get the robot position
    void GetRobotPosition(struct_EstimatedRobotPosition * ptEstimatedRobotPosition)
    {
        ptEstimatedRobotPosition->currentPosX__mm = m_estimatedRobotPosition.currentPosX__mm;
        ptEstimatedRobotPosition->currentPosY__mm = m_estimatedRobotPosition.currentPosY__mm;
        ptEstimatedRobotPosition->currentPosAngle__rad = m_estimatedRobotPosition.currentPosAngle__rad;
        ptEstimatedRobotPosition->currentPosAngle__deg = m_estimatedRobotPosition.currentPosAngle__deg;
        ptEstimatedRobotPosition->opti_currentPosAngle__cos = m_estimatedRobotPosition.opti_currentPosAngle__cos;
        ptEstimatedRobotPosition->opti_currentPosAngle__sin = m_estimatedRobotPosition.opti_currentPosAngle__sin;
        ptEstimatedRobotPosition->matchingQuality = m_estimatedRobotPosition.matchingQuality;
        ptEstimatedRobotPosition->appliedDxErr__mm = m_estimatedRobotPosition.appliedDxErr__mm;
        ptEstimatedRobotPosition->appliedDyErr__mm = m_estimatedRobotPosition.appliedDyErr__mm;
        ptEstimatedRobotPosition->appliedDangleErr__rad = m_estimatedRobotPosition.appliedDangleErr__rad;
        ptEstimatedRobotPosition->appliedDangleErr__deg = m_estimatedRobotPosition.appliedDangleErr__deg;
    }


    // Check the matching quality of the Lidar data using the given position
    // The "Normal" function does the cached data
    // The "Opti" function reuse the cached data
    // Be carrefull when using the Opti function
    uint64_t ComputeMatching(double xInMm, double yInMm, double preComputedCos, double preComputedSin);
    uint64_t Opti_ComputeMatching(double xInMm, double yInMm);

    // Update all maps with the Lidar data
    void UpdateMap()
    {
        UpdateMap(&m_globalMap);
        UpdateMap(&m_thumbnailMap);
    }

private:
    // OUTPUT MAP
    // ======================================================================================
    // The map is a square with the following side size
    uint32_t m_allMapSquareSize__mm = 0;

    // Global map of the world
    struct_Map m_globalMap;
    // Reduce map for fast post processing
    struct_Map m_thumbnailMap;

    // Robot position estimation
    struct_EstimatedRobotPosition m_estimatedRobotPosition;


	// Pointer to the lidar data
	// TODO : Do stuff nicer than direct access
    double * m_tabOfLidarMeasuresInCartesianRef_X__mm;
    double * m_tabOfLidarMeasuresInCartesianRef_Y__mm;
    int32_t * m_pt_opti_nbOfMeasuresTakenIntoAccount_minus1;

    // INTERNAL FUNCTIONS
    // ======================================================================================
    // Cached data for ComputeMatching(...)
    double m_opti_computeMatching_cached_X[LIDAR_MAX_NB_OF_VIRTUAL_MEASURES_AT_MAX_DIST * LIDAR_MAX_NB_MEASURES_PER_REVOLUTION] = {0.0};
    double m_opti_computeMatching_cached_Y[LIDAR_MAX_NB_OF_VIRTUAL_MEASURES_AT_MAX_DIST * LIDAR_MAX_NB_MEASURES_PER_REVOLUTION] = {0.0};

    // Update a specific map
    void UpdateMap(struct_Map * ptMap);

    // Trace one Lidar ray on the global map
    inline void RayTraceLidarData(struct_Map * ptMap, int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t xp, int32_t yp);
};

#endif // C_CORESLAM_PF_REAL_ANGLE_8BPP_MAP_H
