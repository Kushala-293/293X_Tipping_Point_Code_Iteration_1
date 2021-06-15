#include "main.h"

pros::Controller master(pros::E_CONTROLLER_MASTER);

double ticksToInch(int ticks, double wheelDiameter){
  double rotations = (double)(ticks)/36000;
  double travelDistance = rotations*wheelDiameter*M_PI;
  return travelDistance;
}

double average (double firstTerm, double secondTerm){
  return (firstTerm + secondTerm)/2;
}

double convertToDeg(double rad){
  return rad*(180/M_PI);
}

double convertToRad(double deg){
  return deg*(M_PI/180);
}

double wrapTheta(double rad){
  rad = fmod(rad,2*M_PI);
    if (rad < 0)
        rad += 2*M_PI;
    return rad;
}
