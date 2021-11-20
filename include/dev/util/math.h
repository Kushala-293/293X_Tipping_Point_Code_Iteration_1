#pragma once
#include "api.h"

double ticksToInch(int ticks, double wheelDiameter);
double average (double firstTerm, double secondTerm);

float convertToRad(float deg);
float convertToDeg(float rad);

float wrapTheta(float rad);
