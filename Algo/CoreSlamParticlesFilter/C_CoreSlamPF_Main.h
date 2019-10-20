#ifndef C_CORESLAM_PF_MAIN_H
#define C_CORESLAM_PF_MAIN_H

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
#include "C_CoreSlamPF_RealAngle_8bppMap.h"
#include "C_CoreSlamPF_UpOrderMatchPosList.h"

// Disable to allow debug and calibration purpose
#define ENABLE_ESTIMATION

// This enable SLAM based on LIDAR Data
// For optimization on low power system, the algo use 8bpp map and lots of tweaks
// The main position estimation can work with or without odometry
class C_CoreSlamPF_Main
{
public:
    // Constructor
    C_CoreSlamPF_Main(uint32_t globalMapSquareSize__mm, uint32_t lidarMinReliableMeasuredDist__mm, uint32_t lidarMaxReliableMeasuredDist__mm, uint32_t lidarMinDistToAddVirtualMeasures__mm, uint32_t maxNbOfVirtualMeasuresAtMaxDist);

    // Destructor
    ~C_CoreSlamPF_Main();

    // Accessors
    // ======================================================================================

    int GET_bestEstimatorIndex(void)
    {
        return m_bestEstimatorIndex;
    }

    uint8_t * GET_ptGlobalMap8bpp(void)
    {
        return m_tabMapEstimators[m_bestEstimatorIndex].GET_ptGlobalMap8bpp();
    }

    uint8_t * GET_ptThnlGlobalMap8bpp(void)
    {
        return m_tabMapEstimators[m_bestEstimatorIndex].GET_ptThnlGlobalMap8bpp();
    }

    uint32_t GET_GlobalMapScale__mmPerPixel(void)
    {
        return m_tabMapEstimators[m_bestEstimatorIndex].GET_GlobalMapScale__mmPerPixel();
    }

    uint32_t GET_ThnlGlobalMapScale__mmPerPixel(void)
    {
        return m_tabMapEstimators[m_bestEstimatorIndex].GET_ThnlGlobalMapScale__mmPerPixel();
    }

    uint32_t GET_globalMapSquareSize__mm(void)
    {
        return m_tabMapEstimators[m_bestEstimatorIndex].GET_globalMapSquareSize__mm();
    }

    uint32_t GET_ThnlGlobalMapSquareSize__mm(void)
    {
        return m_tabMapEstimators[m_bestEstimatorIndex].GET_ThnlGlobalMapSquareSize__mm();
    }

    uint32_t GET_globalMapSquareSize__pixel(void)
    {
        return m_tabMapEstimators[m_bestEstimatorIndex].GET_globalMapSquareSize__pixel();
    }

    uint32_t GET_thnlGlobalMapSquareSize__pixel(void)
    {
        return m_tabMapEstimators[m_bestEstimatorIndex].GET_thnlGlobalMapSquareSize__pixel();
    }

    double GET_currentPosX__mm(void)
    {
        return m_tabMapEstimators[m_bestEstimatorIndex].GET_currentPosX__mm();
    }

    uint32_t GET_currentPosX__pixel(void)
    {
        return m_tabMapEstimators[m_bestEstimatorIndex].GET_currentPosX__pixel();
    }

    double GET_currentPosY__mm(void)
    {
        return m_tabMapEstimators[m_bestEstimatorIndex].GET_currentPosY__mm();
    }

    uint32_t GET_currentPosY__pixel(void)
    {
        return m_tabMapEstimators[m_bestEstimatorIndex].GET_currentPosY__pixel();
    }

    double GET_currentPosAngle__rad(void)
    {
        return m_tabMapEstimators[m_bestEstimatorIndex].GET_currentPosAngle__rad();
    }

    double GET_currentPosAngle__deg(void)
    {
        return m_tabMapEstimators[m_bestEstimatorIndex].GET_currentPosAngle__deg();
    }

    void GET_lastGlobalMapUpgradedZone(uint32_t * xMin, uint32_t * xMax, uint32_t * yMin, uint32_t * yMax)
    {
        m_tabMapEstimators[m_bestEstimatorIndex].GET_lastGlobalMapUpgradedZone(xMin, xMax, yMin, yMax);
    }

    void GET_lastThnlGlobalMapUpgradedZone(uint32_t * xMin, uint32_t * xMax, uint32_t * yMin, uint32_t * yMax)
    {
        m_tabMapEstimators[m_bestEstimatorIndex].GET_lastThnlGlobalMapUpgradedZone(xMin, xMax, yMin, yMax);
    }

