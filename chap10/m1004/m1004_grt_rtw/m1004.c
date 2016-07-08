/*
 * m1004.c
 * 
 * Real-Time Workshop code generation for Simulink model "m1004.mdl".
 *
 * Model Version              : 1.1
 * Real-Time Workshop version : 6.1  (R14SP1)  05-Sep-2004
 * C source code generated on : Sun Apr 03 16:14:19 2005
 */

#include "m1004.h"
#include "m1004_private.h"

/* Block signals (auto storage) */
BlockIO_m1004 m1004_B;

/* External output (root outports fed by signals with auto storage) */
ExternalOutputs_m1004 m1004_Y;

/* Real-time model */
rtModel_m1004 m1004_M_;
rtModel_m1004 *m1004_M = &m1004_M_;

/* Model output function */
static void m1004_output(int_T tid)
{

  /* Sin: '<Root>/Sine Wave' */
  m1004_B.SineWave = m1004_P.SineWave_Amp *
    sin(m1004_P.SineWave_Freq * m1004_M->Timing.t[0] + m1004_P.SineWave_Phase) +
    m1004_P.SineWave_Bias;

  /* S-Function "myfunc_wrapper" Block: <Root>/S-Function Builder */

  myfunc_Outputs_wrapper(&m1004_B.SineWave, &m1004_B.SFunctionBuilder );
  printf("Hello World!\n");

  /* Outport: '<Root>/Out1' */
  m1004_Y.Out1 = m1004_B.SFunctionBuilder;
}

/* Model update function */
static void m1004_update(int_T tid)
{

  /* Update absolute time for base rate */

  if(!(++m1004_M->Timing.clockTick0)) ++m1004_M->Timing.clockTickH0;
  m1004_M->Timing.t[0] = m1004_M->Timing.clockTick0 * m1004_M->Timing.stepSize0
    + m1004_M->Timing.clockTickH0 * m1004_M->Timing.stepSize0 * 4294967296.0;

  {
    /* Update absolute timer for sample time: [0.1s, 0.0s] */

    if(!(++m1004_M->Timing.clockTick1)) ++m1004_M->Timing.clockTickH1;
    m1004_M->Timing.t[1] = m1004_M->Timing.clockTick1 *
      m1004_M->Timing.stepSize1 + m1004_M->Timing.clockTickH1 *
      m1004_M->Timing.stepSize1 * 4294967296.0;
  }
}

