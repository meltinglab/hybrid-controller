/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Controller.c
 *
 * Code generated for Simulink model 'Controller'.
 *
 * Model version                  : 1.11
 * Simulink Coder version         : 9.4 (R2020b) 29-Jul-2020
 * C/C++ source code generated on : Fri Feb 26 19:17:22 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objective: MISRA C:2012 guidelines
 * Validation result: All passed
 */

#include "Controller.h"
#include "Controller_private.h"

/* Named constants for Chart: '<S2>/Chart' */
#define Control_IN_Rigenerative_Braking ((uint8_T)5U)
#define Controller_IN_Combined         ((uint8_T)1U)
#define Controller_IN_Dead             ((uint8_T)2U)
#define Controller_IN_ED               ((uint8_T)3U)
#define Controller_IN_NoCharge         ((uint8_T)4U)
#define Controller_SpeedEDmax          (45.0)
#define Controller_maxAccICE           (0.53846153846153844)
#define Controller_maxAccMGU           (0.46153846153846156)

/* Block signals (default storage) */
B_Controller_T Controller_B;

/* Block states (default storage) */
DW_Controller_T Controller_DW;

/* External inputs (root inport signals with default storage) */
ExtU_Controller_T Controller_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_Controller_T Controller_Y;

/* Real-time model */
static RT_MODEL_Controller_T Controller_M_;
RT_MODEL_Controller_T *const Controller_M = &Controller_M_;

