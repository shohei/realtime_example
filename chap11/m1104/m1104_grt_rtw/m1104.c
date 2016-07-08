/*
 * m1104.c
 * 
 * Real-Time Workshop code generation for Simulink model "m1104.mdl".
 *
 * Model Version              : 1.1
 * Real-Time Workshop version : 6.1  (R14SP1)  05-Sep-2004
 * C source code generated on : Fri Apr 15 08:46:24 2005
 */

#include "m1104.h"
#include "m1104_private.h"

#include <stdio.h>
#include "m1104_dt.h"

/* Block signals (auto storage) */
BlockIO_m1104 m1104_B;

/* Block states (auto storage) */
D_Work_m1104 m1104_DWork;

/* Real-time model */
rtModel_m1104 m1104_M_;
rtModel_m1104 *m1104_M = &m1104_M_;

/* Model output function */
void m1104_output(int_T tid)
{

  /* Sin: '<Root>/Sine Wave' */
  m1104_B.SineWave = m1104_P.SineWave_Amp *
    sin(m1104_P.SineWave_Freq * m1104_M->Timing.t[0] + m1104_P.SineWave_Phase) +
    m1104_P.SineWave_Bias;

  /* S-Function "myfunc01_wrapper" Block: <Root>/S-Function Builder */

  myfunc01_Outputs_wrapper(&m1104_B.SineWave, &m1104_B.SFunctionBuilder );
}

/* Model update function */
void m1104_update(int_T tid)
{

  /* Update absolute time for base rate */

  if(!(++m1104_M->Timing.clockTick0)) ++m1104_M->Timing.clockTickH0;
  m1104_M->Timing.t[0] = m1104_M->Timing.clockTick0 * m1104_M->Timing.stepSize0
    + m1104_M->Timing.clockTickH0 * m1104_M->Timing.stepSize0 * 4294967296.0;

  {
    /* Update absolute timer for sample time: [0.01s, 0.0s] */

    if(!(++m1104_M->Timing.clockTick1)) ++m1104_M->Timing.clockTickH1;
    m1104_M->Timing.t[1] = m1104_M->Timing.clockTick1 *
      m1104_M->Timing.stepSize1 + m1104_M->Timing.clockTickH1 *
      m1104_M->Timing.stepSize1 * 4294967296.0;
  }
}

