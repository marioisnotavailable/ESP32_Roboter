#ifndef ROBOTERLIBRARY_H
#define ROBOTERLIBRARY_H

#include <FastLED.h>
#include <Arduino.h>
#include <BluetoothSerial.h>

#define NUM_LEDS 4
#define DATA_PIN 23
#define CLOCK_PIN 18
#define ADC_UB 39
#define VOLTAGE_LEVEL (3.3f / 4095)
#define POWER_WARN_MODE 3.6f
#define R1 47000
#define R2 90000
#define POWER_OFF_MODE 3.3f
#define WAITTIME 5

#define MOTL_Speed 32
#define MOTR_Speed 2
#define MOTL_DIR 33
#define MOTR_DIR 15

#define ENERGY_LED 1
#define PRECENT_25 3.525f
#define PRECENT_50 3.75f
#define PRECENT_75 3.975f
#define PRECENT_100 4.2f

#define ECHO_PIN 26
#define TRIGGER_PIN 25

#define LINEFOLLOW 36
#define LF_Right_Left 12

class Roboter {
private:
    const char *a;
    static bool state1, state2;
    static unsigned long begin;
    static float distance;
    unsigned long start = 0, starttime = 0;
    int count = 0;
    uint8_t batterie_low_cont = 0;
    float newbatterie = 0;
    bool status = false;
    uint8_t richtung = 0;

public:
    Roboter() : a("Robo") {}
    Roboter(const char *);
    static void IRAM_ATTR Ultrasonic_isr();
    void Start();
    void Ultrasonic();
    void VoltageMonitoring();
    void Linefollowerfn();
    void LoadingProgramm();
};

#endif // ROBOTERLIBRARY_H
