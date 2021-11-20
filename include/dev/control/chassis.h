#include "main.h"

//Define drivetrain motors
extern pros::Motor LF, LB, RF, RB;

/**
 * Spins all drive motors at the same voltage
 * @param {double} voltage - The voltage to run the all the drive motors at
 */
void drive(double voltage);

/**
 * Spins all drive motors at the same voltage
 * @param {double} leftVoltage - The voltage to run the all the left drive motors at
 * @param {double} rightVoltage - The voltage to run the all the right drive motors at
 */
void drive(double leftVoltage, double rightVoltage);

// void turnToHeading(double targetDeg, int speedLimit, int acc, double tol);
// void turnToPoint(odomVector point, int speedLimit, int acc, double tol);
//
// void driveToPoint(odomVector point, int speedLimit, int acc, double straightTol, double turnTol);
// void driveToPoint(odomVector path[], int speedLimit, int acc, double tol);
