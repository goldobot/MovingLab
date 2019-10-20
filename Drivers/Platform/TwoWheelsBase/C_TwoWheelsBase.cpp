#include "C_TwoWheelsBase.h"

C_TwoWheelsBase::C_TwoWheelsBase(QWidget * ptParent) :
    QMainWindow(ptParent)
{
    // Configure the HMI
    m_userInterface.setupUi(this);

    // COM port used to connect to the VESC
    m_leftVesc.SetWindowTitle("Left Motor");
    m_rightVesc.SetWindowTitle("Right Motor");

    // Closing windows event
    connect(&m_leftVesc, &C_Vesc::SIG_ClosingWindow, this, &C_TwoWheelsBase::SLOT_ClosingLeftMotorWindow);
    connect(&m_rightVesc, &C_Vesc::SIG_ClosingWindow, this, &C_TwoWheelsBase::SLOT_ClosingRightMotorWindow);

    connect(&m_TIMER_processNewCmd, &QTimer::timeout, this, &C_TwoWheelsBase::SLOT_ProcessNewCmd);
}


void C_TwoWheelsBase::closeEvent (QCloseEvent * ptEvent)
{
    Q_UNUSED(ptEvent);

    // Send a signal to the parent
    emit SIG_ClosingWindow();
}

void C_TwoWheelsBase::SLOT_ClosingLeftMotorWindow(void)
{
    m_userInterface.btn_ShowLeftMotor->setText("Show Left Motor");
}

void C_TwoWheelsBase::SLOT_ClosingRightMotorWindow(void)
{
    m_userInterface.btn_ShowRightMotor->setText("Show Right Motor");
}

void C_TwoWheelsBase::on_btn_ShowLeftMotor_clicked()
{
    // Is hidden, so show the window
    if(m_leftVesc.isHidden())
    {
        m_leftVesc.show();
        m_userInterface.btn_ShowLeftMotor->setText("Hide Left Motor");
    }
    else
    {
        // Is shown, so hide the window
        m_leftVesc.hide();
        m_userInterface.btn_ShowLeftMotor->setText("Show Left Motor");
    }
}

void C_TwoWheelsBase::on_btn_ShowRightMotor_clicked()
{
    // Is hidden, so show the window
    if(m_rightVesc.isHidden())
    {
        m_rightVesc.show();
        m_userInterface.btn_ShowRightMotor->setText("Hide Right Motor");
    }
    else
    {
        // Is shown, so hide the window
        m_rightVesc.hide();
        m_userInterface.btn_ShowRightMotor->setText("Show Right Motor");
    }
}

void C_TwoWheelsBase::on_btn_Forward_clicked(float speed)
{
    m_leftVesc.SetRpm(speed);
    m_rightVesc.SetRpm(speed);
}

void C_TwoWheelsBase::on_btn_ForwardLeft_clicked(float speed, float ration)
{
    m_leftVesc.SetRpm(speed);
    m_rightVesc.SetRpm(ration * speed);
}

void C_TwoWheelsBase::on_btn_ForwardRight_clicked(float speed, float ration)
{
    m_leftVesc.SetRpm(ration * speed);
    m_rightVesc.SetRpm(speed);
}

void C_TwoWheelsBase::on_btn_Stop_clicked()
{
    m_leftVesc.SetRpm(0);
    m_rightVesc.SetRpm(0);

    // Hack part
    // As the motor sing when it is stopped
    // Force really stop

    //m_leftVesc.SetCurrent(0);
    //m_rightVesc.SetCurrent(0);

    //C_Tools_System::delay__ms(5);

    //m_leftVesc.SetDuty(0);
    //m_rightVesc.SetDuty(0);
}

void C_TwoWheelsBase::on_btn_Backward_clicked(float speed)
{
    m_leftVesc.SetRpm(-speed);
    m_rightVesc.SetRpm(-speed);
}