    void GetRobotPosition(struct_EstimatedRobotPosition * ptEstimatedRobotPosition)
    {
        m_tabMapEstimators[m_bestEstimatorIndex].GetRobotPosition(ptEstimatedRobotPosition);
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

    // The map estimator
    C_CoreSlamPF_RealAngle_8bppMap m_tabMapEstimators[MAX_NB_OF_MANAGED_MAP_ESTIMATOR];
    // Mark the slot is taken
    bool m_tabMapEstimatorsFreeSlotMarker[MAX_NB_OF_MANAGED_MAP_ESTIMATOR];
    int m_nbOfFreeSlots = 0;

    int m_bestEstimatorIndex = 0;

    // Liste of best match positions
    C_CoreSlamPF_UpOrderMatchPosList m_listOfBestMatchPos;


    // Semaphore mimic
    // But stay architecture independant
    volatile bool m_isBusy = false;

    // SENSOR MODEL
    // ======================================================================================
    // Max nb of measures per rotation of the Lidar
    uint32_t m_lidarMinReliableMeasuredDist__mm = 0;
    uint32_t m_lidarMinReliableMeasuredDist__pixel = 0;

    uint32_t m_lidarMaxReliableMeasuredDist__mm = 0;
    uint32_t m_lidarMaxReliableMeasuredDist__pixel = 0;

    uint32_t m_opti_SQUARE_OF_MAX_DIST_BETWEEN_MEASURES_TO_ADD_VIRTUAL_MEASURES__MM = LIDAR_MAX_DIST_BETWEEN_MEASURES_TO_ADD_VIRTUAL_MEASURES__MM * LIDAR_MAX_DIST_BETWEEN_MEASURES_TO_ADD_VIRTUAL_MEASURES__MM;
    uint32_t m_lidarMinDistToAddVirtualMeasures__mm = 0;
    uint32_t m_lidarMinDistToAddVirtualMeasures__pixel = 0;
    uint32_t m_maxNbOfVirtualMeasuresAtMaxDist = 0;
    uint32_t m_opti_maxNbOfVirtualMeasuresAtMaxDist_minus1 = 0;

    uint32_t m_lidarDistFromMinDistToAddVirtualMeasuresToMaxReliableMeasuredDist__mm = 0;

    // POSITION ERROR ESTIMATION MODEL
    // ======================================================================================
    static const uint32_t NB_OF_VALUES_OF_DX_ERR_MODEL = 21;
    const double m_tabOfDxErrModel__mm[NB_OF_VALUES_OF_DX_ERR_MODEL] =
    {
        0.0,
        1.0, 2.5, 5.0, 7.5, 10.0, 15.0, 20.0, 25.0, 30.0, 40.0,
        -1.0, -2.5, -5.0, -7.5, -10.0, -15.0, -20.0, -25.0, -30.0, -40.0
    };

    static const uint32_t NB_OF_VALUES_OF_DY_ERR_MODEL = 21;
    const double m_tabOfDyErrModel__mm[NB_OF_VALUES_OF_DY_ERR_MODEL] =
    {
        0.0,
        1.0, 2.5, 5.0, 7.5, 10.0, 15.0, 20.0, 25.0, 30.0, 40.0,
        -1.0, -2.5, -5.0, -7.5, -10.0, -15.0, -20.0, -25.0, -30.0, -40.0
    };

    static const uint32_t NB_OF_VALUES_OF_DANGLE_ERR_MODEL = 33;
    // Warning, for convenient, the values are in deg
    // But they will be converted to rad at the beginning
    double m_tabOfDAngleErrModel__rad[NB_OF_VALUES_OF_DANGLE_ERR_MODEL]=
    {
        0.0,
        0.1, 0.2 , 0.3, 0.5, 1.0, 1.5, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 10.0, 12.0, 14.0,
        -0.1, -0.2 , -0.3, -0.5, -1.0, -1.5, -2.0, -3.0, -4.0, -5.0, -6.0, -7.0, -8.0, -10.0, -12.0, -14.0
    };

    // Precomputed cos and sin value of the Angle model
    double m_opti_cached_tabOfCosOfAngleErrModel[NB_OF_VALUES_OF_DANGLE_ERR_MODEL] = {0.0};
    double m_opti_cached_tabOfSinOfAngleErrModel[NB_OF_VALUES_OF_DANGLE_ERR_MODEL] = {0.0};


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
    double m_tabOfLidarMeasuresInCartesianRef_X__mm[LIDAR_MAX_NB_OF_VIRTUAL_MEASURES_AT_MAX_DIST * LIDAR_MAX_NB_MEASURES_PER_REVOLUTION] = {0.0};
    double m_tabOfLidarMeasuresInCartesianRef_Y__mm[LIDAR_MAX_NB_OF_VIRTUAL_MEASURES_AT_MAX_DIST * LIDAR_MAX_NB_MEASURES_PER_REVOLUTION] = {0.0};
    int32_t m_nbOfMeasuresTakenIntoAccount = 0;
    int32_t m_opti_nbOfMeasuresTakenIntoAccount_minus1 = 0;

    // This SLAM module can integrate up to 10 sensors
    struct_ParamsForUsingLidar m_paramsForUsingLidar[10];


    // INTERNAL FUNCTIONS
    // ======================================================================================

    // Prepare internal data using the new incoming Lidar data
    inline bool ProcessLidarData(int offsetX__mm = 0, int offsetY__mm = 0);

    // Estimate the new position
    inline bool EstimateNewPosition(enum_EstimationType estimationType);

    // Statistic purpose : Nb of map computation pass since last time the value is requested
    uint32_t m_nbMapUpdatePassSinceLastRead = 0;
};

#endif // C_CORESLAM_PF_MAIN_H
