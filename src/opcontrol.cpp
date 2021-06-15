#include "main.h"

void opcontrol(){

  int driveState=1;
  bool driveSwitch=false;

  while(true){

    if(isBeingPressed()==false)
      setBeingPressed(false);

    if(master.get_digital(DIGITAL_A) && !driveSwitch){
      driveState++;
      if(driveState>1)
        driveState=0;
      driveSwitch=true;
    }else if(!master.get_digital(DIGITAL_A)){
      driveSwitch=false;
    }

    if(driveState==0){
      double leftJoystick = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
      double rightJoystick = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
      double correctedLeftJoystick;
      double correctedRightJoystick;
      int correctedOutput;
      int absolute_Difference;

    //DEADBAND
      if (abs(leftJoystick)<10)
        leftJoystick=0;
      if (abs(rightJoystick)<10)
        rightJoystick=0;

    // STRAIGHT LINE CORRECTION
      if (leftJoystick>=0 && rightJoystick>=0)
        absolute_Difference = abs(leftJoystick-rightJoystick);
      else if (leftJoystick<=0 && rightJoystick<=0)
        absolute_Difference = abs(leftJoystick-rightJoystick);
      else
        absolute_Difference=51;

        if (absolute_Difference <= 50){
          correctedOutput = (leftJoystick+rightJoystick)/2;
          correctedLeftJoystick = correctedOutput;
          correctedRightJoystick = correctedOutput;
          LF.move_velocity(correctedLeftJoystick * 1.58);
          LB.move_velocity(correctedLeftJoystick * 1.58);
          RF.move_velocity(-correctedRightJoystick * 1.58);
          RB.move_velocity(-correctedRightJoystick * 1.58);
        }
        else{
          LF.move_velocity(leftJoystick * 1.58);
          LB.move_velocity(leftJoystick * 1.58);
          RF.move_velocity(-rightJoystick * 1.58);
          RB.move_velocity(-rightJoystick * 1.58);
        }
      }else if(driveState==1){
      LF.move_velocity(master.get_analog(ANALOG_LEFT_Y) * 1.58  + master.get_analog(ANALOG_RIGHT_X) * 1.58);
      LB.move_velocity(master.get_analog(ANALOG_LEFT_Y) * 1.58  + master.get_analog(ANALOG_RIGHT_X) * 1.58);
      RF.move_velocity(-master.get_analog(ANALOG_LEFT_Y) * 1.58 + master.get_analog(ANALOG_RIGHT_X) * 1.58);
      RB.move_velocity(-master.get_analog(ANALOG_LEFT_Y) * 1.58 + master.get_analog(ANALOG_RIGHT_X) * 1.58);
    }

     pros::delay(50);
  }
}
