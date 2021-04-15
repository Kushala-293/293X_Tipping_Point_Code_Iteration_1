#include "main.h"

extern pros::Rotation leftEncoder, rightEncoder, middleEncoder;
extern pros::Imu inert;

int getL();
int getM();
int getR();

int getDL();
int getDM();
int getDR();

double getThetaRad();
double getThetaDeg();

double getX();
double getY();

void calibrateOdom();
void resetEncoders();
void zero();
void reset();

void asyncOdom(void* param);
