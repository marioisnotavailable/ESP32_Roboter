#include <FastLED.h>
#include <Arduino.h>
#include <BluetoothSerial.h>

#include "RoboterLibrary.h"

Roboter Roby("Roboter von Mario");

void setup(){
  Roby.Start();
  digitalWrite(MOTL_DIR,LOW);
  digitalWrite(MOTR_DIR,HIGH);
}

void loop(){
}
