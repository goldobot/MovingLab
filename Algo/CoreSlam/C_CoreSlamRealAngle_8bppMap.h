#ifndef C_CORESLAM_REAL_ANGLE_8BPP_MAP_H
#define C_CORESLAM_REAL_ANGLE_8BPP_MAP_H

#include "stdio.h"
#include "stdlib.h"
#include "stddef.h"
#include "stdint.h"
#include "math.h"
#include "string.h"
#include <qmath.h>

#include "Constants.h"
#include "C_Tools_DataTable.h"
#include "C_Tools_Maths.h"

// Disable to allow debug and calibration purpose
#define ENABLE_ESTIMATION

// Disable boundary check to increase speed, but can be dangerous if map is too small
#define ENABLE_MAP_BOUNDARIES_CHECK

// Disable will draw the wall at its normal size
// See documentation of Coreslam for more details about wall V profile
#define WALL_HALF_SIZE_ON_MAP

// This enable SLAM based on LIDAR Data
// For optimization on low power system, the algo use 8bpp map and lots of tweaks
// The main position estimation can work with or without odometry
class C_CoreSlamRealAngle_8bppMap
{
public:
    enum enum_EstimationType
    {
        NONE, THETA_ONLY, COMPLET_POS
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


    // Constructor
    C_CoreSlamRealAngle_8bppMap(uint32_t globalMapSquareSize__mm, uint32_t lidarMinReliableMeasuredDist__mm, uint32_t lidarMaxReliableMeasuredDist__mm, uint32_t lidarMinDistToAddVirtualMeasures__mm, uint32_t maxNbOfVirtualMeasuresAtMaxDist);

    // Destructor
    ~C_CoreSlamRealAngle_8bppMap();

    // Accessors
    // ======================================================================================

    uint8_t * GET_ptGlobalMap8bpp(void)
    {
        return m_globalMap.m_ptRawPixelMatrix_8bpp;
    }

    uint8_t * GET_ptNavMap8bpp(void)
    {
        return m_navMap.m_ptModifiedPixelMatrix_8bpp;
    }

    uint32_t GET_globalMapScale__mmPerPixel(void)
    {
        return m_globalMap.MM_PER_PIXEL;
    }

    uint32_t GET_navMapScale__mmPerPixel(void)
    {
        return m_navMap.MM_PER_PIXEL;
    }

    uint32_t GET_globalMapSquareSize__mm(void)
    {
        return m_globalMapSquareSize__mm;
    }

    uint32_t GET_globalMapSquareSize__pixel(void)
    {
        return (uint32_t)m_globalMap.m_opti_globalMapSquareSize__pixel;
    }

    uint32_t GET_navMapSquareSize__pixel(void)
    {
        return (uint32_t)m_navMap.m_opti_globalMapSquareSize__pixel;
    }

    double GET_currentPosX__mm(void)
    {
        return m_currentPosX__mm;
    }

    uint32_t GET_currentPosX__pixel(void)
    {
        return m_globalMap.m_currentPosX__pixel;
    }

    double GET_currentPosY__mm(void)
    {
        return m_currentPosY__mm;
    }

    uint32_t GET_currentPosY__pixel(void)
    {
        return m_globalMap.m_currentPosY__pixel;
    }

    double GET_currentPosAngle__rad(void)
    {
        return m_currentPosAngle__rad;
    }

    double GET_currentPosAngle__deg(void)
    {
        return m_currentPosAngle__rad * MATHS_CONV_RAD_2_DEG;
    }

    double GET_appliedPosCorrectionX__mm(void)
    {
        return m_appliedDxErrValue__mm;
    }

    double GET_appliedPosCorrectionY__mm(void)
    {
        return m_appliedDyErrValue__mm;
    }

    double GET_appliedPosCorrectionAngle__rad(void)
    {
        return m_appliedDangleErrValue__rad;
    }

    double GET_appliedPosCorrectionAngle__deg(void)
    {
        return (m_appliedDangleErrValue__rad * MATHS_CONV_RAD_2_DEG);
    }

    void GET_lastGlobalMapUpgradedZone(uint32_t * xMin, uint32_t * xMax, uint32_t * yMin, uint32_t * yMax)
    {
        *xMin = m_globalMap.m_opti_globalMapUpdateZoneXmin__pixel;
        *xMax = m_globalMap.m_opti_globalMapUpdateZoneXmax__pixel;
        *yMin = m_globalMap.m_opti_globalMapUpdateZoneYmin__pixel;
        *yMax = m_globalMap.m_opti_globalMapUpdateZoneYmax__pixel;
    }

