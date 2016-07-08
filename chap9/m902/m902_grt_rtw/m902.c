/*
 * m902.c
 * 
 * Real-Time Workshop code generation for Simulink model "m902.mdl".
 *
 * Model Version              : 1.1
 * Real-Time Workshop version : 6.1  (R14SP1)  05-Sep-2004
 * C source code generated on : Sat Apr 02 08:46:32 2005
 */

#include "m902.h"
#include "m902_private.h"

/* External output (root outports fed by signals with auto storage) */
ExternalOutputs_m902 m902_Y;

/* Real-time model */
rtModel_m902 m902_M_;
rtModel_m902 *m902_M = &m902_M_;

/* Model output function */
static void m902_output(int_T tid)
{

  /* local block i/o variables */

  real_T rtb_Step;

  /* Step: '<Root>/Step' */
  {
    real_T currentTime = m902_M->Timing.t[0];
    if (currentTime < m902_P.Step_Time) {
      rtb_Step = m902_P.Step_Y0;
    } else {
      rtb_Step = m902_P.Step_YFinal;
    }
  }

  /* Outport: '<Root>/Out1' incorporates:
   *  Gain: '<Root>/Gain' */
  m902_Y.Out1 = rtb_Step * m902_P.Gain_Gain;
}

/* Model update function */
static void m902_update(int_T tid)
{

  /* Update absolute time for base rate */

  if(!(++m902_M->Timing.clockTick0)) ++m902_M->Timing.clockTickH0;
  m902_M->Timing.t[0] = m902_M->Timing.clockTick0 * m902_M->Timing.stepSize0 +
    m902_M->Timing.clockTickH0 * m902_M->Timing.stepSize0 * 4294967296.0;

  {
    /* Update absolute timer for sample time: [0.2s, 0.0s] */

    if(!(++m902_M->Timing.clockTick1)) ++m902_M->Timing.clockTickH1;
    m902_M->Timing.t[1] = m902_M->Timing.clockTick1 * m902_M->Timing.stepSize1 +
      m902_M->Timing.clockTickH1 * m902_M->Timing.stepSize1 * 4294967296.0;
  }
}

