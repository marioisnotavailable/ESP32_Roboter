#include <Arduino.h>
#include <FastLED.h>

#define ECHO_PIN 26
#define TRIGGER_PIN 25
#define WAIT 4

bool state = false;
unsigned long long begin = 0;
unsigned long long end = 0;

void Ultrasonic(int *distance)
{

    digitalWrite(TRIGGER_PIN, HIGH);
}

void IRAM_ATTR Ultrasonic_isr()
{
    if(state == false){
        begin = micros();
    }else if(state == true){
        end = micros();
    }
    switch(state)
    {
    state = !state;
}