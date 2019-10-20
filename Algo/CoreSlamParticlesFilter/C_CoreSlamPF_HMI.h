#ifndef C_CORESLAM_PF_HMI_H
#define C_CORESLAM_PF_HMI_H

#include <QMainWindow>
#include <QBrush>
#include <QCloseEvent>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QImage>
#include <Qpainter>
#include <QPen>
#include <QScrollBar>
#include <QTimer>
#include <QWidget>
#include <QElapsedTimer>


#include "ui_C_CoreSlamPF_HMI.h"
#include "C_CoreSlamPF_Main.h"
#include "C_CoreSlamPF_RealAngle_8bppMap.h"


#include "Constants.h"

#include "C_ScanseLidar.h"
#include "C_Slamware.h"

class C_CoreSlamPF_HMI : public QMainWindow
{
    Q_OBJECT

public:
    // Constructor
    explicit C_CoreSlamPF_HMI(QWidget * ptParent = nullptr, C_ScanseLidar * ptScanse = nullptr, C_Slamware * ptSlamware = nullptr);

    // Destructor
    ~C_CoreSlamPF_HMI();

    uint32_t GET_ThnlGlobalMapScale__mmPerPixel(void)
    {
        return m_ptCoreSlam->GET_ThnlGlobalMapScale__mmPerPixel();
    }


public slots:
    void SLOT_StoreNewScanData(int sensorId, uint32_t * tabOfMeasures__mm, double * tabOfMeasures__cos, double * tabOfMeasures__sin, uint32_t nbOfMeasures);
    void SLOT_ProcessNewScanData(void);

signals:
    // Closing the window
    void SIG_ClosingWindow(void);
    void SIG_NewEstimation(double posX__mm, double posY__mm, double posTheta__rad, uint8_t * mapData, uint32_t xMin, uint32_t xMax, uint32_t yMin, uint32_t yMax);

private:

    // Fake timer just to create simplified worker threads
    QTimer m_TIMER_processNewScanData;

    void DrawLidarScans(void);
    void Draw8BppMap(uint8_t * mapData, uint32_t xMin, uint32_t xMax, uint32_t yMin, uint32_t yMax);

    C_ScanseLidar * m_ptScanse;
    C_Slamware * m_ptSlamware;

    // The UI of the object
    Ui::C_CoreSlamPF_HMI m_userInterface;

    // LDS view
    QImage m_Lidar;
    QGraphicsPixmapItem * m_ptLidar;

    // Map view
    QGraphicsScene * m_ptMapGrScene;
    QGraphicsPixmapItem * m_ptMap;

    int m_lastX;
    int m_lastY;
    QGraphicsRectItem * m_ptRect;
    QGraphicsPolygonItem * m_ptPoly;
    QGraphicsEllipseItem * m_ptRobotBase;


    double m_mapScale = 1.0;
    double m_mapViewCenterX = 0.0;
    double m_mapViewCenterY = 0.0;

    // Lidar data from Scanse
    QSemaphore m_SEM_measuresAvailable;
    uint32_t m_tabScanseMeasures__mm[LIDAR_MAX_NB_MEASURES_PER_REVOLUTION];
    double m_tabScanseMeasures__cos[LIDAR_MAX_NB_MEASURES_PER_REVOLUTION];
    double m_tabScanseMeasures__sin[LIDAR_MAX_NB_MEASURES_PER_REVOLUTION];
    uint32_t m_nbOfScanseMeasures = 0;
    int m_sensorId = 0;

    C_CoreSlamPF_Main * m_ptCoreSlam = nullptr;
    QImage m_coreSlamMap;

    int m_count = 0;

    uint32_t m_tabConvSlamMapPixelToRgbPixel[256];

    // Estimate the frame rate
    QElapsedTimer m_estimationRateTimer;

    void UpdateHMI();

private slots:

    // Closing the window event
    void closeEvent (QCloseEvent * ptEvent);


    void on_btn_ZoomDefaultMap_clicked();
    void on_btn_CenterMap_clicked();
    void on_btn_ZoomOutMap_clicked();
    void on_btn_ZoomInMap_clicked();
    void on_btn_MoveRightMap_clicked();
    void on_btn_MoveLeftMap_clicked();
    void on_btn_MoveDownMap_clicked();
    void on_btn_MoveUpMap_clicked();
    void on_btn_ResetSlam_clicked();
};

#endif // C_CORESLAM_PF_HMI_H
