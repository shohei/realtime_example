/*
 * m1107.c
 * 
 * Real-Time Workshop code generation for Simulink model "m1107.mdl".
 *
 * Model Version              : 1.10
 * Real-Time Workshop version : 6.1  (R14SP1)  05-Sep-2004
 * C source code generated on : Fri Apr 15 10:30:52 2005
 */

#include "m1107.h"
#include "m1107_private.h"

#include <stdio.h>
#include "m1107_dt.h"

/* Block signals (auto storage) */
BlockIO_m1107 m1107_B;

/* Continuous states */
ContinuousStates_m1107 m1107_X;

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
D_Work_m1107 m1107_DWork;

/* Real-time model */
rtModel_m1107 m1107_M_;
rtModel_m1107 *m1107_M = &m1107_M_;

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

  int_T nXc = 16;

  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void)memcpy(y, x, nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  m1107_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }
  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  m1107_output(0);
  m1107_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++) hB[i] = h * rt_ODE3_B[1][i];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }
  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  m1107_output(0);
  m1107_derivatives();

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
void m1107_output(int_T tid)
{

  /* local block i/o variables */

  real_T rtb_Integrator1_j[4];
  real_T rtb_MathFunction1;
  real_T rtb_Product3;
  real_T rtb_Product4;
  real_T rtb_Product5;
  real_T rtb_Product2;
  real_T rtb_TmpHiddenBuffer_Feeding_Mat[3];
  real_T rtb_Product6;
  real_T rtb_Product1_n;
  real_T rtb_TmpHiddenBuffer_Feeding_M_g[3];
  real_T rtb_TmpHiddenBuffer_Feeding_M_e[3];
  real_T rtb_TmpHiddenBuffer_Feeding__gp[3];
  real_T rtb_TmpHiddenBuffer_Feeding_M_p[3];
  real_T rtb_TmpHiddenBuffer_Feeding__ec[3];
  real_T rtb_Product_d[3];
  real_T rtb_Add_g[3];
  real_T rtb_DotProduct;
  real_T rtb_Integrator[3];
  real_T rtb_MathFunction[9];
  real_T rtb_temp44[9];
  real_T rtb_temp45;
  real_T rtb_temp46[3];

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(m1107_M)) {
    m1107_M->Timing.t[0] = rtsiGetT(&m1107_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(m1107_M)) {
    /* set solver stop time */
    rtsiSetSolverStopTime(&m1107_M->solverInfo,
     ((m1107_M->Timing.clockTick0+1)*m1107_M->Timing.stepSize0));
  }                                     /* end MajorTimeStep */

  /* Integrator: '<S1>/Integrator1' */
  rtb_Integrator1_j[0] = m1107_X.Integrator1_CSTATE[0];
  rtb_Integrator1_j[1] = m1107_X.Integrator1_CSTATE[1];
  rtb_Integrator1_j[2] = m1107_X.Integrator1_CSTATE[2];
  rtb_Integrator1_j[3] = m1107_X.Integrator1_CSTATE[3];

  /* S-Function Block (sfix_dot): <S1>/norm */
  rtb_temp45 = rtb_Integrator1_j[0] * rtb_Integrator1_j[0];
  rtb_temp45 += rtb_Integrator1_j[1] * rtb_Integrator1_j[1];
  rtb_temp45 += rtb_Integrator1_j[2] * rtb_Integrator1_j[2];
  rtb_temp45 += rtb_Integrator1_j[3] * rtb_Integrator1_j[3];

  /* Math: '<S3>/Math Function1' */
  /* Operator : sqrt */
  if (rtb_temp45 < 0.0) {
    rtb_MathFunction1 = -sqrt(-rtb_temp45);
  } else {
    rtb_MathFunction1 = sqrt(rtb_temp45);
  }

  {
    real_T Gain_h_1;
    real_T Product_e_1;
    real_T Product_e_2;
    real_T Gain_h_0;
    real_T Product_e_0;

    /* Gain: '<S5>/Gain' incorporates:
     *  Product: '<S3>/Divide' */
    Gain_h_0 = rtb_Integrator1_j[0] / rtb_MathFunction1 * m1107_P.Gain_Gain;
    Gain_h_1 = rtb_Integrator1_j[1] / rtb_MathFunction1 * m1107_P.Gain_Gain;
    rtb_Product6 = rtb_Integrator1_j[2] / rtb_MathFunction1 * m1107_P.Gain_Gain;
    rtb_Product1_n = rtb_Integrator1_j[3] / rtb_MathFunction1 *
      m1107_P.Gain_Gain;

    /* Product: '<S5>/Product' */
    Product_e_0 = Gain_h_1 * Gain_h_1;
    Product_e_1 = rtb_Product6 * rtb_Product6;
    Product_e_2 = rtb_Product1_n * rtb_Product1_n;

    /* Product: '<S5>/Product3' */
    rtb_Product3 = Gain_h_0 * rtb_Product1_n;

    /* Product: '<S5>/Product4' */
    rtb_Product4 = rtb_Product6 * Gain_h_1;

    /* Product: '<S5>/Product5' */
    rtb_Product5 = rtb_Product1_n * Gain_h_1;

    /* Product: '<S5>/Product2' */
    rtb_Product2 = Gain_h_0 * rtb_Product6;

    /* SignalConversion: '<S5>/TmpHiddenBuffer_Feeding_Matrix Concatenation_AtInput1' incorporates:
     *  Sum: '<S5>/Sum'
     *  Sum: '<S5>/Add'
     *  Sum: '<S5>/Add1'
     *  Constant: '<S5>/Constant1'
     */
    rtb_TmpHiddenBuffer_Feeding_Mat[0] = (m1107_P.Constant1_Value - Product_e_1)
      - Product_e_2;
    rtb_TmpHiddenBuffer_Feeding_Mat[1] = rtb_Product3 + rtb_Product4;
    rtb_TmpHiddenBuffer_Feeding_Mat[2] = rtb_Product5 - rtb_Product2;

    /* Product: '<S5>/Product6' */
    rtb_Product6 *= rtb_Product1_n;

    /* Product: '<S5>/Product1' */
    rtb_Product1_n = Gain_h_0 * Gain_h_1;

    /* SignalConversion: '<S5>/TmpHiddenBuffer_Feeding_Matrix Concatenation_AtInput2' incorporates:
     *  Sum: '<S5>/Add2'
     *  Sum: '<S5>/Sum1'
     *  Sum: '<S5>/Add3'
     *  Constant: '<S5>/Constant1'
     */
    rtb_TmpHiddenBuffer_Feeding_M_g[0] = rtb_Product4 - rtb_Product3;
    rtb_TmpHiddenBuffer_Feeding_M_g[1] = (m1107_P.Constant1_Value - Product_e_0)
      - Product_e_2;
    rtb_TmpHiddenBuffer_Feeding_M_g[2] = rtb_Product6 + rtb_Product1_n;

    /* SignalConversion: '<S5>/TmpHiddenBuffer_Feeding_Matrix Concatenation_AtInput3' incorporates:
     *  Sum: '<S5>/Add4'
     *  Sum: '<S5>/Add5'
     *  Sum: '<S5>/Sum2'
     *  Constant: '<S5>/Constant1'
     */
    rtb_TmpHiddenBuffer_Feeding_M_e[0] = rtb_Product5 + rtb_Product2;
    rtb_TmpHiddenBuffer_Feeding_M_e[1] = rtb_Product6 - rtb_Product1_n;
    rtb_TmpHiddenBuffer_Feeding_M_e[2] = (m1107_P.Constant1_Value - Product_e_0)
      - Product_e_1;
  }

  /* 
   * Matrix Concatenation: <S5>/Matrix Concatenation
   * Horizontal matrix concatenation, 
   * 3 inputs, real, data type: real_T.
   */
  (void) memcpy( ((byte_T *)(m1107_B.MatrixConcatenation)),
   (byte_T *)rtb_TmpHiddenBuffer_Feeding_Mat, 3 * sizeof(real_T) ); /* Input 1: [3x1] */
  (void) memcpy( ((byte_T *)(m1107_B.MatrixConcatenation)) + (3 *
    sizeof(real_T)),
   (byte_T *)rtb_TmpHiddenBuffer_Feeding_M_g, 3 * sizeof(real_T) ); /* Input 2: [3x1] */
  (void) memcpy( ((byte_T *)(m1107_B.MatrixConcatenation)) + (6 *
    sizeof(real_T)),
   (byte_T *)rtb_TmpHiddenBuffer_Feeding_M_e, 3 * sizeof(real_T) ); /* Input 3: [3x1] */

  /* Integrator: '<Root>/Integrator2' */
  m1107_B.Integrator2[0] = m1107_X.Integrator2_CSTATE[0];
  m1107_B.Integrator2[1] = m1107_X.Integrator2_CSTATE[1];
  m1107_B.Integrator2[2] = m1107_X.Integrator2_CSTATE[2];

  /* Integrator: '<S2>/Integrator1' */
  m1107_B.Integrator1[0] = m1107_X.Integrator1_i_CSTATE[0];
  m1107_B.Integrator1[1] = m1107_X.Integrator1_i_CSTATE[1];
  m1107_B.Integrator1[2] = m1107_X.Integrator1_i_CSTATE[2];

  /* Sin: '<Root>/Sine Wave' */
  rtb_temp45 = m1107_P.SineWave_Amp *
    sin(m1107_P.SineWave_Freq * m1107_M->Timing.t[0] + m1107_P.SineWave_Phase) +
    m1107_P.SineWave_Bias;

  /* S-Function Block: <Root>/Reshape */
  rtb_temp46[0] = m1107_P.Constant2_Value;
  rtb_temp46[1] = rtb_temp45;
  rtb_temp46[2] = m1107_P.Constant3_Value;

  /* Product: '<Root>/Product' */
  {
    static const int dims[3] = { 3, 3, 1 };
    rt_MatMultRR_Dbl(m1107_B.Product, m1107_B.MatrixConcatenation,
     rtb_temp46, &dims[0]);
  }

  /* Sin: '<Root>/Sine Wave1' */
  rtb_temp45 = m1107_P.SineWave1_Amp *
    sin(m1107_P.SineWave1_Freq * m1107_M->Timing.t[0] + m1107_P.SineWave1_Phase)
    + m1107_P.SineWave1_Bias;

  /* S-Function Block: <Root>/Reshape1 */
  rtb_temp46[0] = rtb_temp45;
  rtb_temp46[1] = m1107_P.Constant_Value;
  rtb_temp46[2] = m1107_P.Constant1_Value_b;

  /* Product: '<Root>/Product1' */
  {
    static const int dims[3] = { 3, 3, 1 };
    rt_MatMultRR_Dbl(m1107_B.Product1, m1107_B.MatrixConcatenation,
     rtb_temp46, &dims[0]);
  }

  /* Integrator: '<S1>/Integrator' */
  rtb_temp46[0] = m1107_X.Integrator_CSTATE[0];
  rtb_temp46[1] = m1107_X.Integrator_CSTATE[1];
  rtb_temp46[2] = m1107_X.Integrator_CSTATE[2];

  /* Math: '<S1>/Math Function' */
  /* Operator : transpose */
  {
    uint32_T count = 0;
    uint32_T row = 0;
    uint32_T col = 0;
    for (row= 0; row < 3; row++) {
      for (col= 0; col < 3; col++) {
        rtb_MathFunction[row + 3 * col] = m1107_B.MatrixConcatenation[count];
        count++;
      }
    }
  }

  /* Product: '<S1>/Product1' incorporates:
   *  Constant: '<S1>/Constant2'
   */
  {
    static const int dims[6] = { 3, 3, 3 , 3, 3, 3 };
    rt_MatDivRR_Dbl(&m1107_DWork.Product1_DWORK4[0],
     (real_T*)&m1107_P.Constant2_Value_n[0], rtb_MathFunction,
     (real_T*)&m1107_DWork.Product1_DWORK1[0], &m1107_DWork.Product1_DWORK2[0],
     (real_T*)&m1107_DWork.Product1_DWORK3[0], &dims[0]);
    rt_MatMultRR_Dbl(rtb_temp44, m1107_B.MatrixConcatenation,
     &m1107_DWork.Product1_DWORK4[0], &dims[3]);
  }

  /* Product: '<S1>/Product' */
  {
    static const int dims[3] = { 3, 3, 1 };
    rt_MatMultRR_Dbl(m1107_B.Product_a, rtb_temp44,
     rtb_temp46, &dims[0]);
  }

  /* SignalConversion: '<S6>/TmpHiddenBuffer_Feeding_Matrix Concatenation_AtInput1' incorporates:
   *  Gain: '<S6>/Gain'
   *  Constant: '<S6>/Constant1'
   */
  rtb_TmpHiddenBuffer_Feeding__gp[0] = m1107_P.Constant1_Value_k;
  rtb_TmpHiddenBuffer_Feeding__gp[1] = m1107_B.Product_a[2];
  rtb_TmpHiddenBuffer_Feeding__gp[2] = m1107_B.Product_a[1] *
    m1107_P.Gain_Gain_n;

  /* SignalConversion: '<S6>/TmpHiddenBuffer_Feeding_Matrix Concatenation_AtInput2' incorporates:
   *  Gain: '<S6>/Gain1'
   *  Constant: '<S6>/Constant1'
   */
  rtb_TmpHiddenBuffer_Feeding_M_p[0] = m1107_B.Product_a[2] * m1107_P.Gain1_Gain;
  rtb_TmpHiddenBuffer_Feeding_M_p[1] = m1107_P.Constant1_Value_k;
  rtb_TmpHiddenBuffer_Feeding_M_p[2] = m1107_B.Product_a[0];

  /* SignalConversion: '<S6>/TmpHiddenBuffer_Feeding_Matrix Concatenation_AtInput3' incorporates:
   *  Gain: '<S6>/Gain2'
   *  Constant: '<S6>/Constant1'
   */
  rtb_TmpHiddenBuffer_Feeding__ec[0] = m1107_B.Product_a[1];
  rtb_TmpHiddenBuffer_Feeding__ec[1] = m1107_B.Product_a[0] * m1107_P.Gain2_Gain;
  rtb_TmpHiddenBuffer_Feeding__ec[2] = m1107_P.Constant1_Value_k;

  /* 
   * Matrix Concatenation: <S6>/Matrix Concatenation
   * Horizontal matrix concatenation, 
   * 3 inputs, real, data type: real_T.
   */
  (void) memcpy( ((byte_T *)(rtb_temp44)),
   (byte_T *)rtb_TmpHiddenBuffer_Feeding__gp, 3 * sizeof(real_T) ); /* Input 1: [3x1] */
  (void) memcpy( ((byte_T *)(rtb_temp44)) + (3 * sizeof(real_T)),
   (byte_T *)rtb_TmpHiddenBuffer_Feeding_M_p, 3 * sizeof(real_T) ); /* Input 2: [3x1] */
  (void) memcpy( ((byte_T *)(rtb_temp44)) + (6 * sizeof(real_T)),
   (byte_T *)rtb_TmpHiddenBuffer_Feeding__ec, 3 * sizeof(real_T) ); /* Input 3: [3x1] */

  /* Product: '<S4>/Product' */
  {
    static const int dims[3] = { 3, 3, 1 };
    rt_MatMultRR_Dbl(rtb_Product_d, rtb_temp44,
     &rtb_Integrator1_j[1], &dims[0]);
  }

  /* Sum: '<S4>/Add' incorporates:
   *  Product: '<S4>/Product1' */
  rtb_Add_g[0] = rtb_Product_d[0] + m1107_B.Product_a[0] * rtb_Integrator1_j[0];
  rtb_Add_g[1] = rtb_Product_d[1] + m1107_B.Product_a[1] * rtb_Integrator1_j[0];
  rtb_Add_g[2] = rtb_Product_d[2] + m1107_B.Product_a[2] * rtb_Integrator1_j[0];

  /* S-Function Block (sfix_dot): <S1>/omegaXquat  */
  rtb_DotProduct = m1107_B.Product_a[0] * rtb_Integrator1_j[1];
  rtb_DotProduct += m1107_B.Product_a[1] * rtb_Integrator1_j[2];
  rtb_DotProduct += m1107_B.Product_a[2] * rtb_Integrator1_j[3];

  /* Gain: '<S4>/Gain1' incorporates:
   *  Gain: '<S4>/Gain' */
  m1107_B.Gain1[0] = rtb_DotProduct * m1107_P.Gain_Gain_o * m1107_P.Gain1_Gain_e;
  m1107_B.Gain1[1] = rtb_Add_g[0] * m1107_P.Gain1_Gain_e;
  m1107_B.Gain1[2] = rtb_Add_g[1] * m1107_P.Gain1_Gain_e;
  m1107_B.Gain1[3] = rtb_Add_g[2] * m1107_P.Gain1_Gain_e;

  /* Integrator: '<S2>/Integrator' */
  rtb_Integrator[0] = m1107_X.Integrator_m_CSTATE[0];
  rtb_Integrator[1] = m1107_X.Integrator_m_CSTATE[1];
  rtb_Integrator[2] = m1107_X.Integrator_m_CSTATE[2];

  /* Gain: '<S2>/Gain' */
  m1107_B.Gain[0] = rtb_Integrator[0] * m1107_P.Gain_Gain_g;
  m1107_B.Gain[1] = rtb_Integrator[1] * m1107_P.Gain_Gain_g;
  m1107_B.Gain[2] = rtb_Integrator[2] * m1107_P.Gain_Gain_g;
}

