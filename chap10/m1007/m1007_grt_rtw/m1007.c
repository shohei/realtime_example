/*
 * m1007.c
 * 
 * Real-Time Workshop code generation for Simulink model "m1007.mdl".
 *
 * Model Version              : 1.1
 * Real-Time Workshop version : 6.1  (R14SP1)  05-Sep-2004
 * C source code generated on : Sun Apr 03 17:43:27 2005
 */

#include "m1007.h"
#include "m1007_private.h"

/* Block signals (auto storage) */
BlockIO_m1007 m1007_B;

/* Continuous states */
ContinuousStates_m1007 m1007_X;

/* External output (root outports fed by signals with auto storage) */
ExternalOutputs_m1007 m1007_Y;

/* Real-time model */
rtModel_m1007 m1007_M_;
rtModel_m1007 *m1007_M = &m1007_M_;

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
  m1007_derivatives();

  /* f1 = f(t + (h/2), y + (h/2)*f0) */
  temp = 0.5 * h;
  for (i = 0; i < nXc; i++) x[i] = y[i] + (temp*f0[i]);
  rtsiSetT(si, t + temp);
  rtsiSetdX(si, f1);
  m1007_output(0);
  m1007_derivatives();

  /* f2 = f(t + (h/2), y + (h/2)*f1) */
  for (i = 0; i < nXc; i++) x[i] = y[i] + (temp*f1[i]);
  rtsiSetdX(si, f2);
  m1007_output(0);
  m1007_derivatives();

  /* f3 = f(t + h, y + h*f2) */
  for (i = 0; i < nXc; i++) x[i] = y[i] + (h*f2[i]);
  rtsiSetT(si, tnew);
  rtsiSetdX(si, f3);
  m1007_output(0);
  m1007_derivatives();

  /* tnew = t + h
     ynew = y + (h/6)*(f0 + 2*f1 + 2*f2 + 2*f3) */
  temp = h / 6.0;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + temp*(f0[i] + 2.0*f1[i] + 2.0*f2[i] + f3[i]);
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model output function */
void m1007_output(int_T tid)
{

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(m1007_M)) {
    m1007_M->Timing.t[0] = rtsiGetT(&m1007_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(m1007_M)) {
    /* set solver stop time */
    rtsiSetSolverStopTime(&m1007_M->solverInfo,
     ((m1007_M->Timing.clockTick0+1)*m1007_M->Timing.stepSize0));
  }                                     /* end MajorTimeStep */

  /* Sin: '<Root>/Sine Wave' */
  m1007_B.SineWave = m1007_P.SineWave_Amp *
    sin(m1007_P.SineWave_Freq * m1007_M->Timing.t[0] + m1007_P.SineWave_Phase) +
    m1007_P.SineWave_Bias;

  {
    real_T *pxc = m1007_M->ModelData.contStates;
    m1007_B.SFunctionBuilder=pxc[0];
  }

  /* Outport: '<Root>/Out1' */
  m1007_Y.Out1 = m1007_B.SFunctionBuilder;
}

/* Model update function */
void m1007_update(int_T tid)
{

  if (rtmIsMajorTimeStep(m1007_M)) {
    rt_ertODEUpdateContinuousStates(&m1007_M->solverInfo, 0);
  }

  /* Update absolute time for base rate */

  if(!(++m1007_M->Timing.clockTick0)) ++m1007_M->Timing.clockTickH0;
  m1007_M->Timing.t[0] = m1007_M->Timing.clockTick0 * m1007_M->Timing.stepSize0
    + m1007_M->Timing.clockTickH0 * m1007_M->Timing.stepSize0 * 4294967296.0;

  if (rtmIsMajorTimeStep(m1007_M) &&
   m1007_M->Timing.TaskCounters.TID[1] == 0) {
    /* Update absolute timer for sample time: [0.1s, 0.0s] */

    if(!(++m1007_M->Timing.clockTick1)) ++m1007_M->Timing.clockTickH1;
    m1007_M->Timing.t[1] = m1007_M->Timing.clockTick1 *
      m1007_M->Timing.stepSize1 + m1007_M->Timing.clockTickH1 *
      m1007_M->Timing.stepSize1 * 4294967296.0;
  }

  rate_scheduler();
}

