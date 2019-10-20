#ifndef C_CORESLAM_PF_DATA_STRUCT_DEF_H
#define C_CORESLAM_PF_DATA_STRUCT_DEF_H


// Manage a list of positions which match the map with a given score


#include "stdio.h"
#include "stdlib.h"
#include "stddef.h"
#include "stdint.h"
#include "math.h"
#include "string.h"


// A match position
struct struct_MatchPos
{
    // ID of the particle which produces the matching
    int mapEstimatorId;

    // Score of the matching
    uint64_t matchingQuality;

    // Estimated position which gives the matching quality
    double posX__mm;
    double posY__mm;
    double posAngle__rad;

    // Estimated position error which gives the matching quality
    double posErrX__mm;
    double posErrY__mm;
    double posErrAngle__rad;

    // Pointer to the next match position
    struct_MatchPos * ptNextMatchPos;
};


enum enum_EstimationType
{
    NO_CALC, THETA_ONLY, COMPLET_POS
};

// Describe how to use the lidar data
struct struct_ParamsForUsingLidar
{
    // Position of the lidar sensor compared to the center of the robot
    int lidarPosOffsetX__mm;
    int lidarPosOffsetY__mm;

    // Type of estimation using the sensor
    enum_EstimationType estimationType;

    // Integration weight (0 to N : 0 is high, N is low)
    int mapIntegrationWeight;
};


// Structure which store all data about robot position
struct struct_EstimatedRobotPosition
{
    // Current estimated position on the global map
    double currentPosX__mm = 0.0;
    double currentPosY__mm = 0.0;
    double currentPosAngle__rad = 0.0;
    double currentPosAngle__deg = 0.0;

    // Optimization (precomputed values)
    double opti_currentPosAngle__cos = 0.0;
    double opti_currentPosAngle__sin = 0.0;

    // Position estimator

    // Lower is better
    uint64_t matchingQuality = 0;

    // Applied correction
    // Compared to the error model which is a custom model
    double appliedDxErr__mm = 0.0;
    double appliedDyErr__mm = 0.0;
    double appliedDangleErr__rad = 0.0;
    double appliedDangleErr__deg = 0.0;
};

// Describe a map structure
struct struct_Map
{
    // Map of the world
    uint8_t * ptMap8bpp = nullptr;

    // Initial pixels value of the map
    uint32_t initMapPixelValue = 0;

    // Map scaling
    uint32_t mmPerPixel = 0;
    double convPixel2Mm = 0.0;
    double convMm2Pixel = 0.0;

    // Robot position scaled to the map
    uint32_t currentPosX__pixel = 0;
    uint32_t currentPosY__pixel = 0;

    // Obstacle model
    uint32_t obstaclesWidth__mm = 0;
    uint32_t obstaclesHalfWidth__pixel = 0;

    // Updated zone in the map
    uint32_t opti_mapUpdateZoneXmin__pixel = 0;
    uint32_t opti_mapUpdateZoneXmax__pixel = 0;
    uint32_t opti_mapUpdateZoneYmin__pixel = 0;
    uint32_t opti_mapUpdateZoneYmax__pixel = 0;

    // Precomputed values for optimization
    int32_t opti_mapSquareSize__pixel = 0;
    int32_t opti_minus_mapSideSize__pixel = 0;
    int32_t opti_mapSideSize_minus1__pixel = 0;

    // Map updating parameter
    int32_t rayTraceAlphaModel = 0;
    int32_t opti_256MinusAlphaModel = 0;
};


#endif // C_CORESLAM_PF_DATA_STRUCT_DEF_H
