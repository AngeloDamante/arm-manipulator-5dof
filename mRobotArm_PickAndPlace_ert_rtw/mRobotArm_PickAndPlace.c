/*
 * mRobotArm_PickAndPlace.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "mRobotArm_PickAndPlace".
 *
 * Model version              : 1.86
 * Simulink Coder version : 9.5 (R2021a) 14-Nov-2020
 * C source code generated on : Wed Nov 10 11:24:26 2021
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Atmel->AVR
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "mRobotArm_PickAndPlace.h"
#include "mRobotArm_PickAndPlace_private.h"
#include "mRobotArm_PickAndPlace_dt.h"

/* Named constants for Chart: '<Root>/chart2' */
#define mRobotArm_Pi_IN_WayPointReached (4UL)
#define mRobotArm_PickAn_IN_ToNextPoint (2UL)
#define mRobotArm_PickAn_IN_ToNextState (3UL)
#define mRobotArm_PickAndPlace_IN_Init (1UL)

/* Block signals (default storage) */
B_mRobotArm_PickAndPlace_T mRobotArm_PickAndPlace_B;

/* Block states (default storage) */
DW_mRobotArm_PickAndPlace_T mRobotArm_PickAndPlace_DW;

/* Real-time model */
static RT_MODEL_mRobotArm_PickAndPla_T mRobotArm_PickAndPlace_M_;
RT_MODEL_mRobotArm_PickAndPla_T *const mRobotArm_PickAndPlace_M =
  &mRobotArm_PickAndPlace_M_;

/* Forward declaration for local functions */
static void mRobotArm_PickAndPla_carnotRule(real_T l1, real_T l2, real_T l3,
  boolean_T *bFlag, real_T *angleRad);
static real_T mRobotArm_PickAndPlace_nextStep(real_T current, real_T desired);
real_T rt_modd_snf(real_T u0, real_T u1)
{
  real_T q;
  real_T y;
  boolean_T yEq;
  y = u0;
  if (u1 == 0.0) {
    if (u0 == 0.0) {
      y = u1;
    }
  } else if (rtIsNaN(u0) || rtIsNaN(u1) || rtIsInf(u0)) {
    y = (rtNaN);
  } else if (u0 == 0.0) {
    y = 0.0 / u1;
  } else if (rtIsInf(u1)) {
    if ((u1 < 0.0) != (u0 < 0.0)) {
      y = u1;
    }
  } else {
    y = fmod(u0, u1);
    yEq = (y == 0.0);
    if ((!yEq) && (u1 > floor(u1))) {
      q = fabs(u0 / u1);
      yEq = !(fabs(q - floor(q + 0.5)) > DBL_EPSILON * q);
    }

    if (yEq) {
      y = u1 * 0.0;
    } else if ((u0 < 0.0) != (u1 < 0.0)) {
      y += u1;
    }
  }

  return y;
}

real_T rt_atan2d_snf(real_T u0, real_T u1)
{
  real_T y;
  int16_T u0_0;
  int16_T u1_0;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = (rtNaN);
  } else if (rtIsInf(u0) && rtIsInf(u1)) {
    if (u0 > 0.0) {
      u0_0 = 1;
    } else {
      u0_0 = -1;
    }

    if (u1 > 0.0) {
      u1_0 = 1;
    } else {
      u1_0 = -1;
    }

    y = atan2(u0_0, u1_0);
  } else if (u1 == 0.0) {
    if (u0 > 0.0) {
      y = RT_PI / 2.0;
    } else if (u0 < 0.0) {
      y = -(RT_PI / 2.0);
    } else {
      y = 0.0;
    }
  } else {
    y = atan2(u0, u1);
  }

  return y;
}

/* Function for MATLAB Function: '<Root>/MATLAB Function3' */
static void mRobotArm_PickAndPla_carnotRule(real_T l1, real_T l2, real_T l3,
  boolean_T *bFlag, real_T *angleRad)
{
  real_T c23;
  if ((l1 <= 0.0) || (l2 <= 0.0) || (l3 <= 0.0)) {
    *bFlag = false;
    *angleRad = 0.0;
  } else {
    c23 = ((l2 * l2 + l3 * l3) - l1 * l1) / (2.0 * l2 * l3);
    if ((c23 > 1.0) || (c23 < -1.0)) {
      *bFlag = false;
      *angleRad = 0.0;
    } else {
      *bFlag = true;
      *angleRad = acos(c23);
    }
  }
}