/* Model initialize function */
void m902_initialize(boolean_T firstTime)
{

  if (firstTime) {
    /* registration code */
    /* initialize real-time model */
    (void)memset((char_T *)m902_M, 0, sizeof(rtModel_m902));

    {
      /* Setup solver object */

      rtsiSetSimTimeStepPtr(&m902_M->solverInfo, &m902_M->Timing.simTimeStep);
      rtsiSetTPtr(&m902_M->solverInfo, &rtmGetTPtr(m902_M));
      rtsiSetStepSizePtr(&m902_M->solverInfo, &m902_M->Timing.stepSize0);
      rtsiSetErrorStatusPtr(&m902_M->solverInfo, &rtmGetErrorStatus(m902_M));

      rtsiSetRTModelPtr(&m902_M->solverInfo, m902_M);
    }
    rtsiSetSimTimeStep(&m902_M->solverInfo, MAJOR_TIME_STEP);

    /* Initialize timing info */
    {
      int_T *mdlTsMap = m902_M->Timing.sampleTimeTaskIDArray;
      mdlTsMap[0] = 0;
      mdlTsMap[1] = 1;
      m902_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
      m902_M->Timing.sampleTimes = (&m902_M->Timing.sampleTimesArray[0]);
      m902_M->Timing.offsetTimes = (&m902_M->Timing.offsetTimesArray[0]);
      /* task periods */
      m902_M->Timing.sampleTimes[0] = (0.0);
      m902_M->Timing.sampleTimes[1] = (0.2);

      /* task offsets */
      m902_M->Timing.offsetTimes[0] = (0.0);
      m902_M->Timing.offsetTimes[1] = (0.0);
    }

    rtmSetTPtr(m902_M, &m902_M->Timing.tArray[0]);

    {
      int_T *mdlSampleHits = m902_M->Timing.sampleHitArray;
      mdlSampleHits[0] = 1;
      mdlSampleHits[1] = 1;
      m902_M->Timing.sampleHits = (&mdlSampleHits[0]);
    }

    rtmSetTFinal(m902_M, 10.0);
    m902_M->Timing.stepSize0 = 0.2;
    m902_M->Timing.stepSize1 = 0.2;

    /* Setup for data logging */
    {
      static RTWLogInfo rt_DataLoggingInfo;

      m902_M->rtwLogInfo = &rt_DataLoggingInfo;

      rtliSetLogFormat(m902_M->rtwLogInfo, 0);

      rtliSetLogMaxRows(m902_M->rtwLogInfo, 1000);

      rtliSetLogDecimation(m902_M->rtwLogInfo, 1);

      rtliSetLogVarNameModifier(m902_M->rtwLogInfo, "rt_");

      rtliSetLogT(m902_M->rtwLogInfo, "tout");

      rtliSetLogX(m902_M->rtwLogInfo, "");

      rtliSetLogXFinal(m902_M->rtwLogInfo, "");

      rtliSetSigLog(m902_M->rtwLogInfo, "");

      rtliSetLogXSignalInfo(m902_M->rtwLogInfo, NULL);

      rtliSetLogXSignalPtrs(m902_M->rtwLogInfo, NULL);

      rtliSetLogY(m902_M->rtwLogInfo, "yout");

      /*
       * Set pointers to the data and signal info for each output
       */
      {
        static void * rt_LoggedOutputSignalPtrs[] = {
          &m902_Y.Out1
        };

        rtliSetLogYSignalPtrs(m902_M->rtwLogInfo,
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
          "m902/Out1"};

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

        rtliSetLogYSignalInfo(m902_M->rtwLogInfo, rt_LoggedOutputSignalInfo);
      }
    }

    m902_M->solverInfoPtr = (&m902_M->solverInfo);
    m902_M->Timing.stepSize = (0.2);
    rtsiSetFixedStepSize(&m902_M->solverInfo, 0.2);
    rtsiSetSolverMode(&m902_M->solverInfo, SOLVER_MODE_SINGLETASKING);

    /* parameters */
    m902_M->ModelData.defaultParam = ((real_T *) &m902_P);

    /* external outputs */
    m902_M->ModelData.outputs = (&m902_Y);
    m902_Y.Out1 = 0.0;

    /* initialize non-finites */
    rt_InitInfAndNaN(sizeof(real_T));
  }
}

/* Model terminate function */
void m902_terminate(void)
{
}

/*========================================================================*
 * Start of GRT compatible call interface                                 *
 *========================================================================*/

void MdlOutputs(int_T tid) {

  m902_output(tid);
}

void MdlUpdate(int_T tid) {

  m902_update(tid);
}

void MdlInitializeSizes(void) {
  m902_M->Sizes.numContStates = (0);    /* Number of continuous states */
  m902_M->Sizes.numY = (1);             /* Number of model outputs */
  m902_M->Sizes.numU = (0);             /* Number of model inputs */
  m902_M->Sizes.sysDirFeedThru = (0);   /* The model is not direct feedthrough */
  m902_M->Sizes.numSampTimes = (2);     /* Number of sample times */
  m902_M->Sizes.numBlocks = (3);        /* Number of blocks */
  m902_M->Sizes.numBlockIO = (0);       /* Number of block outputs */
  m902_M->Sizes.numBlockPrms = (4);     /* Sum of parameter "widths" */
}

void MdlInitializeSampleTimes(void) {
}

void MdlInitialize(void) {
}

void MdlStart(void) {
  MdlInitialize();
}

rtModel_m902 *m902(void) {
  m902_initialize(1);
  return m902_M;
}

void MdlTerminate(void) {
  m902_terminate();
}

/*========================================================================*
 * End of GRT compatible call interface                                   *
 *========================================================================*/

