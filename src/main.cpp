#include <FastLED.h>
#include <Arduino.h>
#include <BluetoothSerial.h>
//#include <ArduinoOTA.h>
//#include <WiFi.h>

//#include "WiFiconfig.h"
#include "RoboterLibrary.h"

Roboter Roby("Roboter von Mario");

//void initWiFi();

void setup(){
  Serial.begin(115200);

  //initWiFi();
  
  Roby.init();
}

void loop(){
  //ArduinoOTA.handle();
  /*Roby.VoltageMonitoring();
  Roby.Ultrasonic();
  Roby.Linefollowerfn();*/
  Roby.Colorsensor();
}


/*void initWiFi(){
  WiFi.mode(WIFI_AP);
  WiFi.softAP(WIFI_SSID,WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  
  Serial.println(WiFi.softAPIP().toString());
}*/
