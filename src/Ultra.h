#include <Arduino.h>
#include <FastLED.h>

#define ECHO_PIN 26
#define TRIGGER_PIN 25
#define WAIT 4

unsigned long long start = 0;

void Ultrasonic(int* distance){
    //attachInterrupt(digitalPinToInterrupt(ECHO_PIN),Ultrasonic_isr,CHANGE);
    digitalWrite(TRIGGER_PIN,HIGH);
    //if (micros - start >= 4)
    //{
     //   digitalWrite(TRIGGER_PIN,HIGH);
    //}
}
