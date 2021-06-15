#include "main.h"

pros::Rotation leftEncoder(1);
pros::Rotation middleEncoder(20);
pros::Rotation rightEncoder(10);
pros::Imu inert(12);

const double wheelDiameter = 2.75;
const double wheelTrack = 9.11304; //Big Number->Undershoot  Small Number->Overshoot
const double middleWheelTrack = 2.75;

bool initOdomRun=true;

odomPos globalPosition;

double totalLeft=0, totalMiddle=0, totalRight=0;

//General Functions
void calibrateOdom(){
  rightEncoder.reverse();
  middleEncoder.reverse();

  leftEncoder.reset_position();
  middleEncoder.reset_position();
  rightEncoder.reset_position();

  inert.reset();

  while(inert.is_calibrating())
    pros::delay(20);
}

void resetPosition(odomPos& position){
  position.x=0;
  position.y=0;
  position.a=0;
  position.lastLeft=0;
  position.lastMiddle=0;
  position.lastRight=0;
  position.lastInert=0;
}

void setPosition(double x, double y, double theta, odomPos& position){
  position.x=x;
  position.y=y;
  position.a=convertToRad(theta);
}

void vectorToPolar(odomVector& vector, odomPolar& polar)
{
	if (vector.x || vector.y)
	{
		polar.magnitude = sqrt(vector.x * vector.x + vector.y * vector.y);
		polar.angle = atan2(vector.y, vector.x);
	}
	else
		polar.magnitude = polar.angle = 0;
}

void polarToVector(odomPolar& polar, odomVector& vector)
{
	if (polar.magnitude)
	{
		vector.x = polar.magnitude * cos(polar.angle);
		vector.y = polar.magnitude * sin(polar.angle);
	}
	else
		vector.x = vector.y = 0;
}

float getAngleOfLine(odomLine line)
{
	return atan2(line.p2.x - line.p1.x, line.p2.y - line.p1.y);
}

float getLengthOfLine(odomLine line)
{
	float x = line.p2.x - line.p1.x;
	float y = line.p2.y - line.p1.y;
	return sqrt(x * x + y * y);
}

void trackPosition(int currentL, int currentR, int currentM, double currentInert, odomPos& position){

      double xOffset, yOffset;
      double avgRad, deltaRad, endRad;
      double deltaL, deltaM, deltaR;

      //Change in Robot Position Vector Since Last Iteration
      deltaL = ticksToInch(currentL - position.lastLeft,wheelDiameter);
      deltaM = ticksToInch(currentM - position.lastMiddle,wheelDiameter);
      deltaR = ticksToInch(currentR - position.lastRight,wheelDiameter);
      //deltaRad = average(convertToRad(currentInert - position.lastInert),(deltaL - deltaR) / wheelTrack);
      deltaRad = (deltaL - deltaR) / wheelTrack;
      totalLeft += deltaL;
      totalMiddle += deltaM;
      totalRight += deltaR;

      //Update Last Robot Position Vector
      position.lastLeft=currentL;
      position.lastMiddle=currentM;
      position.lastRight=currentR;
      position.lastInert=currentInert;

      //Checks if Robot Turned and Calculate Position Offset Accordingly
      if(deltaRad==0){
        avgRad = 0;
        xOffset = deltaM;
        yOffset = deltaR;
      }else{
        avgRad = deltaRad/2;
        xOffset= 2*sin(avgRad)*(deltaM/deltaRad + middleWheelTrack);
        yOffset = 2*sin(avgRad)*(deltaR/deltaRad + wheelTrack/2);
      }

      //Calcualte End Angle of Robot
      endRad = avgRad + position.a;

      //Update Global Position Vector
      position.x+=yOffset*sin(endRad);
      position.y+=yOffset*cos(endRad);

      position.x+=xOffset*cos(endRad);
      position.y+=xOffset*-sin(endRad);

      position.a+=deltaRad;
}

//Async Task
void asyncOdom(void* param){
  while(true){
    trackPosition(leftEncoder.get_position(),rightEncoder.get_position(),middleEncoder.get_position(),inert.get_rotation(),globalPosition);
    // pros::lcd::set_text(3, "(" + std::to_string(totalLeft) + ")");
    // pros::lcd::set_text(4, "(" + std::to_string(totalMiddle) + ")");
    // pros::lcd::set_text(5, "(" + std::to_string(totalRight) + ")");
    pros::delay(1);
  }
}
