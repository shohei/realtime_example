/*
 * m1103.c
 * 
 * Real-Time Workshop code generation for Simulink model "m1103.mdl".
 *
 * Model Version              : 1.2
 * Real-Time Workshop version : 6.1  (R14SP1)  05-Sep-2004
 * C source code generated on : Tue May 10 10:14:56 2005
 */

#include "m1103.h"
#include "m1103_private.h"

#include <stdio.h>
#include "m1103_dt.h"

/* Block signals (auto storage) */
BlockIO_m1103 m1103_B;

/* Block states (auto storage) */
D_Work_m1103 m1103_DWork;

/* Real-time model */
rtModel_m1103 m1103_M_;
rtModel_m1103 *m1103_M = &m1103_M_;

/* Model output function */
void m1103_output(int_T tid)
{

  /* local block i/o variables */

  real_T rtb_SineWave;

  /* Sin: '<Root>/Sine Wave' */
  rtb_SineWave = m1103_P.SineWave_Amp *
    sin(m1103_P.SineWave_Freq * m1103_M->Timing.t[0] + m1103_P.SineWave_Phase) +
    m1103_P.SineWave_Bias;

  /* Gain: '<Root>/Gain' */
  m1103_B.Gain = rtb_SineWave * m1103_P.Gain_Gain;
}

/* Model update function */
void m1103_update(int_T tid)
{

  /* Update absolute time for base rate */

  if(!(++m1103_M->Timing.clockTick0)) ++m1103_M->Timing.clockTickH0;
  m1103_M->Timing.t[0] = m1103_M->Timing.clockTick0 * m1103_M->Timing.stepSize0
    + m1103_M->Timing.clockTickH0 * m1103_M->Timing.stepSize0 * 4294967296.0;

  {
    /* Update absolute timer for sample time: [0.01s, 0.0s] */

    if(!(++m1103_M->Timing.clockTick1)) ++m1103_M->Timing.clockTickH1;
    m1103_M->Timing.t[1] = m1103_M->Timing.clockTick1 *
      m1103_M->Timing.stepSize1 + m1103_M->Timing.clockTickH1 *
      m1103_M->Timing.stepSize1 * 4294967296.0;
  }
}

