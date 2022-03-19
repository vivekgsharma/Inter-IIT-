// C4:5B:BE:63:19:BA    Sever IP Address
#include <Arduino.h>
#if defined(ESP32)
  #include <WiFi.h>
#elif defined(ESP8266)
  #include <ESP8266WiFi.h>
#endif
#include <Firebase_ESP_Client.h>

#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"
#define WIFI_SSID "Inter"
#define WIFI_PASSWORD "#helloworld"
#define API_KEY "AIzaSyA5bJvaz2rlyiGu3MtKcDLCo7Ycd4OZzkM"
#define DATABASE_URL "https://inter-iit-60162-default-rtdb.firebaseio.com/" 
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
unsigned long sendDataPrevMillis = 0;
int count = 0;
bool signupOK = false;


void setup(){
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(300);
  }
 
  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;
if (Firebase.signUp(&config, &auth, "", "")){
    signupOK = true;
  }
  else{
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  config.token_status_callback = tokenStatusCallback;
  
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void loop(){
  if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 15000 || sendDataPrevMillis == 0)){
    sendDataPrevMillis = millis();
    int a=random (1,20);
    int b=random (1,20);
    int c=random (1,20);
    int d=random (1,20);
    int e=random (1,20);
    
    
   // Serial.print("in loop");
    bool sent1=Firebase.RTDB.setInt(&fbdo, "BinPerLevel/29-84715419999999|77-8817452/height", a);
    bool sent2=Firebase.RTDB.setInt(&fbdo, "BinPerLevel/29-8624811|77-8941031/height", b);
    bool sent3=Firebase.RTDB.setInt(&fbdo, "BinPerLevel/29-8542626|77-8880002/height", c);
    bool sent4=Firebase.RTDB.setInt(&fbdo, "BinPerLevel/29-8542626|77-8880002/height", d);
    bool sent5=Firebase.RTDB.setInt(&fbdo, "BinPerLevel/29-8765003|77-8890677/height", e);
    
    
    if(sent1 || sent2 || sent3 || sent4 || sent5) 
    Serial.print("Scuces");
  }
}