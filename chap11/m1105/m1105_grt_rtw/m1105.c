/*
 * m1105.c
 * 
 * Real-Time Workshop code generation for Simulink model "m1105.mdl".
 *
 * Model Version              : 1.8
 * Real-Time Workshop version : 6.1  (R14SP1)  05-Sep-2004
 * C source code generated on : Fri Apr 15 09:14:36 2005
 */

#include "m1105.h"
#include "m1105_private.h"

#include <stdio.h>
#include "m1105_dt.h"

/* Block signals (auto storage) */
BlockIO_m1105 m1105_B;

/* Continuous states */
ContinuousStates_m1105 m1105_X;

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
D_Work_m1105 m1105_DWork;

/* Real-time model */
rtModel_m1105 m1105_M_;
rtModel_m1105 *m1105_M = &m1105_M_;

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

  int_T nXc = 6;

  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void)memcpy(y, x, nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  m1105_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }
  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  m1105_output(0);
  m1105_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++) hB[i] = h * rt_ODE3_B[1][i];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }
  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  m1105_output(0);
  m1105_derivatives();

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
void m1105_output(int_T tid)
{

  /* local block i/o variables */

  real_T rtb_Integrator[3];

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(m1105_M)) {
    m1105_M->Timing.t[0] = rtsiGetT(&m1105_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(m1105_M)) {
    /* set solver stop time */
    rtsiSetSolverStopTime(&m1105_M->solverInfo,
     ((m1105_M->Timing.clockTick0+1)*m1105_M->Timing.stepSize0));
  }                                     /* end MajorTimeStep */

  /* Integrator: '<Root>/Integrator1' */
  m1105_B.Integrator1[0] = m1105_X.Integrator1_CSTATE[0];
  m1105_B.Integrator1[1] = m1105_X.Integrator1_CSTATE[1];
  m1105_B.Integrator1[2] = m1105_X.Integrator1_CSTATE[2];

  /* Integrator: '<Root>/Integrator' */
  rtb_Integrator[0] = m1105_X.Integrator_CSTATE[0];
  rtb_Integrator[1] = m1105_X.Integrator_CSTATE[1];
  rtb_Integrator[2] = m1105_X.Integrator_CSTATE[2];

  /* Gain: '<Root>/Gain' */
  m1105_B.Gain[0] = rtb_Integrator[0] * m1105_P.Gain_Gain;
  m1105_B.Gain[1] = rtb_Integrator[1] * m1105_P.Gain_Gain;
  m1105_B.Gain[2] = rtb_Integrator[2] * m1105_P.Gain_Gain;

  if (rtmIsMajorTimeStep(m1105_M) &&
   m1105_M->Timing.TaskCounters.TID[1] == 0) { /* Sample time: [0.01s, 0.0s] */

    /* Constant: '<Root>/Constant' */
    m1105_B.Constant = m1105_P.Constant_Value;
  }

  /* Sin: '<Root>/Sine Wave' */
  m1105_B.SineWave = m1105_P.SineWave_Amp *
    sin(m1105_P.SineWave_Freq * m1105_M->Timing.t[0] + m1105_P.SineWave_Phase) +
    m1105_P.SineWave_Bias;

  if (rtmIsMajorTimeStep(m1105_M) &&
   m1105_M->Timing.TaskCounters.TID[1] == 0) { /* Sample time: [0.01s, 0.0s] */

    /* Constant: '<Root>/Constant1' */
    m1105_B.Constant1 = m1105_P.Constant1_Value;
  }

  /* Gain: '<Root>/Gain1' incorporates:
   *  Gain: '<Root>/Gain2'
   *  Sum: '<Root>/Sum1'
   *  Sum: '<Root>/Sum' */
  m1105_B.Gain1[0] = (m1105_B.Constant - (m1105_B.Integrator1[0] +
    m1105_B.Gain[0] * m1105_P.Gain2_Gain)) * m1105_P.Gain1_Gain;
  m1105_B.Gain1[1] = (m1105_B.SineWave - (m1105_B.Integrator1[1] +
    m1105_B.Gain[1] * m1105_P.Gain2_Gain)) * m1105_P.Gain1_Gain;
  m1105_B.Gain1[2] = (m1105_B.Constant1 - (m1105_B.Integrator1[2] +
    m1105_B.Gain[2] * m1105_P.Gain2_Gain)) * m1105_P.Gain1_Gain;
}

