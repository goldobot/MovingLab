#ifndef C_SCANSE_LIDAR_H
#define C_SCANSE_LIDAR_H

#include <QGraphicsPixmapItem>
#include <QSemaphore>

#include "ui_C_ScanseLidar.h"
#include "C_ScanseLidar_Protocol.h"

// Class which manages the ScanseLidar device
// ScanseLidar device is only the Lidar
class C_ScanseLidar : public QMainWindow
{
    Q_OBJECT

public:
    // Constructor
    explicit C_ScanseLidar(QWidget * ptParent = nullptr);

    // COM port name to use to connect to the device
    bool SetComPortName(const QString & comPortName)
    {
        return m_comPort.SetComPortName(comPortName);
    }

    // Connect to the device
    bool Connect(void)
    {
        return m_lidarProtocol.Connect();
    }

    // Disconnect from the device
    bool Disconnect(void)
    {
        return m_lidarProtocol.Disconnect();
    }

    // Is the device connected
    bool IsConnected(void)
    {
        return m_comPort.IsConnected();
    }

    C_ScanseLidar_Protocol * GetProtocol(void)
    {
        return &m_lidarProtocol;
    }


signals:
    // Closing the window
    void SIG_ClosingWindow(void);

private :
    // The UI of the object
    Ui::C_ScanseLidar m_userInterface;

    // The COM port used for connecting to the device
    C_SerialCom m_comPort;

    // The protocol manager
    C_ScanseLidar_Protocol m_lidarProtocol;

    // Representation of the scan
    uint32_t MM_PER_PIXEL = 17;
    double CONV_PIXEL_2_MM = (double)MM_PER_PIXEL;
    double CONV_MM_2_PIXEL = 1.0 / CONV_PIXEL_2_MM;

    int SCANSE_LIDAR_OFFSET_X__pixel = SCANSE_LIDAR_OFFSET_X__mm * CONV_MM_2_PIXEL;
    int SCANSE_LIDAR_OFFSET_Y__pixel = SCANSE_LIDAR_OFFSET_Y__mm * CONV_MM_2_PIXEL;


    // Lidar management
    void DrawLidarScans(void);
    // Refreshing counter
    int m_nbOfScreenRefresh = 0;

    // Lidar data from ScanseLidar
    QSemaphore m_SEM_measuresAvailable;
    uint32_t m_tabMeasures__mm[LIDAR_MAX_NB_MEASURES_PER_REVOLUTION];
    double m_tabMeasures__cos[LIDAR_MAX_NB_MEASURES_PER_REVOLUTION];
    double m_tabMeasures__sin[LIDAR_MAX_NB_MEASURES_PER_REVOLUTION];
    uint32_t m_nbOfMeasures = 0;

    // Lidar view

    // Scene which contains all graphics items
    QGraphicsScene * m_ptLdsScanGrScene;

    // Image showing the Lidar scan
    QImage m_lidarScanImage;
    // Graphic item whihc lets direct access to the scan image
    QGraphicsPixmapItem * m_ptDirectAccessToLidarScanImage;

    // Center of the lidar view
    double m_viewCenterX = 0.0;
    double m_viewCenterY = 0.0;

    // Timer used to monitor the module
    QTimer m_monitoringTimer;


    // Fake timer just to create simplified worker threads
    QTimer m_TIMER_processNewScanData;

private slots:
    // User slots
    //***********************************************************************************
    // The COM port window is closing
    void SLOT_ClosingComPortWindow(void);

    // Lidar data incoming
    void SLOT_StoreNewScanData(int sensorId, uint32_t * tabOfMeasures__mm, double * tabOfMeasures__cos, double * tabOfMeasures__sin, uint32_t nbOfMeasures);
    void SLOT_ProcessNewScanData(void);

    // Check the malfunction of a module
    void SLOT_PeriodicCheckModulesMalFunction();


    // Standard slots
    //***********************************************************************************
    // Closing the window
    void closeEvent (QCloseEvent * ptEvent);

    // Show the COM port window
    void on_btn_ShowComPort_clicked();

    // Connect to the device
    void on_btn_Connect_clicked();

    // Lidar visual zooming
    void on_btn_ZoomIn_clicked();
    void on_btn_ZoomOut_clicked();
    void on_btn_ZoomDefault_clicked();

    // Lidar visual moving
    void on_btn_MoveDownLdsScan_clicked();
    void on_btn_MoveUpLdsScan_clicked();
    void on_btn_MoveLeftLdsScan_clicked();
    void on_btn_MoveRightLdsScan_clicked();
    void on_btn_CenterLdsScan_clicked();
};

#endif // C_SCANSE_LIDAR_H
