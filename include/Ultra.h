#include <Arduino.h>
#include <FastLED.h>

#define ECHO_PIN 26
#define TRIGGER_PIN 25
#define WAIT 4

bool state1 = false;
bool state2 = false;
unsigned long long begin = 0;
unsigned long long end = 0;
unsigned long long start = 0;
int distance = 0;

int Ultrasonic()
{
    if (state2 == false)
    {
        digitalWrite(TRIGGER_PIN, HIGH);
    }
    
    if (micros() - start >= 4)
    {
        digitalWrite(TRIGGER_PIN, LOW);
        state2 = true;
    }
    if(state2 == false){
        distance = (end - start) / 2 * 0.033; 
    }
    return distance;
}

void IRAM_ATTR Ultrasonic_isr()
{
    if(state1 == false){
        begin = micros();
    }else if(state1 == true){
        end = micros();
        state2 = false;
    }
    state1 = !state1;
}