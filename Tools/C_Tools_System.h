#ifndef C_TOOLS_SYSTEM_H
#define C_TOOLS_SYSTEM_H

#include "stdio.h"
#include "stdlib.h"
#include "stddef.h"
#include "stdint.h"
#include "math.h"
#include "string.h"

#include <QTimer>
#include <QApplication>

class C_Tools_System
{
public:
    C_Tools_System(){}

    static void FillArrayDouble(double * ptArray, int nbElt, double defaultVal = 0.0)
    {
        // Set default content
        double * ptArrayFill = ptArray;
        for(int i = 0; i < nbElt; i++)
        {
            *ptArrayFill = defaultVal;
            ptArrayFill++;
        }
    }


    // Tool function to wait
    static inline void delay__ms(int waitTime__ms)
    {
        if(waitTime__ms > 0)
        {
            QEventLoop loop;
            QTimer t;
            t.connect(&t, &QTimer::timeout, &loop, &QEventLoop::quit);
            t.start(waitTime__ms);
            loop.exec();
        }
    }


    static inline QByteArray ConvToQByteArray(const void * source, size_t nbOfBytes)
    {
        // Create a shadow buff
        char copyOfSource[4096];

        // Do the copy (type ignore)
        memcpy(copyOfSource, source, nbOfBytes);

        //QByteArray bytesArray = QByteArray(copyOfSource, nbOfBytes);

        return QByteArray(copyOfSource, static_cast<int>(nbOfBytes));
    }

    static inline bool ExtractU8(QByteArray & source, void * dest, size_t nbOfBytes)
    {
        // Not enough data
        if(nbOfBytes > source.length()) return false;

        // Copy the first wanted bytes
        memcpy(dest, source.constData(), nbOfBytes);

        // Now we have copied, so remove the read bytes from the source
        source.remove(0, nbOfBytes);

        return true;
    }

};

#endif // C_TOOLS_SYSTEM_H
