#include "main.h"

extern pros::Motor skewerLift, skewer;
extern pros::ADIPotentiometer skewerPot, liftPot;
extern pros::ADIAnalogIn button;


extern double skewerTargetHeight, skewerTargetAngle, baseHeight;
extern bool goingToBaseHeight, cocked, justScored, isJerkingOff, justJerked, manualMode;

void setTargetHeight(double targetHeight);
void setTargetAngle(double targetAngle);
void setCocked(bool state);
void setScored(bool state);
void updateSkewer();
void jerkOff();
void reset();

void asyncSkewer(void* param);
