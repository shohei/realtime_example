#define S_FUNCTION_NAME spaceshipRot
#define S_FUNCTION_LEVEL 2
#include "simstruc.h"
#define U(element) (*uPtrs[element])
static real_T R[3][3]={ {  1, 0, 0 } ,
                        {  0, 1, 0 } ,
                        {  0, 0, 1 }  };
static real_T invI[3][3]={{  1,  0, 0   } ,
                           {  0,0.5, 0   } ,
                           {  0,  0, 0.5 }  };
static void mdlInitializeSizes(SimStruct *S)
{
    ssSetNumSFcnParams(S, 0);
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) return;
    ssSetNumContStates(S, 18);
    ssSetNumDiscStates(S, 0);
    if (!ssSetNumInputPorts(S, 1)) return;
    ssSetInputPortWidth(S, 0, 3);
    ssSetInputPortDirectFeedThrough(S, 0, 1);
    if (!ssSetNumOutputPorts(S, 3)) return;
    ssSetOutputPortWidth(S, 0, 9);
    ssSetOutputPortWidth(S, 1, 3);
    ssSetOutputPortWidth(S, 2, 3);
    ssSetNumSampleTimes(S, 1);
    ssSetNumRWork(S, 0);
    ssSetNumIWork(S, 0);
    ssSetNumPWork(S, 0);
    ssSetNumModes(S, 0);
    ssSetNumNonsampledZCs(S, 0);
    ssSetOptions(S, SS_OPTION_EXCEPTION_FREE_CODE);
}
static void mdlInitializeSampleTimes(SimStruct *S)
{
    ssSetSampleTime(S, 0, CONTINUOUS_SAMPLE_TIME);
    ssSetOffsetTime(S, 0, 0.0);
    ssSetModelReferenceSampleTimeDefaultInheritance(S);         
}
#define MDL_INITIALIZE_CONDITIONS
static void mdlInitializeConditions(SimStruct *S)
{
    real_T *x0 = ssGetContStates(S);
    x0[0]=1;x0[1]=0;x0[2]=0;
    x0[3]=0;x0[4]=1;x0[5]=0;
    x0[6]=0;x0[7]=0;x0[8]=1;
    x0[9]=0;x0[10]=0;x0[11]=0;
    x0[12]=0;x0[13]=0;x0[14]=0;
    x0[15]=0;x0[16]=0;x0[17]=0;
}
static void mdlOutputs(SimStruct *S, int_T tid)
{
    real_T *y = ssGetOutputPortRealSignal(S,0);
    real_T *y1 = ssGetOutputPortRealSignal(S,1);
    real_T *y2 = ssGetOutputPortRealSignal(S,2);
    real_T *x = ssGetContStates(S);
    int_T i;    
    for(i=0;i<9;i++)
    {
        y[i]=x[i];
    }
    for(i=0;i<3;i++)
    {
        y1[i]=x[i+12];
    }
    for(i=0;i<3;i++)
    {
        y2[i]=x[i+9];
    }
}
#define MDL_DERIVATIVES
static void mdlDerivatives(SimStruct *S)
{
    real_T *dx = ssGetdX(S);
    real_T *x = ssGetContStates(S);
    InputRealPtrsType uPtrs = ssGetInputPortRealSignalPtrs(S,0);
    int_T i,j;
    real_T W[3][3],W1[3][3];
    
    R[0][0]=x[0];
    R[1][0]=x[1];
    R[2][0]=x[2];
    R[0][1]=x[3];
    R[1][1]=x[4];
    R[2][1]=x[5];
    R[0][2]=x[6];
    R[1][2]=x[7];
    R[2][2]=x[8];
    
    multMat(W1,R,invI);
    transMat(R);
    multMat(W,W1,R);
    transMat(R);
    for(i=0;i<3;i++)
    {
        x[i+9]=0;
        for(j=0;j<3;j++)
        {
            x[i+9]+=W[i][j]*x[15+j];
        }
    }
    dx[0]=-x[11]*R[1][0]+x[10]*R[2][0];
    dx[1]= x[11]*R[0][0]-x[9]*R[2][0];
    dx[2]=-x[10]*R[0][0]+x[9]*R[1][0];
    dx[3]=-x[11]*R[1][1]+x[10]*R[2][1];
    dx[4]= x[11]*R[0][1]-x[9]*R[2][1];
    dx[5]=-x[10]*R[0][1]+x[9]*R[1][1];
    dx[6]=-x[11]*R[1][2]+x[10]*R[2][2];
    dx[7]= x[11]*R[0][2]-x[9]*R[2][2];
    dx[8]=-x[10]*R[0][2]+x[9]*R[1][2];
    
    dx[9]=0;
    dx[10]=0;
    dx[11]=0;
    
    dx[12]= x[9];
    dx[13]= x[10];
    dx[14]= x[11];
    
    dx[15]= U(0);
    dx[16]= U(1);
    dx[17]= U(2);
}
void multMat(real_T a[3][3], real_T b[3][3], real_T c[3][3])
{
    int_T i,j,k;
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            a[i][j]=0;
            for(k=0;k<3;k++)
            {
                a[i][j]+=b[i][k]*c[k][j];
            }
        }
    }
}
void transMat(real_T a[3][3])
{
    real_T w12,w13,w23;
    w12=a[1][2];
    w13=a[1][3];
    w23=a[2][3];
    a[1][2]=a[2][1];
    a[1][3]=a[3][1];
    a[2][3]=a[3][2];
    a[2][1]=w12;
    a[3][1]=w13;
    a[3][2]=w23;
}
static void mdlTerminate(SimStruct *S)
{
    UNUSED_ARG(S);
}

#ifdef  MATLAB_MEX_FILE
#include "simulink.c"
#else
#include "cg_sfun.h"
#endif