#ifndef C_PATH_FINDER_H
#define C_PATH_FINDER_H

#include <QMainWindow>
#include <QBrush>
#include <QCloseEvent>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QImage>
#include <QPen>
#include <QScrollBar>
#include <QTimer>
#include <QWidget>
#include <QSemaphore>
#include <QElapsedTimer>

#include <qmath.h>

#include "ui_C_PathFinder.h"

#include "C_AStar.h"

#include "Constants.h"

#include "C_Tools_DataTable.h"
#include "C_Tools_Maths.h"
#include "C_TwoWheelsBase.h"

class C_PathFinder : public QMainWindow
{
    Q_OBJECT

public:
    // Constructor
    explicit C_PathFinder(QWidget * ptParent, uint32_t mmPerPixel);

    // Destructor
    ~C_PathFinder(){}

public slots:

    void SLOT_StoreNewEstimation(double posX__mm, double posY__mm, double posTheta__rad, uint8_t * mapData, uint32_t xMin, uint32_t xMax, uint32_t yMin, uint32_t yMax);
    void SLOT_ProcessNewEstimation(void);
    void SLOT_PositionRegulation(void);

signals:
    // Closing the window
    void SIG_ClosingWindow(void);
    void SIG_ExecuteCmd(C_TwoWheelsBase::enum_MvtCmd cmd, float speed = 0.0, float ratio = 1.0);

private:

    // Manage click on the scene
    class MapScene : public QGraphicsScene
    {
    public:
        MapScene(QObject * parent = 0){m_ptParent = parent;}
        ~MapScene(){}

    protected:
        void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    private :
        QObject * m_ptParent;

    };

    // The UI of the object
    Ui::C_PathFinder m_userInterface;

    double CONV_PIXEL_2_MM;
    double CONV_MM_2_PIXEL;

    // Map of the world
    QSemaphore m_SEM_newWorldMapAvailable;
    uint32_t m_worldMapSize__pixel = 0;
    uint8_t * m_ptWorldMapRawData = nullptr;
    uint32_t m_worldMapUpdatedZone_xMin__pixel = 0;
    uint32_t m_worldMapUpdatedZone_xMax__pixel = 0;
    uint32_t m_worldMapUpdatedZone_yMin__pixel = 0;
    uint32_t m_worldMapUpdatedZone_yMax__pixel = 0;

    // Map view
    MapScene * m_ptMapGrScene;
    QGraphicsPixmapItem * m_ptMap;
    QImage m_worldMapImage;


    // Robot position
    double m_robotPosX__pixel = 0.0;
    double m_robotPosY__pixel = 0.0;
    double m_robotAngle__rad = 0.0;

    // Astar algo
    C_AStar m_coreAstar;
    bool m_needPathComputation = false;
    bool m_needPathComputationLast = false;

    // Estimate the frame rate
    QElapsedTimer m_estimationRateTimer;
    int m_numberOfComputationCycles = 0;

    void UpdateHMI();
    void DrawPath(QPainter * qPainter, AStarPathType pathType, QColor color, bool drawLine);

    void DriveTheRobot(void);

    double m_mapScale = 1.0;
    double m_mapViewCenterX = 0.0;
    double m_mapViewCenterY = 0.0;

    // Show the CoreSlam Map
    uint32_t m_currentPathPointId = 0;
    uint32_t m_pathSize = 0;
    bool m_isLastTarget = false;

    uint32_t m_tabConvSlamMapPixelToRgbPixel[256];

    // Fake timer just to create simplified worker threads
    QTimer m_TIMER_processNewMap;

    // Periodic position regulation
    QTimer m_TIMER_positionRegulation;
    bool m_needPositionRegulation = false;
    int m_wantedPosX = 0;
    int m_wantedPosY = 0;
    bool m_wantedPosReached = false;

    float m_LastSpeed = 100.0;
    float CalcSpeed(float desiredSpeed, bool force = false);


private slots:
    // User slots
    //***********************************************************************************

    // Standard slots
    //***********************************************************************************
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

};

#endif // C_PATH_FINDER_H
