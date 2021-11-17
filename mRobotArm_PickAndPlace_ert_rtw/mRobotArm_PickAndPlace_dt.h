/*
 * mRobotArm_PickAndPlace_dt.h
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

#include "ext_types.h"

/* data type size table */
static uint_T rtDataTypeSizes[] = {
  sizeof(real_T),
  sizeof(real32_T),
  sizeof(int8_T),
  sizeof(uint8_T),
  sizeof(int16_T),
  sizeof(uint16_T),
  sizeof(int32_T),
  sizeof(uint32_T),
  sizeof(boolean_T),
  sizeof(fcn_call_T),
  sizeof(int_T),
  sizeof(void*),
  sizeof(action_T),
  2*sizeof(uint32_T)
};

/* data type name table */
static const char_T * rtDataTypeNames[] = {
  "real_T",
  "real32_T",
  "int8_T",
  "uint8_T",
  "int16_T",
  "uint16_T",
  "int32_T",
  "uint32_T",
  "boolean_T",
  "fcn_call_T",
  "int_T",
  "pointer_T",
  "action_T",
  "timer_uint32_pair_T"
};

/* data type transitions for block I/O structure */
static DataTypeTransition rtBTransitions[] = {
  { (char_T *)(&mRobotArm_PickAndPlace_B.jc[0]), 0, 0, 5 },

  { (char_T *)(&mRobotArm_PickAndPlace_B.MathFunction), 0, 0, 34 },

  { (char_T *)(&mRobotArm_PickAndPlace_B.flag), 8, 0, 1 }
  ,

  { (char_T *)(&mRobotArm_PickAndPlace_DW.DelayOneStep_DSTATE[0]), 0, 0, 18 },

  { (char_T *)(&mRobotArm_PickAndPlace_DW.adEE_PWORK.LoggedData), 11, 0, 2 },

  { (char_T *)(&mRobotArm_PickAndPlace_DW.sfEvent), 6, 0, 1 },

  { (char_T *)(&mRobotArm_PickAndPlace_DW.is_c2_mRobotArm_PickAndPlace), 7, 0, 1
  },

  { (char_T *)(&mRobotArm_PickAndPlace_DW.is_active_c2_mRobotArm_PickAndP), 3, 0,
    1 },

  { (char_T *)(&mRobotArm_PickAndPlace_DW.doneDoubleBufferReInit), 8, 0, 1 }
};

/* data type transition table for block I/O structure */
static DataTypeTransitionTable rtBTransTable = {
  9U,
  rtBTransitions
};

/* data type transitions for Parameters structure */
static DataTypeTransition rtPTransitions[] = {
  { (char_T *)(&mRobotArm_PickAndPlace_P.adHome[0]), 0, 0, 30 }
};

/* data type transition table for Parameters structure */
static DataTypeTransitionTable rtPTransTable = {
  1U,
  rtPTransitions
};

/* [EOF] mRobotArm_PickAndPlace_dt.h */
