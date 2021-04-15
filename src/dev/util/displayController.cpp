#include "dev/util/displayController.h"
#include "dev/util/autonController.h"
#include "dev/util/misc.h"
#include "dev/util/odom.h"

pros::ADIAnalogIn button('A');
bool beingPressed = false;
bool initDisplayRun=true;

void display(){

  pros::lcd::set_text(0, "Auton Name: " + getAutonName());
  pros::lcd::set_text(1, "Auton Info: " + getAutonDescription());

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

    pros::delay(500);
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
