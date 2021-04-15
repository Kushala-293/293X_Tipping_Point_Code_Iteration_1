#pragma once
#include "api.h"

extern pros::Controller master;

double ticksToInch(int ticks, double wheelDiameter);

double convertToRad(double deg);
double convertToDeg(double rad);
