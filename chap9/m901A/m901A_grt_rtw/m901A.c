/*
 * m901A.c
 * 
 * Real-Time Workshop code generation for Simulink model "m901A.mdl".
 *
 * Model Version              : 1.1
 * Real-Time Workshop version : 6.1  (R14SP1)  05-Sep-2004
 * C source code generated on : Fri Apr 29 08:34:08 2005
 */

#include "m901A.h"
#include "m901A_private.h"

/* Block signals (auto storage) */
BlockIO_m901A m901A_B;

/* Block states (auto storage) */
D_Work_m901A m901A_DWork;

/* Real-time model */
rtModel_m901A m901A_M_;
rtModel_m901A *m901A_M = &m901A_M_;

/* Model output function */
static void m901A_output(int_T tid)
{

  /* local block i/o variables */

  real_T rtb_Step;

  /* Step: '<Root>/Step' */
  {
    real_T currentTime = m901A_M->Timing.t[0];
    if (currentTime < m901A_P.Step_Time) {
      rtb_Step = m901A_P.Step_Y0;
    } else {
      rtb_Step = m901A_P.Step_YFinal;
    }
  }

  /* Gain: '<Root>/Gain' */
  m901A_B.Gain = rtb_Step * m901A_P.Gain_Gain;

  /* Scope: '<Root>/Scope' */
  {
    real_T u[2];
    u[0] = m901A_M->Timing.t[1];
    u[1] = m901A_B.Gain;
    rt_UpdateLogVar(m901A_DWork.Scope_PWORK.LoggedData, u);
  }
}

/* Model update function */
static void m901A_update(int_T tid)
{

  /* Update absolute time for base rate */

  if(!(++m901A_M->Timing.clockTick0)) ++m901A_M->Timing.clockTickH0;
  m901A_M->Timing.t[0] = m901A_M->Timing.clockTick0 * m901A_M->Timing.stepSize0
    + m901A_M->Timing.clockTickH0 * m901A_M->Timing.stepSize0 * 4294967296.0;

  {
    /* Update absolute timer for sample time: [0.5s, 0.0s] */

    if(!(++m901A_M->Timing.clockTick1)) ++m901A_M->Timing.clockTickH1;
    m901A_M->Timing.t[1] = m901A_M->Timing.clockTick1 *
      m901A_M->Timing.stepSize1 + m901A_M->Timing.clockTickH1 *
      m901A_M->Timing.stepSize1 * 4294967296.0;
  }
}