/* Model update function */
void m1105_update(int_T tid)
{

  if (rtmIsMajorTimeStep(m1105_M)) {
    rt_ertODEUpdateContinuousStates(&m1105_M->solverInfo, 0);
  }

  /* Update absolute time for base rate */

  if(!(++m1105_M->Timing.clockTick0)) ++m1105_M->Timing.clockTickH0;
  m1105_M->Timing.t[0] = m1105_M->Timing.clockTick0 * m1105_M->Timing.stepSize0
    + m1105_M->Timing.clockTickH0 * m1105_M->Timing.stepSize0 * 4294967296.0;

  if (rtmIsMajorTimeStep(m1105_M) &&
   m1105_M->Timing.TaskCounters.TID[1] == 0) {
    /* Update absolute timer for sample time: [0.01s, 0.0s] */

    if(!(++m1105_M->Timing.clockTick1)) ++m1105_M->Timing.clockTickH1;
    m1105_M->Timing.t[1] = m1105_M->Timing.clockTick1 *
      m1105_M->Timing.stepSize1 + m1105_M->Timing.clockTickH1 *
      m1105_M->Timing.stepSize1 * 4294967296.0;
  }

  rate_scheduler();
}

/* Derivatives for root system: '<Root>' */
void m1105_derivatives(void)
{
  /* simstruct variables */
  StateDerivatives_m1105 *m1105_Xdot = (StateDerivatives_m1105*)
    m1105_M->ModelData.derivs;

  /* Integrator Block: <Root>/Integrator1 */
  {

    m1105_Xdot->Integrator1_CSTATE[0] = m1105_B.Gain[0];
    m1105_Xdot->Integrator1_CSTATE[1] = m1105_B.Gain[1];
    m1105_Xdot->Integrator1_CSTATE[2] = m1105_B.Gain[2];
  }

  /* Integrator Block: <Root>/Integrator */
  {

    m1105_Xdot->Integrator_CSTATE[0] = m1105_B.Gain1[0];
    m1105_Xdot->Integrator_CSTATE[1] = m1105_B.Gain1[1];
    m1105_Xdot->Integrator_CSTATE[2] = m1105_B.Gain1[2];
  }
}