/* Function for Chart: '<Root>/chart2' */
static real_T mRobotArm_PickAndPlace_nextStep(real_T current, real_T desired)
{
  if (current < desired) {
    current++;
  }

  if (current > desired) {
    current--;
  }

  return current;
}

/* Model step function */
void mRobotArm_PickAndPlace_step(void)
{
  {
    real_T b_r;
    real_T theta;
    real_T v;
    real_T wx;
    real_T wy;
    int16_T i;
    boolean_T x[4];
    boolean_T bBeta;
    boolean_T exitg1;
    boolean_T rtb_ok;

    /* Math: '<Root>/Math Function' incorporates:
     *  Clock: '<Root>/Clock'
     *  Constant: '<Root>/Constant7'
     */
    mRobotArm_PickAndPlace_B.MathFunction = rt_modd_snf
      (mRobotArm_PickAndPlace_M->Timing.t[0],
       mRobotArm_PickAndPlace_P.Constant7_Value);

    /* MATLAB Function: '<Root>/MATLAB Function3' incorporates:
     *  Constant: '<Root>/Constant'
     *  Delay: '<Root>/Delay One Step'
     */
    if (mRobotArm_PickAndPlace_B.MathFunction != 0.0) {
      mRobotArm_PickAndPlace_B.flag = true;
      for (i = 0; i < 5; i++) {
        mRobotArm_PickAndPlace_B.jc[i] =
          mRobotArm_PickAndPlace_DW.DelayOneStep_DSTATE[i];
      }
    } else {
      rtb_ok = true;
      mRobotArm_PickAndPlace_B.base = rt_atan2d_snf
        (mRobotArm_PickAndPlace_P.pickPoint[1],
         mRobotArm_PickAndPlace_P.pickPoint[0]);
      if ((!(mRobotArm_PickAndPlace_B.base >= -1.5707963267948966)) ||
          (!(mRobotArm_PickAndPlace_B.base <= 1.5707963267948966))) {
        if (mRobotArm_PickAndPlace_B.base < 0.0) {
          mRobotArm_PickAndPlace_B.base += 3.1415926535897931;
        }

        if (mRobotArm_PickAndPlace_B.base > 0.0) {
          mRobotArm_PickAndPlace_B.base -= 3.1415926535897931;
        }

        rtb_ok = false;
      }

      mRobotArm_PickAndPlace_B.r = sqrt(mRobotArm_PickAndPlace_P.pickPoint[0] *
        mRobotArm_PickAndPlace_P.pickPoint[0] +
        mRobotArm_PickAndPlace_P.pickPoint[1] *
        mRobotArm_PickAndPlace_P.pickPoint[1]);
      if (!rtb_ok) {
        mRobotArm_PickAndPlace_B.r = -mRobotArm_PickAndPlace_B.r;
      }

      mRobotArm_PickAndPlace_B.z = mRobotArm_PickAndPlace_P.pickPoint[2] - 70.0;
      mRobotArm_PickAndPlace_B.flag = false;
      i = 0;
      exitg1 = false;
      while ((!exitg1) && (i < 721)) {
        mRobotArm_PickAndPlace_B.phi = (real_T)i * 0.017453292519943295 +
          -6.2831853071795862;
        b_r = sqrt(mRobotArm_PickAndPlace_B.r * mRobotArm_PickAndPlace_B.r +
                   mRobotArm_PickAndPlace_B.z * mRobotArm_PickAndPlace_B.z);
        theta = rt_atan2d_snf(mRobotArm_PickAndPlace_B.z,
                              mRobotArm_PickAndPlace_B.r);
        wx = cos(theta - 1.5707963267948966) * b_r - cos
          (mRobotArm_PickAndPlace_B.phi - 1.5707963267948966) * 185.0;
        wy = sin(theta - 1.5707963267948966) * b_r - sin
          (mRobotArm_PickAndPlace_B.phi - 1.5707963267948966) * 185.0;
        v = sqrt(wy * wy + wx * wx);
        mRobotArm_PickAndPla_carnotRule(v, 125.0, 125.0, &rtb_ok, &b_r);
        mRobotArm_PickAndPla_carnotRule(125.0, v, 125.0, &bBeta, &theta);
        if ((!rtb_ok) || (!bBeta)) {
          mRobotArm_PickAndPlace_B.flag = false;
          wy = 0.0;
          wx = 0.0;
          v = 0.0;
        } else {
          mRobotArm_PickAndPlace_B.flag = true;
          wy = rt_atan2d_snf(wy, wx) - theta;
          wx = 3.1415926535897931 - b_r;
          v = ((mRobotArm_PickAndPlace_B.phi - 1.5707963267948966) - wy) -
            (3.1415926535897931 - b_r);
          if ((!(wy >= -1.3089969389957472)) || (!(wy <= 1.308996938995747)) ||
              ((!(3.1415926535897931 - b_r >= -1.5707963267948966)) ||
               (!(3.1415926535897931 - b_r <= 1.5707963267948966))) || ((!(v >=
                 -1.5707963267948966)) || (!(v <= 1.5707963267948966)))) {
            wy += 2.0 * theta;
            wx = -(3.1415926535897931 - b_r);
            v = ((mRobotArm_PickAndPlace_B.phi - 1.5707963267948966) - wy) -
              (-(3.1415926535897931 - b_r));
            if ((!(wy >= -1.3089969389957472)) || (!(wy <= 1.308996938995747)) ||
                ((!(-(3.1415926535897931 - b_r) >= -1.5707963267948966)) ||
                 (!(-(3.1415926535897931 - b_r) <= 1.5707963267948966))) ||
                ((!(v >= -1.5707963267948966)) || (!(v <= 1.5707963267948966))))
            {
              mRobotArm_PickAndPlace_B.flag = false;
            }
          }
        }

        if (mRobotArm_PickAndPlace_B.flag) {
          exitg1 = true;
        } else {
          i++;
        }
      }

      mRobotArm_PickAndPlace_B.jc[0] = (mRobotArm_PickAndPlace_B.base -
        1.5707963267948966) + 1.5707963267948966;
      mRobotArm_PickAndPlace_B.jc[1] = wy + 1.5707963267948966;
      mRobotArm_PickAndPlace_B.jc[2] = wx + 1.5707963267948966;
      mRobotArm_PickAndPlace_B.jc[3] = v + 1.5707963267948966;
      mRobotArm_PickAndPlace_B.jc[4] = 0.0;
    }

    /* End of MATLAB Function: '<Root>/MATLAB Function3' */

    /* MATLAB Function: '<Root>/MATLAB Function4' incorporates:
     *  Constant: '<Root>/Constant'
     *  Constant: '<Root>/Constant6'
     */
    if ((mRobotArm_PickAndPlace_P.adWS[0] <= 0.0) ||
        (mRobotArm_PickAndPlace_P.adWS[1] <= 0.0)) {
      rtb_ok = false;
    } else if (mRobotArm_PickAndPlace_P.adWS[1] >=
               mRobotArm_PickAndPlace_P.adWS[0]) {
      rtb_ok = false;
    } else if (mRobotArm_PickAndPlace_P.pickPoint[2] < 0.0) {
      rtb_ok = false;
    } else {
      mRobotArm_PickAndPlace_B.base = mRobotArm_PickAndPlace_P.pickPoint[0] *
        mRobotArm_PickAndPlace_P.pickPoint[0] +
        mRobotArm_PickAndPlace_P.pickPoint[1] *
        mRobotArm_PickAndPlace_P.pickPoint[1];
      if (mRobotArm_PickAndPlace_B.base + mRobotArm_PickAndPlace_P.pickPoint[2] *
          mRobotArm_PickAndPlace_P.pickPoint[2] > mRobotArm_PickAndPlace_P.adWS
          [0] * mRobotArm_PickAndPlace_P.adWS[0]) {
        rtb_ok = false;
      } else if ((mRobotArm_PickAndPlace_B.base < mRobotArm_PickAndPlace_P.adWS
                  [1] * mRobotArm_PickAndPlace_P.adWS[1]) &&
                 (mRobotArm_PickAndPlace_P.pickPoint[2] <
                  mRobotArm_PickAndPlace_P.adWS[2])) {
        rtb_ok = false;
      } else {
        rtb_ok = true;
      }
    }

    /* End of MATLAB Function: '<Root>/MATLAB Function4' */

    /* Switch: '<Root>/Switch' incorporates:
     *  Constant: '<Root>/Constant8'
     *  Gain: '<Root>/rad2deg'
     *  Gain: '<Root>/rad2deg1'
     *  Logic: '<Root>/AND'
     */
    for (i = 0; i < 5; i++) {
      if (mRobotArm_PickAndPlace_B.flag && rtb_ok) {
        mRobotArm_PickAndPlace_B.Switch[i] =
          mRobotArm_PickAndPlace_P.rad2deg_Gain * mRobotArm_PickAndPlace_B.jc[i];
      } else {
        mRobotArm_PickAndPlace_B.Switch[i] =
          mRobotArm_PickAndPlace_P.rad2deg1_Gain *
          mRobotArm_PickAndPlace_P.adHome[i];
      }
    }

    /* End of Switch: '<Root>/Switch' */

    /* Sum: '<S1>/Sum' incorporates:
     *  Constant: '<Root>/Constant3'
     *  Constant: '<S1>/Constant7'
     *  MATLAB Function: '<Root>/MATLAB Function1'
     */
    mRobotArm_PickAndPlace_B.base = mRobotArm_PickAndPlace_P.Constant7_Value_m -
      mRobotArm_PickAndPlace_P.Constant3_Value[0];

    /* Sum: '<S1>/Sum' incorporates:
     *  Constant: '<Root>/Constant4'
     *  Constant: '<S1>/Constant7'
     *  MATLAB Function: '<Root>/MATLAB Function1'
     */
    mRobotArm_PickAndPlace_B.Sum[0] = mRobotArm_PickAndPlace_B.base;
    mRobotArm_PickAndPlace_B.Sum[1] = mRobotArm_PickAndPlace_P.Constant7_Value_m
      - mRobotArm_PickAndPlace_B.Switch[0];
    mRobotArm_PickAndPlace_B.Sum[2] = mRobotArm_PickAndPlace_B.base;
    mRobotArm_PickAndPlace_B.Sum[3] = mRobotArm_PickAndPlace_P.Constant7_Value_m
      - mRobotArm_PickAndPlace_P.Constant4_Value[0];
    mRobotArm_PickAndPlace_B.Sum[4] = mRobotArm_PickAndPlace_B.base;

    /* Sum: '<S1>/Sum' incorporates:
     *  Constant: '<Root>/Constant3'
     *  Constant: '<S1>/Constant7'
     *  MATLAB Function: '<Root>/MATLAB Function1'
     */
    mRobotArm_PickAndPlace_B.base = mRobotArm_PickAndPlace_P.Constant7_Value_m -
      mRobotArm_PickAndPlace_P.Constant3_Value[1];

    /* Sum: '<S1>/Sum' incorporates:
     *  Constant: '<Root>/Constant4'
     *  Constant: '<S1>/Constant7'
     *  MATLAB Function: '<Root>/MATLAB Function1'
     */
    mRobotArm_PickAndPlace_B.Sum[5] = mRobotArm_PickAndPlace_B.base;
    mRobotArm_PickAndPlace_B.Sum[6] = mRobotArm_PickAndPlace_P.Constant7_Value_m
      - mRobotArm_PickAndPlace_B.Switch[1];
    mRobotArm_PickAndPlace_B.Sum[7] = mRobotArm_PickAndPlace_B.base;
    mRobotArm_PickAndPlace_B.Sum[8] = mRobotArm_PickAndPlace_P.Constant7_Value_m
      - mRobotArm_PickAndPlace_P.Constant4_Value[1];
    mRobotArm_PickAndPlace_B.Sum[9] = mRobotArm_PickAndPlace_B.base;

    /* Sum: '<S1>/Sum' incorporates:
     *  Constant: '<Root>/Constant3'
     *  Constant: '<S1>/Constant7'
     *  MATLAB Function: '<Root>/MATLAB Function1'
     */
    mRobotArm_PickAndPlace_B.base = mRobotArm_PickAndPlace_P.Constant7_Value_m -
      mRobotArm_PickAndPlace_P.Constant3_Value[2];

    /* Sum: '<S1>/Sum' incorporates:
     *  Constant: '<Root>/Constant4'
     *  Constant: '<S1>/Constant7'
     *  MATLAB Function: '<Root>/MATLAB Function1'
     */
    mRobotArm_PickAndPlace_B.Sum[10] = mRobotArm_PickAndPlace_B.base;
    mRobotArm_PickAndPlace_B.Sum[11] =
      mRobotArm_PickAndPlace_P.Constant7_Value_m -
      mRobotArm_PickAndPlace_B.Switch[2];
    mRobotArm_PickAndPlace_B.Sum[12] = mRobotArm_PickAndPlace_B.base;
    mRobotArm_PickAndPlace_B.Sum[13] =
      mRobotArm_PickAndPlace_P.Constant7_Value_m -
      mRobotArm_PickAndPlace_P.Constant4_Value[2];
    mRobotArm_PickAndPlace_B.Sum[14] = mRobotArm_PickAndPlace_B.base;

    /* Sum: '<S1>/Sum' incorporates:
     *  Constant: '<Root>/Constant3'
     *  Constant: '<S1>/Constant7'
     *  MATLAB Function: '<Root>/MATLAB Function1'
     */
    mRobotArm_PickAndPlace_B.base = mRobotArm_PickAndPlace_P.Constant7_Value_m -
      mRobotArm_PickAndPlace_P.Constant3_Value[3];

    /* Sum: '<S1>/Sum' incorporates:
     *  Constant: '<Root>/Constant4'
     *  Constant: '<S1>/Constant7'
     *  MATLAB Function: '<Root>/MATLAB Function1'
     */
    mRobotArm_PickAndPlace_B.Sum[15] = mRobotArm_PickAndPlace_B.base;
    mRobotArm_PickAndPlace_B.Sum[16] =
      mRobotArm_PickAndPlace_P.Constant7_Value_m -
      mRobotArm_PickAndPlace_B.Switch[3];
    mRobotArm_PickAndPlace_B.Sum[17] = mRobotArm_PickAndPlace_B.base;
    mRobotArm_PickAndPlace_B.Sum[18] =
      mRobotArm_PickAndPlace_P.Constant7_Value_m -
      mRobotArm_PickAndPlace_P.Constant4_Value[3];
    mRobotArm_PickAndPlace_B.Sum[19] = mRobotArm_PickAndPlace_B.base;

    /* Constant: '<Root>/Start' */
    mRobotArm_PickAndPlace_B.Start = mRobotArm_PickAndPlace_P.Start_Value;
    for (i = 0; i < 6; i++) {
      /* Delay: '<Root>/Delay One Step2' */
      mRobotArm_PickAndPlace_B.DelayOneStep2[i] =
        mRobotArm_PickAndPlace_DW.DelayOneStep2_DSTATE[i];
    }

    /* Chart: '<Root>/chart2' incorporates:
     *  Sum: '<S1>/Sum'
     */
    mRobotArm_PickAndPlace_DW.sfEvent = -1L;
    switch (mRobotArm_PickAndPlace_DW.is_c2_mRobotArm_PickAndPlace) {
     case mRobotArm_PickAndPlace_IN_Init:
      if (mRobotArm_PickAndPlace_B.Start == 1.0) {
        mRobotArm_PickAndPlace_DW.is_c2_mRobotArm_PickAndPlace =
          mRobotArm_PickAn_IN_ToNextPoint;
        mRobotArm_PickAndPlace_DW.adEEdesired[0] = mRobotArm_PickAndPlace_B.Sum
          [(int16_T)mRobotArm_PickAndPlace_DW.currentState - 1];
        mRobotArm_PickAndPlace_DW.adEEdesired[1] = mRobotArm_PickAndPlace_B.Sum
          [(int16_T)mRobotArm_PickAndPlace_DW.currentState + 4];
        mRobotArm_PickAndPlace_DW.adEEdesired[2] = mRobotArm_PickAndPlace_B.Sum
          [(int16_T)mRobotArm_PickAndPlace_DW.currentState + 9];
        mRobotArm_PickAndPlace_DW.adEEdesired[3] = mRobotArm_PickAndPlace_B.Sum
          [(int16_T)mRobotArm_PickAndPlace_DW.currentState + 14];
      } else {
        for (i = 0; i < 6; i++) {
          mRobotArm_PickAndPlace_B.adEE[i] =
            mRobotArm_PickAndPlace_B.DelayOneStep2[i];
        }
      }
      break;

     case mRobotArm_PickAn_IN_ToNextPoint:
      x[0] = (mRobotArm_PickAndPlace_B.DelayOneStep2[0] ==
              mRobotArm_PickAndPlace_DW.adEEdesired[0]);
      x[1] = (mRobotArm_PickAndPlace_B.DelayOneStep2[1] ==
              mRobotArm_PickAndPlace_DW.adEEdesired[1]);
      x[2] = (mRobotArm_PickAndPlace_B.DelayOneStep2[2] ==
              mRobotArm_PickAndPlace_DW.adEEdesired[2]);
      x[3] = (mRobotArm_PickAndPlace_B.DelayOneStep2[3] ==
              mRobotArm_PickAndPlace_DW.adEEdesired[3]);
      rtb_ok = true;
      i = 0;
      exitg1 = false;
      while ((!exitg1) && (i < 4)) {
        if (!x[i]) {
          rtb_ok = false;
          exitg1 = true;
        } else {
          i++;
        }
      }

      if (rtb_ok) {
        mRobotArm_PickAndPlace_DW.is_c2_mRobotArm_PickAndPlace =
          mRobotArm_Pi_IN_WayPointReached;
        if (mRobotArm_PickAndPlace_DW.currentState == 1.0) {
          mRobotArm_PickAndPlace_DW.GripperDesired = 50.0;
        } else if (mRobotArm_PickAndPlace_DW.currentState == 3.0) {
          mRobotArm_PickAndPlace_DW.GripperDesired = 10.0;
        }
      } else {
        mRobotArm_PickAndPlace_B.adEE[0] = mRobotArm_PickAndPlace_nextStep
          (mRobotArm_PickAndPlace_B.DelayOneStep2[0],
           mRobotArm_PickAndPlace_DW.adEEdesired[0]);
        mRobotArm_PickAndPlace_B.adEE[1] = mRobotArm_PickAndPlace_nextStep
          (mRobotArm_PickAndPlace_B.DelayOneStep2[1],
           mRobotArm_PickAndPlace_DW.adEEdesired[1]);
        mRobotArm_PickAndPlace_B.adEE[2] = mRobotArm_PickAndPlace_nextStep
          (mRobotArm_PickAndPlace_B.DelayOneStep2[2],
           mRobotArm_PickAndPlace_DW.adEEdesired[2]);
        mRobotArm_PickAndPlace_B.adEE[3] = mRobotArm_PickAndPlace_nextStep
          (mRobotArm_PickAndPlace_B.DelayOneStep2[3],
           mRobotArm_PickAndPlace_DW.adEEdesired[3]);
      }
      break;

     case mRobotArm_PickAn_IN_ToNextState:
      if (mRobotArm_PickAndPlace_DW.stop == 0.0) {
        mRobotArm_PickAndPlace_DW.is_c2_mRobotArm_PickAndPlace =
          mRobotArm_PickAn_IN_ToNextPoint;
        mRobotArm_PickAndPlace_DW.adEEdesired[0] = mRobotArm_PickAndPlace_B.Sum
          [(int16_T)mRobotArm_PickAndPlace_DW.currentState - 1];
        mRobotArm_PickAndPlace_DW.adEEdesired[1] = mRobotArm_PickAndPlace_B.Sum
          [(int16_T)mRobotArm_PickAndPlace_DW.currentState + 4];
        mRobotArm_PickAndPlace_DW.adEEdesired[2] = mRobotArm_PickAndPlace_B.Sum
          [(int16_T)mRobotArm_PickAndPlace_DW.currentState + 9];
        mRobotArm_PickAndPlace_DW.adEEdesired[3] = mRobotArm_PickAndPlace_B.Sum
          [(int16_T)mRobotArm_PickAndPlace_DW.currentState + 14];
      }
      break;

     default:
      /* case IN_WayPointReached: */
      if (mRobotArm_PickAndPlace_B.adEE[5] ==
          mRobotArm_PickAndPlace_DW.GripperDesired) {
        mRobotArm_PickAndPlace_DW.is_c2_mRobotArm_PickAndPlace =
          mRobotArm_PickAn_IN_ToNextState;
        if (mRobotArm_PickAndPlace_DW.currentState < 5.0) {
          mRobotArm_PickAndPlace_DW.currentState++;
        } else {
          mRobotArm_PickAndPlace_DW.stop = 1.0;
          for (i = 0; i < 6; i++) {
            mRobotArm_PickAndPlace_B.adEE[i] =
              mRobotArm_PickAndPlace_B.DelayOneStep2[i];
          }
        }
      } else {
        mRobotArm_PickAndPlace_B.adEE[5] = mRobotArm_PickAndPlace_nextStep
          (mRobotArm_PickAndPlace_B.DelayOneStep2[5],
           mRobotArm_PickAndPlace_DW.GripperDesired);
      }
      break;
    }

    /* End of Chart: '<Root>/chart2' */
  }

  {
    int16_T i;

    /* Update for Delay: '<Root>/Delay One Step' */
    for (i = 0; i < 5; i++) {
      mRobotArm_PickAndPlace_DW.DelayOneStep_DSTATE[i] =
        mRobotArm_PickAndPlace_B.jc[i];
    }

    /* End of Update for Delay: '<Root>/Delay One Step' */

    /* Update for Delay: '<Root>/Delay One Step2' */
    for (i = 0; i < 6; i++) {
      mRobotArm_PickAndPlace_DW.DelayOneStep2_DSTATE[i] =
        mRobotArm_PickAndPlace_B.adEE[i];
    }

    /* End of Update for Delay: '<Root>/Delay One Step2' */
  }

  /* External mode */
  rtExtModeUploadCheckTrigger(2);

  {                                    /* Sample time: [0.0s, 0.0s] */
    rtExtModeUpload(0, (real_T)mRobotArm_PickAndPlace_M->Timing.t[0]);
  }

  {                                    /* Sample time: [0.02s, 0.0s] */
    rtExtModeUpload(1, (real_T)(((mRobotArm_PickAndPlace_M->Timing.clockTick1+
      mRobotArm_PickAndPlace_M->Timing.clockTickH1* 4294967296.0)) * 0.02));
  }

  /* signal main to stop simulation */
  {                                    /* Sample time: [0.0s, 0.0s] */
    if ((rtmGetTFinal(mRobotArm_PickAndPlace_M)!=-1) &&
        !((rtmGetTFinal(mRobotArm_PickAndPlace_M)-
           mRobotArm_PickAndPlace_M->Timing.t[0]) >
          mRobotArm_PickAndPlace_M->Timing.t[0] * (DBL_EPSILON))) {
      rtmSetErrorStatus(mRobotArm_PickAndPlace_M, "Simulation finished");
    }

    if (rtmGetStopRequested(mRobotArm_PickAndPlace_M)) {
      rtmSetErrorStatus(mRobotArm_PickAndPlace_M, "Simulation finished");
    }
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++mRobotArm_PickAndPlace_M->Timing.clockTick0)) {
    ++mRobotArm_PickAndPlace_M->Timing.clockTickH0;
  }

  mRobotArm_PickAndPlace_M->Timing.t[0] =
    mRobotArm_PickAndPlace_M->Timing.clockTick0 *
    mRobotArm_PickAndPlace_M->Timing.stepSize0 +
    mRobotArm_PickAndPlace_M->Timing.clockTickH0 *
    mRobotArm_PickAndPlace_M->Timing.stepSize0 * 4294967296.0;

  {
    /* Update absolute timer for sample time: [0.02s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The resolution of this integer timer is 0.02, which is the step size
     * of the task. Size of "clockTick1" ensures timer will not overflow during the
     * application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick1 and the high bits
     * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
     */
    mRobotArm_PickAndPlace_M->Timing.clockTick1++;
    if (!mRobotArm_PickAndPlace_M->Timing.clockTick1) {
      mRobotArm_PickAndPlace_M->Timing.clockTickH1++;
    }
  }
}

