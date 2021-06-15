#include "main.h"

extern pros::Motor LF, LB, RF, RB;

void left(int speed);
void right(int speed);
void drive(int speed);

void turnToHeading(double targetDeg, int speedLimit, int acc, double tol);
void turnToPoint(odomVector point, int speedLimit, int acc, double tol);

void driveToPoint(odomVector point, int speedLimit, int acc, double tol);
void driveToPoint(odomVector path[], int speedLimit, int acc, double tol);