/* Model step function */
void Controller_step(void)
{
  real_T rtb_Acc;
  real_T rtb_Saturation3;
  real_T u0;
  int32_T rtb_state;
  int8_T rtPrevAction;
  boolean_T rtb_Compare_l;

  /* Sum: '<S2>/Subtract' incorporates:
   *  Inport: '<Root>/AccPedal'
   *  Inport: '<Root>/BrakePedal'
   */
  rtb_Acc = Controller_U.AccPedal - Controller_U.BrakePedal;

  /* Chart: '<S2>/Chart' incorporates:
   *  Inport: '<Root>/SOC'
   *  Inport: '<Root>/fuelLevel'
   *  Inport: '<Root>/realSpeed'
   */
  if (((uint32_T)Controller_DW.is_active_c3_Controller) == 0U) {
    Controller_DW.is_active_c3_Controller = 1U;
    Controller_DW.is_c3_Controller = Controller_IN_Dead;

    /* Dead state. It occurs when there is no fuel in the tank and not charge in the battery */
    rtb_state = 0;
  } else {
    switch (Controller_DW.is_c3_Controller) {
     case Controller_IN_Combined:
      if (rtb_Acc < 0.0) {
        Controller_DW.is_c3_Controller = Control_IN_Rigenerative_Braking;

        /* you will go in that state every time you brake. So the acceleration will be lower than zero. */
        /* this will so charge the battery til to reach the SOCmax that will limit my case */
        rtb_state = 4;
      } else if ((Controller_U.fuelLevel < 0.5) && (Controller_U.SOC <= 15.0)) {
        Controller_DW.is_c3_Controller = Controller_IN_Dead;

        /* Dead state. It occurs when there is no fuel in the tank and not charge in the battery */
        rtb_state = 0;
      } else if (((Controller_U.realSpeed < Controller_SpeedEDmax) &&
                  (Controller_U.SOC > 15.0)) && (rtb_Acc < Controller_maxAccMGU))
      {
        Controller_DW.is_c3_Controller = Controller_IN_ED;

        /* Electric drive. Occurs when forced by the city zone of under a reference speed */
        /* imponi v<vedmax se non vi è benzina */
        rtb_state = 2;
      } else if ((Controller_U.SOC <= 15.0) && (Controller_U.fuelLevel > 0.5)) {
        Controller_DW.is_c3_Controller = Controller_IN_NoCharge;

        /* occurs when the battery SOC is under a treshold. The car switch full ICE */
        rtb_state = 1;
      } else {
        /* )(Hybrid drive) over a certain spped both the engine will collaborate to give the required torque */
        /* IMPONI V<VEDmin se finisce il carburante prima di andare in ED */
        rtb_state = 3;
      }
      break;

     case Controller_IN_Dead:
      if (rtb_Acc < 0.0) {
        Controller_DW.is_c3_Controller = Control_IN_Rigenerative_Braking;

        /* you will go in that state every time you brake. So the acceleration will be lower than zero. */
        /* this will so charge the battery til to reach the SOCmax that will limit my case */
        rtb_state = 4;
      } else if (((Controller_U.SOC > 15.0) && ((rtb_Acc > Controller_maxAccICE)
        || (rtb_Acc > Controller_maxAccMGU))) && (Controller_U.fuelLevel > 0.5))
      {
        Controller_DW.is_c3_Controller = Controller_IN_Combined;

        /* )(Hybrid drive) over a certain spped both the engine will collaborate to give the required torque */
        /* IMPONI V<VEDmin se finisce il carburante prima di andare in ED */
        rtb_state = 3;
      } else if (Controller_U.SOC > 15.0) {
        Controller_DW.is_c3_Controller = Controller_IN_ED;

        /* Electric drive. Occurs when forced by the city zone of under a reference speed */
        /* imponi v<vedmax se non vi è benzina */
        rtb_state = 2;
      } else if (Controller_U.fuelLevel > 0.5) {
        Controller_DW.is_c3_Controller = Controller_IN_NoCharge;

        /* occurs when the battery SOC is under a treshold. The car switch full ICE */
        rtb_state = 1;
      } else {
        /* Dead state. It occurs when there is no fuel in the tank and not charge in the battery */
        rtb_state = 0;
      }
      break;

     case Controller_IN_ED:
      if (rtb_Acc < 0.0) {
        Controller_DW.is_c3_Controller = Control_IN_Rigenerative_Braking;

        /* you will go in that state every time you brake. So the acceleration will be lower than zero. */
        /* this will so charge the battery til to reach the SOCmax that will limit my case */
        rtb_state = 4;
      } else if ((Controller_U.SOC < 15.0) && (Controller_U.fuelLevel < 0.5)) {
        Controller_DW.is_c3_Controller = Controller_IN_Dead;

        /* Dead state. It occurs when there is no fuel in the tank and not charge in the battery */
        rtb_state = 0;
      } else if ((Controller_U.fuelLevel > 0.5) && (Controller_U.SOC <= 15.0)) {
        Controller_DW.is_c3_Controller = Controller_IN_NoCharge;

        /* occurs when the battery SOC is under a treshold. The car switch full ICE */
        rtb_state = 1;
      } else if (((Controller_U.realSpeed >= Controller_SpeedEDmax) &&
                  (Controller_U.fuelLevel > 0.5)) || ((Controller_U.fuelLevel >
                   0.5) && (rtb_Acc > Controller_maxAccMGU))) {
        Controller_DW.is_c3_Controller = Controller_IN_Combined;

        /* )(Hybrid drive) over a certain spped both the engine will collaborate to give the required torque */
        /* IMPONI V<VEDmin se finisce il carburante prima di andare in ED */
        rtb_state = 3;
      } else {
        /* Electric drive. Occurs when forced by the city zone of under a reference speed */
        /* imponi v<vedmax se non vi è benzina */
        rtb_state = 2;
      }
      break;

     case Controller_IN_NoCharge:
      if (rtb_Acc < 0.0) {
        Controller_DW.is_c3_Controller = Control_IN_Rigenerative_Braking;

        /* you will go in that state every time you brake. So the acceleration will be lower than zero. */
        /* this will so charge the battery til to reach the SOCmax that will limit my case */
        rtb_state = 4;
      } else if ((Controller_U.fuelLevel < 0.5) && (Controller_U.SOC <= 15.0)) {
        Controller_DW.is_c3_Controller = Controller_IN_Dead;

        /* Dead state. It occurs when there is no fuel in the tank and not charge in the battery */
        rtb_state = 0;
      } else if (((Controller_U.SOC > 15.0) && (Controller_U.realSpeed <
                   Controller_SpeedEDmax)) || ((Controller_U.fuelLevel < 0.5) &&
                  (Controller_U.SOC > 15.0))) {
        Controller_DW.is_c3_Controller = Controller_IN_ED;

        /* Electric drive. Occurs when forced by the city zone of under a reference speed */
        /* imponi v<vedmax se non vi è benzina */
        rtb_state = 2;
      } else if (((Controller_U.SOC > 15.0) && (Controller_U.fuelLevel > 0.5)) &&
                 (rtb_Acc > Controller_maxAccICE)) {
        Controller_DW.is_c3_Controller = Controller_IN_Combined;

        /* )(Hybrid drive) over a certain spped both the engine will collaborate to give the required torque */
        /* IMPONI V<VEDmin se finisce il carburante prima di andare in ED */
        rtb_state = 3;
      } else {
        /* occurs when the battery SOC is under a treshold. The car switch full ICE */
        rtb_state = 1;
      }
      break;

     default:
      /* case IN_Rigenerative_Braking: */
      if (rtb_Acc < 0.0) {
        Controller_DW.is_c3_Controller = Control_IN_Rigenerative_Braking;

        /* you will go in that state every time you brake. So the acceleration will be lower than zero. */
        /* this will so charge the battery til to reach the SOCmax that will limit my case */
        rtb_state = 4;
      } else if ((Controller_U.SOC < 15.0) && (Controller_U.fuelLevel < 0.5)) {
        Controller_DW.is_c3_Controller = Controller_IN_Dead;

        /* Dead state. It occurs when there is no fuel in the tank and not charge in the battery */
        rtb_state = 0;
      } else if ((Controller_U.SOC > 15.0) && (Controller_U.realSpeed <
                  Controller_SpeedEDmax)) {
        Controller_DW.is_c3_Controller = Controller_IN_ED;

        /* Electric drive. Occurs when forced by the city zone of under a reference speed */
        /* imponi v<vedmax se non vi è benzina */
        rtb_state = 2;
      } else if ((Controller_U.fuelLevel > 0.5) && (Controller_U.SOC < 15.0)) {
        Controller_DW.is_c3_Controller = Controller_IN_NoCharge;

        /* occurs when the battery SOC is under a treshold. The car switch full ICE */
        rtb_state = 1;
      } else if (((Controller_U.SOC > 15.0) && (Controller_U.realSpeed >
                   Controller_SpeedEDmax)) && (Controller_U.fuelLevel > 0.5)) {
        Controller_DW.is_c3_Controller = Controller_IN_Combined;

        /* )(Hybrid drive) over a certain spped both the engine will collaborate to give the required torque */
        /* IMPONI V<VEDmin se finisce il carburante prima di andare in ED */
        rtb_state = 3;
      } else {
        /* you will go in that state every time you brake. So the acceleration will be lower than zero. */
        /* this will so charge the battery til to reach the SOCmax that will limit my case */
        rtb_state = 4;
      }
      break;
    }
  }

  /* End of Chart: '<S2>/Chart' */

  /* SwitchCase: '<S3>/Switch Case' */
  rtPrevAction = Controller_DW.SwitchCase_ActiveSubsystem;
  switch (rtb_state) {
   case 0:
    Controller_DW.SwitchCase_ActiveSubsystem = 0;
    break;

   case 1:
    Controller_DW.SwitchCase_ActiveSubsystem = 1;
    break;

   case 2:
    Controller_DW.SwitchCase_ActiveSubsystem = 2;
    break;

   case 3:
    Controller_DW.SwitchCase_ActiveSubsystem = 3;
    break;

   default:
    Controller_DW.SwitchCase_ActiveSubsystem = 4;
    break;
  }

  switch (Controller_DW.SwitchCase_ActiveSubsystem) {
   case 0:
    /* Outputs for IfAction SubSystem: '<S3>/Dead' incorporates:
     *  ActionPort: '<S6>/Action Port'
     */
    /* Sum: '<S10>/Sum' incorporates:
     *  Constant: '<S6>/Constant'
     *  Merge: '<S3>/Merge2'
     *  SignalConversion generated from: '<S6>/Brake'
     */
    Controller_B.Merge2 = 0.0;

    /* Gain: '<S9>/Gain' incorporates:
     *  Constant: '<S6>/Constant'
     *  Merge: '<S3>/Merge'
     *  SignalConversion generated from: '<S6>/ICreq'
     */
    Controller_B.Merge = 0.0;

    /* Gain: '<S8>/Gain' incorporates:
     *  Constant: '<S6>/Constant'
     *  Merge: '<S3>/Merge1'
     *  SignalConversion generated from: '<S6>/MGUreq'
     */
    Controller_B.Merge1 = 0.0;

    /* End of Outputs for SubSystem: '<S3>/Dead' */
    break;

   case 1:
    /* Outputs for IfAction SubSystem: '<S3>/No charge' incorporates:
     *  ActionPort: '<S9>/Action Port'
     */
    /* Gain: '<S9>/Gain' incorporates:
     *  Inport: '<Root>/AccPedal'
     */
    Controller_B.Merge = 1.8571428571428572 * Controller_U.AccPedal;

    /* Saturate: '<S9>/Saturation' */
    if (Controller_B.Merge > 1.0) {
      /* Gain: '<S9>/Gain' incorporates:
       *  Merge: '<S3>/Merge'
       */
      Controller_B.Merge = 1.0;
    } else {
      if (Controller_B.Merge < 0.0) {
        /* Gain: '<S9>/Gain' incorporates:
         *  Merge: '<S3>/Merge'
         */
        Controller_B.Merge = 0.0;
      }
    }

    /* End of Saturate: '<S9>/Saturation' */

    /* Gain: '<S8>/Gain' incorporates:
     *  Constant: '<S9>/Constant'
     *  Merge: '<S3>/Merge1'
     *  SignalConversion generated from: '<S9>/MGUreq'
     */
    Controller_B.Merge1 = 0.0;

    /* Sum: '<S10>/Sum' incorporates:
     *  Constant: '<S9>/Constant1'
     *  Merge: '<S3>/Merge2'
     *  SignalConversion generated from: '<S9>/FrontBrake'
     */
    Controller_B.Merge2 = 0.0;

    /* End of Outputs for SubSystem: '<S3>/No charge' */
    break;

   case 2:
    /* Outputs for IfAction SubSystem: '<S3>/ED' incorporates:
     *  ActionPort: '<S8>/Action Port'
     */
    /* Gain: '<S9>/Gain' incorporates:
     *  Constant: '<S8>/Constant'
     *  Merge: '<S3>/Merge'
     *  SignalConversion generated from: '<S8>/ICreq'
     */
    Controller_B.Merge = 0.0;

    /* Gain: '<S8>/Gain' incorporates:
     *  Inport: '<Root>/AccPedal'
     */
    Controller_B.Merge1 = 2.1666666666666665 * Controller_U.AccPedal;

    /* Saturate: '<S8>/Saturation' */
    if (Controller_B.Merge1 > 1.0) {
      /* Gain: '<S8>/Gain' incorporates:
       *  Merge: '<S3>/Merge1'
       */
      Controller_B.Merge1 = 1.0;
    } else {
      if (Controller_B.Merge1 < 0.0) {
        /* Gain: '<S8>/Gain' incorporates:
         *  Merge: '<S3>/Merge1'
         */
        Controller_B.Merge1 = 0.0;
      }
    }

    /* End of Saturate: '<S8>/Saturation' */

    /* Sum: '<S10>/Sum' incorporates:
     *  Constant: '<S8>/Constant1'
     *  Merge: '<S3>/Merge2'
     *  SignalConversion generated from: '<S8>/FrontBrake'
     */
    Controller_B.Merge2 = 0.0;

    /* End of Outputs for SubSystem: '<S3>/ED' */
    break;

   case 3:
    if (((int32_T)Controller_DW.SwitchCase_ActiveSubsystem) != ((int32_T)
         rtPrevAction)) {
      /* InitializeConditions for IfAction SubSystem: '<S3>/Combined' incorporates:
       *  ActionPort: '<S5>/Action Port'
       */
      /* InitializeConditions for SwitchCase: '<S3>/Switch Case' incorporates:
       *  DiscreteIntegrator: '<S17>/Integrator'
       */
      Controller_DW.Integrator_DSTATE_n = Controller_ConstB.Constant_c;
      Controller_DW.Integrator_PrevResetState_n = 0;

      /* End of InitializeConditions for SubSystem: '<S3>/Combined' */
    }

    /* Outputs for IfAction SubSystem: '<S3>/Combined' incorporates:
     *  ActionPort: '<S5>/Action Port'
     */
    /* RelationalOperator: '<S15>/Compare' incorporates:
     *  Constant: '<S12>/Time constant'
     *  Constant: '<S15>/Constant'
     *  Sum: '<S12>/Sum1'
     */
    rtb_Compare_l = ((2.0 - Controller_B.Probe_j[0]) <= 0.0);

    /* DiscreteIntegrator: '<S17>/Integrator' */
    if (rtb_Compare_l || (((int32_T)Controller_DW.Integrator_PrevResetState_n)
                          != 0)) {
      Controller_DW.Integrator_DSTATE_n = Controller_ConstB.Constant_c;
    }

    /* Gain: '<S5>/Gain' incorporates:
     *  DiscreteIntegrator: '<S17>/Integrator'
     */
    rtb_Acc = 1.8571428571428572 * Controller_DW.Integrator_DSTATE_n;

    /* Saturate: '<S5>/Saturation' */
    if (rtb_Acc > 1.0) {
      rtb_Acc = 1.0;
    } else {
      if (rtb_Acc < 0.0) {
        rtb_Acc = 0.0;
      }
    }

    /* End of Saturate: '<S5>/Saturation' */

    /* Sum: '<S5>/Sum' incorporates:
     *  Gain: '<S5>/Gain2'
     *  Inport: '<Root>/AccPedal'
     */
    rtb_Saturation3 = Controller_U.AccPedal - (0.53846153846153844 * rtb_Acc);

    /* Gain: '<S8>/Gain' incorporates:
     *  Gain: '<S5>/Gain1'
     */
    Controller_B.Merge1 = 2.1666666666666665 * rtb_Saturation3;

    /* Saturate: '<S5>/Saturation1' */
    if (Controller_B.Merge1 > 1.0) {
      /* Gain: '<S8>/Gain' */
      Controller_B.Merge1 = 1.0;
    } else {
      if (Controller_B.Merge1 < 0.0) {
        /* Gain: '<S8>/Gain' */
        Controller_B.Merge1 = 0.0;
      }
    }

    /* End of Saturate: '<S5>/Saturation1' */

    /* Sum: '<S5>/Sum2' incorporates:
     *  Gain: '<S5>/Gain3'
     */
    u0 = rtb_Saturation3 - (0.46153846153846156 * Controller_B.Merge1);

    /* Saturate: '<S5>/Saturation3' */
    if (rtb_Saturation3 > 0.0) {
      rtb_Saturation3 = 0.0;
    } else {
      if (rtb_Saturation3 < -1.0) {
        rtb_Saturation3 = -1.0;
      }
    }

    /* End of Saturate: '<S5>/Saturation3' */

    /* Saturate: '<S5>/Saturation2' */
    if (u0 > 1.0) {
      u0 = 1.0;
    } else {
      if (u0 < 0.0) {
        u0 = 0.0;
      }
    }

    /* End of Saturate: '<S5>/Saturation2' */

    /* Gain: '<S9>/Gain' incorporates:
     *  Gain: '<S5>/Gain4'
     *  Merge: '<S3>/Merge'
     *  Sum: '<S5>/Sum1'
     *  Sum: '<S5>/Sum3'
     */
    Controller_B.Merge = ((rtb_Saturation3 + u0) * 1.8571428571428572) + rtb_Acc;

    /* Sum: '<S10>/Sum' incorporates:
     *  Constant: '<S5>/Constant1'
     *  Merge: '<S3>/Merge2'
     *  SignalConversion generated from: '<S5>/FrontBrake'
     */
    Controller_B.Merge2 = 0.0;

    /* Update for DiscreteIntegrator: '<S17>/Integrator' incorporates:
     *  Constant: '<S12>/Time constant'
     *  Inport: '<Root>/AccPedal'
     *  MinMax: '<S12>/Max'
     *  Product: '<S11>/1overT'
     *  Sum: '<S11>/Sum1'
     */
    Controller_DW.Integrator_DSTATE_n += ((1.0 / fmax(Controller_B.Probe_j[0],
      2.0)) * (Controller_U.AccPedal - Controller_DW.Integrator_DSTATE_n)) *
      0.01;
    Controller_DW.Integrator_PrevResetState_n = (int8_T)(rtb_Compare_l ? 1 : 0);

    /* End of Outputs for SubSystem: '<S3>/Combined' */
    break;

   case 4:
    if (((int32_T)Controller_DW.SwitchCase_ActiveSubsystem) != ((int32_T)
         rtPrevAction)) {
      /* InitializeConditions for IfAction SubSystem: '<S3>/Regenerative braking' incorporates:
       *  ActionPort: '<S10>/Action Port'
       */
      /* InitializeConditions for SwitchCase: '<S3>/Switch Case' incorporates:
       *  DiscreteIntegrator: '<S24>/Integrator'
       */
      Controller_DW.Integrator_DSTATE = Controller_ConstB.Constant;
      Controller_DW.Integrator_PrevResetState = 0;

      /* End of InitializeConditions for SubSystem: '<S3>/Regenerative braking' */
    }

    /* Outputs for IfAction SubSystem: '<S3>/Regenerative braking' incorporates:
     *  ActionPort: '<S10>/Action Port'
     */
    /* RelationalOperator: '<S22>/Compare' incorporates:
     *  Constant: '<S19>/Time constant'
     *  Constant: '<S22>/Constant'
     *  Sum: '<S19>/Sum1'
     */
    rtb_Compare_l = ((1.0 - Controller_B.Probe[0]) <= 0.0);

    /* DiscreteIntegrator: '<S24>/Integrator' */
    if (rtb_Compare_l || (((int32_T)Controller_DW.Integrator_PrevResetState) !=
                          0)) {
      Controller_DW.Integrator_DSTATE = Controller_ConstB.Constant;
    }

    /* Gain: '<S10>/Gain2' incorporates:
     *  Constant: '<S10>/Constant'
     *  DiscreteIntegrator: '<S24>/Integrator'
     *  Inport: '<Root>/SOC'
     *  Product: '<S10>/Product'
     *  RelationalOperator: '<S10>/GreaterThan'
     */
    rtb_Acc = (((real_T)((99.0 > Controller_U.SOC) ? 1 : 0)) *
               Controller_DW.Integrator_DSTATE) * 4.666666666666667;

    /* Saturate: '<S10>/Saturation' */
    if (rtb_Acc > 1.0) {
      rtb_Acc = 1.0;
    } else {
      if (rtb_Acc < 0.0) {
        rtb_Acc = 0.0;
      }
    }

    /* End of Saturate: '<S10>/Saturation' */

    /* Sum: '<S10>/Sum' incorporates:
     *  Gain: '<S10>/Gain1'
     *  Inport: '<Root>/BrakePedal'
     */
    Controller_B.Merge2 = Controller_U.BrakePedal - (0.21428571428571427 *
      rtb_Acc);

    /* Saturate: '<S10>/Saturation2' */
    if (Controller_B.Merge2 > 0.0) {
      rtb_Saturation3 = 0.0;
    } else if (Controller_B.Merge2 < -1.0) {
      rtb_Saturation3 = -1.0;
    } else {
      rtb_Saturation3 = Controller_B.Merge2;
    }

    /* End of Saturate: '<S10>/Saturation2' */

    /* Gain: '<S8>/Gain' incorporates:
     *  Gain: '<S10>/Gain'
     *  Gain: '<S10>/Gain3'
     *  Merge: '<S3>/Merge1'
     *  Sum: '<S10>/Sum1'
     *
     * Block description for '<S10>/Gain':
     *  added a gain about -0.65 to introduce the concept of efficency in the
     *  regenerative braking
     */
    Controller_B.Merge1 = -((4.666666666666667 * rtb_Saturation3) + rtb_Acc);

    /* Saturate: '<S10>/Saturation1' */
    if (Controller_B.Merge2 > 1.0) {
      /* Sum: '<S10>/Sum' incorporates:
       *  Merge: '<S3>/Merge2'
       */
      Controller_B.Merge2 = 1.0;
    } else {
      if (Controller_B.Merge2 < 0.0) {
        /* Sum: '<S10>/Sum' incorporates:
         *  Merge: '<S3>/Merge2'
         */
        Controller_B.Merge2 = 0.0;
      }
    }

    /* End of Saturate: '<S10>/Saturation1' */

    /* Gain: '<S9>/Gain' incorporates:
     *  Constant: '<S10>/Constant1'
     *  Merge: '<S3>/Merge'
     *  SignalConversion generated from: '<S10>/ICreq'
     */
    Controller_B.Merge = 0.0;

    /* Update for DiscreteIntegrator: '<S24>/Integrator' incorporates:
     *  Constant: '<S19>/Time constant'
     *  Inport: '<Root>/BrakePedal'
     *  MinMax: '<S19>/Max'
     *  Product: '<S18>/1overT'
     *  Sum: '<S18>/Sum1'
     */
    Controller_DW.Integrator_DSTATE += ((1.0 / fmax(Controller_B.Probe[0], 1.0))
      * (Controller_U.BrakePedal - Controller_DW.Integrator_DSTATE)) * 0.01;
    Controller_DW.Integrator_PrevResetState = (int8_T)(rtb_Compare_l ? 1 : 0);

    /* End of Outputs for SubSystem: '<S3>/Regenerative braking' */
    break;

   default:
    /* no actions */
    break;
  }

  /* End of SwitchCase: '<S3>/Switch Case' */

  /* Outport: '<Root>/ICEdem' */
  Controller_Y.ICEdem = Controller_B.Merge;

  /* Outport: '<Root>/Brake' */
  Controller_Y.Brake = Controller_B.Merge2;

  /* Outport: '<Root>/MGUdem' */
  Controller_Y.MGUdem = Controller_B.Merge1;
}