/* Model initialize function */
void mRobotArm_PickAndPlace_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)mRobotArm_PickAndPlace_M, 0,
                sizeof(RT_MODEL_mRobotArm_PickAndPla_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&mRobotArm_PickAndPlace_M->solverInfo,
                          &mRobotArm_PickAndPlace_M->Timing.simTimeStep);
    rtsiSetTPtr(&mRobotArm_PickAndPlace_M->solverInfo, &rtmGetTPtr
                (mRobotArm_PickAndPlace_M));
    rtsiSetStepSizePtr(&mRobotArm_PickAndPlace_M->solverInfo,
                       &mRobotArm_PickAndPlace_M->Timing.stepSize0);
    rtsiSetErrorStatusPtr(&mRobotArm_PickAndPlace_M->solverInfo,
                          (&rtmGetErrorStatus(mRobotArm_PickAndPlace_M)));
    rtsiSetRTModelPtr(&mRobotArm_PickAndPlace_M->solverInfo,
                      mRobotArm_PickAndPlace_M);
  }

  rtsiSetSimTimeStep(&mRobotArm_PickAndPlace_M->solverInfo, MAJOR_TIME_STEP);
  rtsiSetSolverName(&mRobotArm_PickAndPlace_M->solverInfo,"FixedStepDiscrete");
  rtmSetTPtr(mRobotArm_PickAndPlace_M, &mRobotArm_PickAndPlace_M->Timing.tArray
             [0]);
  rtmSetTFinal(mRobotArm_PickAndPlace_M, -1);
  mRobotArm_PickAndPlace_M->Timing.stepSize0 = 0.02;

  /* External mode info */
  mRobotArm_PickAndPlace_M->Sizes.checksums[0] = (3570988890U);
  mRobotArm_PickAndPlace_M->Sizes.checksums[1] = (3471266082U);
  mRobotArm_PickAndPlace_M->Sizes.checksums[2] = (293344712U);
  mRobotArm_PickAndPlace_M->Sizes.checksums[3] = (1930235094U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[7];
    mRobotArm_PickAndPlace_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    systemRan[2] = &rtAlwaysEnabled;
    systemRan[3] = &rtAlwaysEnabled;
    systemRan[4] = &rtAlwaysEnabled;
    systemRan[5] = &rtAlwaysEnabled;
    systemRan[6] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(mRobotArm_PickAndPlace_M->extModeInfo,
      &mRobotArm_PickAndPlace_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(mRobotArm_PickAndPlace_M->extModeInfo,
                        mRobotArm_PickAndPlace_M->Sizes.checksums);
    rteiSetTPtr(mRobotArm_PickAndPlace_M->extModeInfo, rtmGetTPtr
                (mRobotArm_PickAndPlace_M));
  }

  /* block I/O */
  (void) memset(((void *) &mRobotArm_PickAndPlace_B), 0,
                sizeof(B_mRobotArm_PickAndPlace_T));

  /* states (dwork) */
  (void) memset((void *)&mRobotArm_PickAndPlace_DW, 0,
                sizeof(DW_mRobotArm_PickAndPlace_T));

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    mRobotArm_PickAndPlace_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 14;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.PTransTable = &rtPTransTable;
  }

  /* Start for Constant: '<Root>/Start' */
  mRobotArm_PickAndPlace_B.Start = mRobotArm_PickAndPlace_P.Start_Value;

  {
    int16_T i;

    /* InitializeConditions for Delay: '<Root>/Delay One Step' */
    for (i = 0; i < 5; i++) {
      mRobotArm_PickAndPlace_DW.DelayOneStep_DSTATE[i] =
        mRobotArm_PickAndPlace_P.adHome[i];
    }

    /* End of InitializeConditions for Delay: '<Root>/Delay One Step' */

    /* SystemInitialize for Chart: '<Root>/chart2' */
    mRobotArm_PickAndPlace_DW.sfEvent = -1L;
    mRobotArm_PickAndPlace_DW.adEEdesired[0] = 0.0;
    mRobotArm_PickAndPlace_DW.adEEdesired[1] = 0.0;
    mRobotArm_PickAndPlace_DW.adEEdesired[2] = 0.0;
    mRobotArm_PickAndPlace_DW.adEEdesired[3] = 0.0;
    for (i = 0; i < 6; i++) {
      /* InitializeConditions for Delay: '<Root>/Delay One Step2' */
      mRobotArm_PickAndPlace_DW.DelayOneStep2_DSTATE[i] =
        mRobotArm_PickAndPlace_P.DelayOneStep2_InitialCondition[i];

      /* SystemInitialize for Chart: '<Root>/chart2' */
      mRobotArm_PickAndPlace_B.adEE[i] = 0.0;
    }

    /* Chart: '<Root>/chart2' */
    mRobotArm_PickAndPlace_DW.is_active_c2_mRobotArm_PickAndP = 1U;
    mRobotArm_PickAndPlace_DW.is_c2_mRobotArm_PickAndPlace =
      mRobotArm_PickAndPlace_IN_Init;
    mRobotArm_PickAndPlace_DW.currentState = 1.0;
    mRobotArm_PickAndPlace_DW.stop = 0.0;
    mRobotArm_PickAndPlace_DW.GripperDesired = 10.0;
  }
}

/* Model terminate function */
void mRobotArm_PickAndPlace_terminate(void)
{
  /* (no terminate code required) */
}
