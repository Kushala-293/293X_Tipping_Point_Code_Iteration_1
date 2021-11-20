#include "main.h"

extern pros::Rotation leftEncoder, rightEncoder;
extern pros::Imu inert;

typedef struct _pos
{
	float a;
	float y;
	float x;
	int lastLeft;
	int lastRight;
	int lastMiddle;
	int lastInert;
} odomPos;

typedef struct _vector
{
	float y;
	float x;
} odomVector; // 2D cartesian vector

typedef struct _polar
{
	float magnitude;
	float angle;
} odomPolar; // 2D polar vector

typedef struct _line
{
	odomVector p1;
	odomVector p2;
} odomLine;

extern odomPos globalPosition;

void calibrateOdom();
void trackPosition(int left, int right, int back, odomPos& position); // Update the position of the robot
void setPosition(double x, double y, double theta, odomPos& position); // Set the position
void resetPosition(odomPos& position); // Reset the position
void vectorToPolar(odomVector& vector, odomPolar& polar); // Convert a cartesian vector to a polar vector
void polarToVector(odomPolar& polar, odomVector& vector); // Convert a polar vector to a cartesian vector
float getAngleOfLine(odomLine line);
float getLengthOfLine(odomLine line);

void asyncOdom(void* param);
