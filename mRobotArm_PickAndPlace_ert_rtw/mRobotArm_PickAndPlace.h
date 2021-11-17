/*
 * mRobotArm_PickAndPlace.h
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

#ifndef RTW_HEADER_mRobotArm_PickAndPlace_h_
#define RTW_HEADER_mRobotArm_PickAndPlace_h_
#include <float.h>
#include <math.h>
#include <string.h>
#include <stddef.h>
#ifndef mRobotArm_PickAndPlace_COMMON_INCLUDES_
#define mRobotArm_PickAndPlace_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_extmode.h"
#include "sysran_types.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "dt_info.h"
#include "ext_work.h"
#endif                             /* mRobotArm_PickAndPlace_COMMON_INCLUDES_ */

#include "mRobotArm_PickAndPlace_types.h"

/* Shared type includes */
#include "multiword_types.h"
#include "MW_target_hardware_resources.h"
#include "rt_defines.h"
#include "rt_nonfinite.h"
#include "rtGetInf.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetFinalTime
#define rtmGetFinalTime(rtm)           ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetRTWExtModeInfo
#define rtmGetRTWExtModeInfo(rtm)      ((rtm)->extModeInfo)
#endif

#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
#define rtmGetStopRequested(rtm)       ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
#define rtmSetStopRequested(rtm, val)  ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
#define rtmGetStopRequestedPtr(rtm)    (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
#define rtmGetT(rtm)                   (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmGetTFinal
#define rtmGetTFinal(rtm)              ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                ((rtm)->Timing.t)
#endif

/* Block signals (default storage) */
typedef struct {
  real_T jc[5];                        /* '<Root>/MATLAB Function3' */
  real_T Switch[5];                    /* '<Root>/Switch' */
  real_T MathFunction;                 /* '<Root>/Math Function' */
  real_T Sum[20];                      /* '<S1>/Sum' */
  real_T Start;                        /* '<Root>/Start' */
  real_T DelayOneStep2[6];             /* '<Root>/Delay One Step2' */
  real_T adEE[6];                      /* '<Root>/chart2' */
  real_T r;
  real_T z;
  real_T phi;
  real_T base;
  boolean_T flag;                      /* '<Root>/MATLAB Function3' */
} B_mRobotArm_PickAndPlace_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T DelayOneStep_DSTATE[5];       /* '<Root>/Delay One Step' */
  real_T DelayOneStep2_DSTATE[6];      /* '<Root>/Delay One Step2' */
  real_T adEEdesired[4];               /* '<Root>/chart2' */
  real_T currentState;                 /* '<Root>/chart2' */
  real_T stop;                         /* '<Root>/chart2' */
  real_T GripperDesired;               /* '<Root>/chart2' */
  struct {
    void *LoggedData;
  } adEE_PWORK;                        /* '<Root>/adEE' */

  struct {
    void *LoggedData;
  } Scope_PWORK;                       /* '<Root>/Scope' */

  int32_T sfEvent;                     /* '<Root>/chart2' */
  uint32_T is_c2_mRobotArm_PickAndPlace;/* '<Root>/chart2' */
  uint8_T is_active_c2_mRobotArm_PickAndP;/* '<Root>/chart2' */
  boolean_T doneDoubleBufferReInit;    /* '<Root>/chart2' */
} DW_mRobotArm_PickAndPlace_T;

/* Parameters (default storage) */
struct P_mRobotArm_PickAndPlace_T_ {
  real_T adHome[5];                    /* Variable: adHome
                                        * Referenced by:
                                        *   '<Root>/Constant8'
                                        *   '<Root>/Delay One Step'
                                        */
  real_T adWS[3];                      /* Variable: adWS
                                        * Referenced by: '<Root>/Constant6'
                                        */
  real_T pickPoint[3];                 /* Variable: pickPoint
                                        * Referenced by: '<Root>/Constant'
                                        */
  real_T rad2deg_Gain;                 /* Expression: 180/pi
                                        * Referenced by: '<Root>/rad2deg'
                                        */
  real_T rad2deg1_Gain;                /* Expression: 180/pi
                                        * Referenced by: '<Root>/rad2deg1'
                                        */
  real_T Constant3_Value[4];           /* Expression: rad2deg(initPoint)
                                        * Referenced by: '<Root>/Constant3'
                                        */
  real_T Constant7_Value;              /* Expression: 20
                                        * Referenced by: '<Root>/Constant7'
                                        */
  real_T Constant4_Value[4];           /* Expression: rad2deg(placePoint)
                                        * Referenced by: '<Root>/Constant4'
                                        */
  real_T Constant7_Value_m;            /* Expression: 180
                                        * Referenced by: '<S1>/Constant7'
                                        */
  real_T Start_Value;                  /* Expression: 1
                                        * Referenced by: '<Root>/Start'
                                        */
  real_T DelayOneStep2_InitialCondition[6];/* Expression: [90; 90; 45; 45; 0; 10]
                                            * Referenced by: '<Root>/Delay One Step2'
                                            */
};

/* Real-time Model Data Structure */
struct tag_RTM_mRobotArm_PickAndPlac_T {
  const char_T *errorStatus;
  RTWExtModeInfo *extModeInfo;
  RTWSolverInfo solverInfo;

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, sample times, etc.
   */
  struct {
    uint32_T checksums[4];
  } Sizes;

  /*
   * SpecialInfo:
   * The following substructure contains special information
   * related to other components that are dependent on RTW.
   */
  struct {
    const void *mappingInfo;
  } SpecialInfo;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick0;
    uint32_T clockTickH0;
    time_T stepSize0;
    uint32_T clockTick1;
    uint32_T clockTickH1;
    time_T tFinal;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[2];
  } Timing;
};

/* Block parameters (default storage) */
extern P_mRobotArm_PickAndPlace_T mRobotArm_PickAndPlace_P;

/* Block signals (default storage) */
extern B_mRobotArm_PickAndPlace_T mRobotArm_PickAndPlace_B;

/* Block states (default storage) */
extern DW_mRobotArm_PickAndPlace_T mRobotArm_PickAndPlace_DW;

/* Model entry point functions */
extern void mRobotArm_PickAndPlace_initialize(void);
extern void mRobotArm_PickAndPlace_step(void);
extern void mRobotArm_PickAndPlace_terminate(void);

/* Real-time Model object */
extern RT_MODEL_mRobotArm_PickAndPla_T *const mRobotArm_PickAndPlace_M;
extern volatile boolean_T stopRequested;
extern volatile boolean_T runModel;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'mRobotArm_PickAndPlace'
 * '<S1>'   : 'mRobotArm_PickAndPlace/FKMapper'
 * '<S2>'   : 'mRobotArm_PickAndPlace/MATLAB Function1'
 * '<S3>'   : 'mRobotArm_PickAndPlace/MATLAB Function3'
 * '<S4>'   : 'mRobotArm_PickAndPlace/MATLAB Function4'
 * '<S5>'   : 'mRobotArm_PickAndPlace/chart2'
 */
#endif                                /* RTW_HEADER_mRobotArm_PickAndPlace_h_ */
