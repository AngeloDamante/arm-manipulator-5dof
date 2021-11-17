/*
 * mRobotArm_PickAndPlace_data.c
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

/* Block parameters (default storage) */
P_mRobotArm_PickAndPlace_T mRobotArm_PickAndPlace_P = {
  /* Variable: adHome
   * Referenced by:
   *   '<Root>/Constant8'
   *   '<Root>/Delay One Step'
   */
  { 1.5707963267948966, 1.5707963267948966, 1.5707963267948966,
    1.5707963267948966, 0.0 },

  /* Variable: adWS
   * Referenced by: '<Root>/Constant6'
   */
  { 435.0, 100.0, 220.0 },

  /* Variable: pickPoint
   * Referenced by: '<Root>/Constant'
   */
  { 130.0, -130.0, 10.0 },

  /* Expression: 180/pi
   * Referenced by: '<Root>/rad2deg'
   */
  57.295779513082323,

  /* Expression: 180/pi
   * Referenced by: '<Root>/rad2deg1'
   */
  57.295779513082323,

  /* Expression: rad2deg(initPoint)
   * Referenced by: '<Root>/Constant3'
   */
  { 90.0, 90.0, 45.0, 45.0 },

  /* Expression: 20
   * Referenced by: '<Root>/Constant7'
   */
  20.0,

  /* Expression: rad2deg(placePoint)
   * Referenced by: '<Root>/Constant4'
   */
  { 135.00031568872456, 68.29656917959413, 25.559647240786024,
    0.14323944878270581 },

  /* Expression: 180
   * Referenced by: '<S1>/Constant7'
   */
  180.0,

  /* Expression: 1
   * Referenced by: '<Root>/Start'
   */
  1.0,

  /* Expression: [90; 90; 45; 45; 0; 10]
   * Referenced by: '<Root>/Delay One Step2'
   */
  { 90.0, 90.0, 45.0, 45.0, 0.0, 10.0 }
};
