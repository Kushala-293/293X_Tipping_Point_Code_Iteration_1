#include "main.h"

static int autonSelection=0;
int maxAuton=5;

std::string autonDescription;
std::string autonName;

void setAuton(int auton){
  autonSelection=auton;
}

int getAuton(){
  return autonSelection;
}

int getMaxAuton(){
  return maxAuton;
}

std::string getAutonName(){
  return autonName;
}

std::string getAutonDescription(){
  return autonDescription;
}

void updateAuton(){
  switch(autonSelection){
    case 0:
      autonName="Blue Side Left";
      autonDescription="Blue Side Left Desc";
      break;
    case 1:
      autonName="Blue Side Right";
      autonDescription="Blue Side Right Desc";
      break;
    case 2:
      autonName="Red Side Left";
      autonDescription="Red Side Left Desc";
      break;
    case 3:
      autonName="Red Side Right";
      autonDescription="Red Side Right Desc";
      break;
    case 4:
      autonName="Skills";
      autonDescription="Skills Desc";
      break;
    case 5:
      autonName="Testing";
      autonDescription="TESTING ONLY";
      break;
    default:
      break;
  }
}
