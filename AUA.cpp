#include "AUA.h"
#include "config_AUA.h"

AUA::AUA(){
  //this->Token = AUAToken;
  //this->URI = AUAURI;
  strcpy(this->Token, AUAToken);
  strcpy(this->URI, AUAURI);
}

String AUA::GetRecentPlay(){
  String UserRaw;
  String InfoRaw;
  String ReturnStr;
  // Putting JsonDocuments inside the function leads to the program crashing. Probably because they are static and not dynamic objects
  //Check WiFi connection status
  if(WiFi.status()== WL_CONNECTED){
    char UserRequest[66] = "";
    strcat(UserRequest, this->URI);
    strcat(UserRequest, "user/info?usercode=440498495");
    Serial.println("Getting user data");
    UserRaw = httpGETRequest(UserRequest);
    Serial.println(UserRaw);
    DeserializationError error = deserializeJson(UserJson, UserRaw);
    if (error) {
      Serial.print("deserializeJson() failed: ");
      Serial.println(error.c_str());
      ReturnJson["status"] = -121;
      ReturnJson["message"] = error.c_str();
    }
    else if(UserJson["status"] != 0){
      Serial.print("Api error with status "); Serial.print(UserJson["status"] | 0); Serial.println(":");
      Serial.println(UserJson["message"] | "No message");
      ReturnJson["status"] = UserJson["status"];
      ReturnJson["message"] = UserJson["message"];
    }
    else{
      int SongDiff = UserJson["content"]["recent_score"][0]["difficulty"];
      char InfoRequest[128] = "";
      strcat(InfoRequest, this->URI);
      strcat(InfoRequest, "song/info?songid=");
      strcat(InfoRequest, UserJson["content"]["recent_score"][0]["song_id"]);
      Serial.println("Getting song info");
      InfoRaw = httpGETRequest(InfoRequest);
      Serial.println(InfoRaw);
      DeserializationError error = deserializeJson(InfoJson, InfoRaw);
      if (error) {
        Serial.print("deserializeJson() failed: ");
        Serial.println(error.c_str());
        ReturnJson["status"] = -122;
        ReturnJson["message"] = error.c_str();
      }
      else if(InfoJson["status"] != 0){
        Serial.print("Api error with status "); Serial.print(InfoJson["status"] | 0); Serial.println(":");
        Serial.println(InfoJson["message"] | "No message");
        ReturnJson["status"] = InfoJson["status"];
        ReturnJson["message"] = InfoJson["message"];
      }
      else{
        Serial.println("Done with the requests");
        ReturnJson["status"] = InfoJson["status"];
        ReturnJson["user_name"] = UserJson["content"]["account_info"]["name"];
        ReturnJson["user_rating"] = UserJson["content"]["account_info"]["rating"];
        ReturnJson["score"] = UserJson["content"]["recent_score"][0]["score"];
        ReturnJson["play_rating"] = UserJson["content"]["recent_score"][0]["rating"];
        ReturnJson["near_count"] = UserJson["content"]["recent_score"][0]["near_count"];
        ReturnJson["miss_count"] = UserJson["content"]["recent_score"][0]["miss_count"];
        ReturnJson["perfect_count"] = UserJson["content"]["recent_score"][0]["perfect_count"];
        ReturnJson["shiny_perfect_count"] = UserJson["content"]["recent_score"][0]["shiny_perfect_count"];
        ReturnJson["name_en"] = InfoJson["content"]["difficulties"][SongDiff]["name_en"];
        ReturnJson["artist"] = InfoJson["content"]["difficulties"][SongDiff]["artist"];
        ReturnJson["chart_potential"] = InfoJson["content"]["difficulties"][SongDiff]["rating"];
      }
    }
  }
  else {
    Serial.println("WiFi Disconnected");
    ReturnJson["status"] = -123;
    ReturnJson["message"] = "WiFi Disconnected";
  }
  Serial.println(ReturnStr);
  serializeJson(ReturnJson, ReturnStr);
  Serial.println(ReturnStr);
  return ReturnStr;
}

String AUA::httpGETRequest(const char* serverName){
  HTTPClient http;
    
  // Your Domain name with URL path or IP address with path
  http.begin(serverName);
  http.addHeader("Authorization",this->Token);
  
  // Send HTTP GET request
  int httpResponseCode = http.GET();
  
  String payload = "{}"; 
  
  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();

  return payload;
}
