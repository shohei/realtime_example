/*
 * m1006.c
 * 
 * Real-Time Workshop code generation for Simulink model "m1006.mdl".
 *
 * Model Version              : 1.1
 * Real-Time Workshop version : 6.1  (R14SP1)  05-Sep-2004
 * C source code generated on : Sun Apr 03 17:02:26 2005
 */

#include "m1006.h"
#include "m1006_private.h"

/* Block signals (auto storage) */
BlockIO_m1006 m1006_B;

/* Continuous states */
ContinuousStates_m1006 m1006_X;

/* External output (root outports fed by signals with auto storage) */
ExternalOutputs_m1006 m1006_Y;

/* Real-time model */
rtModel_m1006 m1006_M_;
rtModel_m1006 *m1006_M = &m1006_M_;

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

/* This function updates continuous states using the ODE4 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si , int_T tid)
{
  time_T t = rtsiGetT(si);
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE4_IntgData *id = rtsiGetSolverData(si);
  real_T *y = id->y;
  real_T *f0 = id->f[0];
  real_T *f1 = id->f[1];
  real_T *f2 = id->f[2];
  real_T *f3 = id->f[3];
  real_T temp;
  int_T i;

  int_T nXc = 1;

  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void)memcpy(y, x, nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  m1006_derivatives();

  /* f1 = f(t + (h/2), y + (h/2)*f0) */
  temp = 0.5 * h;
  for (i = 0; i < nXc; i++) x[i] = y[i] + (temp*f0[i]);
  rtsiSetT(si, t + temp);
  rtsiSetdX(si, f1);
  m1006_output(0);
  m1006_derivatives();

  /* f2 = f(t + (h/2), y + (h/2)*f1) */
  for (i = 0; i < nXc; i++) x[i] = y[i] + (temp*f1[i]);
  rtsiSetdX(si, f2);
  m1006_output(0);
  m1006_derivatives();

  /* f3 = f(t + h, y + h*f2) */
  for (i = 0; i < nXc; i++) x[i] = y[i] + (h*f2[i]);
  rtsiSetT(si, tnew);
  rtsiSetdX(si, f3);
  m1006_output(0);
  m1006_derivatives();

  /* tnew = t + h
     ynew = y + (h/6)*(f0 + 2*f1 + 2*f2 + 2*f3) */
  temp = h / 6.0;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + temp*(f0[i] + 2.0*f1[i] + 2.0*f2[i] + f3[i]);
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model output function */
void m1006_output(int_T tid)
{

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(m1006_M)) {
    m1006_M->Timing.t[0] = rtsiGetT(&m1006_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(m1006_M)) {
    /* set solver stop time */
    rtsiSetSolverStopTime(&m1006_M->solverInfo,
     ((m1006_M->Timing.clockTick0+1)*m1006_M->Timing.stepSize0));
  }                                     /* end MajorTimeStep */

  /* Sin: '<Root>/Sine Wave' */
  m1006_B.SineWave = m1006_P.SineWave_Amp *
    sin(m1006_P.SineWave_Freq * m1006_M->Timing.t[0] + m1006_P.SineWave_Phase) +
    m1006_P.SineWave_Bias;

  /* S-Function "motor_wrapper" Block: <Root>/S-Function Builder */

  {
    real_T *pxc = m1006_M->ModelData.contStates;
    motor_Outputs_wrapper(&m1006_B.SineWave, &m1006_B.SFunctionBuilder, pxc);
  }

  /* Outport: '<Root>/Out1' */
  m1006_Y.Out1 = m1006_B.SFunctionBuilder;
}

/* Model update function */
void m1006_update(int_T tid)
{

  if (rtmIsMajorTimeStep(m1006_M)) {
    rt_ertODEUpdateContinuousStates(&m1006_M->solverInfo, 0);
  }

  /* Update absolute time for base rate */

  if(!(++m1006_M->Timing.clockTick0)) ++m1006_M->Timing.clockTickH0;
  m1006_M->Timing.t[0] = m1006_M->Timing.clockTick0 * m1006_M->Timing.stepSize0
    + m1006_M->Timing.clockTickH0 * m1006_M->Timing.stepSize0 * 4294967296.0;

  if (rtmIsMajorTimeStep(m1006_M) &&
   m1006_M->Timing.TaskCounters.TID[1] == 0) {
    /* Update absolute timer for sample time: [0.1s, 0.0s] */

    if(!(++m1006_M->Timing.clockTick1)) ++m1006_M->Timing.clockTickH1;
    m1006_M->Timing.t[1] = m1006_M->Timing.clockTick1 *
      m1006_M->Timing.stepSize1 + m1006_M->Timing.clockTickH1 *
      m1006_M->Timing.stepSize1 * 4294967296.0;
  }

  rate_scheduler();
}

