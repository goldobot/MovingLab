#ifndef C_TWO_WHEELS_BASE_H
#define C_TWO_WHEELS_BASE_H

#include <QSemaphore>

#include "ui_C_TwoWheelsBase.h"
#include "C_Vesc.h"
#include "C_Tools_System.h"

class C_TwoWheelsBase : public QMainWindow
{
    Q_OBJECT

public:
    // Constructor
    explicit C_TwoWheelsBase(QWidget * ptParent = nullptr);

    enum enum_MvtCmd
    {
        STOP, FORWARD, BACKWARD, TURN_LEFT, TURN_RIGHT, FORWARD_LEFT, FORWARD_RIGHT, BACKWARD_LEFT, BACKWARD_RIGHT, UNKOWN
    };


    const double MOVE_AND_TURN_FACTOR = 1.3;

    // COM port name to use to connect to the device
    bool SetComPortName(const QString & leftVescComPortName, const QString & rightVescComPortName)
    {
        return m_leftVesc.SetComPortName(leftVescComPortName) && m_rightVesc.SetComPortName(rightVescComPortName);
    }

    // Connect to the device
    bool Connect(void)
    {
        return m_leftVesc.Connect() && m_rightVesc.Connect();
    }

    // Disconnect from the device
    bool Disconnect(void)
    {
        bool result1 = m_leftVesc.Disconnect();
        bool result2 = m_rightVesc.Disconnect();

        return result1 && result2;
    }

signals:
    // Closing the window
    void SIG_ClosingWindow(void);

public slots:
    void SLOT_StoreNewCmd(enum_MvtCmd cmdToDo, float speed, float ratio);
    void SLOT_ProcessNewCmd(void);

private :
    // The UI of the object
    Ui::C_TwoWheelsBase m_userInterface;

    // The Left VESC COM port
    C_Vesc m_leftVesc;
    C_Vesc m_rightVesc;

    QSemaphore m_SEM_newCmd;
    enum_MvtCmd m_cmdToDo = UNKOWN;
    float m_cmdToDoSpeed = 0.0;
    float m_cmdToDoRatio = 0.0;

    // Fake timer just to create simplified worker threads
    QTimer m_TIMER_processNewCmd;

private slots:
    // User slots
    //***********************************************************************************
    void SLOT_ClosingLeftMotorWindow(void);
    void SLOT_ClosingRightMotorWindow(void);

    // Standard slots
    //***********************************************************************************
    // Closing the window
    void closeEvent (QCloseEvent * ptEvent);
    void keyPressEvent(QKeyEvent * ptEvent);

    void on_btn_ShowLeftMotor_clicked();
    void on_btn_ShowRightMotor_clicked();
    void on_btn_Forward_clicked(float speed = 300);
    void on_btn_Stop_clicked();
    void on_btn_Backward_clicked(float speed = 300);
    void on_btn_TurnRight_clicked(float speed = 200);
    void on_btn_TurnLeft_clicked(float speed = 200);
    void on_btn_ForwardLeft_clicked(float speed = 300, float ration = 1.3);
    void on_btn_ForwardRight_clicked(float speed = 300, float ration = 1.3);
    void on_btn_BackwardRight_clicked(float speed = 300, float ration = 1.3);
    void on_btn_BackwardLeft_clicked(float speed = 300, float ration = 1.3);
};

#endif // C_TWO_WHEELS_BASE_H
