//#include <Arduino.h>
#include <U8g2lib.h>
#include "config_WiFi.h"

#include <SPI.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <IRremoteESP8266.h>
#include <IRutils.h>
#include "AUA.h"

/*-------------------------------------------------------------------------------------------------------------------------
Source for WiFi: https://randomnerdtutorials.com/esp32-useful-wi-fi-functions-arduino/#3 
Source for HTTP: https://randomnerdtutorials.com/esp32-http-get-post-arduino/
 
-------------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------Pins--------------------------------
Screen          Using SPI
GND             GND
VDD             3.3V or Vin
SCK             GPIO18
SDA             GPIO23 (MOSI)
RES             GPIO17
DC              GPIO16
CS              GPIO5

Analog Stick
GND             GND
+5V             3.3V or Vin
VRx             GPIO34
VRy             GPIO35
SW              GPIO11

Infrared Reader
GND             GND
VCC             3.3V
S               GPIO33
-------------------------------------------------------------------------*/

U8G2_SH1106_128X64_NONAME_F_4W_HW_SPI   u8g2  (U8G2_R0, 5, 16, 17);     // Initialize screen

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastTime = 0;
bool firstTime = false;
// Timer set to 10 minutes (600000)
//unsigned long timerDelay = 600000;
// Set timer to 5 seconds (5000)
unsigned long timerDelay = 60000;
AUA ArcAPI = AUA();

const int IR_KEY_1 = 0xFFA25D; //Old value: 0xFD00FF;
const int IR_KEY_2 = 0xFF629D; //Old value: 0xFD807F;
const int IR_KEY_3 = 0xFFE21D; //Old value: 0xFD40BF;
const int IR_KEY_4 = 0xFF22DD; //Old value: 0xFD20DF;
const int IR_KEY_5 = 0xFF02FD; //Old value: 0xFDA05F;
const int IR_KEY_6 = 0xFFC23D; //Old value: 0xFD609F;
const int IR_KEY_7 = 0xFFE01F; //Old value: 0xFD10EF;
const int IR_KEY_8 = 0xFFA857; //Old value: 0xFD906F;
const int IR_KEY_9 = 0xFF906F; //Old value: 0xFD50AF;
const int IR_KEY_0 = 0xFF9867;//Old value: 0xFDB04F;
const int IR_KEY_STAR = 0xFF6897; //Old value: 0xFD30CF;
const int IR_KEY_HASH = 0xFFB04F; //Old value: 0xFD708F;
const int IR_KEY_UP_ARROW = 0xFF18E7; //Old value: 0xFD8877;
const int IR_KEY_DOWN_ARROW = 0xFF4AB5; //Old value: 0xFD9867;
const int IR_KEY_RIGHT_ARROW = 0xFF5AA5; //Old value: 0xFD6897;
const int IR_KEY_LEFT_ARROW = 0xFF10EF; //Old value: 0xFD28D7;
const int IR_KEY_OK = 0xFF38C7; //Old value: 0xFDA857;

decode_results results;


void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(WiFiSSID, WiFiPass);
  ConnectingWifi(WiFiSSID);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  ConnectedWifi(WiFiSSID);
  Serial.println(WiFi.localIP());
}

void setup()
{
  Serial.begin(115200);                     // Begin serial
  u8g2.begin();                             // Start screen
  u8g2.setFont(u8g2_font_ncenB08_tr);       // Choose font
  u8g2.setBitmapMode(1);                    // Bitmaps go over each other
  initWiFi();
  Serial.println("Setup ran fully");
  delay(2000);
}

void loop() 
{
 if ((millis() - lastTime) > timerDelay or !firstTime) {
    String RecentPlay = ArcAPI.GetRecentPlay();
    Serial.println(RecentPlay);
    firstTime = true;
    lastTime = millis();
  }
}
