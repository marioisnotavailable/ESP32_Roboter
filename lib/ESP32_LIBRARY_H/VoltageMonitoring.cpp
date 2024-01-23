/*_______________Variables_______________*/
#include "libraryESP32.h"

int batterie = 0;
unsigned long long starttime = 0;
int count = 0;
int batteie_low_cont = 0;

/*_______________Voltage monitoring_______________*/

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

//TODO LoadingProgramm fertig machen
/*_______________Loading Programm_______________*/

/*void LoadingProgramm(){

if ((batterie / 200 * VOLTAGE_LEVEL * (R2 + R1) / R2) < PRECENT_25)
{

}
if ((batterie / 200 * VOLTAGE_LEVEL * (R2 + R1) / R2) >= PRECENT_25)
{

}
if ((batterie / 200 * VOLTAGE_LEVEL * (R2 + R1) / R2) >= PRECENT_75)
{

}
if ((batterie / 200 * VOLTAGE_LEVEL * (R2 + R1) / R2) >= PRECENT_100)
{

}
}*/