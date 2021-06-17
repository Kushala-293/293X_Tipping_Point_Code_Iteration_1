#include "main.h"


pros::ADIAnalogIn button('A');
bool beingPressed = false;
bool initDisplayRun=true;

void display(){

  pros::lcd::set_text(0, "Auton Name: " + getAutonName());
  pros::lcd::set_text(1, "Auton Info: " + getAutonDescription());
  pros::lcd::set_text(3, "Y: (" + std::to_string(globalPosition.y) + ")");
  pros::lcd::set_text(4, "X: (" + std::to_string(globalPosition.x) + ")");
  pros::lcd::set_text(5, "A: (" + std::to_string(convertToDeg(globalPosition.a)) + ")");

  if(pros::competition::is_autonomous())
    pros::lcd::set_text(6, "Autonomous Enabled");
  else
    pros::lcd::clear_line(6);


  if(button.get_value()<25 && !beingPressed){
    setAuton(getAuton()+1);
    beingPressed=true;
  }else if(button.get_value()>=25){
    beingPressed=false;
  }
  if(getAuton()>getMaxAuton() || initDisplayRun)
    setAuton(0);

  updateAuton();
  initDisplayRun=false;
}

void asyncDisplay(void* param){
  while(true){
    if(isBeingPressed()==false)
      setBeingPressed(false);

    display();

    pros::delay(250);
  }
}

void refresh(){
  setAuton(0);
}

bool isBeingPressed(){
  return beingPressed;
}

void setBeingPressed(bool state){
  beingPressed=state;
}
