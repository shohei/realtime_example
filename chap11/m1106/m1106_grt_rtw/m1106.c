/*
 * m1106.c
 * 
 * Real-Time Workshop code generation for Simulink model "m1106.mdl".
 *
 * Model Version              : 1.5
 * Real-Time Workshop version : 6.1  (R14SP1)  05-Sep-2004
 * C source code generated on : Fri Apr 15 09:54:51 2005
 */

#include "m1106.h"
#include "m1106_private.h"

#include <stdio.h>
#include "m1106_dt.h"

/* Block signals (auto storage) */
BlockIO_m1106 m1106_B;

/* Continuous states */
ContinuousStates_m1106 m1106_X;

/* Solver Matrices */

/* A and B matrices used by ODE3 fixed-step solver */
static const real_T rt_ODE3_A[3] = {
  1.0/2.0, 3.0/4.0, 1.0
};
static const real_T rt_ODE3_B[3][3] = {
  { 1.0/2.0, 0.0, 0.0 },
  { 0.0, 3.0/4.0, 0.0 },
  { 2.0/9.0, 1.0/3.0, 4.0/9.0 }
};

/* Block states (auto storage) */
D_Work_m1106 m1106_DWork;

/* Real-time model */
rtModel_m1106 m1106_M_;
rtModel_m1106 *m1106_M = &m1106_M_;

/* This function implements a singletasking scheduler for a system with 2
 * rates.  This function is called by the generated step function, hence the
 * generated code self-manages all its subrates.
 */
static void rate_scheduler(void)
{

  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
}

/* This function updates continuous states using the ODE3 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si , int_T tid)
{
  time_T t = rtsiGetT(si);
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE3_IntgData *id = rtsiGetSolverData(si);
  real_T *y = id->y;
  real_T *f0 = id->f[0];
  real_T *f1 = id->f[1];
  real_T *f2 = id->f[2];
  real_T hB[3];
  int_T i;

  int_T nXc = 15;

  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void)memcpy(y, x, nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  m1106_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }
  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  m1106_output(0);
  m1106_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++) hB[i] = h * rt_ODE3_B[1][i];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }
  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  m1106_output(0);
  m1106_derivatives();

  /* tnew = t + hA(3);
     ynew = y + f*hB(:,3); */
  for (i = 0; i <= 2; i++) hB[i] = h * rt_ODE3_B[2][i];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2]);
  }
  rtsiSetT(si, tnew);

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model output function */
void m1106_output(int_T tid)
{

  /* local block i/o variables */

  real_T rtb_SineWave;

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(m1106_M)) {
    m1106_M->Timing.t[0] = rtsiGetT(&m1106_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(m1106_M)) {
    /* set solver stop time */
    rtsiSetSolverStopTime(&m1106_M->solverInfo,
     ((m1106_M->Timing.clockTick0+1)*m1106_M->Timing.stepSize0));
  }                                     /* end MajorTimeStep */

  /* Sin: '<Root>/Sine Wave' */
  rtb_SineWave = m1106_P.SineWave_Amp *
    sin(m1106_P.SineWave_Freq * m1106_M->Timing.t[0] + m1106_P.SineWave_Phase) +
    m1106_P.SineWave_Bias;

  /* SignalConversion: '<Root>/TmpHiddenBuffer_Feeding_S-Function Builder_AtInput1' incorporates:
   *  Constant: '<Root>/Constant'
   */
  m1106_B.TmpHiddenBuffer_Feeding_SFunct[0] = m1106_P.Constant_Value;
  m1106_B.TmpHiddenBuffer_Feeding_SFunct[1] = rtb_SineWave;
  m1106_B.TmpHiddenBuffer_Feeding_SFunct[2] = m1106_P.Constant_Value;
  m1106_B.TmpHiddenBuffer_Feeding_SFunct[3] = m1106_P.Constant_Value;

  /* S-Function "builderF_wrapper" Block: <Root>/S-Function Builder */

  {
    real_T *pxc = m1106_M->ModelData.contStates;
    builderF_Outputs_wrapper(m1106_B.TmpHiddenBuffer_Feeding_SFunct,
     m1106_B.SFunctionBuilder_o1, m1106_B.SFunctionBuilder_o2,
     m1106_B.SFunctionBuilder_o3, pxc);
  }
}