/* Derivatives for root system: '<Root>' */
void m1007_derivatives(void)
{

  {
    real_T *dx = m1007_M->ModelData.derivs;
    dx[0]=0.5*m1007_B.SineWave;
  }
}

/* Model initialize function */
void m1007_initialize(boolean_T firstTime)
{

  if (firstTime) {
    /* registration code */
    /* initialize real-time model */
    (void)memset((char_T *)m1007_M, 0, sizeof(rtModel_m1007));

    {
      /* Setup solver object */

      rtsiSetSimTimeStepPtr(&m1007_M->solverInfo, &m1007_M->Timing.simTimeStep);
      rtsiSetTPtr(&m1007_M->solverInfo, &rtmGetTPtr(m1007_M));
      rtsiSetStepSizePtr(&m1007_M->solverInfo, &m1007_M->Timing.stepSize0);
      rtsiSetdXPtr(&m1007_M->solverInfo, &m1007_M->ModelData.derivs);
      rtsiSetContStatesPtr(&m1007_M->solverInfo, &m1007_M->ModelData.contStates);
      rtsiSetNumContStatesPtr(&m1007_M->solverInfo,
       &m1007_M->Sizes.numContStates);
      rtsiSetErrorStatusPtr(&m1007_M->solverInfo, &rtmGetErrorStatus(m1007_M));

      rtsiSetRTModelPtr(&m1007_M->solverInfo, m1007_M);
    }
    rtsiSetSimTimeStep(&m1007_M->solverInfo, MAJOR_TIME_STEP);
    m1007_M->ModelData.intgData.y = m1007_M->ModelData.odeY;
    m1007_M->ModelData.intgData.f[0] = m1007_M->ModelData.odeF[0];
    m1007_M->ModelData.intgData.f[1] = m1007_M->ModelData.odeF[1];
    m1007_M->ModelData.intgData.f[2] = m1007_M->ModelData.odeF[2];
    m1007_M->ModelData.intgData.f[3] = m1007_M->ModelData.odeF[3];
    m1007_M->ModelData.contStates = ((real_T *) &m1007_X);
    rtsiSetSolverData(&m1007_M->solverInfo, (void
      *)&m1007_M->ModelData.intgData);
    rtsiSetSolverName(&m1007_M->solverInfo,"ode4");

    /* Initialize timing info */
    {
      int_T *mdlTsMap = m1007_M->Timing.sampleTimeTaskIDArray;
      mdlTsMap[0] = 0;
      mdlTsMap[1] = 1;
      m1007_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
      m1007_M->Timing.sampleTimes = (&m1007_M->Timing.sampleTimesArray[0]);
      m1007_M->Timing.offsetTimes = (&m1007_M->Timing.offsetTimesArray[0]);
      /* task periods */
      m1007_M->Timing.sampleTimes[0] = (0.0);
      m1007_M->Timing.sampleTimes[1] = (0.1);

      /* task offsets */
      m1007_M->Timing.offsetTimes[0] = (0.0);
      m1007_M->Timing.offsetTimes[1] = (0.0);
    }

    rtmSetTPtr(m1007_M, &m1007_M->Timing.tArray[0]);

    {
      int_T *mdlSampleHits = m1007_M->Timing.sampleHitArray;
      mdlSampleHits[0] = 1;
      mdlSampleHits[1] = 1;
      m1007_M->Timing.sampleHits = (&mdlSampleHits[0]);
    }

    rtmSetTFinal(m1007_M, 10.0);
    m1007_M->Timing.stepSize0 = 0.1;
    m1007_M->Timing.stepSize1 = 0.1;

    /* Setup for data logging */
    {
      static RTWLogInfo rt_DataLoggingInfo;

      m1007_M->rtwLogInfo = &rt_DataLoggingInfo;

      rtliSetLogFormat(m1007_M->rtwLogInfo, 0);

      rtliSetLogMaxRows(m1007_M->rtwLogInfo, 1000);

      rtliSetLogDecimation(m1007_M->rtwLogInfo, 1);

      rtliSetLogVarNameModifier(m1007_M->rtwLogInfo, "rt_");

      rtliSetLogT(m1007_M->rtwLogInfo, "tout");

      rtliSetLogX(m1007_M->rtwLogInfo, "");

      rtliSetLogXFinal(m1007_M->rtwLogInfo, "");

      rtliSetSigLog(m1007_M->rtwLogInfo, "");

      rtliSetLogXSignalInfo(m1007_M->rtwLogInfo, NULL);

      rtliSetLogXSignalPtrs(m1007_M->rtwLogInfo, NULL);

      rtliSetLogY(m1007_M->rtwLogInfo, "yout");

      /*
       * Set pointers to the data and signal info for each output
       */
      {
        static void * rt_LoggedOutputSignalPtrs[] = {
          &m1007_Y.Out1
        };

        rtliSetLogYSignalPtrs(m1007_M->rtwLogInfo,
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
          "m1007/Out1"};

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

        rtliSetLogYSignalInfo(m1007_M->rtwLogInfo, rt_LoggedOutputSignalInfo);
      }
    }

    m1007_M->solverInfoPtr = (&m1007_M->solverInfo);
    m1007_M->Timing.stepSize = (0.1);
    rtsiSetFixedStepSize(&m1007_M->solverInfo, 0.1);
    rtsiSetSolverMode(&m1007_M->solverInfo, SOLVER_MODE_SINGLETASKING);

    {
      /* block I/O */
      void *b = (void *) &m1007_B;
      m1007_M->ModelData.blockIO = (b);

      {

        int_T i;
        b =&m1007_B.SineWave;
        for (i = 0; i < 2; i++) {
          ((real_T*)b)[i] = 0.0;
        }
      }
    }
    /* parameters */
    m1007_M->ModelData.defaultParam = ((real_T *) &m1007_P);
    /* states */
    {
      real_T *x = (real_T *) &m1007_X;
      m1007_M->ModelData.contStates = (x);
      (void)memset((char_T *)x, 0, sizeof(ContinuousStates_m1007));
    }

    /* external outputs */
    m1007_M->ModelData.outputs = (&m1007_Y);
    m1007_Y.Out1 = 0.0;

    /* initialize non-finites */
    rt_InitInfAndNaN(sizeof(real_T));
  }
}

