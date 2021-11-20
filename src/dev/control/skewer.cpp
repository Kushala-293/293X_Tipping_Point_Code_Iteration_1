#include "main.h"

pros::Motor skewerLift(4, MOTOR_GEARSET_18, 1, MOTOR_ENCODER_COUNTS),
            skewer(15, MOTOR_GEARSET_18, 1, MOTOR_ENCODER_COUNTS);

double skewerTargetAngle=1485, skewerTargetHeight=0, baseHeight=0;
double skewerError, lastSkewerError=0, skewerProportion, skewerDerivative, skewer_kP=0.3, skewer_kD=0.1, skewer_velCap=90, skewerOutput;
double cockedSkewerError, lastCockedSkewerError=0, cockedSkewerProportion, cockedSkewerDerivative, cockedSkewer_kP=0.3, cockedSkewer_kD=0.1, cockedSkewer_velCap=90, cockedSkewerOutput;
double liftError, lastLiftError=0, liftProportion, liftDerivative, lift_kP=0.6, lift_kD=0.1, liftOutput;
bool goingToBaseHeight=true, cocked=false, justScored=false, isJerkingOff=false, justJerked=false, manualMode=false;

pros::ADIPotentiometer skewerPot('A');
pros::ADIPotentiometer liftPot('B');
pros::ADIAnalogIn button('C');



void setTargetHeight(double target){
  if(!manualMode)
    skewerTargetHeight = target;
}

void setTargetAngle(double target){
  if(!manualMode)
    skewerTargetAngle = target;
}

void setCocked(bool state){
  cocked=state;
}

void setScored(bool state){
  justScored=state;
}

void reset(){
    setTargetAngle(1485);
    setTargetHeight(baseHeight);
    setCocked(false);
    setScored(false);
    isJerkingOff=false;
    justJerked=false;
    goingToBaseHeight=true;
}

void updateSkewer(){

 skewerError = skewerTargetAngle - skewerPot.get_value();
 cockedSkewerError = 1900 - skewerPot.get_value();
 liftError = skewerTargetHeight - liftPot.get_value();

 skewerProportion = (skewerError) * skewer_kP;
 skewerDerivative = (skewerError-lastSkewerError) * skewer_kD;
 lastSkewerError = skewerError;
 skewerOutput = skewerProportion + skewerDerivative;

 if(skewerOutput>skewer_velCap)
  skewerOutput=skewer_velCap;
 else if(skewerOutput<-skewer_velCap)
  skewerOutput=-skewer_velCap;

 cockedSkewerProportion = (cockedSkewerError) * cockedSkewer_kP;
 cockedSkewerDerivative = (cockedSkewerError-lastCockedSkewerError) * cockedSkewer_kD;
 lastCockedSkewerError = cockedSkewerError;
 cockedSkewerOutput = cockedSkewerProportion + cockedSkewerDerivative;

 liftProportion = (liftError) * lift_kP;
 liftDerivative = (liftError-lastLiftError) * lift_kD;
 lastLiftError = liftError;
 liftOutput = liftProportion + liftDerivative;

if(manualMode)
  liftOutput=0;

if(button.get_value()<20){
  baseHeight=liftPot.get_value();
}

 if(!isJerkingOff){
   if(abs(liftError)>50){

     if(abs(cockedSkewerError)>20){
       skewer.move(cockedSkewerOutput);
     }else{
       skewerLift.move(liftOutput);
     }
   }else{
   skewer.move(skewerOutput);
    }
  }else{
    skewer.move(skewerOutput);
    skewerLift.move(liftOutput);

    if(abs(skewerError)<10 && abs(liftError)<30)
      isJerkingOff=false;
  }

  lastLiftError=liftError;
  lastSkewerError=skewerError;

}



void asyncSkewer(void* param){
  while(true){
    updateSkewer();
    pros::delay(50);
  }
}