/* Model initialize function */
void m1103_initialize(boolean_T firstTime)
{

  if (firstTime) {
    /* registration code */
    /* initialize real-time model */
    (void)memset((char_T *)m1103_M, 0, sizeof(rtModel_m1103));

    {
      /* Setup solver object */

      rtsiSetSimTimeStepPtr(&m1103_M->solverInfo, &m1103_M->Timing.simTimeStep);
      rtsiSetTPtr(&m1103_M->solverInfo, &rtmGetTPtr(m1103_M));
      rtsiSetStepSizePtr(&m1103_M->solverInfo, &m1103_M->Timing.stepSize0);
      rtsiSetErrorStatusPtr(&m1103_M->solverInfo, &rtmGetErrorStatus(m1103_M));

      rtsiSetRTModelPtr(&m1103_M->solverInfo, m1103_M);
    }
    rtsiSetSimTimeStep(&m1103_M->solverInfo, MAJOR_TIME_STEP);

    /* Initialize timing info */
    {
      int_T *mdlTsMap = m1103_M->Timing.sampleTimeTaskIDArray;
      mdlTsMap[0] = 0;
      mdlTsMap[1] = 1;
      m1103_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
      m1103_M->Timing.sampleTimes = (&m1103_M->Timing.sampleTimesArray[0]);
      m1103_M->Timing.offsetTimes = (&m1103_M->Timing.offsetTimesArray[0]);
      /* task periods */
      m1103_M->Timing.sampleTimes[0] = (0.0);
      m1103_M->Timing.sampleTimes[1] = (0.01);

      /* task offsets */
      m1103_M->Timing.offsetTimes[0] = (0.0);
      m1103_M->Timing.offsetTimes[1] = (0.0);
    }

    rtmSetTPtr(m1103_M, &m1103_M->Timing.tArray[0]);

    {
      int_T *mdlSampleHits = m1103_M->Timing.sampleHitArray;
      mdlSampleHits[0] = 1;
      mdlSampleHits[1] = 1;
      m1103_M->Timing.sampleHits = (&mdlSampleHits[0]);
    }

    rtmSetTFinal(m1103_M, 10.0);
    m1103_M->Timing.stepSize0 = 0.01;
    m1103_M->Timing.stepSize1 = 0.01;

    /* Setup for data logging */
    {
      static RTWLogInfo rt_DataLoggingInfo;

      m1103_M->rtwLogInfo = &rt_DataLoggingInfo;

      rtliSetLogFormat(m1103_M->rtwLogInfo, 0);

      rtliSetLogMaxRows(m1103_M->rtwLogInfo, 1000);

      rtliSetLogDecimation(m1103_M->rtwLogInfo, 1);

      rtliSetLogVarNameModifier(m1103_M->rtwLogInfo, "rt_");

      rtliSetLogT(m1103_M->rtwLogInfo, "");

      rtliSetLogX(m1103_M->rtwLogInfo, "");

      rtliSetLogXFinal(m1103_M->rtwLogInfo, "");

      rtliSetSigLog(m1103_M->rtwLogInfo, "");

      rtliSetLogXSignalInfo(m1103_M->rtwLogInfo, NULL);

      rtliSetLogXSignalPtrs(m1103_M->rtwLogInfo, NULL);

      rtliSetLogY(m1103_M->rtwLogInfo, "");

      rtliSetLogYSignalInfo(m1103_M->rtwLogInfo, NULL);

      rtliSetLogYSignalPtrs(m1103_M->rtwLogInfo, NULL);
    }

    /* external mode info */
    m1103_M->Sizes.checksums[0] = (283821504U);
    m1103_M->Sizes.checksums[1] = (1625872310U);
    m1103_M->Sizes.checksums[2] = (2116792508U);
    m1103_M->Sizes.checksums[3] = (2454095611U);

    {
      static const int8_T rtAlwaysEnabled = EXTMODE_SUBSYS_ALWAYS_ENABLED;

      static RTWExtModeInfo rt_ExtModeInfo;
      static const void *sysActives[1];

      m1103_M->extModeInfo = (&rt_ExtModeInfo);
      rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, sysActives);

      sysActives[0] = &rtAlwaysEnabled;

      rteiSetModelMappingInfoPtr(&rt_ExtModeInfo,
       &m1103_M->SpecialInfo.mappingInfo);

      rteiSetChecksumsPtr(&rt_ExtModeInfo, m1103_M->Sizes.checksums);

      rteiSetTPtr(&rt_ExtModeInfo, rtmGetTPtr(m1103_M));
    }

    m1103_M->solverInfoPtr = (&m1103_M->solverInfo);
    m1103_M->Timing.stepSize = (0.01);
    rtsiSetFixedStepSize(&m1103_M->solverInfo, 0.01);
    rtsiSetSolverMode(&m1103_M->solverInfo, SOLVER_MODE_SINGLETASKING);

    {
      /* block I/O */
      void *b = (void *) &m1103_B;
      m1103_M->ModelData.blockIO = (b);

      {

        int_T i;
        b =&m1103_B.Gain;
        for (i = 0; i < 1; i++) {
          ((real_T*)b)[i] = 0.0;
        }
      }
    }
    /* parameters */
    m1103_M->ModelData.defaultParam = ((real_T *) &m1103_P);

    /* data type work */
    m1103_M->Work.dwork = ((void *) &m1103_DWork);
    (void)memset((char_T *) &m1103_DWork, 0, sizeof(D_Work_m1103));

    /* data type transition information */
    {
      static DataTypeTransInfo dtInfo;

      (void)memset((char_T *) &dtInfo, 0, sizeof(dtInfo));
      m1103_M->SpecialInfo.mappingInfo = (&dtInfo);

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
void m1103_terminate(void)
{

  /* External mode */
  rtExtModeShutdown(2);
}

/*========================================================================*
 * Start of GRT compatible call interface                                 *
 *========================================================================*/

void MdlOutputs(int_T tid) {

  m1103_output(tid);
}

void MdlUpdate(int_T tid) {

  m1103_update(tid);
}

void MdlInitializeSizes(void) {
  m1103_M->Sizes.numContStates = (0);   /* Number of continuous states */
  m1103_M->Sizes.numY = (0);            /* Number of model outputs */
  m1103_M->Sizes.numU = (0);            /* Number of model inputs */
  m1103_M->Sizes.sysDirFeedThru = (0); /* The model is not direct feedthrough */
  m1103_M->Sizes.numSampTimes = (2);    /* Number of sample times */
  m1103_M->Sizes.numBlocks = (3);       /* Number of blocks */
  m1103_M->Sizes.numBlockIO = (1);      /* Number of block outputs */
  m1103_M->Sizes.numBlockPrms = (5);    /* Sum of parameter "widths" */
}

void MdlInitializeSampleTimes(void) {
}

void MdlInitialize(void) {
}

void MdlStart(void) {
  MdlInitialize();
}

rtModel_m1103 *m1103(void) {
  m1103_initialize(1);
  return m1103_M;
}

void MdlTerminate(void) {
  m1103_terminate();
}

/*========================================================================*
 * End of GRT compatible call interface                                   *
 *========================================================================*/

