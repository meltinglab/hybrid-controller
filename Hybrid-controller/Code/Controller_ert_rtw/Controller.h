/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Controller.h
 *
 * Code generated for Simulink model 'Controller'.
 *
 * Model version                  : 1.9
 * Simulink Coder version         : 9.4 (R2020b) 29-Jul-2020
 * C/C++ source code generated on : Fri Feb 26 10:40:43 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objective: MISRA C:2012 guidelines
 * Validation result: Not run
 */

#ifndef RTW_HEADER_Controller_h_
#define RTW_HEADER_Controller_h_
#include <math.h>
#ifndef Controller_COMMON_INCLUDES_
#define Controller_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* Controller_COMMON_INCLUDES_ */

#include "Controller_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Block signals (default storage) */
typedef struct {
  real_T Merge;                        /* '<S3>/Merge' */
  real_T Merge2;                       /* '<S3>/Merge2' */
  real_T Merge1;                       /* '<S3>/Merge1' */
  real_T Probe[2];                     /* '<S18>/Probe' */
  real_T Probe_b[2];                   /* '<S11>/Probe' */
} B_Controller_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T Integrator_DSTATE;            /* '<S23>/Integrator' */
  real_T Integrator_DSTATE_n;          /* '<S16>/Integrator' */
  int8_T SwitchCase_ActiveSubsystem;   /* '<S3>/Switch Case' */
  int8_T Integrator_PrevResetState;    /* '<S23>/Integrator' */
  int8_T Integrator_PrevResetState_n;  /* '<S16>/Integrator' */
  uint8_T is_active_c3_Controller;     /* '<S2>/Chart' */
  uint8_T is_c3_Controller;            /* '<S2>/Chart' */
} DW_Controller_T;

/* Invariant block signals (default storage) */
typedef struct {
  const real_T Constant;               /* '<S22>/Constant' */
  const real_T Constant_c;             /* '<S15>/Constant' */
} ConstB_Controller_T;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T AccPedal;                     /* '<Root>/AccPedal' */
  real_T BrakePedal;                   /* '<Root>/BrakePedal' */
  real_T fuelLevel;                    /* '<Root>/fuelLevel' */
  real_T SOC;                          /* '<Root>/SOC' */
  real_T realSpeed;                    /* '<Root>/realSpeed' */
} ExtU_Controller_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T ICEdem;                       /* '<Root>/ICEdem' */
  real_T Brake;                        /* '<Root>/Brake' */
  real_T MGUdem;                       /* '<Root>/MGUdem' */
} ExtY_Controller_T;

/* Real-time Model Data Structure */
struct tag_RTM_Controller_T {
  const char_T * volatile errorStatus;
};

/* Block signals (default storage) */
extern B_Controller_T Controller_B;

/* Block states (default storage) */
extern DW_Controller_T Controller_DW;

/* External inputs (root inport signals with default storage) */
extern ExtU_Controller_T Controller_U;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_Controller_T Controller_Y;
extern const ConstB_Controller_T Controller_ConstB;/* constant block i/o */

/* Model entry point functions */
extern void Controller_initialize(void);
extern void Controller_step(void);
extern void Controller_terminate(void);

/* Real-time Model object */
extern RT_MODEL_Controller_T *const Controller_M;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S16>/Saturation' : Eliminated Saturate block
 * Block '<S10>/K' : Eliminated nontunable gain of 1
 * Block '<S23>/Saturation' : Eliminated Saturate block
 * Block '<S17>/K' : Eliminated nontunable gain of 1
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Note that this particular code originates from a subsystem build,
 * and has its own system numbers different from the parent model.
 * Refer to the system hierarchy for this subsystem below, and use the
 * MATLAB hilite_system command to trace the generated code back
 * to the parent model.  For example,
 *
 * hilite_system('ControllerModel/Controller')    - opens subsystem ControllerModel/Controller
 * hilite_system('ControllerModel/Controller/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'ControllerModel'
 * '<S1>'   : 'ControllerModel/Controller'
 * '<S2>'   : 'ControllerModel/Controller/FSM'
 * '<S3>'   : 'ControllerModel/Controller/TrqDemController'
 * '<S4>'   : 'ControllerModel/Controller/FSM/Chart'
 * '<S5>'   : 'ControllerModel/Controller/TrqDemController/Combined'
 * '<S6>'   : 'ControllerModel/Controller/TrqDemController/Dead'
 * '<S7>'   : 'ControllerModel/Controller/TrqDemController/ED'
 * '<S8>'   : 'ControllerModel/Controller/TrqDemController/No charge'
 * '<S9>'   : 'ControllerModel/Controller/TrqDemController/Regenerative braking'
 * '<S10>'  : 'ControllerModel/Controller/TrqDemController/Combined/Low-Pass Filter (Discrete or Continuous)'
 * '<S11>'  : 'ControllerModel/Controller/TrqDemController/Combined/Low-Pass Filter (Discrete or Continuous)/Enable//disable time constant'
 * '<S12>'  : 'ControllerModel/Controller/TrqDemController/Combined/Low-Pass Filter (Discrete or Continuous)/Initialization'
 * '<S13>'  : 'ControllerModel/Controller/TrqDemController/Combined/Low-Pass Filter (Discrete or Continuous)/Integrator (Discrete or Continuous)'
 * '<S14>'  : 'ControllerModel/Controller/TrqDemController/Combined/Low-Pass Filter (Discrete or Continuous)/Enable//disable time constant/Compare To Zero'
 * '<S15>'  : 'ControllerModel/Controller/TrqDemController/Combined/Low-Pass Filter (Discrete or Continuous)/Initialization/Init_param'
 * '<S16>'  : 'ControllerModel/Controller/TrqDemController/Combined/Low-Pass Filter (Discrete or Continuous)/Integrator (Discrete or Continuous)/Discrete'
 * '<S17>'  : 'ControllerModel/Controller/TrqDemController/Regenerative braking/Low-Pass Filter (Discrete or Continuous)'
 * '<S18>'  : 'ControllerModel/Controller/TrqDemController/Regenerative braking/Low-Pass Filter (Discrete or Continuous)/Enable//disable time constant'
 * '<S19>'  : 'ControllerModel/Controller/TrqDemController/Regenerative braking/Low-Pass Filter (Discrete or Continuous)/Initialization'
 * '<S20>'  : 'ControllerModel/Controller/TrqDemController/Regenerative braking/Low-Pass Filter (Discrete or Continuous)/Integrator (Discrete or Continuous)'
 * '<S21>'  : 'ControllerModel/Controller/TrqDemController/Regenerative braking/Low-Pass Filter (Discrete or Continuous)/Enable//disable time constant/Compare To Zero'
 * '<S22>'  : 'ControllerModel/Controller/TrqDemController/Regenerative braking/Low-Pass Filter (Discrete or Continuous)/Initialization/Init_param'
 * '<S23>'  : 'ControllerModel/Controller/TrqDemController/Regenerative braking/Low-Pass Filter (Discrete or Continuous)/Integrator (Discrete or Continuous)/Discrete'
 */
#endif                                 /* RTW_HEADER_Controller_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
