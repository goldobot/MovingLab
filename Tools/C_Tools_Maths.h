#ifndef C_TOOLS_MATHS_H
#define C_TOOLS_MATHS_H

#include "stdio.h"
#include "stdlib.h"
#include "stddef.h"
#include "stdint.h"
#include "math.h"
#include "string.h"

// MATHS TOOLS
// ======================================================================================
#define MATHS_CONV_DEG_2_RAD 0.01745329251994329576923690768489
#define MATHS_CONV_RAD_2_DEG 57.295779513082320876798154814105

#define MATHS_PI 3.1415926535897932384626433832795
#define MATHS_MINUS_PI (-MATHS_PI)
#define MATHS_2PI 6.283185307179586476925286766559
#define MATHS_MINUS_2PI (-MATHS_2PI)
#define MATHS_HALF_PI 1.5707963267948966192313216916398
#define MATHS_MINUS_HALF_PI (-MATHS_HALF_PI)

class C_Tools_Maths
{
public:
    C_Tools_Maths(){}


    // Maths function
    // ======================================================================================
    static inline int32_t Opti_floor(double value)
    {
        return (int32_t)(value + 1073741824.0) - 1073741824;
    }

    static inline int32_t Opti_abs(int32_t value)
    {
        return ((value >> 31) | 1) * value;
    }

    static inline uint32_t Opti_round(double value)
    {
        return (uint32_t)(value + 0.5);
    }

    // This function returns the angle in the same reference than the CoreSlam Map ref
    static inline double ComputeAngle(double x0, double y0, double x1, double y1)
    {
        return atan2(y1 - y0, x1 - x0);
    }


    // https://www.codeproject.com/Articles/69941/Best-Square-Root-Method-Algorithm-Function-Precisi
    /*
    double inline __fastcall sqrt14(double n)
    {
        _asm fld qword ptr [esp+4]
        _asm fsqrt
        _asm ret 8
    }
    */
    /*
    double sqrt13(double n)
    {
      __asm{
         fld n
         fsqrt
       }
    }

    */

    // Slower but more precise
    static inline float sqrt1(const float x)
    {
      union
      {
        int i;
        float x;
      } u;
      u.x = x;
      u.i = (1<<29) + (u.i >> 1) - (1<<22);

      // Two Babylonian Steps (simplified from:)
      // u.x = 0.5f * (u.x + x/u.x);
      // u.x = 0.5f * (u.x + x/u.x);
      u.x =       u.x + x/u.x;
      u.x = 0.25f*u.x + x/u.x;

      return u.x;
    }

    // Faster but less accurate
    static inline float sqrt7(float x)
     {
       unsigned int i = *(unsigned int*) &x;
       // adjust bias
       i  += 127 << 23;
       // approximation of square root
       i >>= 1;
       return *(float*) &i;
     }
};

#endif // C_TOOLS_MATHS_H
