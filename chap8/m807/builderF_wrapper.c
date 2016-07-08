/*
  *
  *   --- THIS FILE GENERATED BY S-FUNCTION BUILDER: 3.0 ---
  *
  *   This file is a wrapper S-function produced by the S-Function
  *   Builder which only recognizes certain fields.  Changes made
  *   outside these fields will be lost the next time the block is
  *   used to load, edit, and resave this file. This file will be overwritten
  *   by the S-function Builder block. If you want to edit this file by hand, 
  *   you must change it only in the area defined as:  
  *
  *        %%%-SFUNWIZ_wrapper_XXXXX_Changes_BEGIN 
  *            Your Changes go here
  *        %%%-SFUNWIZ_wrapper_XXXXXX_Changes_END
  *
  *   For better compatibility with the Real-Time Workshop, the
  *   "wrapper" S-function technique is used.  This is discussed
  *   in the Real-Time Workshop User's Manual in the Chapter titled,
  *   "Wrapper S-functions".
  *
  *   Created: Mon Apr 11 07:06:59 2005
  */


/*
 * Include Files
 *
 */
#if defined(MATLAB_MEX_FILE)
#include "tmwtypes.h"
#include "simstruc_types.h"
#else
#include "rtwtypes.h"
#endif
/* %%%-SFUNWIZ_wrapper_includes_Changes_BEGIN --- EDIT HERE TO _END */
#include <math.h>
/* %%%-SFUNWIZ_wrapper_includes_Changes_END --- EDIT HERE TO _BEGIN */
#define u_width 3
#define y_width 3
/*
 * Create external references here.  
 *
 */
/* %%%-SFUNWIZ_wrapper_externs_Changes_BEGIN --- EDIT HERE TO _END */
/* extern double func(double a); */
/* %%%-SFUNWIZ_wrapper_externs_Changes_END --- EDIT HERE TO _BEGIN */

/*
 * Output functions
 *
 */
void builderF_Outputs_wrapper(const real_T *u0,
                          real_T *y0,
                          real_T *y1,
                          real_T *y2,
                          const real_T *xC)
{
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_BEGIN --- EDIT HERE TO _END */
/* This sample sets the output equal to the input
          y0[0] = u0[0];
 For complex signals use: y0[0].re = u0[0].re;
                          y0[0].im = u0[0].im;
                          y1[0].re = u1[0].re;
                          y1[0].im = u1[0].im;*/
 y0[0]=xC[0];
 y0[1]=xC[1];
 y0[2]=xC[2];
 y0[3]=xC[3];
 y0[4]=xC[4];
 y0[5]=xC[5];
 y0[6]=xC[6];
 y0[7]=xC[7];
 y0[8]=xC[8];
 y1[0]=xC[9];
 y1[1]=xC[10];
 y1[2]=xC[11];
 y2[0]=xC[12];
 y2[1]=xC[13];
 y2[2]=xC[14];

/* %%%-SFUNWIZ_wrapper_Outputs_Changes_END --- EDIT HERE TO _BEGIN */
}

/*
  *  Derivatives function
  *
  */
void builderF_Derivatives_wrapper(const real_T *u0,
                          const real_T *y0,
                          const real_T *y1,
                          const real_T *y2,
                          real_T *dx,
                          real_T *xC)
{
/* %%%-SFUNWIZ_wrapper_Derivatives_Changes_BEGIN --- EDIT HERE TO _END */
/*
  * Code example
  *   dx[0] = xC[0];
 */
     static real_T invI[9]={1,0,0,0,0.5,0,0,0,1};
     static real_T w[9]={0,0,0,0,0,0,0,0,0};
     static real_T w1[9]={0,0,0,0,0,0,0,0,0};
     
     static real_T omega[3]={0,0,0};
     int_T i,j,k;
     for(i=0;i<3;i++)
     {
         for(j=0;j<3;j++)
         {
             w[i+3*j]=0;
             for(k=0;k<3;k++)
             {
                 w[i+3*j]+=xC[i+3*k]*invI[k+3*j];
             }
         }
     }
     for(i=0;i<3;i++)
     {
         for(j=0;j<3;j++)
         {
             w1[i+3*j]=0;
             for(k=0;k<3;k++)
             {
                 w1[i+3*j]+=w[i+3*k]*xC[j+3*k];
             }
         }
     }
     for(i=0;i<3;i++)
     {
         omega[i]=0;
         for(j=0;j<3;j++)
         {
             omega[i]+=w1[i+3*j]*xC[j+9];
         }
     }
            dx[0]=-omega[2]*xC[1]+omega[1]*xC[2];
            dx[1]= omega[2]*xC[0]-omega[0]*xC[2];
            dx[2]=-omega[1]*xC[0]+omega[0]*xC[1];
            
            dx[3]=-omega[2]*xC[4]+omega[1]*xC[5];
            dx[4]= omega[2]*xC[3]-omega[0]*xC[5];
            dx[5]=-omega[1]*xC[3]+omega[0]*xC[4];
            
            dx[6]=-omega[2]*xC[7]+omega[1]*xC[8];
            dx[7]= omega[2]*xC[6]-omega[0]*xC[8];
            dx[8]=-omega[1]*xC[6]+omega[0]*xC[7];
                      
            dx[12]=omega[0];
            dx[13]=omega[1];
            dx[14]=omega[2];
            
            dx[9]=u0[0];
            dx[10]=u0[1];
            dx[11]=u0[2];

/* %%%-SFUNWIZ_wrapper_Derivatives_Changes_END --- EDIT HERE TO _BEGIN */
}