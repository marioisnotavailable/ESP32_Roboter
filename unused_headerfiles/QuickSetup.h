#include "VoltageMonitoring.h"
#include "Ultra.h"

void QuickSetup()
{
  SerialBT.begin("ESP_von_Mario");
  FastLED.addLeds<SK9822, DATA_PIN, CLOCK_PIN, RBG>(leds, NUM_LEDS);
  ledcSetup(0, 16000, 10);
  ledcSetup(1, 16000, 10);
  ledcAttachPin(MOTL_Speed, 0);
  ledcAttachPin(MOTR_Speed, 1);
  pinMode(TRIGGER_PIN,OUTPUT);
  pinMode(ECHO_PIN,INPUT);
  attachInterrupt(digitalPinToInterrupt(ECHO_PIN),Ultrasonic_isr,CHANGE);
}