/* Model terminate function */
void m1007_terminate(void)
{
}

/*========================================================================*
 * Start of GRT compatible call interface                                 *
 *========================================================================*/

void MdlOutputs(int_T tid) {

  m1007_output(tid);
}

void MdlUpdate(int_T tid) {

  m1007_update(tid);
}

void MdlInitializeSizes(void) {
  m1007_M->Sizes.numContStates = (1);   /* Number of continuous states */
  m1007_M->Sizes.numY = (1);            /* Number of model outputs */
  m1007_M->Sizes.numU = (0);            /* Number of model inputs */
  m1007_M->Sizes.sysDirFeedThru = (0); /* The model is not direct feedthrough */
  m1007_M->Sizes.numSampTimes = (2);    /* Number of sample times */
  m1007_M->Sizes.numBlocks = (3);       /* Number of blocks */
  m1007_M->Sizes.numBlockIO = (2);      /* Number of block outputs */
  m1007_M->Sizes.numBlockPrms = (4);    /* Sum of parameter "widths" */
}

void MdlInitializeSampleTimes(void) {
}

void MdlInitialize(void) {

  {
    real_T *xC = m1007_M->ModelData.contStates;
    xC[0] = 0;
  }
}

void MdlStart(void) {
  MdlInitialize();
}

rtModel_m1007 *m1007(void) {
  m1007_initialize(1);
  return m1007_M;
}

void MdlTerminate(void) {
  m1007_terminate();
}

/*========================================================================*
 * End of GRT compatible call interface                                   *
 *========================================================================*/

