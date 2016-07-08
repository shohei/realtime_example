/*
 * m904.c
 * 
 * Real-Time Workshop code generation for Simulink model "m904.mdl".
 *
 * Model Version              : 1.8
 * Real-Time Workshop version : 6.1  (R14SP1)  05-Sep-2004
 * C source code generated on : Mon Apr 11 10:30:00 2005
 */

#include "m904.h"
#include "m904_private.h"

/* Block signals (auto storage) */
BlockIO_m904 m904_B;

/* Continuous states */
ContinuousStates_m904 m904_X;

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
D_Work_m904 m904_DWork;

/* Real-time model */
rtModel_m904 m904_M_;
rtModel_m904 *m904_M = &m904_M_;

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
  m904_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }
  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  m904_output(0);
  m904_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++) hB[i] = h * rt_ODE3_B[1][i];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }
  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  m904_output(0);
  m904_derivatives();

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
void m904_output(int_T tid)
{

  /* local block i/o variables */

  real_T rtb_Integrator[3];

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(m904_M)) {
    m904_M->Timing.t[0] = rtsiGetT(&m904_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(m904_M)) {
    /* set solver stop time */
    rtsiSetSolverStopTime(&m904_M->solverInfo,
     ((m904_M->Timing.clockTick0+1)*m904_M->Timing.stepSize0));
  }                                     /* end MajorTimeStep */

  /* Integrator: '<Root>/Integrator1' */
  m904_B.Integrator1[0] = m904_X.Integrator1_CSTATE[0];
  m904_B.Integrator1[1] = m904_X.Integrator1_CSTATE[1];
  m904_B.Integrator1[2] = m904_X.Integrator1_CSTATE[2];

  /* Integrator: '<Root>/Integrator' */
  rtb_Integrator[0] = m904_X.Integrator_CSTATE[0];
  rtb_Integrator[1] = m904_X.Integrator_CSTATE[1];
  rtb_Integrator[2] = m904_X.Integrator_CSTATE[2];

  /* Gain: '<Root>/Gain' */
  m904_B.Gain[0] = rtb_Integrator[0] * m904_P.Gain_Gain;
  m904_B.Gain[1] = rtb_Integrator[1] * m904_P.Gain_Gain;
  m904_B.Gain[2] = rtb_Integrator[2] * m904_P.Gain_Gain;

  /* Step: '<Root>/Step' */
  {
    real_T currentTime = m904_M->Timing.t[0];
    if (currentTime < m904_P.Step_Time) {
      m904_B.Step = m904_P.Step_Y0;
    } else {
      m904_B.Step = m904_P.Step_YFinal;
    }
  }

  /* Gain: '<Root>/Gain1' incorporates:
   *  Gain: '<Root>/Gain2'
   *  Sum: '<Root>/Sum1'
   *  Sum: '<Root>/Sum'
   *  Constant: '<Root>/Constant1'
   *  Constant: '<Root>/Constant'
   */
  m904_B.Gain1[0] = (m904_P.Constant_Value - (m904_B.Integrator1[0] +
    m904_B.Gain[0] * m904_P.Gain2_Gain)) * m904_P.Gain1_Gain;
  m904_B.Gain1[1] = (m904_B.Step - (m904_B.Integrator1[1] + m904_B.Gain[1] *
    m904_P.Gain2_Gain)) * m904_P.Gain1_Gain;
  m904_B.Gain1[2] = (m904_P.Constant1_Value - (m904_B.Integrator1[2] +
    m904_B.Gain[2] * m904_P.Gain2_Gain)) * m904_P.Gain1_Gain;
}

/* Model update function */
void m904_update(int_T tid)
{

  if (rtmIsMajorTimeStep(m904_M)) {
    rt_ertODEUpdateContinuousStates(&m904_M->solverInfo, 0);
  }

  /* Update absolute time for base rate */

  if(!(++m904_M->Timing.clockTick0)) ++m904_M->Timing.clockTickH0;
  m904_M->Timing.t[0] = m904_M->Timing.clockTick0 * m904_M->Timing.stepSize0 +
    m904_M->Timing.clockTickH0 * m904_M->Timing.stepSize0 * 4294967296.0;

  if (rtmIsMajorTimeStep(m904_M) &&
   m904_M->Timing.TaskCounters.TID[1] == 0) {
    /* Update absolute timer for sample time: [0.01s, 0.0s] */

    if(!(++m904_M->Timing.clockTick1)) ++m904_M->Timing.clockTickH1;
    m904_M->Timing.t[1] = m904_M->Timing.clockTick1 * m904_M->Timing.stepSize1 +
      m904_M->Timing.clockTickH1 * m904_M->Timing.stepSize1 * 4294967296.0;
  }

  rate_scheduler();
}

