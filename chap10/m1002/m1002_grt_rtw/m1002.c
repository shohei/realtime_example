/*
 * m1002.c
 * 
 * Real-Time Workshop code generation for Simulink model "m1002.mdl".
 *
 * Model Version              : 1.2
 * Real-Time Workshop version : 6.1  (R14SP1)  05-Sep-2004
 * C source code generated on : Sun Apr 03 14:42:29 2005
 */

#include "m1002.h"
#include "m1002_private.h"

/* Block signals (auto storage) */
BlockIO_m1002 m1002_B;

/* External output (root outports fed by signals with auto storage) */
ExternalOutputs_m1002 m1002_Y;

/* Real-time model */
rtModel_m1002 m1002_M_;
rtModel_m1002 *m1002_M = &m1002_M_;

/* Model output function */
static void m1002_output(int_T tid)
{

  /* Sin: '<Root>/Sine Wave' */
  m1002_B.SineWave = m1002_P.SineWave_Amp *
    sin(m1002_P.SineWave_Freq * m1002_M->Timing.t[0] + m1002_P.SineWave_Phase) +
    m1002_P.SineWave_Bias;

  /* S-Function "myfunc_wrapper" Block: <Root>/S-Function Builder */

  myfunc_Outputs_wrapper(&m1002_B.SineWave, &m1002_B.SFunctionBuilder );

  /* Outport: '<Root>/Out1' */
  m1002_Y.Out1 = m1002_B.SFunctionBuilder;
}

/* Model update function */
static void m1002_update(int_T tid)
{

  /* Update absolute time for base rate */

  if(!(++m1002_M->Timing.clockTick0)) ++m1002_M->Timing.clockTickH0;
  m1002_M->Timing.t[0] = m1002_M->Timing.clockTick0 * m1002_M->Timing.stepSize0
    + m1002_M->Timing.clockTickH0 * m1002_M->Timing.stepSize0 * 4294967296.0;

  {
    /* Update absolute timer for sample time: [0.1s, 0.0s] */

    if(!(++m1002_M->Timing.clockTick1)) ++m1002_M->Timing.clockTickH1;
    m1002_M->Timing.t[1] = m1002_M->Timing.clockTick1 *
      m1002_M->Timing.stepSize1 + m1002_M->Timing.clockTickH1 *
      m1002_M->Timing.stepSize1 * 4294967296.0;
  }
}

