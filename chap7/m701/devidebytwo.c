	#define S_FUNCTION_NAME  devidebytwo
	#define S_FUNCTION_LEVEL 2
	#include "simstruc.h"
	static void mdlInitializeSizes(SimStruct *S)
	{
	    ssSetNumSFcnParams(S, 0);
	    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) return;
	    if (!ssSetNumInputPorts(S, 1)) return;
	    ssSetInputPortWidth(S, 0, DYNAMICALLY_SIZED);
	    ssSetInputPortDirectFeedThrough(S, 0, 1);
	    if (!ssSetNumOutputPorts(S,1)) return;
	    ssSetOutputPortWidth(S, 0, DYNAMICALLY_SIZED);
	    ssSetNumSampleTimes(S, 1);
	    ssSetOptions(S,
	                 SS_OPTION_WORKS_WITH_CODE_REUSE |
	                 SS_OPTION_EXCEPTION_FREE_CODE |
                     SS_OPTION_USE_TLC_WITH_ACCELERATOR);
	}
	static void mdlInitializeSampleTimes(SimStruct *S)
	{
	    ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
	    ssSetOffsetTime(S, 0, 0.0);
	    ssSetModelReferenceSampleTimeDefaultInheritance(S); 
	}
	static void mdlOutputs(SimStruct *S, int_T tid)
	{
	    int_T             i;
	    InputRealPtrsType uPtrs = ssGetInputPortRealSignalPtrs(S,0);
	    real_T            *y    = ssGetOutputPortRealSignal(S,0);
	    int_T             width = ssGetOutputPortWidth(S,0);
	    for (i=0; i<width; i++) {
	        *y++ = (*uPtrs[i])/2.0; 
	    }
	}
	static void mdlTerminate(SimStruct *S)
	{
	}
	#ifdef  MATLAB_MEX_FILE
	#include "simulink.c"
	#else
	#include "cg_sfun.h"
	#endif
