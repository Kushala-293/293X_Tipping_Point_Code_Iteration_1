#include "main.h"

extern pros::ADIAnalogIn button;

void display();

void asyncDisplay(void* param);

void refresh();

bool isBeingPressed();

void setBeingPressed(bool state);
