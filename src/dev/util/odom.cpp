#include "main.h"
#include "dev/util/odom.h"
#include "dev/util/misc.h"

pros::Rotation leftEncoder(1);
pros::Rotation middleEncoder(20);
pros::Rotation rightEncoder(10);

pros::Imu inert(12);

const double wheelDiameter = 2.75;
const double wheelTrack = 9.275; // 8.56
const double middleWheelTrack = 2.75;

bool initOdomRun=true;

int initL=0, initM=0, initR=0;
int currentL=0, currentM=0, currentR=0;
double deltaL=0, deltaM=0, deltaR=0, lastL=0, lastM=0, lastR=0;
double currentInert=0, deltaInert=0, lastInert=0;
double deltaRad=0, globalRad=0, avgRad=0, globalDeg=0;
double polarRadius=0, polarTheta=0;
double offsetX=0, offsetY=0, deltaX=0, deltaY=0, globalX=0, globalY=0;

//Encoder Values
int getL(){
  return currentL;
}
int getM(){
  return currentM;
}
int getR(){
  return currentR;
}

//Change in Encoder Values
int getDL(){
  return deltaL;
}
int getDM(){
  return deltaM;
}
int getDR(){
  return deltaR;
}

//Robot Positioning
double getThetaRad(){
  return deltaRad;
}
double getX(){
  return globalX;
}
double getY(){
  return globalY;
}

//General Functions
void calibrateOdom(){
  rightEncoder.reverse();
  middleEncoder.reverse();
  inert.reset();

  resetEncoders();
}
void resetEncoders(){
  leftEncoder.reset_position();
  middleEncoder.reset_position();
  rightEncoder.reset_position();
}
void zero(){

}
void reset();

//Async Task
void asyncOdom(void* param){
  while(!pros::competition::is_autonomous() || pros::competition::is_disabled() ||initOdomRun){
  initL=leftEncoder.get_position();
  initM=middleEncoder.get_position();
  initR=rightEncoder.get_position();
  pros::delay(50);
  while(leftEncoder.get_position()-initL!=0){
    initL=leftEncoder.get_position();
    pros::delay(20);
  }
  while(middleEncoder.get_position()-initM!=0){
    initM=middleEncoder.get_position();
    pros::delay(20);
  }
  while(rightEncoder.get_position()-initR!=0){
    initR=rightEncoder.get_position();
    pros::delay(20);
  }
  initOdomRun=false;
}
  while(true){
      //Current Encoder Position
      currentL = leftEncoder.get_position()-initL;
      currentM = middleEncoder.get_position()-initM;
      currentR = rightEncoder.get_position()-initR;

      //Change in Encoder Position Since Last Iteration
      deltaL = ticksToInch(currentL - lastL,wheelDiameter);
      deltaM = ticksToInch(currentM - lastM,wheelDiameter);
      deltaR = ticksToInch(currentR - lastR,wheelDiameter);

      //Update Last Encoder Positions
      lastL = currentL;
      lastM = currentM;
      lastR = currentR;

      //Calculate Change in Heading via Inertial Sensor
      currentInert=inert.get_rotation();
      deltaInert = currentInert-lastInert;
      lastInert=currentInert;

      //Calculate Change in Orientation via Odometry
      deltaRad = (deltaL-deltaR)/wheelTrack;

      //Average Inertial and Odometry Deltas for Accuracy
      deltaRad = (convertToRad(deltaInert)+deltaRad)/2;

      //Checks if Robot Turned and Update Position Accordingly
      if(deltaRad==0){
        offsetX = deltaM;
        offsetY = deltaR;
      }else{
        offsetX = 2*sin(deltaRad/2)*(deltaM/deltaRad + middleWheelTrack);
        offsetY = 2*sin(deltaRad/2)*(deltaR/deltaRad + wheelTrack/2);
      }

      //Account for Undefined Conversions
      if(isnan(offsetX))
        offsetX=0;
      if(isnan(offsetY))
        offsetY=0;

      //Account for Offset Position Vector
      avgRad= globalRad + deltaRad/2;
      polarRadius = hypot(offsetX,offsetY);
      polarTheta = atan2(offsetY,offsetX) - avgRad;
      deltaX = cos(polarTheta) * polarRadius;
      deltaY = sin(polarTheta) * polarRadius;

      //Account for Undefined Conversions
      if(isnan(deltaX))
        deltaX=0;
      if(isnan(deltaY))
        deltaY=0;

      //Update Global Position
      globalX+=deltaX;
      globalY+=deltaY;

      //Update Global Orientation
      globalRad += deltaRad;
      globalDeg = convertToDeg(globalRad);

      pros::lcd::set_text(2, "(" + std::to_string(currentL) + "," + std::to_string(currentM) + "," + std::to_string(currentR) + ")");
      pros::lcd::set_text(3, "(" + std::to_string(ticksToInch(currentL,wheelDiameter)) + "," + std::to_string(ticksToInch(currentM,wheelDiameter)) + "," + std::to_string(ticksToInch(currentR,wheelDiameter)) + ")");
      pros::lcd::set_text(4, "(" + std::to_string(globalX) + ")");
      pros::lcd::set_text(5, "(" + std::to_string(globalY) + ")");
      pros::lcd::set_text(6, "(" + std::to_string(globalDeg) + ")");
      pros::delay(10);
  }
}