/* Model update function */
void m1106_update(int_T tid)
{

  if (rtmIsMajorTimeStep(m1106_M)) {
    rt_ertODEUpdateContinuousStates(&m1106_M->solverInfo, 0);
  }

  /* Update absolute time for base rate */

  if(!(++m1106_M->Timing.clockTick0)) ++m1106_M->Timing.clockTickH0;
  m1106_M->Timing.t[0] = m1106_M->Timing.clockTick0 * m1106_M->Timing.stepSize0
    + m1106_M->Timing.clockTickH0 * m1106_M->Timing.stepSize0 * 4294967296.0;

  if (rtmIsMajorTimeStep(m1106_M) &&
   m1106_M->Timing.TaskCounters.TID[1] == 0) {
    /* Update absolute timer for sample time: [0.01s, 0.0s] */

    if(!(++m1106_M->Timing.clockTick1)) ++m1106_M->Timing.clockTickH1;
    m1106_M->Timing.t[1] = m1106_M->Timing.clockTick1 *
      m1106_M->Timing.stepSize1 + m1106_M->Timing.clockTickH1 *
      m1106_M->Timing.stepSize1 * 4294967296.0;
  }

  rate_scheduler();
}

/* Derivatives for root system: '<Root>' */
void m1106_derivatives(void)
{

  /* S-Function "builderF_wrapper" Block: <Root>/S-Function Builder */

  {
    real_T *pxc = m1106_M->ModelData.contStates;
    real_T *dx = m1106_M->ModelData.derivs;
    builderF_Derivatives_wrapper(m1106_B.TmpHiddenBuffer_Feeding_SFunct,
     m1106_B.SFunctionBuilder_o1, m1106_B.SFunctionBuilder_o2,
     m1106_B.SFunctionBuilder_o3, dx, pxc);
  }
}

