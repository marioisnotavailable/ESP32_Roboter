#include <Arduino.h>
#include <FastLED.h>

#define ECHO_PIN 26
#define TRIGGER_PIN 25
#define WAIT 4

unsigned long long start = 0;

void Ultrasonic(int* distance){
    
    digitalWrite(TRIGGER_PIN,HIGH);
}

void IRAM_ATTR Ultrasonic_isr(){

}
