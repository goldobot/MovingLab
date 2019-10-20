#include "C_CoreSlamPF_UpOrderMatchPosList.h"


void C_CoreSlamPF_UpOrderMatchPosList::Add(struct_MatchPos * ptNewMatchPos)
{
    // Allocate memory
    struct_MatchPos * ptAllocatedMemory = allocMemoryKeepingBest();

    // The first item
    if(m_nbOfMatchPos == 1)
    {
        m_ptMatchPosList = ptAllocatedMemory;
    }

    // Copy the item
    ptAllocatedMemory->mapEstimatorId = ptNewMatchPos->mapEstimatorId;
    ptAllocatedMemory->matchingQuality = ptNewMatchPos->matchingQuality;
    ptAllocatedMemory->posX__mm = ptNewMatchPos->posX__mm;
    ptAllocatedMemory->posY__mm = ptNewMatchPos->posY__mm;
    ptAllocatedMemory->posAngle__rad = ptNewMatchPos->posAngle__rad;
    ptAllocatedMemory->posErrX__mm = ptNewMatchPos->posErrX__mm;
    ptAllocatedMemory->posErrY__mm = ptNewMatchPos->posErrY__mm;
    ptAllocatedMemory->posErrAngle__rad = ptNewMatchPos->posErrAngle__rad;

    // Allways null for the moment
    // Because it is just an add into the internal buffer
    // ptAllocatedMemory->ptNextMatchPos = nullptr;
}


void C_CoreSlamPF_UpOrderMatchPosList::OrderLowToHigh(void)
{
    // Something to order
    if(m_nbOfMatchPos > 0)
    {
        // Reset the items markers
        memset(m_opti_markOrderedItem, 0, m_nbOfMatchPos);

        // Number of ordered items
        int nbOfOrderedItem = 0;

        // Pointer to the last best found
        struct_MatchPos * ptLastBestItem = nullptr;

        // Loop until all items are ordered
        while(nbOfOrderedItem < m_nbOfMatchPos)
        {
            // Search for the lowest value
            uint64_t bestItemQuality = UINT64_MAX;
            int bestItemIndex = 0;

            // Scan each item (which is not already ordered)
            for(int itemIndex = 0; itemIndex < m_nbOfMatchPos; itemIndex++)
            {
                // Not already ordered
                if(m_opti_markOrderedItem[itemIndex] == 0)
                {
                    // Better quality (small value)
                    if(m_ptCachedMatchPosList[itemIndex].matchingQuality < bestItemQuality)
                    {
                        bestItemIndex = itemIndex;
                        bestItemQuality = m_ptCachedMatchPosList[itemIndex].matchingQuality ;
                    }
                }
            }

            // We got the best item index

            // If the first, it is the list head
            if (nbOfOrderedItem == 0)
            {
                m_ptMatchPosList = ptLastBestItem = &m_ptCachedMatchPosList[bestItemIndex];
            }

            // Not the first, chain it to the last best
            else
            {
                // Link to the last best
                // Save the best for next iteration
                ptLastBestItem = (ptLastBestItem->ptNextMatchPos = &m_ptCachedMatchPosList[bestItemIndex]);
            }

            // Mark the ordered item
            m_opti_markOrderedItem[bestItemIndex] = 1;

            nbOfOrderedItem++;
        }

        // Next item to the tail of the list shall be set to null
        ptLastBestItem->ptNextMatchPos = nullptr;
    }
}


struct_MatchPos * C_CoreSlamPF_UpOrderMatchPosList::allocMemoryKeepingBest()
{
    // Has room in static memory
    if(m_nbOfMatchPos < MAX_NB_OF_MANAGED_MAP_ESTIMATOR)
    {
        // Inc the number of items in the list
        m_nbOfMatchPos++;

        return &(m_ptCachedMatchPosList[m_nbOfMatchPos-1]);
    }

    // Not enough room
    // Use the room of the worst match pos

    // Search for the lowest value
    uint64_t worstItemQuality = 0;
    int indexOfWorstItem = 0;

    // Scan each item
    for(int itemIndex = 0; itemIndex < m_nbOfMatchPos; itemIndex++)
    {
        // Badder quality (big value)
        if(m_ptCachedMatchPosList[itemIndex].matchingQuality > worstItemQuality)
        {
            indexOfWorstItem = itemIndex;
            worstItemQuality = m_ptCachedMatchPosList[itemIndex].matchingQuality ;
        }
    }

    return &(m_ptCachedMatchPosList[indexOfWorstItem]);
}
