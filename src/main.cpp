#include <FastLED.h>
#include <Arduino.h>
#include <BluetoothSerial.h>

#include "ESP32Library.h"

extern BluetoothSerial SerialBT;
extern CRGB leds[NUM_LEDS];
extern float distance;

unsigned long starttimee = 0;

void setup(){
  QuickSetup();
}

void loop(){
  //LoadingProgramm();
  VoltageMonitoring();
  Ultrasonic();
  Linefollowerfn();

  //if(millis() - starttimee > 1000){
  //  SerialBT.println(distanceSonic);
  //  starttimee = millis();
  //}
}