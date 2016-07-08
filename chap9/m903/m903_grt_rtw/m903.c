/*
 * m903.c
 * 
 * Real-Time Workshop code generation for Simulink model "m903.mdl".
 *
 * Model Version              : 1.8
 * Real-Time Workshop version : 6.1  (R14SP1)  05-Sep-2004
 * C source code generated on : Sat Apr 02 09:22:49 2005
 */

#include "m903.h"
#include "m903_private.h"

/* Block signals (auto storage) */
BlockIO_m903 m903_B;

/* Continuous states */
ContinuousStates_m903 m903_X;

/* External output (root outports fed by signals with auto storage) */
ExternalOutputs_m903 m903_Y;

/* Real-time model */
rtModel_m903 m903_M_;
rtModel_m903 *m903_M = &m903_M_;

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
  m903_derivatives();

  /* f1 = f(t + (h/2), y + (h/2)*f0) */
  temp = 0.5 * h;
  for (i = 0; i < nXc; i++) x[i] = y[i] + (temp*f0[i]);
  rtsiSetT(si, t + temp);
  rtsiSetdX(si, f1);
  m903_output(0);
  m903_derivatives();

  /* f2 = f(t + (h/2), y + (h/2)*f1) */
  for (i = 0; i < nXc; i++) x[i] = y[i] + (temp*f1[i]);
  rtsiSetdX(si, f2);
  m903_output(0);
  m903_derivatives();

  /* f3 = f(t + h, y + h*f2) */
  for (i = 0; i < nXc; i++) x[i] = y[i] + (h*f2[i]);
  rtsiSetT(si, tnew);
  rtsiSetdX(si, f3);
  m903_output(0);
  m903_derivatives();

  /* tnew = t + h
     ynew = y + (h/6)*(f0 + 2*f1 + 2*f2 + 2*f3) */
  temp = h / 6.0;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + temp*(f0[i] + 2.0*f1[i] + 2.0*f2[i] + f3[i]);
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model output function */
void m903_output(int_T tid)
{

  /* local block i/o variables */

  real_T rtb_Integrator;

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(m903_M)) {
    m903_M->Timing.t[0] = rtsiGetT(&m903_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(m903_M)) {
    /* set solver stop time */
    rtsiSetSolverStopTime(&m903_M->solverInfo,
     ((m903_M->Timing.clockTick0+1)*m903_M->Timing.stepSize0));
  }                                     /* end MajorTimeStep */

  /* Integrator: '<Root>/Integrator' */
  rtb_Integrator = m903_X.Integrator_CSTATE;

  /* Outport: '<Root>/Out1' */
  m903_Y.Out1 = rtb_Integrator;

  /* Sin: '<Root>/Sine Wave' */
  m903_B.SineWave = m903_P.SineWave_Amp *
    sin(m903_P.SineWave_Freq * m903_M->Timing.t[0] + m903_P.SineWave_Phase) +
    m903_P.SineWave_Bias;
}

/* Model update function */
void m903_update(int_T tid)
{

  if (rtmIsMajorTimeStep(m903_M)) {
    rt_ertODEUpdateContinuousStates(&m903_M->solverInfo, 0);
  }

  /* Update absolute time for base rate */

  if(!(++m903_M->Timing.clockTick0)) ++m903_M->Timing.clockTickH0;
  m903_M->Timing.t[0] = m903_M->Timing.clockTick0 * m903_M->Timing.stepSize0 +
    m903_M->Timing.clockTickH0 * m903_M->Timing.stepSize0 * 4294967296.0;

  if (rtmIsMajorTimeStep(m903_M) &&
   m903_M->Timing.TaskCounters.TID[1] == 0) {
    /* Update absolute timer for sample time: [0.1s, 0.0s] */

    if(!(++m903_M->Timing.clockTick1)) ++m903_M->Timing.clockTickH1;
    m903_M->Timing.t[1] = m903_M->Timing.clockTick1 * m903_M->Timing.stepSize1 +
      m903_M->Timing.clockTickH1 * m903_M->Timing.stepSize1 * 4294967296.0;
  }

  rate_scheduler();
}