/* Model initialize function */
void m1104_initialize(boolean_T firstTime)
{

  if (firstTime) {
    /* registration code */
    /* initialize real-time model */
    (void)memset((char_T *)m1104_M, 0, sizeof(rtModel_m1104));

    {
      /* Setup solver object */

      rtsiSetSimTimeStepPtr(&m1104_M->solverInfo, &m1104_M->Timing.simTimeStep);
      rtsiSetTPtr(&m1104_M->solverInfo, &rtmGetTPtr(m1104_M));
      rtsiSetStepSizePtr(&m1104_M->solverInfo, &m1104_M->Timing.stepSize0);
      rtsiSetErrorStatusPtr(&m1104_M->solverInfo, &rtmGetErrorStatus(m1104_M));

      rtsiSetRTModelPtr(&m1104_M->solverInfo, m1104_M);
    }
    rtsiSetSimTimeStep(&m1104_M->solverInfo, MAJOR_TIME_STEP);

    /* Initialize timing info */
    {
      int_T *mdlTsMap = m1104_M->Timing.sampleTimeTaskIDArray;
      mdlTsMap[0] = 0;
      mdlTsMap[1] = 1;
      m1104_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
      m1104_M->Timing.sampleTimes = (&m1104_M->Timing.sampleTimesArray[0]);
      m1104_M->Timing.offsetTimes = (&m1104_M->Timing.offsetTimesArray[0]);
      /* task periods */
      m1104_M->Timing.sampleTimes[0] = (0.0);
      m1104_M->Timing.sampleTimes[1] = (0.01);

      /* task offsets */
      m1104_M->Timing.offsetTimes[0] = (0.0);
      m1104_M->Timing.offsetTimes[1] = (0.0);
    }

    rtmSetTPtr(m1104_M, &m1104_M->Timing.tArray[0]);

    {
      int_T *mdlSampleHits = m1104_M->Timing.sampleHitArray;
      mdlSampleHits[0] = 1;
      mdlSampleHits[1] = 1;
      m1104_M->Timing.sampleHits = (&mdlSampleHits[0]);
    }

    rtmSetTFinal(m1104_M, 10.0);
    m1104_M->Timing.stepSize0 = 0.01;
    m1104_M->Timing.stepSize1 = 0.01;

    /* Setup for data logging */
    {
      static RTWLogInfo rt_DataLoggingInfo;

      m1104_M->rtwLogInfo = &rt_DataLoggingInfo;

      rtliSetLogFormat(m1104_M->rtwLogInfo, 0);

      rtliSetLogMaxRows(m1104_M->rtwLogInfo, 1000);

      rtliSetLogDecimation(m1104_M->rtwLogInfo, 1);

      rtliSetLogVarNameModifier(m1104_M->rtwLogInfo, "rt_");

      rtliSetLogT(m1104_M->rtwLogInfo, "");

      rtliSetLogX(m1104_M->rtwLogInfo, "");

      rtliSetLogXFinal(m1104_M->rtwLogInfo, "");

      rtliSetSigLog(m1104_M->rtwLogInfo, "");

      rtliSetLogXSignalInfo(m1104_M->rtwLogInfo, NULL);

      rtliSetLogXSignalPtrs(m1104_M->rtwLogInfo, NULL);

      rtliSetLogY(m1104_M->rtwLogInfo, "");

      rtliSetLogYSignalInfo(m1104_M->rtwLogInfo, NULL);

      rtliSetLogYSignalPtrs(m1104_M->rtwLogInfo, NULL);
    }

    /* external mode info */
    m1104_M->Sizes.checksums[0] = (2052729464U);
    m1104_M->Sizes.checksums[1] = (4124583652U);
    m1104_M->Sizes.checksums[2] = (4122135704U);
    m1104_M->Sizes.checksums[3] = (2771391822U);

    {
      static const int8_T rtAlwaysEnabled = EXTMODE_SUBSYS_ALWAYS_ENABLED;

      static RTWExtModeInfo rt_ExtModeInfo;
      static const void *sysActives[1];

      m1104_M->extModeInfo = (&rt_ExtModeInfo);
      rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, sysActives);

      sysActives[0] = &rtAlwaysEnabled;

      rteiSetModelMappingInfoPtr(&rt_ExtModeInfo,
       &m1104_M->SpecialInfo.mappingInfo);

      rteiSetChecksumsPtr(&rt_ExtModeInfo, m1104_M->Sizes.checksums);

      rteiSetTPtr(&rt_ExtModeInfo, rtmGetTPtr(m1104_M));
    }

    m1104_M->solverInfoPtr = (&m1104_M->solverInfo);
    m1104_M->Timing.stepSize = (0.01);
    rtsiSetFixedStepSize(&m1104_M->solverInfo, 0.01);
    rtsiSetSolverMode(&m1104_M->solverInfo, SOLVER_MODE_SINGLETASKING);

    {
      /* block I/O */
      void *b = (void *) &m1104_B;
      m1104_M->ModelData.blockIO = (b);

      {

        int_T i;
        b =&m1104_B.SineWave;
        for (i = 0; i < 2; i++) {
          ((real_T*)b)[i] = 0.0;
        }
      }
    }
    /* parameters */
    m1104_M->ModelData.defaultParam = ((real_T *) &m1104_P);

    /* data type work */
    m1104_M->Work.dwork = ((void *) &m1104_DWork);
    (void)memset((char_T *) &m1104_DWork, 0, sizeof(D_Work_m1104));

    /* data type transition information */
    {
      static DataTypeTransInfo dtInfo;

      (void)memset((char_T *) &dtInfo, 0, sizeof(dtInfo));
      m1104_M->SpecialInfo.mappingInfo = (&dtInfo);

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
void m1104_terminate(void)
{

  /* External mode */
  rtExtModeShutdown(2);
}

/*========================================================================*
 * Start of GRT compatible call interface                                 *
 *========================================================================*/

void MdlOutputs(int_T tid) {

  m1104_output(tid);
}

void MdlUpdate(int_T tid) {

  m1104_update(tid);
}

void MdlInitializeSizes(void) {
  m1104_M->Sizes.numContStates = (0);   /* Number of continuous states */
  m1104_M->Sizes.numY = (0);            /* Number of model outputs */
  m1104_M->Sizes.numU = (0);            /* Number of model inputs */
  m1104_M->Sizes.sysDirFeedThru = (0); /* The model is not direct feedthrough */
  m1104_M->Sizes.numSampTimes = (2);    /* Number of sample times */
  m1104_M->Sizes.numBlocks = (3);       /* Number of blocks */
  m1104_M->Sizes.numBlockIO = (2);      /* Number of block outputs */
  m1104_M->Sizes.numBlockPrms = (4);    /* Sum of parameter "widths" */
}

void MdlInitializeSampleTimes(void) {
}

void MdlInitialize(void) {
}

void MdlStart(void) {
  MdlInitialize();
}

rtModel_m1104 *m1104(void) {
  m1104_initialize(1);
  return m1104_M;
}

void MdlTerminate(void) {
  m1104_terminate();
}

/*========================================================================*
 * End of GRT compatible call interface                                   *
 *========================================================================*/