/* Model initialize function */
void m1004_initialize(boolean_T firstTime)
{

  if (firstTime) {
    /* registration code */
    /* initialize real-time model */
    (void)memset((char_T *)m1004_M, 0, sizeof(rtModel_m1004));

    {
      /* Setup solver object */

      rtsiSetSimTimeStepPtr(&m1004_M->solverInfo, &m1004_M->Timing.simTimeStep);
      rtsiSetTPtr(&m1004_M->solverInfo, &rtmGetTPtr(m1004_M));
      rtsiSetStepSizePtr(&m1004_M->solverInfo, &m1004_M->Timing.stepSize0);
      rtsiSetErrorStatusPtr(&m1004_M->solverInfo, &rtmGetErrorStatus(m1004_M));

      rtsiSetRTModelPtr(&m1004_M->solverInfo, m1004_M);
    }
    rtsiSetSimTimeStep(&m1004_M->solverInfo, MAJOR_TIME_STEP);

    /* Initialize timing info */
    {
      int_T *mdlTsMap = m1004_M->Timing.sampleTimeTaskIDArray;
      mdlTsMap[0] = 0;
      mdlTsMap[1] = 1;
      m1004_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
      m1004_M->Timing.sampleTimes = (&m1004_M->Timing.sampleTimesArray[0]);
      m1004_M->Timing.offsetTimes = (&m1004_M->Timing.offsetTimesArray[0]);
      /* task periods */
      m1004_M->Timing.sampleTimes[0] = (0.0);
      m1004_M->Timing.sampleTimes[1] = (0.1);

      /* task offsets */
      m1004_M->Timing.offsetTimes[0] = (0.0);
      m1004_M->Timing.offsetTimes[1] = (0.0);
    }

    rtmSetTPtr(m1004_M, &m1004_M->Timing.tArray[0]);

    {
      int_T *mdlSampleHits = m1004_M->Timing.sampleHitArray;
      mdlSampleHits[0] = 1;
      mdlSampleHits[1] = 1;
      m1004_M->Timing.sampleHits = (&mdlSampleHits[0]);
    }

    rtmSetTFinal(m1004_M, 10.0);
    m1004_M->Timing.stepSize0 = 0.1;
    m1004_M->Timing.stepSize1 = 0.1;

    /* Setup for data logging */
    {
      static RTWLogInfo rt_DataLoggingInfo;

      m1004_M->rtwLogInfo = &rt_DataLoggingInfo;

      rtliSetLogFormat(m1004_M->rtwLogInfo, 0);

      rtliSetLogMaxRows(m1004_M->rtwLogInfo, 1000);

      rtliSetLogDecimation(m1004_M->rtwLogInfo, 1);

      rtliSetLogVarNameModifier(m1004_M->rtwLogInfo, "rt_");

      rtliSetLogT(m1004_M->rtwLogInfo, "tout");

      rtliSetLogX(m1004_M->rtwLogInfo, "");

      rtliSetLogXFinal(m1004_M->rtwLogInfo, "");

      rtliSetSigLog(m1004_M->rtwLogInfo, "");

      rtliSetLogXSignalInfo(m1004_M->rtwLogInfo, NULL);

      rtliSetLogXSignalPtrs(m1004_M->rtwLogInfo, NULL);

      rtliSetLogY(m1004_M->rtwLogInfo, "yout");

      /*
       * Set pointers to the data and signal info for each output
       */
      {
        static void * rt_LoggedOutputSignalPtrs[] = {
          &m1004_Y.Out1
        };

        rtliSetLogYSignalPtrs(m1004_M->rtwLogInfo,
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
          "m1004/Out1"};

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

        rtliSetLogYSignalInfo(m1004_M->rtwLogInfo, rt_LoggedOutputSignalInfo);
      }
    }

    m1004_M->solverInfoPtr = (&m1004_M->solverInfo);
    m1004_M->Timing.stepSize = (0.1);
    rtsiSetFixedStepSize(&m1004_M->solverInfo, 0.1);
    rtsiSetSolverMode(&m1004_M->solverInfo, SOLVER_MODE_SINGLETASKING);

    {
      /* block I/O */
      void *b = (void *) &m1004_B;
      m1004_M->ModelData.blockIO = (b);

      {

        int_T i;
        b =&m1004_B.SineWave;
        for (i = 0; i < 2; i++) {
          ((real_T*)b)[i] = 0.0;
        }
      }
    }
    /* parameters */
    m1004_M->ModelData.defaultParam = ((real_T *) &m1004_P);

    /* external outputs */
    m1004_M->ModelData.outputs = (&m1004_Y);
    m1004_Y.Out1 = 0.0;

    /* initialize non-finites */
    rt_InitInfAndNaN(sizeof(real_T));
  }
}

/* Model terminate function */
void m1004_terminate(void)
{
}

/*========================================================================*
 * Start of GRT compatible call interface                                 *
 *========================================================================*/

void MdlOutputs(int_T tid) {

  m1004_output(tid);
}

void MdlUpdate(int_T tid) {

  m1004_update(tid);
}

void MdlInitializeSizes(void) {
  m1004_M->Sizes.numContStates = (0);   /* Number of continuous states */
  m1004_M->Sizes.numY = (1);            /* Number of model outputs */
  m1004_M->Sizes.numU = (0);            /* Number of model inputs */
  m1004_M->Sizes.sysDirFeedThru = (0); /* The model is not direct feedthrough */
  m1004_M->Sizes.numSampTimes = (2);    /* Number of sample times */
  m1004_M->Sizes.numBlocks = (3);       /* Number of blocks */
  m1004_M->Sizes.numBlockIO = (2);      /* Number of block outputs */
  m1004_M->Sizes.numBlockPrms = (4);    /* Sum of parameter "widths" */
}

void MdlInitializeSampleTimes(void) {
}

void MdlInitialize(void) {
}

void MdlStart(void) {
  MdlInitialize();
}

rtModel_m1004 *m1004(void) {
  m1004_initialize(1);
  return m1004_M;
}

void MdlTerminate(void) {
  m1004_terminate();
}

/*========================================================================*
 * End of GRT compatible call interface                                   *
 *========================================================================*/