/* Model initialize function */
void m1106_initialize(boolean_T firstTime)
{

  if (firstTime) {
    /* registration code */
    /* initialize real-time model */
    (void)memset((char_T *)m1106_M, 0, sizeof(rtModel_m1106));

    {
      /* Setup solver object */

      rtsiSetSimTimeStepPtr(&m1106_M->solverInfo, &m1106_M->Timing.simTimeStep);
      rtsiSetTPtr(&m1106_M->solverInfo, &rtmGetTPtr(m1106_M));
      rtsiSetStepSizePtr(&m1106_M->solverInfo, &m1106_M->Timing.stepSize0);
      rtsiSetdXPtr(&m1106_M->solverInfo, &m1106_M->ModelData.derivs);
      rtsiSetContStatesPtr(&m1106_M->solverInfo, &m1106_M->ModelData.contStates);
      rtsiSetNumContStatesPtr(&m1106_M->solverInfo,
       &m1106_M->Sizes.numContStates);
      rtsiSetErrorStatusPtr(&m1106_M->solverInfo, &rtmGetErrorStatus(m1106_M));

      rtsiSetRTModelPtr(&m1106_M->solverInfo, m1106_M);
    }
    rtsiSetSimTimeStep(&m1106_M->solverInfo, MAJOR_TIME_STEP);
    m1106_M->ModelData.intgData.y = m1106_M->ModelData.odeY;
    m1106_M->ModelData.intgData.f[0] = m1106_M->ModelData.odeF[0];
    m1106_M->ModelData.intgData.f[1] = m1106_M->ModelData.odeF[1];
    m1106_M->ModelData.intgData.f[2] = m1106_M->ModelData.odeF[2];
    m1106_M->ModelData.contStates = ((real_T *) &m1106_X);
    rtsiSetSolverData(&m1106_M->solverInfo, (void
      *)&m1106_M->ModelData.intgData);
    rtsiSetSolverName(&m1106_M->solverInfo,"ode3");

    /* Initialize timing info */
    {
      int_T *mdlTsMap = m1106_M->Timing.sampleTimeTaskIDArray;
      mdlTsMap[0] = 0;
      mdlTsMap[1] = 1;
      m1106_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
      m1106_M->Timing.sampleTimes = (&m1106_M->Timing.sampleTimesArray[0]);
      m1106_M->Timing.offsetTimes = (&m1106_M->Timing.offsetTimesArray[0]);
      /* task periods */
      m1106_M->Timing.sampleTimes[0] = (0.0);
      m1106_M->Timing.sampleTimes[1] = (0.01);

      /* task offsets */
      m1106_M->Timing.offsetTimes[0] = (0.0);
      m1106_M->Timing.offsetTimes[1] = (0.0);
    }

    rtmSetTPtr(m1106_M, &m1106_M->Timing.tArray[0]);

    {
      int_T *mdlSampleHits = m1106_M->Timing.sampleHitArray;
      mdlSampleHits[0] = 1;
      mdlSampleHits[1] = 1;
      m1106_M->Timing.sampleHits = (&mdlSampleHits[0]);
    }

    rtmSetTFinal(m1106_M, 10.0);
    m1106_M->Timing.stepSize0 = 0.01;
    m1106_M->Timing.stepSize1 = 0.01;

    /* Setup for data logging */
    {
      static RTWLogInfo rt_DataLoggingInfo;

      m1106_M->rtwLogInfo = &rt_DataLoggingInfo;

      rtliSetLogFormat(m1106_M->rtwLogInfo, 0);

      rtliSetLogMaxRows(m1106_M->rtwLogInfo, 1000);

      rtliSetLogDecimation(m1106_M->rtwLogInfo, 1);

      rtliSetLogVarNameModifier(m1106_M->rtwLogInfo, "rt_");

      rtliSetLogT(m1106_M->rtwLogInfo, "");

      rtliSetLogX(m1106_M->rtwLogInfo, "");

      rtliSetLogXFinal(m1106_M->rtwLogInfo, "");

      rtliSetSigLog(m1106_M->rtwLogInfo, "");

      rtliSetLogXSignalInfo(m1106_M->rtwLogInfo, NULL);

      rtliSetLogXSignalPtrs(m1106_M->rtwLogInfo, NULL);

      rtliSetLogY(m1106_M->rtwLogInfo, "");

      rtliSetLogYSignalInfo(m1106_M->rtwLogInfo, NULL);

      rtliSetLogYSignalPtrs(m1106_M->rtwLogInfo, NULL);
    }

    /* external mode info */
    m1106_M->Sizes.checksums[0] = (4188066653U);
    m1106_M->Sizes.checksums[1] = (3073154716U);
    m1106_M->Sizes.checksums[2] = (1156662660U);
    m1106_M->Sizes.checksums[3] = (1624809808U);

    {
      static const int8_T rtAlwaysEnabled = EXTMODE_SUBSYS_ALWAYS_ENABLED;

      static RTWExtModeInfo rt_ExtModeInfo;
      static const void *sysActives[1];

      m1106_M->extModeInfo = (&rt_ExtModeInfo);
      rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, sysActives);

      sysActives[0] = &rtAlwaysEnabled;

      rteiSetModelMappingInfoPtr(&rt_ExtModeInfo,
       &m1106_M->SpecialInfo.mappingInfo);

      rteiSetChecksumsPtr(&rt_ExtModeInfo, m1106_M->Sizes.checksums);

      rteiSetTPtr(&rt_ExtModeInfo, rtmGetTPtr(m1106_M));
    }

    m1106_M->solverInfoPtr = (&m1106_M->solverInfo);
    m1106_M->Timing.stepSize = (0.01);
    rtsiSetFixedStepSize(&m1106_M->solverInfo, 0.01);
    rtsiSetSolverMode(&m1106_M->solverInfo, SOLVER_MODE_SINGLETASKING);

    {
      /* block I/O */
      void *b = (void *) &m1106_B;
      m1106_M->ModelData.blockIO = (b);

      {

        int_T i;
        b =&m1106_B.TmpHiddenBuffer_Feeding_SFunct[0];
        for (i = 0; i < 19; i++) {
          ((real_T*)b)[i] = 0.0;
        }
      }
    }
    /* parameters */
    m1106_M->ModelData.defaultParam = ((real_T *) &m1106_P);
    /* states */
    {
      real_T *x = (real_T *) &m1106_X;
      m1106_M->ModelData.contStates = (x);
      (void)memset((char_T *)x, 0, sizeof(ContinuousStates_m1106));
    }

    /* data type work */
    m1106_M->Work.dwork = ((void *) &m1106_DWork);
    (void)memset((char_T *) &m1106_DWork, 0, sizeof(D_Work_m1106));

    /* data type transition information */
    {
      static DataTypeTransInfo dtInfo;

      (void)memset((char_T *) &dtInfo, 0, sizeof(dtInfo));
      m1106_M->SpecialInfo.mappingInfo = (&dtInfo);

      dtInfo.numDataTypes = 14;
      dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
      dtInfo.dataTypeNames = &rtDataTypeNames[0];

      /* Block I/O transition table */
      dtInfo.B = &rtBTransTable;

      /* Parameters transition table */
      dtInfo.P = &rtPTransTable;
    }

    /* initialize non-finites */
    rt_InitInfAndNaN(sizeof(real_T));
  }
}

