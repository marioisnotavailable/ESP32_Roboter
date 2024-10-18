#include <FastLED.h>
#include <Arduino.h>
#include <BluetoothSerial.h>

#include "ESP32Library.h"

extern BluetoothSerial SerialBT;
extern CRGB leds[NUM_LEDS];
extern float distance;

bool a = true;
bool b = true;
unsigned long starttimee = 0;
int i = 250;


void setup(){
  QuickSetup("ESP von Mario");
  digitalWrite(MOTL_DIR,LOW);
  digitalWrite(MOTR_DIR,HIGH);
}

void loop(){
  VoltageMonitoring();
  Ultrasonic();
  if (distance < 10)
  {
    ledcWrite(0,0);
    ledcWrite(1,0);
  }else{
    digitalWrite(MOTL_DIR,b);
    digitalWrite(MOTR_DIR,!b);
  if(millis() - starttimee >= 1){
    starttimee = millis();   
     if(a){
      if (i >= 1024)
      {
        a = false;
      }
      i++;
  }else{
      if (i <= 250)
      {
        a = true;
        b = !
        
        b;
      }
      i--;
  }
  ledcWrite(0,i);
  ledcWrite(1,i);
  }
}
}