/* Derivatives for root system: '<Root>' */
void m1006_derivatives(void)
{

  /* S-Function "motor_wrapper" Block: <Root>/S-Function Builder */

  {
    real_T *pxc = m1006_M->ModelData.contStates;
    real_T *dx = m1006_M->ModelData.derivs;
    motor_Derivatives_wrapper(&m1006_B.SineWave, &m1006_B.SFunctionBuilder, dx,
     pxc);
  }
}

/* Model initialize function */
void m1006_initialize(boolean_T firstTime)
{

  if (firstTime) {
    /* registration code */
    /* initialize real-time model */
    (void)memset((char_T *)m1006_M, 0, sizeof(rtModel_m1006));

    {
      /* Setup solver object */

      rtsiSetSimTimeStepPtr(&m1006_M->solverInfo, &m1006_M->Timing.simTimeStep);
      rtsiSetTPtr(&m1006_M->solverInfo, &rtmGetTPtr(m1006_M));
      rtsiSetStepSizePtr(&m1006_M->solverInfo, &m1006_M->Timing.stepSize0);
      rtsiSetdXPtr(&m1006_M->solverInfo, &m1006_M->ModelData.derivs);
      rtsiSetContStatesPtr(&m1006_M->solverInfo, &m1006_M->ModelData.contStates);
      rtsiSetNumContStatesPtr(&m1006_M->solverInfo,
       &m1006_M->Sizes.numContStates);
      rtsiSetErrorStatusPtr(&m1006_M->solverInfo, &rtmGetErrorStatus(m1006_M));

      rtsiSetRTModelPtr(&m1006_M->solverInfo, m1006_M);
    }
    rtsiSetSimTimeStep(&m1006_M->solverInfo, MAJOR_TIME_STEP);
    m1006_M->ModelData.intgData.y = m1006_M->ModelData.odeY;
    m1006_M->ModelData.intgData.f[0] = m1006_M->ModelData.odeF[0];
    m1006_M->ModelData.intgData.f[1] = m1006_M->ModelData.odeF[1];
    m1006_M->ModelData.intgData.f[2] = m1006_M->ModelData.odeF[2];
    m1006_M->ModelData.intgData.f[3] = m1006_M->ModelData.odeF[3];
    m1006_M->ModelData.contStates = ((real_T *) &m1006_X);
    rtsiSetSolverData(&m1006_M->solverInfo, (void
      *)&m1006_M->ModelData.intgData);
    rtsiSetSolverName(&m1006_M->solverInfo,"ode4");

    /* Initialize timing info */
    {
      int_T *mdlTsMap = m1006_M->Timing.sampleTimeTaskIDArray;
      mdlTsMap[0] = 0;
      mdlTsMap[1] = 1;
      m1006_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
      m1006_M->Timing.sampleTimes = (&m1006_M->Timing.sampleTimesArray[0]);
      m1006_M->Timing.offsetTimes = (&m1006_M->Timing.offsetTimesArray[0]);
      /* task periods */
      m1006_M->Timing.sampleTimes[0] = (0.0);
      m1006_M->Timing.sampleTimes[1] = (0.1);

      /* task offsets */
      m1006_M->Timing.offsetTimes[0] = (0.0);
      m1006_M->Timing.offsetTimes[1] = (0.0);
    }

    rtmSetTPtr(m1006_M, &m1006_M->Timing.tArray[0]);

    {
      int_T *mdlSampleHits = m1006_M->Timing.sampleHitArray;
      mdlSampleHits[0] = 1;
      mdlSampleHits[1] = 1;
      m1006_M->Timing.sampleHits = (&mdlSampleHits[0]);
    }

    rtmSetTFinal(m1006_M, 10.0);
    m1006_M->Timing.stepSize0 = 0.1;
    m1006_M->Timing.stepSize1 = 0.1;

    /* Setup for data logging */
    {
      static RTWLogInfo rt_DataLoggingInfo;

      m1006_M->rtwLogInfo = &rt_DataLoggingInfo;

      rtliSetLogFormat(m1006_M->rtwLogInfo, 0);

      rtliSetLogMaxRows(m1006_M->rtwLogInfo, 1000);

      rtliSetLogDecimation(m1006_M->rtwLogInfo, 1);

      rtliSetLogVarNameModifier(m1006_M->rtwLogInfo, "rt_");

      rtliSetLogT(m1006_M->rtwLogInfo, "tout");

      rtliSetLogX(m1006_M->rtwLogInfo, "");

      rtliSetLogXFinal(m1006_M->rtwLogInfo, "");

      rtliSetSigLog(m1006_M->rtwLogInfo, "");

      rtliSetLogXSignalInfo(m1006_M->rtwLogInfo, NULL);

      rtliSetLogXSignalPtrs(m1006_M->rtwLogInfo, NULL);

      rtliSetLogY(m1006_M->rtwLogInfo, "yout");

      /*
       * Set pointers to the data and signal info for each output
       */
      {
        static void * rt_LoggedOutputSignalPtrs[] = {
          &m1006_Y.Out1
        };

        rtliSetLogYSignalPtrs(m1006_M->rtwLogInfo,
         ((LogSignalPtrsType)rt_LoggedOutputSignalPtrs));
      }
      {

        static int_T rt_LoggedOutputWidths[] = {
          1
        };

        static int_T rt_LoggedOutputNumDimensions[] = {
          1
        };

        static int_T rt_LoggedOutputDimensions[] = {
          1
        };

        static BuiltInDTypeId rt_LoggedOutputDataTypeIds[] = {
          SS_DOUBLE
        };

        static int_T rt_LoggedOutputComplexSignals[] = {
          0
        };

        static const char_T *rt_LoggedOutputLabels[] = {
          ""};

        static const char_T *rt_LoggedOutputBlockNames[] = {
          "m1006/Out1"};

        static RTWLogDataTypeConvert rt_RTWLogDataTypeConvert[] = {
          { 0, SS_DOUBLE, SS_DOUBLE, 1.0, 0, 0.0}
        };

        static RTWLogSignalInfo rt_LoggedOutputSignalInfo[] = {
          {
            1,
            rt_LoggedOutputWidths,
            rt_LoggedOutputNumDimensions,
            rt_LoggedOutputDimensions,
            rt_LoggedOutputDataTypeIds,
            rt_LoggedOutputComplexSignals,
            NULL,
            rt_LoggedOutputLabels,
            NULL,
            NULL,
            NULL,
            rt_LoggedOutputBlockNames,
            NULL,
            rt_RTWLogDataTypeConvert
          }
        };

        rtliSetLogYSignalInfo(m1006_M->rtwLogInfo, rt_LoggedOutputSignalInfo);
      }
    }

    m1006_M->solverInfoPtr = (&m1006_M->solverInfo);
    m1006_M->Timing.stepSize = (0.1);
    rtsiSetFixedStepSize(&m1006_M->solverInfo, 0.1);
    rtsiSetSolverMode(&m1006_M->solverInfo, SOLVER_MODE_SINGLETASKING);

    {
      /* block I/O */
      void *b = (void *) &m1006_B;
      m1006_M->ModelData.blockIO = (b);

      {

        int_T i;
        b =&m1006_B.SineWave;
        for (i = 0; i < 2; i++) {
          ((real_T*)b)[i] = 0.0;
        }
      }
    }
    /* parameters */
    m1006_M->ModelData.defaultParam = ((real_T *) &m1006_P);
    /* states */
    {
      real_T *x = (real_T *) &m1006_X;
      m1006_M->ModelData.contStates = (x);
      (void)memset((char_T *)x, 0, sizeof(ContinuousStates_m1006));
    }

    /* external outputs */
    m1006_M->ModelData.outputs = (&m1006_Y);
    m1006_Y.Out1 = 0.0;

    /* initialize non-finites */
    rt_InitInfAndNaN(sizeof(real_T));
  }
}

