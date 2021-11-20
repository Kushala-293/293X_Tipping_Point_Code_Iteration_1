#include "main.h"

//Define components
extern pros::Motor intake;
extern pros::Controller master;
extern pros::ADIDigitalOut clamp, leftHook, rightHook;

extern bool clampState, hookState;

void spinIntake(double voltage);

void stopIntake();

void setClamp(bool state);
void setHooks(bool state);

void toggleClamp();
void toggleHook();