    void GET_lastNavMapUpgradedZone(uint32_t * xMin, uint32_t * xMax, uint32_t * yMin, uint32_t * yMax)
    {
        *xMin = m_navMap.m_opti_globalMapUpdateZoneXmin__pixel;
        *xMax = m_navMap.m_opti_globalMapUpdateZoneXmax__pixel;
        *yMin = m_navMap.m_opti_globalMapUpdateZoneYmin__pixel;
        *yMax = m_navMap.m_opti_globalMapUpdateZoneYmax__pixel;
    }

    uint32_t GET_nbMapUpdatePassSinceLastRead()
    {
        uint32_t tmp = m_nbMapUpdatePassSinceLastRead;
        m_nbMapUpdatePassSinceLastRead = 0;
        return tmp;
    }

    bool GET_isBusy()
    {
        return m_isBusy;
    }

    // Reset the algo
    void Reset();

    // Add sensor model
    void AddSensorModel(int sensorModelId, struct_ParamsForUsingLidar params)
    {
        m_paramsForUsingLidar[sensorModelId] = params;
    }


    // Do one step of sensor fusion
    void IntegrateNewSensorData(uint32_t * tabOfDistMeasures__mm, double * tabOfAngleMeasures__cos, double * tabOfAngleMeasures__sin, uint32_t nbOfMeasures, int paramIndex);

private:

    // Semaphore mimic
    // But stay architecture independant
    volatile bool m_isBusy = false;

    // SENSOR MODEL
    // ======================================================================================
    // Max nb of measures per rotation of the Lidar
    static const uint32_t LIDAR_MAX_NB_OF_MEASURES_PER_ROTATION = 5000;

    //uint32_t m_lidarMinReliableMeasuredDist__mm = 0;
    double m_opti_squareOf_lidarMinReliableMeasuredDist__mm = 0;
    //uint32_t m_lidarMinReliableMeasuredDist__pixel = 0;

    //uint32_t m_lidarMaxReliableMeasuredDist__mm = 0;
    double m_opti_squareOf_lidarMaxReliableMeasuredDist__mm = 0;
    //uint32_t m_lidarMaxReliableMeasuredDist__pixel = 0;

    // From this position to m_LidarMaxReliableMeasuredDist__pixel
    // We will add virtual measures from 0 additional measure to
    //static const uint32_t MAX_NB_OF_ADDED_VIRTUAL_MEASURES = 20;
    //const uint32_t MAX_DIST_BETWEEN_MEASURES_TO_ADD_VIRTUAL_MEASURES__MM = 200;
    //const uint32_t SQUARE_OF_MAX_DIST_BETWEEN_MEASURES_TO_ADD_VIRTUAL_MEASURES__MM = MAX_DIST_BETWEEN_MEASURES_TO_ADD_VIRTUAL_MEASURES__MM * MAX_DIST_BETWEEN_MEASURES_TO_ADD_VIRTUAL_MEASURES__MM;
    //uint32_t m_lidarMinDistToAddVirtualMeasures__mm = 0;
    //uint32_t m_lidarMinDistToAddVirtualMeasures__pixel = 0;
    //uint32_t m_maxNbOfVirtualMeasuresAtMaxDist = 0;
    //uint32_t m_opti_maxNbOfVirtualMeasuresAtMaxDist_minus1 = 0;

    //uint32_t m_lidarDistFromMinDistToAddVirtualMeasuresToMaxReliableMeasuredDist__mm = 0;

    // POSITION ERROR FAST ESTIMATION MODEL
    // It gives an fast estimation of the position
    // ======================================================================================
    static const uint32_t NB_OF_VALUES_OF_L1_DX_ERR_MODEL = 11;
    const double m_tabOfL1DxErrModel__mm[NB_OF_VALUES_OF_L1_DX_ERR_MODEL] =
    {
        0.0,
        25.0, 50.0, 75.0, 100.0, 125.0,
        -25.0, -50.0, -75.0, -100.0, -125.0
    };

    static const uint32_t NB_OF_VALUES_OF_L1_DY_ERR_MODEL = 11;
    const double m_tabOfL1DyErrModel__mm[NB_OF_VALUES_OF_L1_DY_ERR_MODEL] =
    {
        0.0,
        25.0, 50.0, 75.0, 100.0, 125.0,
        -25.0, -50.0, -75.0, -100.0, -125.0
    };

    static const uint32_t NB_OF_VALUES_OF_L1_DTHETA_ERR_MODEL = 11;
    // Warning, for convenient, the values are in deg
    // But they will be converted to rad at the beginning
    double m_tabOfL1DThetaErrModel__rad[NB_OF_VALUES_OF_L1_DTHETA_ERR_MODEL]=
    {
        0.0,
        2.5, 5.0, 7.5, 10.0, 12.5,
        -2.5, -5.0, -7.5, -10.0, -12.5
    };

