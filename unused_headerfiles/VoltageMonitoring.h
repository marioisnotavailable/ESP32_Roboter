/*_______________Variables_______________*/
#include <Arduino.h>
#include <BluetoothSerial.h>
#include <FastLED.h>

#define NUM_LEDS 4
#define DATA_PIN 23
#define CLOCK_PIN 18
#define ADC_UB 39
#define VOLTAGE_LEVEL (3.3 / 4095)
#define POWER_WARN_MODE 3.6
#define R1 47000
#define R2 100000
#define POWER_OFF_MODE 3.3
#define WAITTIME 5
#define MOTL_Speed 32
#define MOTR_Speed 2
#define ENERGY_LED 1
#define PRECENT_25 1
#define PRECENT_50 2
#define PRECENT_75 3
#define PRECENT_100 4

int batterie = 0;
float newbatterie = 0;
unsigned long long starttime = 0;
int count = 0;
int batteie_low_cont = 0;

BluetoothSerial SerialBT;
CRGB leds[NUM_LEDS];

/*_______________Voltage monitoring_______________*/

void VoltageMonitoring()
{
  if (millis() - starttime >= WAITTIME)
  {
    batterie += analogRead(ADC_UB);
    count++;
    if (count >= 200)
    {
      newbatterie = batterie / 200 * (VOLTAGE_LEVEL * (R2 + R1) / R2);
      SerialBT.println(newbatterie);
      SerialBT.print("V"); 
      if (newbatterie < POWER_WARN_MODE)
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
      if (newbatterie <= POWER_OFF_MODE)
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

//TODO LoadingProgramm fertig machen
/*_______________Loading Programm_______________*/

void LoadingProgramm(){

if ((batterie / 200 * VOLTAGE_LEVEL * (R2 + R1) / R2) >= PRECENT_25)
{

}
else if ((batterie / 200 * VOLTAGE_LEVEL * (R2 + R1) / R2) >= PRECENT_50)
{

}
else if ((batterie / 200 * VOLTAGE_LEVEL * (R2 + R1) / R2) >= PRECENT_75)
{

}
else if ((batterie / 200 * VOLTAGE_LEVEL * (R2 + R1) / R2) >= PRECENT_100)
{

}
}