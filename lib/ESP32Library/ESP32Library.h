#ifndef ESPLIBRARY_H
#define ESPLIBRARY_H

#include <FastLED.h>
#include <Arduino.h>
#include <BluetoothSerial.h>

#define NUM_LEDS 4
#define DATA_PIN 23
#define CLOCK_PIN 18
#define ADC_UB 39
#define VOLTAGE_LEVEL 3.3 / 4095
#define POWER_WARN_MODE 3.6
#define R1 47000
#define R2 90000
#define POWER_OFF_MODE 3.3
#define WAITTIME 5
#define MOTL_Speed 32
#define MOTR_Speed 2
#define MOTL_DIR 33
#define MOTR_DIR 15
#define ENERGY_LED 1
#define PRECENT_25 3.525
#define PRECENT_50 3.75
#define PRECENT_75 3.975
#define PRECENT_100 4.2

#define ECHO_PIN 26
#define TRIGGER_PIN 25
#define WAIT 4

#define LINEFOLLOW 36
#define LF_Right_Left 12

void QuickSetup();
void Ultrasonic();
void IRAM_ATTR Ultrasonic_isr();
void VoltageMonitoring();
void Linefollowerfn();
void LoadingProgramm();

#endif // ESPLIBRARY_H