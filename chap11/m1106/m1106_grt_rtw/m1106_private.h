/*
 * m1106_private.h
 *
 * Real-Time Workshop code generation for Simulink model "m1106.mdl".
 *
 * Model Version              : 1.5
 * Real-Time Workshop version : 6.1  (R14SP1)  05-Sep-2004
 * C source code generated on : Fri Apr 15 09:54:51 2005
 */
#ifndef _RTW_HEADER_m1106_private_h_
#define _RTW_HEADER_m1106_private_h_

#include "rtwtypes.h"

/* Private macros used by the generated code to access rtModel */

#ifndef __RTWTYPES_H__
#error This file requires rtwtypes.h to be included
#else
#ifdef TMWTYPES_PREVIOUSLY_INCLUDED
#error This file requires rtwtypes.h to be included before tmwtypes.h
#else
/* Check for inclusion of an incorrect version of rtwtypes.h */
#ifndef RTWTYPES_ID_C08S16I32L32N32F1
#error This code was generated with a different "rtwtypes.h" than the file included
#endif                                  /* RTWTYPES_ID_C08S16I32L32N32F1 */
#endif                                  /* TMWTYPES_PREVIOUSLY_INCLUDED */
#endif                                  /* __RTWTYPES_H__ */

extern void builderF_Outputs_wrapper(const real_T *u0,
 real_T *y0,
 real_T *y1,
 real_T *y2,
 const real_T *xC);
extern void builderF_Derivatives_wrapper(const real_T *u0,
 const real_T *y0,
 const real_T *y1,
 const real_T *y2,
 real_T *dx,
 real_T *xC);
/* private model entry point functions */
extern void m1106_derivatives(void);

#endif                                  /* _RTW_HEADER_m1106_private_h_ */
