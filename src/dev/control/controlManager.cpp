#include "main.h"

void asyncSubsystemUpdate(void* param){
  while(true){
    updateSkewer();
    updateTilter();
    pros::delay(50);
  }
}
