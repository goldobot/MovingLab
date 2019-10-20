#ifndef C_NEATO_XV_H
#define C_NEATO_XV_H

#include <QGraphicsPixmapItem>

#include "ui_C_NeatoXV.h"
#include "C_NeatoXV_Protocol.h"

// Class which manages the Neato XV device
// Neato XV device is the whole commercial robot
class C_NeatoXV : public QMainWindow
{
    Q_OBJECT

public:
    // Constructor
    explicit C_NeatoXV(QWidget * ptParent = nullptr);

    // COM port name to use to connect to the device
    bool SetComPortName(const QString & comPortName)
    {
        return m_comPort.SetComPortName(comPortName);
    }

    // Connect to the device
    bool Connect(void)
    {
        return m_protocol.Connect();
    }

    // Disconnect from the device
    bool Disconnect(void)
    {
        return m_protocol.Disconnect();
    }

    // Is the device connected
    bool IsConnected(void)
    {
        return m_comPort.IsConnected();
    }

    C_NeatoXV_Protocol * GetProtocol(void)
    {
        return &m_protocol;
    }

signals:
    // Closing the window
    void SIG_ClosingWindow(void);

private :
    // The UI of the object
    Ui::C_NeatoXV m_userInterface;

    // The COM port used for connecting to the device
    C_SerialCom m_comPort;

    // The protocol manager
    C_NeatoXV_Protocol m_protocol;

    // Lidar management
    void DrawLidarScans(void);
    // Refreshing counter
    int m_nbOfScreenRefresh = 0;

    // Lidar data from Neato
    uint32_t m_tabLidarDistMeasures__mm[LIDAR_NB_MEASURES_PER_REVOLUTION];
    double m_lidarMotorSpeed;

    // Lidar positionning on the robot
    const int NEATO_LIDAR_OFFSET_X__mm = 35;
    const int NEATO_LIDAR_OFFSET_X__scaled = static_cast <int>(NEATO_LIDAR_OFFSET_X__mm * 0.06);
    const int NEATO_LIDAR_OFFSET_Y__mm = -20;
    const int NEATO_LIDAR_OFFSET_Y__scaled = static_cast <int>(NEATO_LIDAR_OFFSET_Y__mm * 0.06);

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

    // Optimization
    void InitPrecomputedData(void);
    double m_tabCosAngle[LIDAR_NB_MEASURES_PER_REVOLUTION];
    double m_tabSinAngle[LIDAR_NB_MEASURES_PER_REVOLUTION];

    // Timer used to monitor the module
    QTimer m_monitoringTimer;

private slots:
    // User slots
    //***********************************************************************************
    // The COM port window is closing
    void SLOT_ClosingComPortWindow(void);

    // Lidar data incoming
    void SLOT_StoreNewScanData(uint32_t tabOfMeasures__mm[LIDAR_NB_MEASURES_PER_REVOLUTION], double scanFreq);

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

#endif // C_NEATO_XV_H
