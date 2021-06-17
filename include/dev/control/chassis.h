#include "main.h"

extern pros::Motor LF, LB, RF, RB;

void left(double speed);
void right(double speed);
void drive(double speed);

void turnToHeading(double targetDeg, int speedLimit, int acc, double tol);
void turnToPoint(odomVector point, int speedLimit, int acc, double tol);

void driveToPoint(odomVector point, int speedLimit, int acc, double straightTol, double turnTol);
void driveToPoint(odomVector path[], int speedLimit, int acc, double tol);