/* Model update function */
void m1107_update(int_T tid)
{

  if (rtmIsMajorTimeStep(m1107_M)) {
    rt_ertODEUpdateContinuousStates(&m1107_M->solverInfo, 0);
  }

  /* Update absolute time for base rate */

  if(!(++m1107_M->Timing.clockTick0)) ++m1107_M->Timing.clockTickH0;
  m1107_M->Timing.t[0] = m1107_M->Timing.clockTick0 * m1107_M->Timing.stepSize0
    + m1107_M->Timing.clockTickH0 * m1107_M->Timing.stepSize0 * 4294967296.0;

  if (rtmIsMajorTimeStep(m1107_M) &&
   m1107_M->Timing.TaskCounters.TID[1] == 0) {
    /* Update absolute timer for sample time: [0.01s, 0.0s] */

    if(!(++m1107_M->Timing.clockTick1)) ++m1107_M->Timing.clockTickH1;
    m1107_M->Timing.t[1] = m1107_M->Timing.clockTick1 *
      m1107_M->Timing.stepSize1 + m1107_M->Timing.clockTickH1 *
      m1107_M->Timing.stepSize1 * 4294967296.0;
  }

  rate_scheduler();
}

/* Derivatives for root system: '<Root>' */
void m1107_derivatives(void)
{
  /* simstruct variables */
  StateDerivatives_m1107 *m1107_Xdot = (StateDerivatives_m1107*)
    m1107_M->ModelData.derivs;

  /* Integrator Block: <S1>/Integrator1 */
  {

    m1107_Xdot->Integrator1_CSTATE[0] = m1107_B.Gain1[0];
    m1107_Xdot->Integrator1_CSTATE[1] = m1107_B.Gain1[1];
    m1107_Xdot->Integrator1_CSTATE[2] = m1107_B.Gain1[2];
    m1107_Xdot->Integrator1_CSTATE[3] = m1107_B.Gain1[3];
  }

  /* Integrator Block: <Root>/Integrator2 */
  {

    m1107_Xdot->Integrator2_CSTATE[0] = m1107_B.Product_a[0];
    m1107_Xdot->Integrator2_CSTATE[1] = m1107_B.Product_a[1];
    m1107_Xdot->Integrator2_CSTATE[2] = m1107_B.Product_a[2];
  }

  /* Integrator Block: <S2>/Integrator1 */
  {

    m1107_Xdot->Integrator1_i_CSTATE[0] = m1107_B.Gain[0];
    m1107_Xdot->Integrator1_i_CSTATE[1] = m1107_B.Gain[1];
    m1107_Xdot->Integrator1_i_CSTATE[2] = m1107_B.Gain[2];
  }

  /* Integrator Block: <S1>/Integrator */
  {

    m1107_Xdot->Integrator_CSTATE[0] = m1107_B.Product1[0];
    m1107_Xdot->Integrator_CSTATE[1] = m1107_B.Product1[1];
    m1107_Xdot->Integrator_CSTATE[2] = m1107_B.Product1[2];
  }

  /* Integrator Block: <S2>/Integrator */
  {

    m1107_Xdot->Integrator_m_CSTATE[0] = m1107_B.Product[0];
    m1107_Xdot->Integrator_m_CSTATE[1] = m1107_B.Product[1];
    m1107_Xdot->Integrator_m_CSTATE[2] = m1107_B.Product[2];
  }
}

