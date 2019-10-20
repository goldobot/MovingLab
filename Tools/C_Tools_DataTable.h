#ifndef C_TOOLS_DATATABLE_H
#define C_TOOLS_DATATABLE_H

#include "stdio.h"
#include "stdlib.h"
#include "stddef.h"
#include "stdint.h"
#include "math.h"
#include "string.h"

class C_Tools_DataTable
{
public:
    C_Tools_DataTable(){}

    static uint16_t * AllocArrayU16(int nbRows, int nbCols, uint16_t defaultVal = 0)
    {
        // Alloc memory
        int nbElt = nbRows * nbCols;
        uint16_t * ptTab = (uint16_t *) malloc(nbElt * sizeof(uint16_t));

        // Set default content
        uint16_t * ptTabFill = ptTab;
        for(int i = 0; i < nbElt; i++)
        {
            *ptTabFill = defaultVal;
            ptTabFill++;
        }

        return ptTab;
    }

    static uint8_t * AllocArrayU8(int nbRows, int nbCols, uint8_t defaultVal = 0)
    {
        // Alloc memory
        int nbElt = nbRows * nbCols;
        uint8_t * ptTab = (uint8_t *) malloc(nbElt * sizeof(uint8_t));

        // Set default content
        uint8_t * ptTabFill = ptTab;
        for(int i = 0; i < nbElt; i++)
        {
            *ptTabFill = defaultVal;
            ptTabFill++;
        }

        return ptTab;
    }

    // Copy a zone of data from src to dst
    // Warning : no verification
    static void CopyArrayU8(uint8_t * ptDst, uint8_t * ptSrc, uint32_t width, uint32_t xMin, uint32_t yMin, uint32_t xMax, uint32_t yMax)
    {
        uint8_t * ptReadSrcOrigine = ptSrc + yMin * width + xMin;
        uint8_t * ptWriteDstOrigine = ptDst + yMin * width + xMin;

        // First pass, re copy map data
        for(uint32_t y = yMin; y < yMax; y++)
        {
            uint8_t * ptReadSrc = ptReadSrcOrigine;
            uint8_t * ptWriteDst = ptWriteDstOrigine;

            for(uint32_t x = xMin; x < xMax; x++)
            {
                (*ptWriteDst) = (*ptReadSrc);

                ptReadSrc++;
                ptWriteDst++;
            }

            ptReadSrcOrigine += width;
            ptWriteDstOrigine += width;
        }
    }

    static double * AllocArrayDouble(int nbRows, int nbCols, double defaultVal = 0.0)
    {
        // Alloc memory
        int nbElt = nbRows * nbCols;
        double * ptTab = (double *) malloc(nbElt * sizeof(double));

        // Set default content
        double * ptTabFill = ptTab;
        for(int i = 0; i < nbElt; i++)
        {
            *ptTabFill = defaultVal;
            ptTabFill++;
        }

        return ptTab;
    }

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

};

#endif // C_TOOLS_DATATABLE_H
