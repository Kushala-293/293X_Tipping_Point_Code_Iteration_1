#include "main.h"

extern pros::Rotation leftEncoder, rightEncoder, middleEncoder;

int getLeftEncoderPos();
int getRightEncoderPos();
int getMiddleEncoderPos();

double getDeltaLeft();
double getDeltaRight();
double getDeltaMiddle();

void resetEncoders();

void odomInit();

void odomUpdate();
