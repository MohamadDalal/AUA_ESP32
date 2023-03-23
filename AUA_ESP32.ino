//#include <Arduino.h>
#include <U8g2lib.h>
#include "config_WiFi.h"

#include <SPI.h>
#include <WiFi.h>
//#include <HTTPClient.h>
//#include <ArduinoJson.h>

#include "AUA.h"
//#include "IR_Remote.h"        // Cannot include this because it is included in Menus.h
#include "Menus.h"
#include "List_Menu.h"

/*-------------------------------------------------------------------------------------------------------------------------
Source for WiFi: https://randomnerdtutorials.com/esp32-useful-wi-fi-functions-arduino/#3 
Source for HTTP: https://randomnerdtutorials.com/esp32-http-get-post-arduino/
Source for object declaration "without instansiation": https://forum.arduino.cc/t/c-object-instantiation-in-setup/337684 Used in IR_Remote
Constructor tutorial: https://www.geeksforgeeks.org/order-constructor-destructor-call-c/
 
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

Buttons
Right Button    GPIO39
Left Button     GPIO36
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
//IR_Remote IR_Driver = IR_Remote(33);    // Seems like I cannot declare the object here and initialize it in setup. So it will be initialized here.
//IR_Remote IR_Driver()                   // Seems that if I use this. I cannot call any methods in the object, as it will tell me that the method does not exist.
IR_Remote IR_Driver = IR_Remote();

const int menuListSize = 3;
//Menu menuList[menuListSize];
Menu* menuList[menuListSize];
int currentMenuListIndex = 0;
int newMenuListIndex = 0;
//Menu baseMenu(&u8g2, 0);


class Test_List_Menu: public List_Menu{
  public:
    Test_List_Menu(){};
    
    Test_List_Menu(U8G2* Display, int ID){
      init(Display, ID);
    };
    void init(U8G2* Display, int ID){
      this->u8g2 = Display;
      this->menuID = ID;
      this->optionArr[0] = new List_Option(0, "BaseMenu 0");
      Serial.print("Created option with label: "); Serial.println(this->optionArr[0]->getLabel());
      this->optionArr[1] = new List_Option(1, "BaseMenu 1");
      Serial.print("Created option with label: "); Serial.println(this->optionArr[1]->getLabel());
      this->optionArr[2] = new List_Option(2, "TestOption 0");
      Serial.print("Created option with label: "); Serial.println(this->optionArr[2]->getLabel());
      this->optionArr[3] = new List_Option(2, "TestOption 1");
      Serial.print("Created option with label: "); Serial.println(this->optionArr[3]->getLabel());
      this->optionArr[4] = new List_Option(2, "TestOption 2");
      Serial.print("Created option with label: "); Serial.println(this->optionArr[4]->getLabel());
      this->Initialized = true;
    };
};



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
  IR_Driver.isInitialized();
  IR_Driver.init(33);
  /*for(int i=0; i<menuListSize; i++){
    menuList[i] =  Menu(&u8g2, i);
  }*/
  //menuList[0] =  Menu(&u8g2, 0);
  //menuList[1] =  Menu(&u8g2, 1);
  //menuList[2] =  Menu(&u8g2, 2);
  //menuList[2] = Test_List_Menu(&u8g2, 2);
  menuList[0] = new Menu(&u8g2, 0);
  menuList[1] = new Menu(&u8g2, 1);
  menuList[2] = new Test_List_Menu(&u8g2, 2);
  //Serial.print("The ID of the base menu is: "); Serial.println(baseMenu.getMenuID());
  Serial.println("Setup ran fully");
  delay(2000);
}

void loop() 
{
 if ((millis() - lastTime) > timerDelay or !firstTime) {
    //String RecentPlay = ArcAPI.GetRecentPlay();
    //Serial.println(RecentPlay);
    firstTime = true;
    lastTime = millis();
  }
  //baseMenu.drawScreen();
  /*u8g2.clearBuffer();
  menuList[currentMenuListIndex].drawScreen();
  //Serial.println(menuList[currentMenuListIndex].getMenuID());
  newMenuListIndex = menuList[currentMenuListIndex].decodeInput(IR_Driver.IR_Read());
  //Serial.print("Current Menu Index: "); Serial.print(currentMenuListIndex); Serial.print("\tNew Menu Index: "); Serial.println(newMenuListIndex);
  if(!(newMenuListIndex == currentMenuListIndex)){
    menuList[newMenuListIndex].setPrevMenuID(currentMenuListIndex);
    currentMenuListIndex = newMenuListIndex;
  }
  u8g2.sendBuffer();*/
  /*switch(IR_Driver.IR_Read()){
    case IR_KEY::N1           : Serial.println(IR_KEY::N1);              break;
  }*/
  u8g2.clearBuffer();
  //Serial.println("Checkpoint 1");
  menuList[currentMenuListIndex]->drawScreen();
  //Serial.println("Checkpoint 2");
  newMenuListIndex = menuList[currentMenuListIndex]->decodeInput(IR_Driver.IR_Read());
  //Serial.println("Checkpoint 3");
  if(!(newMenuListIndex == currentMenuListIndex)){
    //Serial.println("Checkpoint 4");
    menuList[newMenuListIndex]->setPrevMenuID(currentMenuListIndex);
    //Serial.println("Checkpoint 5");
    currentMenuListIndex = newMenuListIndex;
    //Serial.println("Checkpoint 6");
  }
  //Serial.println("Checkpoint 7");
  u8g2.sendBuffer();
}
