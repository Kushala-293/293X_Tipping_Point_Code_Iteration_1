#include "main.h"
#include "dev/util/misc.h"

pros::Controller master(pros::E_CONTROLLER_MASTER);

double ticksToInch(int ticks, double wheelDiameter){
  double rotations = (double)(ticks)/36000;
  double travelDistance = rotations*wheelDiameter*M_PI;
  return travelDistance;
}

double convertToDeg(double rad){
  return rad*(180/M_PI);
}

double convertToRad(double deg){
  return deg*(M_PI/180);
}