void C_TwoWheelsBase::on_btn_BackwardLeft_clicked(float speed, float ration)
{
    m_leftVesc.SetRpm(-speed);
    m_rightVesc.SetRpm(-ration * speed);
}

void C_TwoWheelsBase::on_btn_BackwardRight_clicked(float speed, float ration)
{
    m_leftVesc.SetRpm(-ration * speed);
    m_rightVesc.SetRpm(-speed);
}

void C_TwoWheelsBase::on_btn_TurnRight_clicked(float speed)
{
    m_leftVesc.SetRpm(speed);
    m_rightVesc.SetRpm(-speed);
}

void C_TwoWheelsBase::on_btn_TurnLeft_clicked(float speed)
{
    m_leftVesc.SetRpm(-speed);
    m_rightVesc.SetRpm(speed);
}

void C_TwoWheelsBase::keyPressEvent(QKeyEvent * ptEvent)
{
    int key = ptEvent->key();

    switch (key)
    {
    case Qt::Key_0:
    case Qt::Key_5:
        on_btn_Stop_clicked();
        break;
    case Qt::Key_8:
        on_btn_Forward_clicked();
        break;
    case Qt::Key_2:
        on_btn_Backward_clicked();
        break;
    case Qt::Key_4:
        on_btn_TurnLeft_clicked();
        break;
    case Qt::Key_6:
        on_btn_TurnRight_clicked();
        break;
    case Qt::Key_7:
        on_btn_ForwardLeft_clicked();
        break;
    case Qt::Key_9:
        on_btn_ForwardRight_clicked();
        break;
    case Qt::Key_1:
        on_btn_BackwardLeft_clicked();
        break;
    case Qt::Key_3:
        on_btn_BackwardRight_clicked();
        break;

    default:
        break;
    }
}

void C_TwoWheelsBase::SLOT_StoreNewCmd(enum_MvtCmd cmdToDo, float speed, float ratio)
{
    // No pending previous data to be processed
    if(m_SEM_newCmd.available() == 0)
    {
        // Store new scan data
        // Store the measures for internal uses
        m_cmdToDo = cmdToDo;
        m_cmdToDoSpeed = speed;
        m_cmdToDoRatio = ratio;

        // Signal the available new data
        m_SEM_newCmd.release(1);

        // Avoid using emit because it chain to the SLOT and handle the CPU
        // Use of a timer which is an other thread
        m_TIMER_processNewCmd.start(0);
    }
}

void C_TwoWheelsBase::SLOT_ProcessNewCmd(void)
{
    m_TIMER_processNewCmd.stop();

    // Wait for new available data to process
    if(m_SEM_newCmd.available() > 0)
    {
        // Now process the data
        switch (m_cmdToDo)
        {
        case STOP:
            on_btn_Stop_clicked();
            break;

        case FORWARD:
            on_btn_Forward_clicked(m_cmdToDoSpeed);
            break;

        case BACKWARD:
            on_btn_Backward_clicked(m_cmdToDoSpeed);
            break;

        case TURN_RIGHT:
            on_btn_TurnRight_clicked(m_cmdToDoSpeed);
            break;

        case TURN_LEFT:
            on_btn_TurnLeft_clicked(m_cmdToDoSpeed);
            break;

        case FORWARD_RIGHT:
            on_btn_ForwardRight_clicked(m_cmdToDoSpeed, m_cmdToDoRatio);
            break;

        case FORWARD_LEFT:
            on_btn_ForwardLeft_clicked(m_cmdToDoSpeed, m_cmdToDoRatio);
            break;

        case BACKWARD_RIGHT:
            on_btn_BackwardRight_clicked(m_cmdToDoSpeed, m_cmdToDoRatio);
            break;

        case BACKWARD_LEFT:
            on_btn_BackwardLeft_clicked(m_cmdToDoSpeed, m_cmdToDoRatio);
            break;

        default:
            break;
        }

        // Signal the data has been processed
        m_SEM_newCmd.acquire();
    }
}



#include "moc_C_TwoWheelsBase.cpp"
