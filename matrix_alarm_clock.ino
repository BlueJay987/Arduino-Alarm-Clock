#include <RTClib.h>
#include <Wire.h>
RTC_DS3231 rtc;
char t[32];

#include "MD_Parola.h"
#include "MD_MAX72xx.h"
#include "SPI.h"

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define CS_PIN 5
#define DATA_PIN 6
#define CLK_PIN 4
MD_Parola myDisplay = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

byte BUZZER = 3;

int ALARMHOUR = 16;
int ALARMMINUTE = 07;

void checkAlarm() {
  DateTime now = rtc.now();
  if (now.hour() == ALARMHOUR && now.minute() == ALARMMINUTE || Serial.read() == 'a') {
    tone(BUZZER, 250, 400);
    delay(1000);
    tone(BUZZER, 250, 400);
    delay(1000);
    tone(BUZZER, 250, 400);
    delay(1000);
    tone(BUZZER, 250, 400);
    delay(1000);
  }
}

void debugTime() {
  DateTime now = rtc.now();
  Serial.print(now.hour());
  Serial.print(" ");
  Serial.print(now.twelveHour());
  Serial.print(" ");
  Serial.print(now.minute());
  Serial.print(" ");
  Serial.print(now.second());
  Serial.print(" ");
  Serial.print(now.isPM());
  Serial.println(" ");
}

void setup()
{
  myDisplay.begin();
  myDisplay.setIntensity(0);
  myDisplay.setTextAlignment(PA_CENTER);
  myDisplay.setCharSpacing(1);
  myDisplay.displayClear();

  Serial.begin(9600);

  Wire.begin();
  rtc.begin();
  rtc.adjust(DateTime(F(__DATE__),F(__TIME__)));

  if (rtc.lostPower()) {
    Serial.println("rtc.lostpower");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}
void loop()
{
  DateTime now = rtc.now();
  sprintf(t, "%02d:%02d", now.twelveHour(), now.minute());  
  myDisplay.print(t);
  Serial.println(t);
  Serial.println(now.timestamp(DateTime::TIMESTAMP_FULL));
  checkAlarm();
  //debugTime();
  delay(1000);
}