/* Model initialize function */
void Controller_initialize(void)
{
  /* Start for SwitchCase: '<S3>/Switch Case' */
  Controller_DW.SwitchCase_ActiveSubsystem = -1;

  /* SystemInitialize for IfAction SubSystem: '<S3>/Combined' */
  /* Start for Probe: '<S12>/Probe' */
  Controller_B.Probe_j[0] = 0.01;
  Controller_B.Probe_j[1] = 0.0;

  /* InitializeConditions for DiscreteIntegrator: '<S17>/Integrator' */
  Controller_DW.Integrator_DSTATE_n = Controller_ConstB.Constant_c;

  /* End of SystemInitialize for SubSystem: '<S3>/Combined' */

  /* SystemInitialize for IfAction SubSystem: '<S3>/Regenerative braking' */
  /* Start for Probe: '<S19>/Probe' */
  Controller_B.Probe[0] = 0.01;
  Controller_B.Probe[1] = 0.0;

  /* InitializeConditions for DiscreteIntegrator: '<S24>/Integrator' */
  Controller_DW.Integrator_DSTATE = Controller_ConstB.Constant;

  /* End of SystemInitialize for SubSystem: '<S3>/Regenerative braking' */

  /* SystemInitialize for Outport: '<Root>/ICEdem' */
  Controller_Y.ICEdem = Controller_B.Merge;

  /* SystemInitialize for Outport: '<Root>/Brake' */
  Controller_Y.Brake = Controller_B.Merge2;

  /* SystemInitialize for Outport: '<Root>/MGUdem' */
  Controller_Y.MGUdem = Controller_B.Merge1;
}

/* Model terminate function */
void Controller_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