    // Precomputed cos and sin value of the Angle model
    double m_opti_cached_tabOfCosOfL1ThetaErrModel[NB_OF_VALUES_OF_L1_DTHETA_ERR_MODEL] = {0.0};
    double m_opti_cached_tabOfSinOfL1ThetaErrModel[NB_OF_VALUES_OF_L1_DTHETA_ERR_MODEL] = {0.0};


    // POSITION ERROR PRECISE ESTIMATION MODEL
    // It gives a precise estimation of the position relative to the fast estimation
    // ======================================================================================
    static const uint32_t NB_OF_VALUES_OF_L2_DX_ERR_MODEL = 9;
    const double m_tabOfL2DxErrModel__mm[NB_OF_VALUES_OF_L2_DX_ERR_MODEL] =
    {
        0.0,
        5.0, 10.0, 15.0, 20.0,
        -5.0, -10.0, -15.0, -20.0
    };

    static const uint32_t NB_OF_VALUES_OF_L2_DY_ERR_MODEL = 9;
    const double m_tabOfL2DyErrModel__mm[NB_OF_VALUES_OF_L2_DY_ERR_MODEL] =
    {
        0.0,
        5.0, 10.0, 15.0, 20.0,
        -5.0, -10.0, -15.0, -20.0
    };

    static const uint32_t NB_OF_VALUES_OF_L2_DTHETA_ERR_MODEL = 9;
    // Warning, for convenient, the values are in deg
    // But they will be converted to rad at the beginning
    double m_tabOfL2DThetaErrModel__rad[NB_OF_VALUES_OF_L2_DTHETA_ERR_MODEL]=
    {
        0.0,
        0.5, 1.0, 1.5, 2.0,
        -0.5, -1.0, -1.5, -2.0
    };

    // Precomputed cos and sin value of the Angle model
    double m_opti_cached_tabOfCosOfL2ThetaErrModel[NB_OF_VALUES_OF_L2_DTHETA_ERR_MODEL] = {0.0};
    double m_opti_cached_tabOfSinOfL2ThetaErrModel[NB_OF_VALUES_OF_L2_DTHETA_ERR_MODEL] = {0.0};


    // POSITION ERROR PRECISE ESTIMATION MODEL
    // It gives a precise estimation of the position relative to the fast estimation
    // ======================================================================================
    static const uint32_t NB_OF_VALUES_OF_L3_DX_ERR_MODEL = 9;
    const double m_tabOfL3DxErrModel__mm[NB_OF_VALUES_OF_L3_DX_ERR_MODEL] =
    {
        0.0,
        1.0, 2.0, 3.0, 4.0,
        -1.0, -2.0, -3.0, -4.0
    };

    static const uint32_t NB_OF_VALUES_OF_L3_DY_ERR_MODEL = 9;
    const double m_tabOfL3DyErrModel__mm[NB_OF_VALUES_OF_L3_DY_ERR_MODEL] =
    {
        0.0,
        1.0, 2.0, 3.0, 4.0,
        -1.0, -2.0, -3.0, -4.0
    };

    static const uint32_t NB_OF_VALUES_OF_L3_DTHETA_ERR_MODEL = 9;
    // Warning, for convenient, the values are in deg
    // But they will be converted to rad at the beginning
    double m_tabOfL3DThetaErrModel__rad[NB_OF_VALUES_OF_L3_DTHETA_ERR_MODEL]=
    {
        0.0,
        0.1, 0.2, 0.3, 0.4,
        -0.1, -0.2, -0.3, -0.4
    };

    // Precomputed cos and sin value of the Angle model
    double m_opti_cached_tabOfCosOfL3ThetaErrModel[NB_OF_VALUES_OF_L3_DTHETA_ERR_MODEL] = {0.0};
    double m_opti_cached_tabOfSinOfL3ThetaErrModel[NB_OF_VALUES_OF_L3_DTHETA_ERR_MODEL] = {0.0};

    // Debug data
    // ======================================================================================
    // Store the correction param of the SLAM algo
    double m_appliedDxErrValue__mm = 0.0;
    double m_appliedDyErrValue__mm = 0.0;
    double m_appliedDangleErrValue__rad = 0.0;

    // SENSOR DATA INPUTS
    // ======================================================================================

    // Laser scan measures by Lidar
    // Each element of the table is a distance measure at an angle
    uint32_t * m_tabOfLidarMeasures__mm = nullptr;
    double * m_tabOfLidarMeasures__cos = nullptr;
    double * m_tabOfLidarMeasures__sin = nullptr;
    uint32_t m_nbOfMeasures = 0;

    // Laser scan converted to the cartesian ref
    // Static table : Hypothese : never bigger than 50 * LIDAR_NB_OF_MEASURES_PER_ROTATION
    double m_tabOfLidarMeasuresInCartesianRef_X__mm[LIDAR_MAX_NB_OF_MEASURES_PER_ROTATION] = {0.0};
    double m_tabOfLidarMeasuresInCartesianRef_Y__mm[LIDAR_MAX_NB_OF_MEASURES_PER_ROTATION] = {0.0};

