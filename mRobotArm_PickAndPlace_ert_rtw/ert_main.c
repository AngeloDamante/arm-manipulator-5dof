#include "mRobotArm_PickAndPlace.h"
#include "rtwtypes.h"
#include <ext_work.h>
#include <ext_svr.h>
#include <ext_share.h>
#include <updown.h>

volatile int IsrOverrun = 0;
static boolean_T OverrunFlag = 0;
void rt_OneStep(void)
{
  /* Check for overrun. Protect OverrunFlag against preemption */
  if (OverrunFlag++) {
    IsrOverrun = 1;
    OverrunFlag--;
    return;
  }

#ifndef _MW_ARDUINO_LOOP_

  sei();

#endif;

  mRobotArm_PickAndPlace_step();

  /* Get model outputs here */
#ifndef _MW_ARDUINO_LOOP_

  cli();

#endif;

  OverrunFlag--;
  rtExtModeCheckEndTrigger();
}

volatile boolean_T stopRequested;
volatile boolean_T runModel;
int main(void)
{
  float modelBaseRate = 0.02;
  float systemClock = 0;

  /* Initialize variables */
  stopRequested = false;
  runModel = false;
  init();
  MW_Arduino_Init();
  rtmSetErrorStatus(mRobotArm_PickAndPlace_M, 0);

  /* initialize external mode */
  rtParseArgsForExtMode(0, NULL);
  mRobotArm_PickAndPlace_initialize();
  cli();
  sei();

  /* External mode */
  rtSetTFinalForExtMode(&rtmGetTFinal(mRobotArm_PickAndPlace_M));
  rtExtModeCheckInit(2);

  {
    boolean_T rtmStopReq = false;
    rtExtModeWaitForStartPkt(mRobotArm_PickAndPlace_M->extModeInfo, 2,
      &rtmStopReq);
    if (rtmStopReq) {
      rtmSetStopRequested(mRobotArm_PickAndPlace_M, true);
    }
  }

  rtERTExtModeStartMsg();
  cli();
  configureArduinoAVRTimer();
  runModel =
    (rtmGetErrorStatus(mRobotArm_PickAndPlace_M) == (NULL)) &&
    !rtmGetStopRequested(mRobotArm_PickAndPlace_M);

#ifndef _MW_ARDUINO_LOOP_

  sei();

#endif;

  sei();
  while (runModel) {
    /* External mode */
    {
      boolean_T rtmStopReq = false;
      rtExtModeOneStep(mRobotArm_PickAndPlace_M->extModeInfo, 2, &rtmStopReq);
      if (rtmStopReq) {
        rtmSetStopRequested(mRobotArm_PickAndPlace_M, true);
      }
    }

    stopRequested = !(
                      (rtmGetErrorStatus(mRobotArm_PickAndPlace_M) == (NULL)) &&
                      !rtmGetStopRequested(mRobotArm_PickAndPlace_M));
    runModel = !(stopRequested);
    MW_Arduino_Loop();
  }

  /* Disable rt_OneStep() here */

  /* Terminate model */
  mRobotArm_PickAndPlace_terminate();
  rtExtModeShutdown(2);
  cli();
  return 0;
}
