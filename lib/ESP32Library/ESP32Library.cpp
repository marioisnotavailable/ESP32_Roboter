#include "ESP32Library.h"

bool state1 = false;
bool state2 = false;
unsigned long long begin = 0;
unsigned long long start = 0;
float distance = 0;

int batterie = 0;
unsigned long long starttime = 0;
int count = 0;
int batterie_low_cont = 0;
float newbatterie = 0;

bool status = false;

BluetoothSerial SerialBT;
CRGB leds[NUM_LEDS];

void QuickSetup()
{
  SerialBT.begin("ESP_von_Nici");
  FastLED.addLeds<SK9822, DATA_PIN, CLOCK_PIN, RBG>(leds, NUM_LEDS);
  pinMode(ADC_UB, INPUT);
  ledcSetup(0, 16000, 10);
  ledcSetup(1, 16000, 10);
  ledcAttachPin(MOTL_Speed, 0);
  ledcAttachPin(MOTR_Speed, 1);
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(MOTR_DIR, OUTPUT);
  pinMode(MOTL_DIR, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(ECHO_PIN), Ultrasonic_isr, CHANGE);
  pinMode(LF_Right_Left, OUTPUT);
  pinMode(LINEFOLLOW, INPUT);
}

void Ultrasonic()
{
  if (state2 == false)
  {
    digitalWrite(TRIGGER_PIN, HIGH);
  }

  if ((micros() - start >= 4) && (digitalRead(TRIGGER_PIN) == HIGH))
  {
    digitalWrite(TRIGGER_PIN, LOW);
    state2 = true;
    start = micros();
  }
}

void IRAM_ATTR Ultrasonic_isr()
{
  if (state1 == false)
  {
    begin = micros();
  }
  if (state1 == true)
  {
    distance = (micros() - begin) / 2 * 0.033;
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
    if (count >= 200)
    {
      newbatterie = batterie / 200 * (VOLTAGE_LEVEL * (R2 + R1) / R2);
      SerialBT.print(newbatterie);
      SerialBT.println("V");
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
        batterie_low_cont++;
      }
      else
      {
        batterie_low_cont = 0;
      }
      count = 0;
      batterie = 0;
    }
    starttime = millis();
  }
  if (batterie_low_cont >= 3)
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

void LoadingProgramm()
{

  if ((batterie / 200 * VOLTAGE_LEVEL * (R2 + R1) / R2) >= PRECENT_25)
  {
    for (int i = 0; i < NUM_LEDS; i++)
    {
      leds[i] = CRGB::Orange;
    }
    FastLED.show();
  }
  else if ((batterie / 200 * VOLTAGE_LEVEL * (R2 + R1) / R2) >= PRECENT_50)
  {
    for (int i = 0; i < NUM_LEDS; i++)
    {
      leds[i] = CRGB::Yellow;
    }
    FastLED.show();
  }
  else if ((batterie / 200 * VOLTAGE_LEVEL * (R2 + R1) / R2) >= PRECENT_75)
  {
    for (int i = 0; i < NUM_LEDS; i++)
    {
      leds[i] = CRGB::LightGreen;
    }
    FastLED.show();
  }
  else if ((batterie / 200 * VOLTAGE_LEVEL * (R2 + R1) / R2) >= PRECENT_100)
  {
    for (int i = 0; i < NUM_LEDS; i++)
    {
      leds[i] = CRGB::Green;
    }
    FastLED.show();
  }
}

void Linefollowerfn()
{
  if (status == false)
  {
    status = !status;
    digitalWrite(LF_Right_Left, HIGH);
    if (analogRead(LINEFOLLOW) > 1500)
    {
      ledcWrite(MOTR_Speed, 1000);
    }
    else
    {
      ledcWrite(MOTR_Speed, 0);
    }
  }
  else
  {
    status = !status;
    digitalWrite(LF_Right_Left, LOW);
    if (analogRead(LINEFOLLOW) > 1500)
    {
      ledcWrite(MOTL_Speed, 1000);
    }
    else
    {
      ledcWrite(MOTL_Speed, 0);
    }
  }
}