    double m_opti_UpdateMap_var1[LIDAR_MAX_NB_OF_MEASURES_PER_ROTATION] = {0.0};
    double m_opti_UpdateMap_var2[LIDAR_MAX_NB_OF_MEASURES_PER_ROTATION] = {0.0};
    double m_opti_UpdateMap_var3[LIDAR_MAX_NB_OF_MEASURES_PER_ROTATION] = {0.0};

    int32_t m_nbOfMeasuresTakenIntoAccount = 0;
    int32_t m_opti_nbOfMeasuresTakenIntoAccount_minus1 = 0;

    // This SLAM module can integrate up to 10 sensors
    struct_ParamsForUsingLidar m_paramsForUsingLidar[10];


    // OUTPUT MAP
    // ======================================================================================

    // Describe a map structure
    struct struct_Map
    {
        // Map of the world
        uint8_t * m_ptRawPixelMatrix_8bpp = nullptr;
        uint8_t * m_ptModifiedPixelMatrix_8bpp = nullptr;

        uint32_t INIT_MAP_PIXEL_VALUE;

        uint32_t MM_PER_PIXEL;
        double CONV_PIXEL_2_MM;
        double CONV_MM_2_PIXEL;

        uint32_t m_currentPosX__pixel;
        uint32_t m_currentPosY__pixel;

        uint32_t m_opti_globalMapUpdateZoneXmin__pixel;
        uint32_t m_opti_globalMapUpdateZoneXmax__pixel;
        uint32_t m_opti_globalMapUpdateZoneYmin__pixel;
        uint32_t m_opti_globalMapUpdateZoneYmax__pixel;

        uint32_t OBSTACLES_WIDTH__MM;
        uint32_t OBSTACLES_HALF_WIDTH__PIXEL;

        int32_t m_opti_globalMapSquareSize__pixel;
        int32_t m_opti_minus_globalMapSideSize__pixel;
        int32_t m_opti_globalMapSideSize_minus1__pixel;

        // How fast a detection will affect the map
        // Bigger value will effect faster
        int32_t RAY_TRACE_ALPHA_MODEL;
        int32_t m_opti_256MinusAlphaModel;
    };

    struct_Map m_globalMap;
    struct_Map m_navMap;

    // The map is a square with the following side size
    uint32_t m_globalMapSquareSize__mm = 0;


    // Current position on the global map
    double m_currentPosX__mm = 0.0;
    double m_currentPosY__mm = 0.0;
    double m_currentPosAngle__rad = 0.0;

    // Optimization
    double m_opti_currentPosAngle__cos = 0.0;
    double m_opti_currentPosAngle__sin = 0.0;

    // INTERNAL FUNCTIONS
    // ======================================================================================

    // Estimate the new position
    bool EstimateNewPosition(int optimizationLevel, enum_EstimationType estimationType);

    // Prepare internal data using the new incoming Lidar data
    bool ProcessLidarData(int offsetX__mm = 0, int offsetY__mm = 0);

    // Check the matching quality of the Lidar data using the given position
    // The "Normal" function does the cached data
    // The "Opti" function reuse the cached data
    // Be carrefull when using the Opti function
    uint64_t ComputeMatching(double xInMm, double yInMm, double preComputedCos, double preComputedSin);
    inline uint64_t Opti_ComputeMatching(double xInMm, double yInMm);
    // Cached data for ComputeMatching(...)
    double m_opti_computeMatching_cached_X[LIDAR_MAX_NB_OF_MEASURES_PER_ROTATION] = {0.0};
    double m_opti_computeMatching_cached_Y[LIDAR_MAX_NB_OF_MEASURES_PER_ROTATION] = {0.0};

    // Update the global map with the Lidar data
    void UpdateMap(struct_Map * ptMap);
    void UpdateMap_Opti(struct_Map * ptMap);

    // Trace one Lidar ray on the global map
    void UpdateMapWithASingleMeasuredPoint(struct_Map * ptMap, int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t xp, int32_t yp);

    // Same than the here before function except it favorize obstacle markage
    void UpdateMapWithASingleMeasuredPointForceBlack(struct_Map * ptMap, int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t xp, int32_t yp);

    void UpdateModifiedMap(struct_Map * ptMap);
    void AddMarginToModifiedMap(struct_Map * ptMap);
    void AddMarginToPoint(struct_Map * ptMap, int32_t xp, int32_t yp);

    // Statistic purpose : Nb of map computation pass since last time the value is requested
    uint32_t m_nbMapUpdatePassSinceLastRead = 0;
};

#endif // C_CORESLAM_REAL_ANGLE_8BPP_MAP_H
