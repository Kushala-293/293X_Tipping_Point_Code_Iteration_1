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

float convertToDeg(float rad){
  return rad*(180/M_PI);
}

float convertToRad(float deg){
  return deg*(M_PI/180);
}

float wrapTheta(float rad){
  rad = fmod(rad,2*M_PI);
    if (rad < 0)
        rad += 2*M_PI;
    return rad;
}
