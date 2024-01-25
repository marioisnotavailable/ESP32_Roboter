#include <FastLED.h>
#include <Arduino.h>
#include <BluetoothSerial.h>

#include "ESP32Library.h"

extern BluetoothSerial SerialBT;
extern CRGB leds[NUM_LEDS];

int distanceSonic = 0;

void setup(){
  QuickSetup();
}

void loop(){
  //leds[1] = CRGB::Black;
  VoltageMonitoring();
  distanceSonic = Ultrasonic();
  //SerialBT.println(distanceSonic);
}