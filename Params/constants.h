#ifndef CONSTANTS_H
#define CONSTANTS_H

// GLOBAL MAP MODEL
// ======================================================================================
// The estimated map is a square with the given side size
#define GLOBAL_MAP_SIDE_SIZE__MM                                         30000

// ROBOT MODEL
// ======================================================================================
// Radius of the robot base
#define ROBOT_BASE_RADIUS__MM                                            210.0

// GENERAL LIDAR MODEL
// ======================================================================================
// Max nb of measure per lidar turn
#define LIDAR_MAX_NB_MEASURES_PER_REVOLUTION                            5000
// Measure greater than this value is considered as not realiable
#define LIDAR_MIN_RELIABLE_MESURED_DISTANCE__MM                         150
// Measure greater than this value is considered as not realiable
#define LIDAR_MAX_RELIABLE_MESURED_DISTANCE__MM                         10000
// Min distance of the measured obstacle to allow adding virtual obtacles
#define LIDAR_MIN_DIST_TO_ADD_VIRTUAL_MEASURES__MM                      10000
// The number of added virtual obstacle is proportionnal to the distance
// At max distance, the number of allowed virtual obtacle
#define LIDAR_MAX_NB_OF_VIRTUAL_MEASURES_AT_MAX_DIST                    20
// If 2 obstacles is so far, so we do not add virtual obstacles
#define LIDAR_MAX_DIST_BETWEEN_MEASURES_TO_ADD_VIRTUAL_MEASURES__MM     200

// SCANSE LIDAR MODEL
// ======================================================================================
// ID of the lidar scanner
#define SCANSE_LIDAR_ID                                                 0
// Position of the center of the lidar compared to the center of the robot
#define SCANSE_LIDAR_OFFSET_X__mm                                       30
#define SCANSE_LIDAR_OFFSET_Y__mm                                       0

// SLAMWARE LIDAR MODEL
// ======================================================================================
// ID of the lidar scanner
#define SLAMWARE_LIDAR_ID                                               1
// Position of the center of the lidar compared to the center of the robot
#define SLAMWARE_LIDAR_OFFSET_X__mm                                     0
#define SLAMWARE_LIDAR_OFFSET_Y__mm                                     0

// SLAM MODEL
// ======================================================================================
// Min number of measurement to allow estimation using the lidar scan
#define MIN_NB_OF_POINTS_TO_ALLOW_POS_ESTIMATION                        10
// Max number of manageable map estimator at the same time
#define MAX_NB_OF_MANAGED_MAP_ESTIMATOR                                 3

// Navigation map content convention
#define NAV_MAP_OBSTACLE_PIXEL_VALUE                                    0

#define NAV_MAP_OBSTACLE_MARGIN_1_PIXEL_VALUE                           50
#define NAV_MAP_OBSTACLE_MARGIN_1_EXPAND_COST                           50

#define NAV_MAP_OBSTACLE_MARGIN_2_PIXEL_VALUE                           128
#define NAV_MAP_OBSTACLE_MARGIN_2_EXPAND_COST                           5

#define NAV_MAP_NO_OBSTACLE_EXPAND_COST                                 1

// PATH FINDER MODEL
// ======================================================================================
#define PATHFINDER_MAX_NB_ITER_OF_SEARCH_LOOP                           50000

#endif // CONSTANTS_H
