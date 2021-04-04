#include "dev/control/chassis.h"
#include "dev/util/misc.h"

pros::Motor LF(2, MOTOR_GEARSET_18, 0, MOTOR_ENCODER_COUNTS),
            LB(3, MOTOR_GEARSET_18, 0, MOTOR_ENCODER_COUNTS),
            RF(9, MOTOR_GEARSET_18, 0, MOTOR_ENCODER_COUNTS),
            RB(8, MOTOR_GEARSET_18, 0, MOTOR_ENCODER_COUNTS);



void left(int speed) {
  LF.move(speed);
  LB.move(speed);
}

void right(int speed) {
  RF.move(speed);
  RB.move(speed);
}

void drive(int speed){
  left(speed);
  right(speed);
}