/* Model initialize function */
void m1107_initialize(boolean_T firstTime)
{

  if (firstTime) {
    /* registration code */
    /* initialize real-time model */
    (void)memset((char_T *)m1107_M, 0, sizeof(rtModel_m1107));

    {
      /* Setup solver object */

      rtsiSetSimTimeStepPtr(&m1107_M->solverInfo, &m1107_M->Timing.simTimeStep);
      rtsiSetTPtr(&m1107_M->solverInfo, &rtmGetTPtr(m1107_M));
      rtsiSetStepSizePtr(&m1107_M->solverInfo, &m1107_M->Timing.stepSize0);
      rtsiSetdXPtr(&m1107_M->solverInfo, &m1107_M->ModelData.derivs);
      rtsiSetContStatesPtr(&m1107_M->solverInfo, &m1107_M->ModelData.contStates);
      rtsiSetNumContStatesPtr(&m1107_M->solverInfo,
       &m1107_M->Sizes.numContStates);
      rtsiSetErrorStatusPtr(&m1107_M->solverInfo, &rtmGetErrorStatus(m1107_M));

      rtsiSetRTModelPtr(&m1107_M->solverInfo, m1107_M);
    }
    rtsiSetSimTimeStep(&m1107_M->solverInfo, MAJOR_TIME_STEP);
    m1107_M->ModelData.intgData.y = m1107_M->ModelData.odeY;
    m1107_M->ModelData.intgData.f[0] = m1107_M->ModelData.odeF[0];
    m1107_M->ModelData.intgData.f[1] = m1107_M->ModelData.odeF[1];
    m1107_M->ModelData.intgData.f[2] = m1107_M->ModelData.odeF[2];
    m1107_M->ModelData.contStates = ((real_T *) &m1107_X);
    rtsiSetSolverData(&m1107_M->solverInfo, (void
      *)&m1107_M->ModelData.intgData);
    rtsiSetSolverName(&m1107_M->solverInfo,"ode3");

    /* Initialize timing info */
    {
      int_T *mdlTsMap = m1107_M->Timing.sampleTimeTaskIDArray;
      mdlTsMap[0] = 0;
      mdlTsMap[1] = 1;
      m1107_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
      m1107_M->Timing.sampleTimes = (&m1107_M->Timing.sampleTimesArray[0]);
      m1107_M->Timing.offsetTimes = (&m1107_M->Timing.offsetTimesArray[0]);
      /* task periods */
      m1107_M->Timing.sampleTimes[0] = (0.0);
      m1107_M->Timing.sampleTimes[1] = (0.01);

      /* task offsets */
      m1107_M->Timing.offsetTimes[0] = (0.0);
      m1107_M->Timing.offsetTimes[1] = (0.0);
    }

    rtmSetTPtr(m1107_M, &m1107_M->Timing.tArray[0]);

    {
      int_T *mdlSampleHits = m1107_M->Timing.sampleHitArray;
      mdlSampleHits[0] = 1;
      mdlSampleHits[1] = 1;
      m1107_M->Timing.sampleHits = (&mdlSampleHits[0]);
    }

    rtmSetTFinal(m1107_M, 10.0);
    m1107_M->Timing.stepSize0 = 0.01;
    m1107_M->Timing.stepSize1 = 0.01;

    /* Setup for data logging */
    {
      static RTWLogInfo rt_DataLoggingInfo;

      m1107_M->rtwLogInfo = &rt_DataLoggingInfo;

      rtliSetLogFormat(m1107_M->rtwLogInfo, 0);

      rtliSetLogMaxRows(m1107_M->rtwLogInfo, 1000);

      rtliSetLogDecimation(m1107_M->rtwLogInfo, 1);

      rtliSetLogVarNameModifier(m1107_M->rtwLogInfo, "rt_");

      rtliSetLogT(m1107_M->rtwLogInfo, "");

      rtliSetLogX(m1107_M->rtwLogInfo, "");

      rtliSetLogXFinal(m1107_M->rtwLogInfo, "");

      rtliSetSigLog(m1107_M->rtwLogInfo, "");

      rtliSetLogXSignalInfo(m1107_M->rtwLogInfo, NULL);

      rtliSetLogXSignalPtrs(m1107_M->rtwLogInfo, NULL);

      rtliSetLogY(m1107_M->rtwLogInfo, "");

      rtliSetLogYSignalInfo(m1107_M->rtwLogInfo, NULL);

      rtliSetLogYSignalPtrs(m1107_M->rtwLogInfo, NULL);
    }

    /* external mode info */
    m1107_M->Sizes.checksums[0] = (4132514235U);
    m1107_M->Sizes.checksums[1] = (775071815U);
    m1107_M->Sizes.checksums[2] = (1124296084U);
    m1107_M->Sizes.checksums[3] = (1557711101U);

    {
      static const int8_T rtAlwaysEnabled = EXTMODE_SUBSYS_ALWAYS_ENABLED;

      static RTWExtModeInfo rt_ExtModeInfo;
      static const void *sysActives[1];

      m1107_M->extModeInfo = (&rt_ExtModeInfo);
      rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, sysActives);

      sysActives[0] = &rtAlwaysEnabled;

      rteiSetModelMappingInfoPtr(&rt_ExtModeInfo,
       &m1107_M->SpecialInfo.mappingInfo);

      rteiSetChecksumsPtr(&rt_ExtModeInfo, m1107_M->Sizes.checksums);

      rteiSetTPtr(&rt_ExtModeInfo, rtmGetTPtr(m1107_M));
    }

    m1107_M->solverInfoPtr = (&m1107_M->solverInfo);
    m1107_M->Timing.stepSize = (0.01);
    rtsiSetFixedStepSize(&m1107_M->solverInfo, 0.01);
    rtsiSetSolverMode(&m1107_M->solverInfo, SOLVER_MODE_SINGLETASKING);

    {
      /* block I/O */
      void *b = (void *) &m1107_B;
      m1107_M->ModelData.blockIO = (b);

      {

        int_T i;
        b =&m1107_B.MatrixConcatenation[0];
        for (i = 0; i < 31; i++) {
          ((real_T*)b)[i] = 0.0;
        }
      }
    }
    /* parameters */
    m1107_M->ModelData.defaultParam = ((real_T *) &m1107_P);
    /* states */
    {
      real_T *x = (real_T *) &m1107_X;
      m1107_M->ModelData.contStates = (x);
      (void)memset((char_T *)x, 0, sizeof(ContinuousStates_m1107));
    }

    /* data type work */
    m1107_M->Work.dwork = ((void *) &m1107_DWork);
    (void)memset((char_T *) &m1107_DWork, 0, sizeof(D_Work_m1107));
    {
      int_T i;
      real_T *dwork_ptr = (real_T *) &m1107_DWork.Product1_DWORK1[0];

      for (i = 0; i < 27; i++) {
        dwork_ptr[i] = 0.0;
      }
    }

    /* data type transition information */
    {
      static DataTypeTransInfo dtInfo;

      (void)memset((char_T *) &dtInfo, 0, sizeof(dtInfo));
      m1107_M->SpecialInfo.mappingInfo = (&dtInfo);

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
void m1107_terminate(void)
{

  /* External mode */
  rtExtModeShutdown(2);
}

/*========================================================================*
 * Start of GRT compatible call interface                                 *
 *========================================================================*/

void MdlOutputs(int_T tid) {

  m1107_output(tid);
}

void MdlUpdate(int_T tid) {

  m1107_update(tid);
}

void MdlInitializeSizes(void) {
  m1107_M->Sizes.numContStates = (16); /* Number of continuous states */
  m1107_M->Sizes.numY = (0);            /* Number of model outputs */
  m1107_M->Sizes.numU = (0);            /* Number of model inputs */
  m1107_M->Sizes.sysDirFeedThru = (0); /* The model is not direct feedthrough */
  m1107_M->Sizes.numSampTimes = (2);    /* Number of sample times */
  m1107_M->Sizes.numBlocks = (62);      /* Number of blocks */
  m1107_M->Sizes.numBlockIO = (8);      /* Number of block outputs */
  m1107_M->Sizes.numBlockPrms = (38);   /* Sum of parameter "widths" */
}

void MdlInitializeSampleTimes(void) {
}

void MdlInitialize(void) {

  /* Integrator Block: <S1>/Integrator1 */
  m1107_X.Integrator1_CSTATE[0] = m1107_P.Integrator1_IC[0];
  m1107_X.Integrator1_CSTATE[1] = m1107_P.Integrator1_IC[1];
  m1107_X.Integrator1_CSTATE[2] = m1107_P.Integrator1_IC[2];
  m1107_X.Integrator1_CSTATE[3] = m1107_P.Integrator1_IC[3];

  /* Integrator Block: <Root>/Integrator2 */
  m1107_X.Integrator2_CSTATE[0] = m1107_P.Integrator2_IC;
  m1107_X.Integrator2_CSTATE[1] = m1107_P.Integrator2_IC;
  m1107_X.Integrator2_CSTATE[2] = m1107_P.Integrator2_IC;

  /* Integrator Block: <S2>/Integrator1 */
  m1107_X.Integrator1_i_CSTATE[0] = m1107_P.Integrator1_IC_n;
  m1107_X.Integrator1_i_CSTATE[1] = m1107_P.Integrator1_IC_n;
  m1107_X.Integrator1_i_CSTATE[2] = m1107_P.Integrator1_IC_n;

  /* Integrator Block: <S1>/Integrator */
  m1107_X.Integrator_CSTATE[0] = m1107_P.Integrator_IC;
  m1107_X.Integrator_CSTATE[1] = m1107_P.Integrator_IC;
  m1107_X.Integrator_CSTATE[2] = m1107_P.Integrator_IC;

  /* Integrator Block: <S2>/Integrator */
  m1107_X.Integrator_m_CSTATE[0] = m1107_P.Integrator_IC_j;
  m1107_X.Integrator_m_CSTATE[1] = m1107_P.Integrator_IC_j;
  m1107_X.Integrator_m_CSTATE[2] = m1107_P.Integrator_IC_j;
}

void MdlStart(void) {

  /* Integrator Block: <Root>/Integrator2 */
  m1107_B.Integrator2[0] = m1107_P.Integrator2_IC;
  m1107_B.Integrator2[1] = m1107_P.Integrator2_IC;
  m1107_B.Integrator2[2] = m1107_P.Integrator2_IC;

  /* Integrator Block: <S2>/Integrator1 */
  m1107_B.Integrator1[0] = m1107_P.Integrator1_IC_n;
  m1107_B.Integrator1[1] = m1107_P.Integrator1_IC_n;
  m1107_B.Integrator1[2] = m1107_P.Integrator1_IC_n;

  MdlInitialize();
}

rtModel_m1107 *m1107(void) {
  m1107_initialize(1);
  return m1107_M;
}

void MdlTerminate(void) {
  m1107_terminate();
}

/*========================================================================*
 * End of GRT compatible call interface                                   *
 *========================================================================*/

