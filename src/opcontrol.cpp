#include "main.h"

void opcontrol(){

  int driveState = 0;
  double direction = 1;

  int goalType = 0;

  while(true){

    if(master.get_digital_new_press(DIGITAL_X)){
      if(master.get_digital(DIGITAL_L2)){//Swaps between drive states (Split Arcade/Tank)
        driveState++;
        driveState=driveState%2;
      }else{//Swaps the drive direction
        direction *= -1.0;
      }
    }

    if(master.get_digital_new_press(DIGITAL_B)){
      manualMode = !manualMode;
    }

    //Tank Control
    if(driveState==0){
      double leftJoystick = master.get_analog(ANALOG_LEFT_Y);
      double rightJoystick = master.get_analog(ANALOG_RIGHT_Y);
      int correctedOutput;
      int absoluteDifference;

      //Deadband
      if (abs(leftJoystick)<10)
        leftJoystick=0;
      if (abs(rightJoystick)<10)
        rightJoystick=0;

      //Straight Line Correction
      if (leftJoystick>=0 && rightJoystick>=0)
        absoluteDifference = abs(leftJoystick-rightJoystick);
      else if (leftJoystick<=0 && rightJoystick<=0)
        absoluteDifference = abs(leftJoystick-rightJoystick);
      else
        absoluteDifference=51;

        if (absoluteDifference <= 50){
          correctedOutput = (leftJoystick+rightJoystick)/2;
          drive(correctedOutput*direction, correctedOutput*direction);
        }else{
          if(direction==1.0)
            drive(leftJoystick, rightJoystick);
          else
            drive(-rightJoystick, -leftJoystick);
        }
      }

      //Split Arcade Control
      else if(driveState==1){
        if(direction == 1.0)
          drive(master.get_analog(ANALOG_LEFT_Y) + master.get_analog(ANALOG_RIGHT_X),
              master.get_analog(ANALOG_LEFT_Y) - master.get_analog(ANALOG_RIGHT_X));
        else
          drive(master.get_analog(ANALOG_LEFT_Y)*direction + master.get_analog(ANALOG_RIGHT_X),
              master.get_analog(ANALOG_LEFT_Y)*direction - master.get_analog(ANALOG_RIGHT_X));
      }

      //Intake
      if(master.get_digital_new_press(DIGITAL_A)){
        if(intake.get_actual_velocity() != 0)
          stopIntake();
        else{
          if(master.get_digital(DIGITAL_L2))
            spinIntake(127);
          else
            spinIntake(-90);
        }
      }

      //Mobile Goal Tilter
      if(master.get_digital(DIGITAL_R1) && !master.get_digital(DIGITAL_L2)){
        goalTilter.move(127);
      }
      else if(master.get_digital(DIGITAL_R2) && !master.get_digital(DIGITAL_L2)){
        goalTilter.move(-127);
      }
      else{
        goalTilter.move(0);
        goalTilter.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
      }

      //Pneumatics
      if(master.get_digital_new_press(DIGITAL_L1)){
        if(!master.get_digital(DIGITAL_L2))
          toggleClamp();
        else
          toggleHook();
      }



        //Skewer + Lift


      if(!manualMode){
        if(master.get_digital_new_press(DIGITAL_RIGHT)){
          goalType=0;
          setCocked(false);
        }else if(master.get_digital_new_press(DIGITAL_UP)){
          goalType=-1;
          setCocked(false);
        }else if(master.get_digital_new_press(DIGITAL_LEFT)){
          goalType=1;
          setCocked(false);
        }else if(master.get_digital_new_press(DIGITAL_DOWN)){
          goalType=52;
          skewerTargetHeight = skewerLift.get_position();
          setCocked(false);
        }


      if(master.get_digital_new_press(DIGITAL_R1) && master.get_digital(DIGITAL_L2)){
        reset();
      }else if(master.get_digital_new_press(DIGITAL_R2) && master.get_digital(DIGITAL_L2)){
        switch(goalType){
          case -1: //Move Skewer Out of Way
            if(!cocked){
              setTargetAngle(2000);
              setCocked(true);
            }else if(cocked){
              reset();
            }
            break;
          case 0: //Low Neutral Goal
              if(justScored){
                isJerkingOff=true;
                justJerked=true;
                setTargetAngle(3150);
                setScored(false);
              }else if(justJerked){
                reset();
              }else if(!cocked){
                setTargetAngle(1900);
                isJerkingOff=true;
                setCocked(true);
              }else if(cocked){
                setTargetAngle(3250);
                setCocked(false);
                setScored(true);
              }
            break;
          case 1: //High Neutral Goal
          if(justScored){
            isJerkingOff=true;
            justJerked=true;
            setTargetAngle(2900);
            setTargetHeight(baseHeight-1730);
            setScored(false);
          }else if(justJerked){
            reset();
          }else if(!cocked){
            setTargetAngle(2000);
            setTargetHeight(baseHeight-1700);
            isJerkingOff=true;
            setCocked(true);
          }else if(cocked){
            setTargetAngle(3000);
            setCocked(false);
            setScored(true);
          }
          case 2: //Platform

            break;
          default:
            break;
      }
    }
  }else{
      setTargetAngle(2000);
      if(master.get_digital(DIGITAL_R1) && master.get_digital(DIGITAL_L2))
        skewerLift.move(-127);
      else if(master.get_digital(DIGITAL_R2) && master.get_digital(DIGITAL_L2))
        skewerLift.move(127);
      else
        skewerLift.move(0);
  }

  //DISPLAY CODE
  if(!isBeingPressed())
    setBeingPressed(false);

   pros::delay(30);

  }
}