/* Derivatives for root system: '<Root>' */
void m903_derivatives(void)
{
  /* simstruct variables */
  StateDerivatives_m903 *m903_Xdot = (StateDerivatives_m903*)
    m903_M->ModelData.derivs;

  /* Integrator Block: <Root>/Integrator */
  {

    m903_Xdot->Integrator_CSTATE = m903_B.SineWave;
  }
}

/* Model initialize function */
void m903_initialize(boolean_T firstTime)
{

  if (firstTime) {
    /* registration code */
    /* initialize real-time model */
    (void)memset((char_T *)m903_M, 0, sizeof(rtModel_m903));

    {
      /* Setup solver object */

      rtsiSetSimTimeStepPtr(&m903_M->solverInfo, &m903_M->Timing.simTimeStep);
      rtsiSetTPtr(&m903_M->solverInfo, &rtmGetTPtr(m903_M));
      rtsiSetStepSizePtr(&m903_M->solverInfo, &m903_M->Timing.stepSize0);
      rtsiSetdXPtr(&m903_M->solverInfo, &m903_M->ModelData.derivs);
      rtsiSetContStatesPtr(&m903_M->solverInfo, &m903_M->ModelData.contStates);
      rtsiSetNumContStatesPtr(&m903_M->solverInfo, &m903_M->Sizes.numContStates);
      rtsiSetErrorStatusPtr(&m903_M->solverInfo, &rtmGetErrorStatus(m903_M));

      rtsiSetRTModelPtr(&m903_M->solverInfo, m903_M);
    }
    rtsiSetSimTimeStep(&m903_M->solverInfo, MAJOR_TIME_STEP);
    m903_M->ModelData.intgData.y = m903_M->ModelData.odeY;
    m903_M->ModelData.intgData.f[0] = m903_M->ModelData.odeF[0];
    m903_M->ModelData.intgData.f[1] = m903_M->ModelData.odeF[1];
    m903_M->ModelData.intgData.f[2] = m903_M->ModelData.odeF[2];
    m903_M->ModelData.intgData.f[3] = m903_M->ModelData.odeF[3];
    m903_M->ModelData.contStates = ((real_T *) &m903_X);
    rtsiSetSolverData(&m903_M->solverInfo, (void *)&m903_M->ModelData.intgData);
    rtsiSetSolverName(&m903_M->solverInfo,"ode4");

    /* Initialize timing info */
    {
      int_T *mdlTsMap = m903_M->Timing.sampleTimeTaskIDArray;
      mdlTsMap[0] = 0;
      mdlTsMap[1] = 1;
      m903_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
      m903_M->Timing.sampleTimes = (&m903_M->Timing.sampleTimesArray[0]);
      m903_M->Timing.offsetTimes = (&m903_M->Timing.offsetTimesArray[0]);
      /* task periods */
      m903_M->Timing.sampleTimes[0] = (0.0);
      m903_M->Timing.sampleTimes[1] = (0.1);

      /* task offsets */
      m903_M->Timing.offsetTimes[0] = (0.0);
      m903_M->Timing.offsetTimes[1] = (0.0);
    }

    rtmSetTPtr(m903_M, &m903_M->Timing.tArray[0]);

    {
      int_T *mdlSampleHits = m903_M->Timing.sampleHitArray;
      mdlSampleHits[0] = 1;
      mdlSampleHits[1] = 1;
      m903_M->Timing.sampleHits = (&mdlSampleHits[0]);
    }

    rtmSetTFinal(m903_M, 10.0);
    m903_M->Timing.stepSize0 = 0.1;
    m903_M->Timing.stepSize1 = 0.1;

    /* Setup for data logging */
    {
      static RTWLogInfo rt_DataLoggingInfo;

      m903_M->rtwLogInfo = &rt_DataLoggingInfo;

      rtliSetLogFormat(m903_M->rtwLogInfo, 0);

      rtliSetLogMaxRows(m903_M->rtwLogInfo, 5000);

      rtliSetLogDecimation(m903_M->rtwLogInfo, 1);

      rtliSetLogVarNameModifier(m903_M->rtwLogInfo, "rt_");

      rtliSetLogT(m903_M->rtwLogInfo, "tout");

      rtliSetLogX(m903_M->rtwLogInfo, "");

      rtliSetLogXFinal(m903_M->rtwLogInfo, "");

      rtliSetSigLog(m903_M->rtwLogInfo, "");

      rtliSetLogXSignalInfo(m903_M->rtwLogInfo, NULL);

      rtliSetLogXSignalPtrs(m903_M->rtwLogInfo, NULL);

      rtliSetLogY(m903_M->rtwLogInfo, "yout");

      /*
       * Set pointers to the data and signal info for each output
       */
      {
        static void * rt_LoggedOutputSignalPtrs[] = {
          &m903_Y.Out1
        };

        rtliSetLogYSignalPtrs(m903_M->rtwLogInfo,
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
          "m903/Out1"};

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

        rtliSetLogYSignalInfo(m903_M->rtwLogInfo, rt_LoggedOutputSignalInfo);
      }
    }

    m903_M->solverInfoPtr = (&m903_M->solverInfo);
    m903_M->Timing.stepSize = (0.1);
    rtsiSetFixedStepSize(&m903_M->solverInfo, 0.1);
    rtsiSetSolverMode(&m903_M->solverInfo, SOLVER_MODE_SINGLETASKING);

    {
      /* block I/O */
      void *b = (void *) &m903_B;
      m903_M->ModelData.blockIO = (b);

      {

        int_T i;
        b =&m903_B.SineWave;
        for (i = 0; i < 1; i++) {
          ((real_T*)b)[i] = 0.0;
        }
      }
    }
    /* parameters */
    m903_M->ModelData.defaultParam = ((real_T *) &m903_P);
    /* states */
    {
      real_T *x = (real_T *) &m903_X;
      m903_M->ModelData.contStates = (x);
      (void)memset((char_T *)x, 0, sizeof(ContinuousStates_m903));
    }

    /* external outputs */
    m903_M->ModelData.outputs = (&m903_Y);
    m903_Y.Out1 = 0.0;

    /* initialize non-finites */
    rt_InitInfAndNaN(sizeof(real_T));
  }
}