/* Model initialize function */
void m901A_initialize(boolean_T firstTime)
{

  if (firstTime) {
    /* registration code */
    /* initialize real-time model */
    (void)memset((char_T *)m901A_M, 0, sizeof(rtModel_m901A));

    {
      /* Setup solver object */

      rtsiSetSimTimeStepPtr(&m901A_M->solverInfo, &m901A_M->Timing.simTimeStep);
      rtsiSetTPtr(&m901A_M->solverInfo, &rtmGetTPtr(m901A_M));
      rtsiSetStepSizePtr(&m901A_M->solverInfo, &m901A_M->Timing.stepSize0);
      rtsiSetErrorStatusPtr(&m901A_M->solverInfo, &rtmGetErrorStatus(m901A_M));

      rtsiSetRTModelPtr(&m901A_M->solverInfo, m901A_M);
    }
    rtsiSetSimTimeStep(&m901A_M->solverInfo, MAJOR_TIME_STEP);

    /* Initialize timing info */
    {
      int_T *mdlTsMap = m901A_M->Timing.sampleTimeTaskIDArray;
      mdlTsMap[0] = 0;
      mdlTsMap[1] = 1;
      m901A_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
      m901A_M->Timing.sampleTimes = (&m901A_M->Timing.sampleTimesArray[0]);
      m901A_M->Timing.offsetTimes = (&m901A_M->Timing.offsetTimesArray[0]);
      /* task periods */
      m901A_M->Timing.sampleTimes[0] = (0.0);
      m901A_M->Timing.sampleTimes[1] = (0.5);

      /* task offsets */
      m901A_M->Timing.offsetTimes[0] = (0.0);
      m901A_M->Timing.offsetTimes[1] = (0.0);
    }

    rtmSetTPtr(m901A_M, &m901A_M->Timing.tArray[0]);

    {
      int_T *mdlSampleHits = m901A_M->Timing.sampleHitArray;
      mdlSampleHits[0] = 1;
      mdlSampleHits[1] = 1;
      m901A_M->Timing.sampleHits = (&mdlSampleHits[0]);
    }

    rtmSetTFinal(m901A_M, 10.0);
    m901A_M->Timing.stepSize0 = 0.5;
    m901A_M->Timing.stepSize1 = 0.5;

    /* Setup for data logging */
    {
      static RTWLogInfo rt_DataLoggingInfo;

      m901A_M->rtwLogInfo = &rt_DataLoggingInfo;

      rtliSetLogFormat(m901A_M->rtwLogInfo, 0);

      rtliSetLogMaxRows(m901A_M->rtwLogInfo, 1000);

      rtliSetLogDecimation(m901A_M->rtwLogInfo, 1);

      rtliSetLogVarNameModifier(m901A_M->rtwLogInfo, "rt_");

      rtliSetLogT(m901A_M->rtwLogInfo, "tout");

      rtliSetLogX(m901A_M->rtwLogInfo, "");

      rtliSetLogXFinal(m901A_M->rtwLogInfo, "");

      rtliSetSigLog(m901A_M->rtwLogInfo, "");

      rtliSetLogXSignalInfo(m901A_M->rtwLogInfo, NULL);

      rtliSetLogXSignalPtrs(m901A_M->rtwLogInfo, NULL);

      rtliSetLogY(m901A_M->rtwLogInfo, "");

      rtliSetLogYSignalInfo(m901A_M->rtwLogInfo, NULL);

      rtliSetLogYSignalPtrs(m901A_M->rtwLogInfo, NULL);
    }

    m901A_M->solverInfoPtr = (&m901A_M->solverInfo);
    m901A_M->Timing.stepSize = (0.5);
    rtsiSetFixedStepSize(&m901A_M->solverInfo, 0.5);
    rtsiSetSolverMode(&m901A_M->solverInfo, SOLVER_MODE_SINGLETASKING);

    {
      /* block I/O */
      void *b = (void *) &m901A_B;
      m901A_M->ModelData.blockIO = (b);

      {

        int_T i;
        b =&m901A_B.Gain;
        for (i = 0; i < 1; i++) {
          ((real_T*)b)[i] = 0.0;
        }
      }
    }
    /* parameters */
    m901A_M->ModelData.defaultParam = ((real_T *) &m901A_P);

    /* data type work */
    m901A_M->Work.dwork = ((void *) &m901A_DWork);
    (void)memset((char_T *) &m901A_DWork, 0, sizeof(D_Work_m901A));

    /* initialize non-finites */
    rt_InitInfAndNaN(sizeof(real_T));
  }
}

/* Model terminate function */
void m901A_terminate(void)
{
}

/*========================================================================*
 * Start of GRT compatible call interface                                 *
 *========================================================================*/

void MdlOutputs(int_T tid) {

  m901A_output(tid);
}

void MdlUpdate(int_T tid) {

  m901A_update(tid);
}

void MdlInitializeSizes(void) {
  m901A_M->Sizes.numContStates = (0);   /* Number of continuous states */
  m901A_M->Sizes.numY = (0);            /* Number of model outputs */
  m901A_M->Sizes.numU = (0);            /* Number of model inputs */
  m901A_M->Sizes.sysDirFeedThru = (0); /* The model is not direct feedthrough */
  m901A_M->Sizes.numSampTimes = (2);    /* Number of sample times */
  m901A_M->Sizes.numBlocks = (3);       /* Number of blocks */
  m901A_M->Sizes.numBlockIO = (1);      /* Number of block outputs */
  m901A_M->Sizes.numBlockPrms = (4);    /* Sum of parameter "widths" */
}

void MdlInitializeSampleTimes(void) {
}

void MdlInitialize(void) {
}

void MdlStart(void) {

  /* Scope Block: <Root>/Scope */
  {
    volatile int_T numCols = 2;

    m901A_DWork.Scope_PWORK.LoggedData = rt_CreateLogVar(
      m901A_M->rtwLogInfo,
     rtmGetTFinal(m901A_M),
     m901A_M->Timing.stepSize0,
     &(rtmGetErrorStatus(m901A_M)),
     "ScopeData",
     SS_DOUBLE,
     0,
     0,
     0,
     2,
     1,
     (int_T *)&numCols,
     5000,
     1,
     0.5,
     1);

    if (m901A_DWork.Scope_PWORK.LoggedData == NULL) return;
  }

  MdlInitialize();
}

rtModel_m901A *m901A(void) {
  m901A_initialize(1);
  return m901A_M;
}

void MdlTerminate(void) {
  m901A_terminate();
}

/*========================================================================*
 * End of GRT compatible call interface                                   *
 *========================================================================*/

