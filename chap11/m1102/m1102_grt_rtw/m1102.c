/*
 * m1102.c
 * 
 * Real-Time Workshop code generation for Simulink model "m1102.mdl".
 *
 * Model Version              : 1.2
 * Real-Time Workshop version : 6.1  (R14SP1)  05-Sep-2004
 * C source code generated on : Tue May 10 09:45:00 2005
 */

#include "m1102.h"
#include "m1102_private.h"

#include <stdio.h>
#include "m1102_dt.h"

/* Block signals (auto storage) */
BlockIO_m1102 m1102_B;

/* Block states (auto storage) */
D_Work_m1102 m1102_DWork;

/* Real-time model */
rtModel_m1102 m1102_M_;
rtModel_m1102 *m1102_M = &m1102_M_;

/* Model output function */
void m1102_output(int_T tid)
{

  /* local block i/o variables */

  real_T rtb_SineWave;

  /* Sin: '<Root>/Sine Wave' */
  rtb_SineWave = m1102_P.SineWave_Amp *
    sin(m1102_P.SineWave_Freq * m1102_M->Timing.t[0] + m1102_P.SineWave_Phase) +
    m1102_P.SineWave_Bias;

  /* Gain: '<Root>/Gain' */
  m1102_B.Gain = rtb_SineWave * m1102_P.Gain_Gain;
}

/* Model update function */
void m1102_update(int_T tid)
{

  /* Update absolute time for base rate */

  if(!(++m1102_M->Timing.clockTick0)) ++m1102_M->Timing.clockTickH0;
  m1102_M->Timing.t[0] = m1102_M->Timing.clockTick0 * m1102_M->Timing.stepSize0
    + m1102_M->Timing.clockTickH0 * m1102_M->Timing.stepSize0 * 4294967296.0;

  {
    /* Update absolute timer for sample time: [0.01s, 0.0s] */

    if(!(++m1102_M->Timing.clockTick1)) ++m1102_M->Timing.clockTickH1;
    m1102_M->Timing.t[1] = m1102_M->Timing.clockTick1 *
      m1102_M->Timing.stepSize1 + m1102_M->Timing.clockTickH1 *
      m1102_M->Timing.stepSize1 * 4294967296.0;
  }
}

