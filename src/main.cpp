#include <FastLED.h>
#include <Arduino.h>
#include <BluetoothSerial.h>

#include "ESP32Library.h"

Roboter Roby("Roboter von Mario");

void setup(){
  Roby.Start();
  digitalWrite(MOTL_DIR,LOW);
  digitalWrite(MOTR_DIR,HIGH);
}

void loop(){
  Roby.VoltageMonitoring();
  Roby.Ultrasonic();
}