/* Model terminate function */
void m903_terminate(void)
{
}

/*========================================================================*
 * Start of GRT compatible call interface                                 *
 *========================================================================*/

void MdlOutputs(int_T tid) {

  m903_output(tid);
}

void MdlUpdate(int_T tid) {

  m903_update(tid);
}

void MdlInitializeSizes(void) {
  m903_M->Sizes.numContStates = (1);    /* Number of continuous states */
  m903_M->Sizes.numY = (1);             /* Number of model outputs */
  m903_M->Sizes.numU = (0);             /* Number of model inputs */
  m903_M->Sizes.sysDirFeedThru = (0);   /* The model is not direct feedthrough */
  m903_M->Sizes.numSampTimes = (2);     /* Number of sample times */
  m903_M->Sizes.numBlocks = (3);        /* Number of blocks */
  m903_M->Sizes.numBlockIO = (1);       /* Number of block outputs */
  m903_M->Sizes.numBlockPrms = (5);     /* Sum of parameter "widths" */
}

void MdlInitializeSampleTimes(void) {
}

void MdlInitialize(void) {

  /* Integrator Block: <Root>/Integrator */
  m903_X.Integrator_CSTATE = m903_P.Integrator_IC;
}

void MdlStart(void) {
  MdlInitialize();
}

rtModel_m903 *m903(void) {
  m903_initialize(1);
  return m903_M;
}

void MdlTerminate(void) {
  m903_terminate();
}

/*========================================================================*
 * End of GRT compatible call interface                                   *
 *========================================================================*/

