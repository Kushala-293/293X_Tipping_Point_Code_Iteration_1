#pragma once
#include "api.h"

extern pros::Controller master;

double ticksToInch(int ticks, double wheelDiameter);
double average (double firstTerm, double secondTerm);

double convertToRad(double deg);
double convertToDeg(double rad);

double wrapTheta(double rad);
