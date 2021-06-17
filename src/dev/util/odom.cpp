#include "main.h"

pros::Rotation leftEncoder(9);
pros::Rotation middleEncoder(18);
pros::Rotation rightEncoder(10);
pros::Imu inert(21);

const double wheelDiameter = 2.75;
const double wheelTrack = 5.15625; //Big Number->Smaller Calculated Angle Change->Undershoot  Small Number->Larger Calculated Angle Change->Overshoot
const double middleWheelTrack = 1.8;

bool initOdomRun=true;

odomPos globalPosition;

//General Functions
void calibrateOdom(){
  rightEncoder.reverse();

  leftEncoder.reset_position();
  middleEncoder.reset_position();
  rightEncoder.reset_position();

  inert.reset();

  resetPosition(globalPosition);

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

void trackPosition(int left, int right, int back, double currentInert, odomPos& position){
  float L = ticksToInch((left - position.lastLeft),2.75) ; // The amount the left side of the robot moved
  float R = ticksToInch((right - position.lastRight),2.75) ; // The amount the right side of the robot moved
  float S = ticksToInch((back - position.lastMiddle),2.75) ; // The amount the back side of the robot moved
  float I = convertToRad(currentInert-position.lastInert);

  // Update the last values
  position.lastLeft = left;
  position.lastRight = right;
  position.lastMiddle = back;
  position.lastInert = currentInert;

float h; // The hypotenuse of the triangle formed by the middle of the robot on the starting position and ending position and the middle of the circle it travels around
float i; // Half on the angle that I've traveled
float h2; // The same as h but using the back instead of the side wheels
float a = (L - R) / (wheelTrack); // The angle that I've traveled
if (a)
{
float r = R / a; // The radius of the circle the robot travel's around with the right side of the robot
i = a / 2.0;
float sinI = sin(i);
h = ((r + wheelTrack/2) * sinI) * 2.0;

float r2 = S / a; // The radius of the circle the robot travel's around with the back of the robot
h2 = ((r2 + middleWheelTrack) * sinI) * 2.0;
}
else
{
h = R;
i = 0;

h2 = S;
}
float p = i + position.a; // The global ending angle of the robot
float cosP = cos(p);
float sinP = sin(p);

// Update the global position
position.y += h * cosP;
position.x += h * sinP;

position.y += h2 * -sinP; // -sin(x) = sin(-x)
position.x += h2 * cosP; // cos(x) = cos(-x)

position.a += a;

}

//Async Task
void asyncOdom(void* param){
  resetPosition(globalPosition);
  while(true){
    trackPosition(leftEncoder.get_position(),rightEncoder.get_position(),middleEncoder.get_position(),inert.get_rotation(),globalPosition);
    // pros::lcd::set_text(3, "(" + std::to_string(totalLeft) + ")");
    // pros::lcd::set_text(4, "(" + std::to_string(totalMiddle) + ")");
    // pros::lcd::set_text(5, "(" + std::to_string(totalRight) + ")");
    pros::delay(1);
  }
}
