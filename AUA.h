#ifndef MOI_AUA_H
#define MOI_AUA_H

#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
// I have to include the config in the cpp file because otherwise I am getting a double declaration error
// Which is because bothe AUA.cpp and the main file are importing AUA.h
//#include "config_AUA.h"

class AUA{

  private:
    char Token[48];
    char URI[38];
    StaticJsonDocument<1024> UserJson;
    StaticJsonDocument<3072> InfoJson;
    StaticJsonDocument<384> ReturnJson;
    String httpGETRequest(const char* serverName);
    
  public:
    AUA();
    String GetRecentPlay();


  
};

#endif
