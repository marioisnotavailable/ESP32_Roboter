#include <FastLED.h>
#include <Arduino.h>
#include <BluetoothSerial.h>
#include <Adafruit_TCS34725.h>
#include <ArduinoOTA.h>
#include <WiFi.h>

#include "WiFiconfig.h"
#include "RoboterLibrary.h"

Roboter Roby("RobotervonMario");

void setup(){
  Serial.begin(115200);
  
  Roby.init();
}

void loop(){
  ArduinoOTA.handle();
  Roby.VoltageMonitoring();
  //Roby.Ultrasonic();
  //Roby.Linefollowerfn();
  //Roby.Colorsensor();
}