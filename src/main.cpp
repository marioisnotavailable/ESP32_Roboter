#include "QuickSetup.h"

int distance = 0;

void setup(){
  QuickSetup();
}

void loop(){
  VoltageMonitoring();
  distance = Ultrasonic();
  SerialBT.println(distance);
}