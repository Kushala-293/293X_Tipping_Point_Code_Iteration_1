#include "main.h"

//Defines motors' ports, gearsets, directions, and encoder units
pros::Motor LF(16, MOTOR_GEARSET_6, 1, MOTOR_ENCODER_COUNTS),
            LB(3, MOTOR_GEARSET_6, 1, MOTOR_ENCODER_COUNTS),
            RF(7, MOTOR_GEARSET_6, 0, MOTOR_ENCODER_COUNTS),
            RB(21, MOTOR_GEARSET_6, 0, MOTOR_ENCODER_COUNTS);

void drive(double voltage){
  LF.move(voltage);
  LB.move(voltage);
  RF.move(voltage);
  RB.move(voltage);
}

void drive(double leftVoltage, double rightVoltage){
  LF.move(leftVoltage);
  LB.move(leftVoltage);
  RF.move(rightVoltage);
  RB.move(rightVoltage);
}

// void turnToHeading(float targetDeg, int speedLimit, int acc, double tol){
//   double error, lastError;
//   double kP=3.2, kI=0, kD=0;
//   double proportion, integral, derivative;
//   double integralActiveZone=10, integralRaw=0, integralMax=20/kI;
//   double finalPower;
//   double velCap=30;
//
//   error = fmod(targetDeg - convertToDeg(wrapTheta(globalPosition.a)) + 540,360) - 180;
//
//   while(abs(error)>=tol){
//     //Error --> Distance from Target
//     error = fmod(targetDeg - convertToDeg(wrapTheta(globalPosition.a)) + 540,360) - 180;
//
//
//     //Proportion
//     proportion = (kP*error);
//
//     //Integral
//     if(abs(error) < integralActiveZone && (int) (error)!=0)
//       integralRaw += error;
//     else
//       integralRaw=0;
//
//     if(integralRaw > integralMax)
//       integralRaw=integralMax;
//     if(integralRaw < integralMax)
//       integralRaw=-integralMax;
//
//     integral = kI*integralRaw;
//
//     //Derivative
//     derivative = kD*(error-lastError);
//     lastError=error;
//
//     if(error==0)
//       derivative=0;
//
//     //Final Power Calculation
//     finalPower = proportion;
//
//     //Slew Rate
//     velCap+=acc;
//     if(velCap>speedLimit)
//       velCap=speedLimit;
//     if(abs(finalPower) > velCap)
//       finalPower=velCap * ((error)/abs(error));
//
//     //Base Control
//     left(finalPower);
//     right(-finalPower);
//
//     //Timeout
//     pros::delay(10);
//   }
// }
// void turnToPoint(odomVector point, int speedLimit, int acc, double tol){
//   odomLine pathLine;
//
//   pathLine.p1.x = globalPosition.x;
//   pathLine.p1.y = globalPosition.y;
//
//   pathLine.p2.x = point.x;
//   pathLine.p2.y = point.y;
//
//   float lineAngle = convertToDeg(getAngleOfLine(pathLine));
//
//   pros::lcd::set_text(7, std::to_string(lineAngle));
//
//   turnToHeading(lineAngle, speedLimit, acc, tol);
// }
//
// void driveDistance(double driveDistance, int speedLimit, int acc, double tol){
//
// }
// void driveToPoint(odomVector point, int speedLimit, int acc, double straightTol, double turnTol){
//   odomLine pathLine;
//
//   pathLine.p1.x = globalPosition.x;
//   pathLine.p1.y = globalPosition.y;
//
//   pathLine.p2.x = point.x;
//   pathLine.p2.y = point.y;
//
//   float straightError = getLengthOfLine(pathLine);
//   float turnError = convertToDeg(getAngleOfLine(pathLine));
//   float lastTurnError,lastStrightError;
//
//   float straightKP=3, straightKI=0, straightKD=0;
//   float integralActiveStraightZone=10, integralStraightRaw=0, integralStraightMax=20/straightKI;
//   float turnKP=1, turnKI=0, turnKD=0;
//   float integralTurnActiveZone=10, integralTurnRaw=0, integralTurnMax=20/turnKI;
//
//   float straightComponent, turnComponent, leftPower, rightPower;
//   float velCap=30;
//
//   turnToPoint(point, speedLimit, acc, turnTol);
//
//   //while(abs(turnError) > turnTol || abs(straightError) > straightTol){
//   while(abs(straightError) > straightTol){
//     pathLine.p1.x = globalPosition.x;
//     pathLine.p1.y = globalPosition.y;
//     straightError = getLengthOfLine(pathLine);
//     //turnError = convertToDeg(getAngleOfLine(pathLine));
//
//     straightComponent = (straightError * straightKP);
//     //turnComponent = (turnError * turnKP);
//
//     velCap+=acc;
//     if(velCap>speedLimit)
//       velCap=speedLimit;
//     if(abs(straightComponent) > velCap)
//       straightComponent = velCap * ((straightError)/abs(straightError));
//     // if(abs(turnComponent) > velCap)
//     //   turnComponent = velCap * ((turnError)/abs(turnError));
//
//     // leftPower = (straightComponent) + (turnComponent);
//     // rightPower = (straightComponent) - (turnComponent);
//     leftPower = (straightComponent);
//     rightPower = (straightComponent);
//
//     pros::lcd::set_text(7, std::to_string(leftPower) + "," + std::to_string(rightPower));
//
//     left(leftPower);
//     right(rightPower);
//
//     pros::delay(10);
//   }
// }
// void driveToPoint(odomVector path[], int speedLimit, int acc, double tol){
//
// }
