#ifndef C_SERIALCOM_CONSOLE_H
#define C_SERIALCOM_CONSOLE_H

#include <QPlainTextEdit>
#include <QScrollBar>

class C_SerialCom_Console : public QPlainTextEdit
{
    Q_OBJECT

public:
    // Constructor
    explicit C_SerialCom_Console(QWidget *parent = nullptr) : QPlainTextEdit(parent)
    {
        document()->setMaximumBlockCount(100);
        QPalette p = palette();
        p.setColor(QPalette::Base, Qt::black);
        p.setColor(QPalette::Text, Qt::green);
        setPalette(p);
    }

    // Show text on the console
    void WriteDataToScreen(const QByteArray &data)
    {
        insertPlainText(data);

        QScrollBar *bar = verticalScrollBar();
        bar->setValue(bar->maximum());
    }

    // Enable or disable echo
    void SetLocalEcho(bool set)
    {
        m_localEchoEnabled = set;
    }

signals:
    // Some thing has been entered
    void SIG_ReadDataFromScreen(const QByteArray &data);

protected:
    // Standard slots
    //***********************************************************************************
    void keyPressEvent(QKeyEvent *e) override
    {
        switch (e->key()) {
        case Qt::Key_Backspace:
        case Qt::Key_Left:
        case Qt::Key_Right:
        case Qt::Key_Up:
        case Qt::Key_Down:
            break;
        default:
            if (m_localEchoEnabled)
            {
                QPlainTextEdit::keyPressEvent(e);
            }

            emit SIG_ReadDataFromScreen(e->text().toLocal8Bit());
        }
    }

private:
    // Store the echo flag
    bool m_localEchoEnabled = false;
};

#endif // C_SERIALCOM_CONSOLE_H
