/*
 * rt_nonfinite.c
 *
 * Real-Time Workshop code generation for Simulink model "m903.mdl".
 *
 * Model Version              : 1.8
 * Real-Time Workshop version : 6.1  (R14SP1)  05-Sep-2004
 * C source code generated on : Sat Apr 02 09:22:49 2005
 */
#ifndef _RTW_HEADER_rt_nonfinite_h_
#define _RTW_HEADER_rt_nonfinite_h_

#include <float.h>
#include "rtwtypes.h"

extern real_T rtInf;
extern real_T rtMinusInf;
extern real_T rtNaN;
extern real32_T rtInfF;
extern real32_T rtMinusInfF;
extern real32_T rtNaNF;

extern void rt_InitInfAndNaN(int_T realSize);
extern boolean_T rtIsInf(real_T value);
extern boolean_T rtIsInfF(real32_T value);
extern boolean_T rtIsNaN(real_T value);
extern boolean_T rtIsNaNF(real32_T value);

#endif                                  /* _RTW_HEADER_rt_nonfinite_h_ */
