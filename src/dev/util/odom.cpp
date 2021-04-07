#include "dev/util/odom.h"
#include "dev/control/chassis.h"

pros::Rotation leftEncoder(1);
pros::Rotation rightEncoder(10);
pros::Rotation middleEncoder(20);

double horizontalWheelTrack = 8.625;//Distance between left and right tracking wheels
double verticalWheelTrack; //Distance between middle tracking wheel and tracking center
double wheelDiameter=2.75; // Diameter of tracking wheels

double deltaLeft;
double deltaRight;
double deltaMiddle;

double posX;//Global X Position of Robot
double posY;//Global Y Position of Robot
double theta;//Global Orientation of Robot

int getLeftEncoderPos(){
  return leftEncoder.get_position();
}
int getRightEncoderPos(){
  return rightEncoder.get_position();
}
int getMiddleEncoderPos(){
  return middleEncoder.get_position();
}

double getDeltaLeft(){
  return deltaLeft;
}
double getDeltaRight(){
  return deltaRight;
}
double getDeltaMiddle(){
  return deltaMiddle;
}

void resetEncoders(){
  leftEncoder.set_position(0);
  rightEncoder.set_position(0);
  middleEncoder.set_position(0);
}

void odomInit(){
  middleEncoder.set_reversed(true);
  rightEncoder.set_reversed(true);
  resetEncoders();
}



void odomUpdate(){
  deltaLeft = (leftEncoder.get_position()/36000.00) * (wheelDiameter*PI);
  deltaMiddle = (middleEncoder.get_position()/36000.00) * (wheelDiameter*PI);
  deltaRight = (rightEncoder.get_position()/36000.00) * (wheelDiameter*PI);
}
