#include <FastLED.h>
#include <Arduino.h>
#include <BluetoothSerial.h>
#include <ArduinoOTA.h>
#include <WiFi.h>

#include "RoboterLibrary.h"

Roboter Roby("Roboter von Mario");

void setup(){
  Serial.begin(115200);

  WiFi.mode(WIFI_AP);
  WiFi.softAP("MARIO","12345678");
  //while (WiFi.status() != WL_CONNECTED) {
   // Serial.print('.');
   // delay(1000);
 // }
  Serial.println(WiFi.softAPIP().toString());
  ArduinoOTA.setRebootOnSuccess(true);
  ArduinoOTA.setPort(3232);
  ArduinoOTA.begin();
  Roby.Start();
  digitalWrite(MOTL_DIR,LOW);
  digitalWrite(MOTR_DIR,HIGH);
}

void loop(){
  ArduinoOTA.handle();

  Roby.VoltageMonitoring();
  Roby.Ultrasonic();
  Roby.Linefollowerfn();
  delay(1000);
  if(millis() % 1000 == 0){
    Serial.println("Hallo");
    digitalWrite(LF_Right_Left, !digitalRead(LF_Right_Left));
  }

}
