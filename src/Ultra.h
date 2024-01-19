#include <Arduino.h>
#include <FastLED.h>

#define ECHO_PIN 26
#define TRIGGER_PIN 25
#define WAIT 4

bool state = false;
unsigned long long begin = 0;
unsigned long long end = 0;
unsigned long long start = 0;

int Ultrasonic()
{
    digitalWrite(TRIGGER_PIN, HIGH);
    if (micros() - start >= 5)
    {
        digitalWrite(TRIGGER_PIN, LOW);
    }
    return (end - start) / 2 * 0.033; 
}

void IRAM_ATTR Ultrasonic_isr()
{
    if(state == false){
        begin = micros();
    }else if(state == true){
        end = micros();
    }
    state = !state;
}