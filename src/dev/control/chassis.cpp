#include "main.h"

pros::Motor LF(2, MOTOR_GEARSET_18, 0, MOTOR_ENCODER_COUNTS),
            LB(3, MOTOR_GEARSET_18, 0, MOTOR_ENCODER_COUNTS),
            RF(9, MOTOR_GEARSET_18, 0, MOTOR_ENCODER_COUNTS),
            RB(8, MOTOR_GEARSET_18, 0, MOTOR_ENCODER_COUNTS);

void left(double speed) {
  LF.move(speed);
  LB.move(speed);
}

void right(double speed) {
  RF.move(speed);
  RB.move(speed);
}

void drive(double speed){
  left(speed);
  right(speed);
}

void turnToHeading(double targetDeg, int speedLimit, int acc, double tol){
  double error, lastError;
  double kP=0.25, kI=0, kD=0;
  double proportion, integral, derivative;
  double integralActiveZone=10, integralRaw=0, integralMax=20/kI;
  double finalPower;
  double velCap=30;

  while(abs(error)>=tol){
    //Error --> Distance from Target
    double error = fmod(targetDeg - convertToDeg(wrapTheta(globalPosition.a)) + 540,360) - 180;

    //Proportion
    proportion = (kP*error);

    //Integral
    if(abs(error) < integralActiveZone && (int) (error)!=0)
      integralRaw += error;
    else
      integralRaw=0;

    if(integralRaw > integralMax)
      integralRaw=integralMax;
    if(integralRaw < integralMax)
      integralRaw=-integralMax;

    integral = kI*integralRaw;

    //Derivative
    derivative = kD*(error-lastError);
    lastError=error;

    if(error==0)
      derivative=0;

    //Final Power Calculation
    finalPower = proportion + integral + derivative;

    //Slew Rate
    velCap+=acc;
    if(velCap>speedLimit)
      velCap=speedLimit;
    if(abs(finalPower) > velCap)
      finalPower=velCap * ((error)/abs(error));

    //Base Control
    left(finalPower);
    right(-finalPower);

    //Timeout
    pros::delay(10);
  }
}
void turnToPoint(odomVector point, int speedLimit, int acc, double tol){

}
void driveDistance(double driveDistance, int speedLimit, int acc, double tol){

}
void driveToPoint(odomVector point, int speedLimit, int acc, double tol){

}
void driveToPoint(odomVector path[], int speedLimit, int acc, double tol){

}