/* Model initialize function */
void m1002_initialize(boolean_T firstTime)
{

  if (firstTime) {
    /* registration code */
    /* initialize real-time model */
    (void)memset((char_T *)m1002_M, 0, sizeof(rtModel_m1002));

    {
      /* Setup solver object */

      rtsiSetSimTimeStepPtr(&m1002_M->solverInfo, &m1002_M->Timing.simTimeStep);
      rtsiSetTPtr(&m1002_M->solverInfo, &rtmGetTPtr(m1002_M));
      rtsiSetStepSizePtr(&m1002_M->solverInfo, &m1002_M->Timing.stepSize0);
      rtsiSetErrorStatusPtr(&m1002_M->solverInfo, &rtmGetErrorStatus(m1002_M));

      rtsiSetRTModelPtr(&m1002_M->solverInfo, m1002_M);
    }
    rtsiSetSimTimeStep(&m1002_M->solverInfo, MAJOR_TIME_STEP);

    /* Initialize timing info */
    {
      int_T *mdlTsMap = m1002_M->Timing.sampleTimeTaskIDArray;
      mdlTsMap[0] = 0;
      mdlTsMap[1] = 1;
      m1002_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
      m1002_M->Timing.sampleTimes = (&m1002_M->Timing.sampleTimesArray[0]);
      m1002_M->Timing.offsetTimes = (&m1002_M->Timing.offsetTimesArray[0]);
      /* task periods */
      m1002_M->Timing.sampleTimes[0] = (0.0);
      m1002_M->Timing.sampleTimes[1] = (0.1);

      /* task offsets */
      m1002_M->Timing.offsetTimes[0] = (0.0);
      m1002_M->Timing.offsetTimes[1] = (0.0);
    }

    rtmSetTPtr(m1002_M, &m1002_M->Timing.tArray[0]);

    {
      int_T *mdlSampleHits = m1002_M->Timing.sampleHitArray;
      mdlSampleHits[0] = 1;
      mdlSampleHits[1] = 1;
      m1002_M->Timing.sampleHits = (&mdlSampleHits[0]);
    }

    rtmSetTFinal(m1002_M, 10.0);
    m1002_M->Timing.stepSize0 = 0.1;
    m1002_M->Timing.stepSize1 = 0.1;

    /* Setup for data logging */
    {
      static RTWLogInfo rt_DataLoggingInfo;

      m1002_M->rtwLogInfo = &rt_DataLoggingInfo;

      rtliSetLogFormat(m1002_M->rtwLogInfo, 0);

      rtliSetLogMaxRows(m1002_M->rtwLogInfo, 1000);

      rtliSetLogDecimation(m1002_M->rtwLogInfo, 1);

      rtliSetLogVarNameModifier(m1002_M->rtwLogInfo, "rt_");

      rtliSetLogT(m1002_M->rtwLogInfo, "tout");

      rtliSetLogX(m1002_M->rtwLogInfo, "");

      rtliSetLogXFinal(m1002_M->rtwLogInfo, "");

      rtliSetSigLog(m1002_M->rtwLogInfo, "");

      rtliSetLogXSignalInfo(m1002_M->rtwLogInfo, NULL);

      rtliSetLogXSignalPtrs(m1002_M->rtwLogInfo, NULL);

      rtliSetLogY(m1002_M->rtwLogInfo, "yout");

      /*
       * Set pointers to the data and signal info for each output
       */
      {
        static void * rt_LoggedOutputSignalPtrs[] = {
          &m1002_Y.Out1
        };

        rtliSetLogYSignalPtrs(m1002_M->rtwLogInfo,
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
          "m1002/Out1"};

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

        rtliSetLogYSignalInfo(m1002_M->rtwLogInfo, rt_LoggedOutputSignalInfo);
      }
    }

    m1002_M->solverInfoPtr = (&m1002_M->solverInfo);
    m1002_M->Timing.stepSize = (0.1);
    rtsiSetFixedStepSize(&m1002_M->solverInfo, 0.1);
    rtsiSetSolverMode(&m1002_M->solverInfo, SOLVER_MODE_SINGLETASKING);

    {
      /* block I/O */
      void *b = (void *) &m1002_B;
      m1002_M->ModelData.blockIO = (b);

      {

        int_T i;
        b =&m1002_B.SineWave;
        for (i = 0; i < 2; i++) {
          ((real_T*)b)[i] = 0.0;
        }
      }
    }
    /* parameters */
    m1002_M->ModelData.defaultParam = ((real_T *) &m1002_P);

    /* external outputs */
    m1002_M->ModelData.outputs = (&m1002_Y);
    m1002_Y.Out1 = 0.0;

    /* initialize non-finites */
    rt_InitInfAndNaN(sizeof(real_T));
  }
}

/* Model terminate function */
void m1002_terminate(void)
{
}

/*========================================================================*
 * Start of GRT compatible call interface                                 *
 *========================================================================*/

void MdlOutputs(int_T tid) {

  m1002_output(tid);
}

void MdlUpdate(int_T tid) {

  m1002_update(tid);
}

void MdlInitializeSizes(void) {
  m1002_M->Sizes.numContStates = (0);   /* Number of continuous states */
  m1002_M->Sizes.numY = (1);            /* Number of model outputs */
  m1002_M->Sizes.numU = (0);            /* Number of model inputs */
  m1002_M->Sizes.sysDirFeedThru = (0); /* The model is not direct feedthrough */
  m1002_M->Sizes.numSampTimes = (2);    /* Number of sample times */
  m1002_M->Sizes.numBlocks = (3);       /* Number of blocks */
  m1002_M->Sizes.numBlockIO = (2);      /* Number of block outputs */
  m1002_M->Sizes.numBlockPrms = (4);    /* Sum of parameter "widths" */
}

void MdlInitializeSampleTimes(void) {
}

void MdlInitialize(void) {
}

void MdlStart(void) {
  MdlInitialize();
}

rtModel_m1002 *m1002(void) {
  m1002_initialize(1);
  return m1002_M;
}

void MdlTerminate(void) {
  m1002_terminate();
}

/*========================================================================*
 * End of GRT compatible call interface                                   *
 *========================================================================*/

