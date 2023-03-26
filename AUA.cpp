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
    char UserRequest[84] = "";
    strcat(UserRequest, this->URI);
    strcat(UserRequest, "user/info?usercode=");
    strcat(UserRequest, AUAUserCode);
    strcat(UserRequest, "&withsonginfo=true");
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
      Serial.println("Done with the requests");
      ReturnJson["status"] = UserJson["status"];
      ReturnJson["user_name"] = UserJson["content"]["account_info"]["name"];
      ReturnJson["user_rating"] = UserJson["content"]["account_info"]["rating"];
      ReturnJson["score"] = UserJson["content"]["recent_score"][0]["score"];
      ReturnJson["play_rating"] = UserJson["content"]["recent_score"][0]["rating"];
      ReturnJson["near_count"] = UserJson["content"]["recent_score"][0]["near_count"];
      ReturnJson["miss_count"] = UserJson["content"]["recent_score"][0]["miss_count"];
      ReturnJson["perfect_count"] = UserJson["content"]["recent_score"][0]["perfect_count"];
      ReturnJson["shiny_perfect_count"] = UserJson["content"]["recent_score"][0]["shiny_perfect_count"];
      ReturnJson["name_en"] = UserJson["content"]["songinfo"][0]["name_en"];
      ReturnJson["artist"] = UserJson["content"]["songinfo"][0]["artist"];
      ReturnJson["chart_potential"] = UserJson["content"]["songinfo"][0]["rating"];
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