/* Derivatives for root system: '<Root>' */
void m904_derivatives(void)
{
  /* simstruct variables */
  StateDerivatives_m904 *m904_Xdot = (StateDerivatives_m904*)
    m904_M->ModelData.derivs;

  /* Integrator Block: <Root>/Integrator1 */
  {

    m904_Xdot->Integrator1_CSTATE[0] = m904_B.Gain[0];
    m904_Xdot->Integrator1_CSTATE[1] = m904_B.Gain[1];
    m904_Xdot->Integrator1_CSTATE[2] = m904_B.Gain[2];
  }

  /* Integrator Block: <Root>/Integrator */
  {

    m904_Xdot->Integrator_CSTATE[0] = m904_B.Gain1[0];
    m904_Xdot->Integrator_CSTATE[1] = m904_B.Gain1[1];
    m904_Xdot->Integrator_CSTATE[2] = m904_B.Gain1[2];
  }
}

/* Model initialize function */
void m904_initialize(boolean_T firstTime)
{

  if (firstTime) {
    /* registration code */
    /* initialize real-time model */
    (void)memset((char_T *)m904_M, 0, sizeof(rtModel_m904));

    {
      /* Setup solver object */

      rtsiSetSimTimeStepPtr(&m904_M->solverInfo, &m904_M->Timing.simTimeStep);
      rtsiSetTPtr(&m904_M->solverInfo, &rtmGetTPtr(m904_M));
      rtsiSetStepSizePtr(&m904_M->solverInfo, &m904_M->Timing.stepSize0);
      rtsiSetdXPtr(&m904_M->solverInfo, &m904_M->ModelData.derivs);
      rtsiSetContStatesPtr(&m904_M->solverInfo, &m904_M->ModelData.contStates);
      rtsiSetNumContStatesPtr(&m904_M->solverInfo, &m904_M->Sizes.numContStates);
      rtsiSetErrorStatusPtr(&m904_M->solverInfo, &rtmGetErrorStatus(m904_M));

      rtsiSetRTModelPtr(&m904_M->solverInfo, m904_M);
    }
    rtsiSetSimTimeStep(&m904_M->solverInfo, MAJOR_TIME_STEP);
    m904_M->ModelData.intgData.y = m904_M->ModelData.odeY;
    m904_M->ModelData.intgData.f[0] = m904_M->ModelData.odeF[0];
    m904_M->ModelData.intgData.f[1] = m904_M->ModelData.odeF[1];
    m904_M->ModelData.intgData.f[2] = m904_M->ModelData.odeF[2];
    m904_M->ModelData.contStates = ((real_T *) &m904_X);
    rtsiSetSolverData(&m904_M->solverInfo, (void *)&m904_M->ModelData.intgData);
    rtsiSetSolverName(&m904_M->solverInfo,"ode3");

    /* Initialize timing info */
    {
      int_T *mdlTsMap = m904_M->Timing.sampleTimeTaskIDArray;
      mdlTsMap[0] = 0;
      mdlTsMap[1] = 1;
      m904_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
      m904_M->Timing.sampleTimes = (&m904_M->Timing.sampleTimesArray[0]);
      m904_M->Timing.offsetTimes = (&m904_M->Timing.offsetTimesArray[0]);
      /* task periods */
      m904_M->Timing.sampleTimes[0] = (0.0);
      m904_M->Timing.sampleTimes[1] = (0.01);

      /* task offsets */
      m904_M->Timing.offsetTimes[0] = (0.0);
      m904_M->Timing.offsetTimes[1] = (0.0);
    }

    rtmSetTPtr(m904_M, &m904_M->Timing.tArray[0]);

    {
      int_T *mdlSampleHits = m904_M->Timing.sampleHitArray;
      mdlSampleHits[0] = 1;
      mdlSampleHits[1] = 1;
      m904_M->Timing.sampleHits = (&mdlSampleHits[0]);
    }

    rtmSetTFinal(m904_M, 10.0);
    m904_M->Timing.stepSize0 = 0.01;
    m904_M->Timing.stepSize1 = 0.01;

    /* Setup for data logging */
    {
      static RTWLogInfo rt_DataLoggingInfo;

      m904_M->rtwLogInfo = &rt_DataLoggingInfo;

      rtliSetLogFormat(m904_M->rtwLogInfo, 0);

      rtliSetLogMaxRows(m904_M->rtwLogInfo, 1000);

      rtliSetLogDecimation(m904_M->rtwLogInfo, 1);

      rtliSetLogVarNameModifier(m904_M->rtwLogInfo, "rt_");

      rtliSetLogT(m904_M->rtwLogInfo, "tout");

      rtliSetLogX(m904_M->rtwLogInfo, "");

      rtliSetLogXFinal(m904_M->rtwLogInfo, "");

      rtliSetSigLog(m904_M->rtwLogInfo, "");

      rtliSetLogXSignalInfo(m904_M->rtwLogInfo, NULL);

      rtliSetLogXSignalPtrs(m904_M->rtwLogInfo, NULL);

      rtliSetLogY(m904_M->rtwLogInfo, "");

      rtliSetLogYSignalInfo(m904_M->rtwLogInfo, NULL);

      rtliSetLogYSignalPtrs(m904_M->rtwLogInfo, NULL);
    }

    m904_M->solverInfoPtr = (&m904_M->solverInfo);
    m904_M->Timing.stepSize = (0.01);
    rtsiSetFixedStepSize(&m904_M->solverInfo, 0.01);
    rtsiSetSolverMode(&m904_M->solverInfo, SOLVER_MODE_SINGLETASKING);

    {
      /* block I/O */
      void *b = (void *) &m904_B;
      m904_M->ModelData.blockIO = (b);

      {

        int_T i;
        b =&m904_B.Integrator1[0];
        for (i = 0; i < 10; i++) {
          ((real_T*)b)[i] = 0.0;
        }
      }
    }
    /* parameters */
    m904_M->ModelData.defaultParam = ((real_T *) &m904_P);
    /* states */
    {
      real_T *x = (real_T *) &m904_X;
      m904_M->ModelData.contStates = (x);
      (void)memset((char_T *)x, 0, sizeof(ContinuousStates_m904));
    }

    /* data type work */
    m904_M->Work.dwork = ((void *) &m904_DWork);
    (void)memset((char_T *) &m904_DWork, 0, sizeof(D_Work_m904));

    /* initialize non-finites */
    rt_InitInfAndNaN(sizeof(real_T));
  }
}

