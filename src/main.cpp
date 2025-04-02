#include <FastLED.h>
#include <Arduino.h>
#include <BluetoothSerial.h>
#include <ArduinoOTA.h>
#include <WiFi.h>

#include "RoboterLibrary.h"

Roboter Roby("Roboter von Mario");

WiFiServer telnetServer(23);
WiFiClient telnetClient;

void OTA(void *parameter);

volatile bool otaflag = false;
void IRAM_ATTR timerISR();
hw_timer_t *timer = NULL;

void initWiFi();
void loopTelnet();

void setup(){
  xTaskCreatePinnedToCore(
    OTA,  // Pass the OTA task function
    "OTA",
    2048,
    NULL,
    1,
    NULL,
    1
  );

  initWiFi();
  initTelnet();

  Serial.begin(115200);

  Roby.Start();
}

void loop(){
  loopTelnet();
  Roby.VoltageMonitoring();
  Roby.Ultrasonic();
  Roby.Linefollowerfn();
  delay(1000);
  if(millis() % 1000 == 0){
    Serial.println("Hallo");
    digitalWrite(LF_Right_Left, !digitalRead(LF_Right_Left));
  }
}

void IRAM_ATTR timerISR() {
  otaflag = true;
}

void OTA(void *parameter)
{
    ArduinoOTA.setRebootOnSuccess(true);
    ArduinoOTA.begin();
    
    for (;;)
    {
        if (otaflag)
        {
            ArduinoOTA.handle();
            otaflag = false;
            if (telnetClient && telnetClient.connected())
            {
                telnetClient.write("OTA is running...\n\r");
            }
        }
    }
}

void initWiFi(){
  WiFi.mode(WIFI_AP);
  WiFi.softAP("MARIO","12345678");
  /*
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  */
  Serial.println(WiFi.softAPIP().toString());
}

void loopTelnet(){
  if (telnetServer.hasClient()) {
    if (telnetClient) {
      telnetClient.stop();
    }
    telnetClient = telnetServer.available();
    Serial.println("Telnet Client Connected");
  }
}

void initTelnet(){
  telnetServer.begin();
  telnetServer.setNoDelay(true);
}

void initTimer(){
  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, &timerISR, true);
  timerAlarmWrite(timer, 1000000, true);
  timerAlarmEnable(timer);
}