/* Model terminate function */
void m1006_terminate(void)
{
}

/*========================================================================*
 * Start of GRT compatible call interface                                 *
 *========================================================================*/

void MdlOutputs(int_T tid) {

  m1006_output(tid);
}

void MdlUpdate(int_T tid) {

  m1006_update(tid);
}

void MdlInitializeSizes(void) {
  m1006_M->Sizes.numContStates = (1);   /* Number of continuous states */
  m1006_M->Sizes.numY = (1);            /* Number of model outputs */
  m1006_M->Sizes.numU = (0);            /* Number of model inputs */
  m1006_M->Sizes.sysDirFeedThru = (0); /* The model is not direct feedthrough */
  m1006_M->Sizes.numSampTimes = (2);    /* Number of sample times */
  m1006_M->Sizes.numBlocks = (3);       /* Number of blocks */
  m1006_M->Sizes.numBlockIO = (2);      /* Number of block outputs */
  m1006_M->Sizes.numBlockPrms = (4);    /* Sum of parameter "widths" */
}

void MdlInitializeSampleTimes(void) {
}

void MdlInitialize(void) {

  /* S-Function Block: <Root>/S-Function Builder */

  {
    real_T *xC = m1006_M->ModelData.contStates;

    xC[0] = 0;
  }
}

void MdlStart(void) {
  MdlInitialize();
}

rtModel_m1006 *m1006(void) {
  m1006_initialize(1);
  return m1006_M;
}

void MdlTerminate(void) {
  m1006_terminate();
}

/*========================================================================*
 * End of GRT compatible call interface                                   *
 *========================================================================*/

