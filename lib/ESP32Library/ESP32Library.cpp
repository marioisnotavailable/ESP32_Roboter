#include "ESP32Library.h"

BluetoothSerial SerialBT;
CRGB leds[NUM_LEDS];

bool Roboter::state1 = false;
bool Roboter::state2 = false;
unsigned long Roboter::begin = 0;
float Roboter::distance = 0;

Roboter::Roboter(char const *name){
  a = name;
}

void Roboter::Start()
{
  SerialBT.begin(a);
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
  digitalWrite(MOTR_DIR, HIGH);
  digitalWrite(MOTL_DIR, LOW);
}

void Roboter::Ultrasonic()
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

void IRAM_ATTR Roboter::Ultrasonic_isr()
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

void Roboter::VoltageMonitoring()
{
  if (millis() - starttime >= WAITTIME)
  {
    newbatterie += analogRead(ADC_UB);
    count++;
    SerialBT.print("a");
    if (count >= 200)
    {
      newbatterie = newbatterie / 200 * (VOLTAGE_LEVEL * (R2 + R1) / R2);
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
          leds[i] = CRGB::Green;
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
      newbatterie = 0;
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

void Roboter::LoadingProgramm()
{

  if ((newbatterie / 200 * VOLTAGE_LEVEL * (R2 + R1) / R2) >= PRECENT_25)
  {
    for (int i = 0; i < NUM_LEDS; i++)
    {
      leds[i] = CRGB::Orange;
    }
    FastLED.show();
  }
  else if ((newbatterie / 200 * VOLTAGE_LEVEL * (R2 + R1) / R2) >= PRECENT_50)
  {
    for (int i = 0; i < NUM_LEDS; i++)
    {
      leds[i] = CRGB::Yellow;
    }
    FastLED.show();
  }
  else if ((newbatterie / 200 * VOLTAGE_LEVEL * (R2 + R1) / R2) >= PRECENT_75)
  {
    for (int i = 0; i < NUM_LEDS; i++)
    {
      leds[i] = CRGB::LightGreen;
    }
    FastLED.show();
  }
  else if ((newbatterie / 200 * VOLTAGE_LEVEL * (R2 + R1) / R2) >= PRECENT_100)
  {
    for (int i = 0; i < NUM_LEDS; i++)
    {
      leds[i] = CRGB::Green;
    }
    FastLED.show();
  }
}

void Roboter::Linefollowerfn()
{
  if(distance < 10){
    ledcWrite(1, 0);
    ledcWrite(0, 0);
  }
  if (status == false)
  {
    status = !status;
    digitalWrite(LF_Right_Left, HIGH);
    if (analogRead(LINEFOLLOW) > 1500)
    {
      if(richtung != 2){
        richtung = 0;
      }
    }
    else
    {
      if(richtung != 2){
        richtung = 1;
      }
    }
  }
  else
  {
    status = !status;
    digitalWrite(LF_Right_Left, LOW);
    if (analogRead(LINEFOLLOW) > 1500)
    {
      if(richtung != 1){
        richtung = 0;
      }
    }
    else
    {
      if(richtung != 1){
        richtung = 2;
      }
    }
  }
  switch (richtung)
  {
  case 0:
    ledcWrite(1, 1024);
    ledcWrite(0, 1024);
    break;
  case 1:
    ledcWrite(0, 1024);
    ledcWrite(1, 512);
    break;
  case 2:
    ledcWrite(1, 1024);
    ledcWrite(0, 512);
    break;
  default:
    break;
  }
}