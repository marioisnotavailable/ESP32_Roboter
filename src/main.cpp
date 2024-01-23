#include "QuickSetup.h"

int distanceSonic = 0;

void setup(){
  QuickSetup();
}

void loop(){
  VoltageMonitoring();
  distance = Ultrasonic();
  SerialBT.println(distance);
}