/* Model terminate function */
void m904_terminate(void)
{
}

/*========================================================================*
 * Start of GRT compatible call interface                                 *
 *========================================================================*/

void MdlOutputs(int_T tid) {

  m904_output(tid);
}

void MdlUpdate(int_T tid) {

  m904_update(tid);
}

void MdlInitializeSizes(void) {
  m904_M->Sizes.numContStates = (6);    /* Number of continuous states */
  m904_M->Sizes.numY = (0);             /* Number of model outputs */
  m904_M->Sizes.numU = (0);             /* Number of model inputs */
  m904_M->Sizes.sysDirFeedThru = (0);   /* The model is not direct feedthrough */
  m904_M->Sizes.numSampTimes = (2);     /* Number of sample times */
  m904_M->Sizes.numBlocks = (11);       /* Number of blocks */
  m904_M->Sizes.numBlockIO = (4);       /* Number of block outputs */
  m904_M->Sizes.numBlockPrms = (10);    /* Sum of parameter "widths" */
}

void MdlInitializeSampleTimes(void) {
}

void MdlInitialize(void) {

  /* Integrator Block: <Root>/Integrator1 */
  m904_X.Integrator1_CSTATE[0] = m904_P.Integrator1_IC;
  m904_X.Integrator1_CSTATE[1] = m904_P.Integrator1_IC;
  m904_X.Integrator1_CSTATE[2] = m904_P.Integrator1_IC;

  /* Integrator Block: <Root>/Integrator */
  m904_X.Integrator_CSTATE[0] = m904_P.Integrator_IC;
  m904_X.Integrator_CSTATE[1] = m904_P.Integrator_IC;
  m904_X.Integrator_CSTATE[2] = m904_P.Integrator_IC;
}

void MdlStart(void) {

  /* Integrator Block: <Root>/Integrator1 */
  m904_B.Integrator1[0] = m904_P.Integrator1_IC;
  m904_B.Integrator1[1] = m904_P.Integrator1_IC;
  m904_B.Integrator1[2] = m904_P.Integrator1_IC;

  MdlInitialize();
}

rtModel_m904 *m904(void) {
  m904_initialize(1);
  return m904_M;
}

void MdlTerminate(void) {
  m904_terminate();
}

/*========================================================================*
 * End of GRT compatible call interface                                   *
 *========================================================================*/