/* Model initialize function */
void m1105_initialize(boolean_T firstTime)
{

  if (firstTime) {
    /* registration code */
    /* initialize real-time model */
    (void)memset((char_T *)m1105_M, 0, sizeof(rtModel_m1105));

    {
      /* Setup solver object */

      rtsiSetSimTimeStepPtr(&m1105_M->solverInfo, &m1105_M->Timing.simTimeStep);
      rtsiSetTPtr(&m1105_M->solverInfo, &rtmGetTPtr(m1105_M));
      rtsiSetStepSizePtr(&m1105_M->solverInfo, &m1105_M->Timing.stepSize0);
      rtsiSetdXPtr(&m1105_M->solverInfo, &m1105_M->ModelData.derivs);
      rtsiSetContStatesPtr(&m1105_M->solverInfo, &m1105_M->ModelData.contStates);
      rtsiSetNumContStatesPtr(&m1105_M->solverInfo,
       &m1105_M->Sizes.numContStates);
      rtsiSetErrorStatusPtr(&m1105_M->solverInfo, &rtmGetErrorStatus(m1105_M));

      rtsiSetRTModelPtr(&m1105_M->solverInfo, m1105_M);
    }
    rtsiSetSimTimeStep(&m1105_M->solverInfo, MAJOR_TIME_STEP);
    m1105_M->ModelData.intgData.y = m1105_M->ModelData.odeY;
    m1105_M->ModelData.intgData.f[0] = m1105_M->ModelData.odeF[0];
    m1105_M->ModelData.intgData.f[1] = m1105_M->ModelData.odeF[1];
    m1105_M->ModelData.intgData.f[2] = m1105_M->ModelData.odeF[2];
    m1105_M->ModelData.contStates = ((real_T *) &m1105_X);
    rtsiSetSolverData(&m1105_M->solverInfo, (void
      *)&m1105_M->ModelData.intgData);
    rtsiSetSolverName(&m1105_M->solverInfo,"ode3");

    /* Initialize timing info */
    {
      int_T *mdlTsMap = m1105_M->Timing.sampleTimeTaskIDArray;
      mdlTsMap[0] = 0;
      mdlTsMap[1] = 1;
      m1105_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
      m1105_M->Timing.sampleTimes = (&m1105_M->Timing.sampleTimesArray[0]);
      m1105_M->Timing.offsetTimes = (&m1105_M->Timing.offsetTimesArray[0]);
      /* task periods */
      m1105_M->Timing.sampleTimes[0] = (0.0);
      m1105_M->Timing.sampleTimes[1] = (0.01);

      /* task offsets */
      m1105_M->Timing.offsetTimes[0] = (0.0);
      m1105_M->Timing.offsetTimes[1] = (0.0);
    }

    rtmSetTPtr(m1105_M, &m1105_M->Timing.tArray[0]);

    {
      int_T *mdlSampleHits = m1105_M->Timing.sampleHitArray;
      mdlSampleHits[0] = 1;
      mdlSampleHits[1] = 1;
      m1105_M->Timing.sampleHits = (&mdlSampleHits[0]);
    }

    rtmSetTFinal(m1105_M, 10.0);
    m1105_M->Timing.stepSize0 = 0.01;
    m1105_M->Timing.stepSize1 = 0.01;

    /* Setup for data logging */
    {
      static RTWLogInfo rt_DataLoggingInfo;

      m1105_M->rtwLogInfo = &rt_DataLoggingInfo;

      rtliSetLogFormat(m1105_M->rtwLogInfo, 0);

      rtliSetLogMaxRows(m1105_M->rtwLogInfo, 1000);

      rtliSetLogDecimation(m1105_M->rtwLogInfo, 1);

      rtliSetLogVarNameModifier(m1105_M->rtwLogInfo, "rt_");

      rtliSetLogT(m1105_M->rtwLogInfo, "");

      rtliSetLogX(m1105_M->rtwLogInfo, "");

      rtliSetLogXFinal(m1105_M->rtwLogInfo, "");

      rtliSetSigLog(m1105_M->rtwLogInfo, "");

      rtliSetLogXSignalInfo(m1105_M->rtwLogInfo, NULL);

      rtliSetLogXSignalPtrs(m1105_M->rtwLogInfo, NULL);

      rtliSetLogY(m1105_M->rtwLogInfo, "");

      rtliSetLogYSignalInfo(m1105_M->rtwLogInfo, NULL);

      rtliSetLogYSignalPtrs(m1105_M->rtwLogInfo, NULL);
    }

    /* external mode info */
    m1105_M->Sizes.checksums[0] = (2594945993U);
    m1105_M->Sizes.checksums[1] = (653747764U);
    m1105_M->Sizes.checksums[2] = (2295418504U);
    m1105_M->Sizes.checksums[3] = (3580442612U);

    {
      static const int8_T rtAlwaysEnabled = EXTMODE_SUBSYS_ALWAYS_ENABLED;

      static RTWExtModeInfo rt_ExtModeInfo;
      static const void *sysActives[1];

      m1105_M->extModeInfo = (&rt_ExtModeInfo);
      rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, sysActives);

      sysActives[0] = &rtAlwaysEnabled;

      rteiSetModelMappingInfoPtr(&rt_ExtModeInfo,
       &m1105_M->SpecialInfo.mappingInfo);

      rteiSetChecksumsPtr(&rt_ExtModeInfo, m1105_M->Sizes.checksums);

      rteiSetTPtr(&rt_ExtModeInfo, rtmGetTPtr(m1105_M));
    }

    m1105_M->solverInfoPtr = (&m1105_M->solverInfo);
    m1105_M->Timing.stepSize = (0.01);
    rtsiSetFixedStepSize(&m1105_M->solverInfo, 0.01);
    rtsiSetSolverMode(&m1105_M->solverInfo, SOLVER_MODE_SINGLETASKING);

    {
      /* block I/O */
      void *b = (void *) &m1105_B;
      m1105_M->ModelData.blockIO = (b);

      {

        int_T i;
        b =&m1105_B.Integrator1[0];
        for (i = 0; i < 12; i++) {
          ((real_T*)b)[i] = 0.0;
        }
      }
    }
    /* parameters */
    m1105_M->ModelData.defaultParam = ((real_T *) &m1105_P);
    /* states */
    {
      real_T *x = (real_T *) &m1105_X;
      m1105_M->ModelData.contStates = (x);
      (void)memset((char_T *)x, 0, sizeof(ContinuousStates_m1105));
    }

    /* data type work */
    m1105_M->Work.dwork = ((void *) &m1105_DWork);
    (void)memset((char_T *) &m1105_DWork, 0, sizeof(D_Work_m1105));

    /* data type transition information */
    {
      static DataTypeTransInfo dtInfo;

      (void)memset((char_T *) &dtInfo, 0, sizeof(dtInfo));
      m1105_M->SpecialInfo.mappingInfo = (&dtInfo);

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
void m1105_terminate(void)
{

  /* External mode */
  rtExtModeShutdown(2);
}

/*========================================================================*
 * Start of GRT compatible call interface                                 *
 *========================================================================*/

void MdlOutputs(int_T tid) {

  m1105_output(tid);
}

void MdlUpdate(int_T tid) {

  m1105_update(tid);
}

void MdlInitializeSizes(void) {
  m1105_M->Sizes.numContStates = (6);   /* Number of continuous states */
  m1105_M->Sizes.numY = (0);            /* Number of model outputs */
  m1105_M->Sizes.numU = (0);            /* Number of model inputs */
  m1105_M->Sizes.sysDirFeedThru = (0); /* The model is not direct feedthrough */
  m1105_M->Sizes.numSampTimes = (2);    /* Number of sample times */
  m1105_M->Sizes.numBlocks = (11);      /* Number of blocks */
  m1105_M->Sizes.numBlockIO = (6);      /* Number of block outputs */
  m1105_M->Sizes.numBlockPrms = (11);   /* Sum of parameter "widths" */
}

void MdlInitializeSampleTimes(void) {
}

void MdlInitialize(void) {

  /* Integrator Block: <Root>/Integrator1 */
  m1105_X.Integrator1_CSTATE[0] = m1105_P.Integrator1_IC;
  m1105_X.Integrator1_CSTATE[1] = m1105_P.Integrator1_IC;
  m1105_X.Integrator1_CSTATE[2] = m1105_P.Integrator1_IC;

  /* Integrator Block: <Root>/Integrator */
  m1105_X.Integrator_CSTATE[0] = m1105_P.Integrator_IC;
  m1105_X.Integrator_CSTATE[1] = m1105_P.Integrator_IC;
  m1105_X.Integrator_CSTATE[2] = m1105_P.Integrator_IC;
}

void MdlStart(void) {

  /* Integrator Block: <Root>/Integrator1 */
  m1105_B.Integrator1[0] = m1105_P.Integrator1_IC;
  m1105_B.Integrator1[1] = m1105_P.Integrator1_IC;
  m1105_B.Integrator1[2] = m1105_P.Integrator1_IC;

  MdlInitialize();
}

rtModel_m1105 *m1105(void) {
  m1105_initialize(1);
  return m1105_M;
}

void MdlTerminate(void) {
  m1105_terminate();
}

/*========================================================================*
 * End of GRT compatible call interface                                   *
 *========================================================================*/