/* Model initialize function */
void m1102_initialize(boolean_T firstTime)
{

  if (firstTime) {
    /* registration code */
    /* initialize real-time model */
    (void)memset((char_T *)m1102_M, 0, sizeof(rtModel_m1102));

    {
      /* Setup solver object */

      rtsiSetSimTimeStepPtr(&m1102_M->solverInfo, &m1102_M->Timing.simTimeStep);
      rtsiSetTPtr(&m1102_M->solverInfo, &rtmGetTPtr(m1102_M));
      rtsiSetStepSizePtr(&m1102_M->solverInfo, &m1102_M->Timing.stepSize0);
      rtsiSetErrorStatusPtr(&m1102_M->solverInfo, &rtmGetErrorStatus(m1102_M));

      rtsiSetRTModelPtr(&m1102_M->solverInfo, m1102_M);
    }
    rtsiSetSimTimeStep(&m1102_M->solverInfo, MAJOR_TIME_STEP);

    /* Initialize timing info */
    {
      int_T *mdlTsMap = m1102_M->Timing.sampleTimeTaskIDArray;
      mdlTsMap[0] = 0;
      mdlTsMap[1] = 1;
      m1102_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
      m1102_M->Timing.sampleTimes = (&m1102_M->Timing.sampleTimesArray[0]);
      m1102_M->Timing.offsetTimes = (&m1102_M->Timing.offsetTimesArray[0]);
      /* task periods */
      m1102_M->Timing.sampleTimes[0] = (0.0);
      m1102_M->Timing.sampleTimes[1] = (0.01);

      /* task offsets */
      m1102_M->Timing.offsetTimes[0] = (0.0);
      m1102_M->Timing.offsetTimes[1] = (0.0);
    }

    rtmSetTPtr(m1102_M, &m1102_M->Timing.tArray[0]);

    {
      int_T *mdlSampleHits = m1102_M->Timing.sampleHitArray;
      mdlSampleHits[0] = 1;
      mdlSampleHits[1] = 1;
      m1102_M->Timing.sampleHits = (&mdlSampleHits[0]);
    }

    rtmSetTFinal(m1102_M, 10.0);
    m1102_M->Timing.stepSize0 = 0.01;
    m1102_M->Timing.stepSize1 = 0.01;

    /* Setup for data logging */
    {
      static RTWLogInfo rt_DataLoggingInfo;

      m1102_M->rtwLogInfo = &rt_DataLoggingInfo;

      rtliSetLogFormat(m1102_M->rtwLogInfo, 0);

      rtliSetLogMaxRows(m1102_M->rtwLogInfo, 1000);

      rtliSetLogDecimation(m1102_M->rtwLogInfo, 1);

      rtliSetLogVarNameModifier(m1102_M->rtwLogInfo, "rt_");

      rtliSetLogT(m1102_M->rtwLogInfo, "");

      rtliSetLogX(m1102_M->rtwLogInfo, "");

      rtliSetLogXFinal(m1102_M->rtwLogInfo, "");

      rtliSetSigLog(m1102_M->rtwLogInfo, "");

      rtliSetLogXSignalInfo(m1102_M->rtwLogInfo, NULL);

      rtliSetLogXSignalPtrs(m1102_M->rtwLogInfo, NULL);

      rtliSetLogY(m1102_M->rtwLogInfo, "");

      rtliSetLogYSignalInfo(m1102_M->rtwLogInfo, NULL);

      rtliSetLogYSignalPtrs(m1102_M->rtwLogInfo, NULL);
    }

    /* external mode info */
    m1102_M->Sizes.checksums[0] = (2927112342U);
    m1102_M->Sizes.checksums[1] = (3624242581U);
    m1102_M->Sizes.checksums[2] = (4127638090U);
    m1102_M->Sizes.checksums[3] = (2622187984U);

    {
      static const int8_T rtAlwaysEnabled = EXTMODE_SUBSYS_ALWAYS_ENABLED;

      static RTWExtModeInfo rt_ExtModeInfo;
      static const void *sysActives[1];

      m1102_M->extModeInfo = (&rt_ExtModeInfo);
      rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, sysActives);

      sysActives[0] = &rtAlwaysEnabled;

      rteiSetModelMappingInfoPtr(&rt_ExtModeInfo,
       &m1102_M->SpecialInfo.mappingInfo);

      rteiSetChecksumsPtr(&rt_ExtModeInfo, m1102_M->Sizes.checksums);

      rteiSetTPtr(&rt_ExtModeInfo, rtmGetTPtr(m1102_M));
    }

    m1102_M->solverInfoPtr = (&m1102_M->solverInfo);
    m1102_M->Timing.stepSize = (0.01);
    rtsiSetFixedStepSize(&m1102_M->solverInfo, 0.01);
    rtsiSetSolverMode(&m1102_M->solverInfo, SOLVER_MODE_SINGLETASKING);

    {
      /* block I/O */
      void *b = (void *) &m1102_B;
      m1102_M->ModelData.blockIO = (b);

      {

        int_T i;
        b =&m1102_B.Gain;
        for (i = 0; i < 1; i++) {
          ((real_T*)b)[i] = 0.0;
        }
      }
    }
    /* parameters */
    m1102_M->ModelData.defaultParam = ((real_T *) &m1102_P);

    /* data type work */
    m1102_M->Work.dwork = ((void *) &m1102_DWork);
    (void)memset((char_T *) &m1102_DWork, 0, sizeof(D_Work_m1102));

    /* data type transition information */
    {
      static DataTypeTransInfo dtInfo;

      (void)memset((char_T *) &dtInfo, 0, sizeof(dtInfo));
      m1102_M->SpecialInfo.mappingInfo = (&dtInfo);

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
void m1102_terminate(void)
{

  /* External mode */
  rtExtModeShutdown(2);
}

/*========================================================================*
 * Start of GRT compatible call interface                                 *
 *========================================================================*/

void MdlOutputs(int_T tid) {

  m1102_output(tid);
}

void MdlUpdate(int_T tid) {

  m1102_update(tid);
}

void MdlInitializeSizes(void) {
  m1102_M->Sizes.numContStates = (0);   /* Number of continuous states */
  m1102_M->Sizes.numY = (0);            /* Number of model outputs */
  m1102_M->Sizes.numU = (0);            /* Number of model inputs */
  m1102_M->Sizes.sysDirFeedThru = (0); /* The model is not direct feedthrough */
  m1102_M->Sizes.numSampTimes = (2);    /* Number of sample times */
  m1102_M->Sizes.numBlocks = (3);       /* Number of blocks */
  m1102_M->Sizes.numBlockIO = (1);      /* Number of block outputs */
  m1102_M->Sizes.numBlockPrms = (5);    /* Sum of parameter "widths" */
}

void MdlInitializeSampleTimes(void) {
}

void MdlInitialize(void) {
}

void MdlStart(void) {
  MdlInitialize();
}

rtModel_m1102 *m1102(void) {
  m1102_initialize(1);
  return m1102_M;
}

void MdlTerminate(void) {
  m1102_terminate();
}

/*========================================================================*
 * End of GRT compatible call interface                                   *
 *========================================================================*/

