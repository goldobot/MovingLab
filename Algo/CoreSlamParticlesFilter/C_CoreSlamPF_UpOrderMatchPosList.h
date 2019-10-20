#ifndef C_CORESLAM_PF_UP_ORDER_MATCH_POS_LIST_H
#define C_CORESLAM_PF_UP_ORDER_MATCH_POS_LIST_H

// Manage a list of positions which match the map with a given score


#include "stdio.h"
#include "stdlib.h"
#include "stddef.h"
#include "stdint.h"
#include "math.h"
#include "string.h"

#include "Constants.h"

#include "C_CoreSlamPF_DataStructDef.h"

class C_CoreSlamPF_UpOrderMatchPosList
{
public:
    // Constructor
    C_CoreSlamPF_UpOrderMatchPosList(){}

    // Destructor
    ~C_CoreSlamPF_UpOrderMatchPosList(){}

    // Reset the match list
    void Clear()
    {
        m_nbOfMatchPos = 0;
        m_ptMatchPosList = nullptr;
    }

    // Get the next item from the given one
    // If no given item, take the head
    struct_MatchPos * GetNext(struct_MatchPos * fromItem = nullptr)
    {
        if(fromItem != nullptr)
        {
            return fromItem->ptNextMatchPos;
        }

        return m_ptMatchPosList;
    }

    // Add an new match pos to the internal list
    // Newer fails because we use a static buffer and we delete the worst match if no room
    void Add(struct_MatchPos * ptNewMatchPos);

    // Order the list of matched pos from low value of match quality to high
    // The lowest value means best quality
    // The highest value means worst quality
    void OrderLowToHigh(void);


private:
    // This static list is used to avoid dynamic memory allocation
    struct_MatchPos m_ptCachedMatchPosList[MAX_NB_OF_MANAGED_MAP_ESTIMATOR];
    // Counts the number of total items in the list
    int m_nbOfMatchPos = 0;

    struct_MatchPos * m_ptMatchPosList = nullptr;

    // Optimize the ordering code
    uint8_t m_opti_markOrderedItem[MAX_NB_OF_MANAGED_MAP_ESTIMATOR];


    // Add the given item to the static memory
    // If not enough room, delete the worst match pos
    inline struct_MatchPos * allocMemoryKeepingBest();
};

#endif // C_CORESLAM_PF_UP_ORDER_MATCH_POS_LIST_H
