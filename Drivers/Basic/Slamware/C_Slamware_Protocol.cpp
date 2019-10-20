#include "C_Slamware_Protocol.h"

bool C_Slamware_Protocol::Connect(void)
{
    return false;
}

bool C_Slamware_Protocol::Disconnect(void)
{
    return true;
}


bool C_Slamware_Protocol::FilterMeasures(void)
{
    int32_t dist_2 = 0;
    int32_t dist_1 = 0;
    int32_t dist_0 = 0;

    double angle_2 = 0.0;
    double angle_1 = 0.0;
    double angle_0 = 0.0;

    int cumulPoint = 0;

    int writeIndex = 0;

    // Read the whole table
    // Do 3 points average
    for(int readIndex = 0; readIndex < m_nbOfMeasures; readIndex++)
    {
        // Shift register mecanism
        dist_2 = dist_1;
        dist_1 = dist_0;
        dist_0 = m_tabDistMeasures__mm[readIndex];

        angle_2 = angle_1;
        angle_1 = angle_0;
        angle_0 = m_tabAngleMeasures__rad[readIndex];

        cumulPoint++;

        // First point
        if(cumulPoint == 1)
        {
            m_tabDistMeasures__mm[writeIndex++] = dist_0;
        }

        // At least 2 measures cumulated
        if(cumulPoint >= 2)
        {
            // The 2 points are so differents
            if((abs(angle_1 - angle_0) > 2.54) || (abs(dist_1 - dist_0) > 200))
            {
                // Store the cumulated measures
                if(cumulPoint > 2) m_tabDistMeasures__mm[writeIndex++] = dist_1;
                m_tabDistMeasures__mm[writeIndex++] = dist_0;

                cumulPoint = 0;
            }
        }

        // At least 3 measures cumulated (and they are near from each to the others)
        if(cumulPoint > 2)
        {
            m_tabDistMeasures__mm[writeIndex++] = (dist_2 + dist_1 + dist_0) / 3;
        }
    }


    // There remains cumulated point
    if(cumulPoint >= 2)
    {
        m_tabDistMeasures__mm[writeIndex++] = dist_0;
    }

    return true;
}

void C_Slamware_Protocol::SLOT_ProcessReceivedData(const QByteArray &data)
{
    m_storedData.append(data);

    struct_Measures oneMeasure;

    while(C_Tools_System::ExtractU8(m_storedData, &oneMeasure, sizeof (oneMeasure)))
    {
        // First measure of a new revolution
        if(oneMeasure.angle__rad >= 100)
        {
            // Filter the measurements
            //FilterMeasures();

            // Publish the previous measures
            if(m_nbOfMeasures > 0)
            {
                // For optimization purpose, compute the sin and cos because everyone need cos and sin
                double * ptAngle__rad = m_tabAngleMeasures__rad;
                double * ptAngle__cos = m_tabAngleMeasures__cos;
                double * ptAngle__sin = m_tabAngleMeasures__sin;

                for(int i = 0; i < m_nbOfMeasures; i++)
                {
                    *ptAngle__cos = qFastCos(*ptAngle__rad);
                    *ptAngle__sin = qFastSin(*ptAngle__rad);

                    ptAngle__rad++; ptAngle__cos++; ptAngle__sin++;
                }

                emit SIG_NewLidarData(SLAMWARE_LIDAR_ID, m_tabDistMeasures__mm, m_tabAngleMeasures__cos, m_tabAngleMeasures__sin, m_nbOfMeasures);
            }

            // Reset the current measures
            m_nbOfMeasures = 0;

            // Now re build the real value of this first measure
            oneMeasure.angle__rad -= 1000.0;
        }

        // Store the measure
        m_tabDistMeasures__mm[m_nbOfMeasures] = oneMeasure.dist__mm;
        m_tabAngleMeasures__rad[m_nbOfMeasures] = oneMeasure.angle__rad;
        m_nbOfMeasures++;
    }
}


#include "moc_C_Slamware_Protocol.cpp"
