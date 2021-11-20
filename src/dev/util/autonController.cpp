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

void runAuton(){
  switch(autonSelection){
    case 0:
      // odomVector firstPoint;
      // firstPoint.x=24;
      // firstPoint.y=24;
      // driveToPoint(firstPoint,45,10,1,1);
      break;
    case 1:

      break;
    case 2:

      break;
    case 3:

      break;
    case 4:

      break;
    case 5:

      break;
    default:
      break;
  }
}
