#include "ESP32Library.h"

bool state1 = false;
bool state2 = false;
unsigned long long begin = 0;
unsigned long long end = 0;
unsigned long long start = 0;
int distance = 0;

int batterie = 0;
unsigned long long starttime = 0;
int count = 0;
int batteie_low_cont = 0;

BluetoothSerial SerialBT;
CRGB leds[NUM_LEDS];

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

void VoltageMonitoring()
{
  if (millis() - starttime >= WAITTIME)
  {
    batterie += analogRead(ADC_UB);
    count++;
    if (count == 200)
    {
      batterie /= 200 * VOLTAGE_LEVEL * (R2 + R1) / R2;
      SerialBT.println(batterie);
      if (batterie < POWER_WARN_MODE)
      {

        for (int i = 0; i < NUM_LEDS; i++)
        {
          leds[i] = CRGB::Red;
        }
        FastLED.show();
      }
      else
      {
        for (int i = 0; i < NUM_LEDS; i++)
        {
          leds[i] = CRGB::Black;
        }
        FastLED.show();
      }
      if (batterie <= POWER_OFF_MODE)
      {
        batteie_low_cont++;
      }
      else
      {
        batteie_low_cont = 0;
      }
      count = 0;
      batterie = 0;
    }
    starttime = millis();
  }
  if (batteie_low_cont >= 3)
  {
    for (int i = 0; i < NUM_LEDS; i++)
    {
      leds[i] = CRGB::Black;
    }
    FastLED.show();
    ledcWrite(0, 0);
    ledcWrite(1, 0);
    esp_sleep_enable_timer_wakeup(4000000);
    esp_deep_sleep_start();
  }
}