/* Model terminate function */
void m1106_terminate(void)
{

  /* External mode */
  rtExtModeShutdown(2);
}

/*========================================================================*
 * Start of GRT compatible call interface                                 *
 *========================================================================*/

void MdlOutputs(int_T tid) {

  m1106_output(tid);
}

void MdlUpdate(int_T tid) {

  m1106_update(tid);
}

void MdlInitializeSizes(void) {
  m1106_M->Sizes.numContStates = (15); /* Number of continuous states */
  m1106_M->Sizes.numY = (0);            /* Number of model outputs */
  m1106_M->Sizes.numU = (0);            /* Number of model inputs */
  m1106_M->Sizes.sysDirFeedThru = (0); /* The model is not direct feedthrough */
  m1106_M->Sizes.numSampTimes = (2);    /* Number of sample times */
  m1106_M->Sizes.numBlocks = (7);       /* Number of blocks */
  m1106_M->Sizes.numBlockIO = (4);      /* Number of block outputs */
  m1106_M->Sizes.numBlockPrms = (5);    /* Sum of parameter "widths" */
}

void MdlInitializeSampleTimes(void) {
}

void MdlInitialize(void) {

  /* S-Function Block: <Root>/S-Function Builder */

  {
    real_T *xC = m1106_M->ModelData.contStates;

    xC[0] = 1;
    xC[1] = 0;
    xC[2] = 0;
    xC[3] = 0;
    xC[4] = 1;
    xC[5] = 0;
    xC[6] = 0;
    xC[7] = 0;
    xC[8] = 1;
    xC[9] = 0;
    xC[10] = 0;
    xC[11] = 0;
    xC[12] = 0;
    xC[13] = 0;
    xC[14] = 0;
  }
}

void MdlStart(void) {
  MdlInitialize();
}

rtModel_m1106 *m1106(void) {
  m1106_initialize(1);
  return m1106_M;
}

void MdlTerminate(void) {
  m1106_terminate();
}

/*========================================================================*
 * End of GRT compatible call interface                                   *
 *========================================================================*/

