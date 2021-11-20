#include "main.h"

pros::Motor intake(8, MOTOR_GEARSET_6, 1, MOTOR_ENCODER_COUNTS);
pros::Controller master (pros::E_CONTROLLER_MASTER);

pros::ADIDigitalOut clamp('F');
pros::ADIDigitalOut leftHook('G');
pros::ADIDigitalOut rightHook('H');

bool clampState= false, hookState=false;

void spinIntake(double voltage){
  intake.move(voltage);
}

void stopIntake(){
  intake.set_brake_mode(MOTOR_BRAKE_COAST);
  intake.move(0);
}

void setClamp(bool state){
  clamp.set_value(state);
  clampState = state;
}

void setHooks(bool state){
  leftHook.set_value(state);
  rightHook.set_value(state);
  hookState = state;
}

void toggleClamp(){
  setClamp(!clampState);
}

void toggleHook(){
  setHooks(!hookState);
}
