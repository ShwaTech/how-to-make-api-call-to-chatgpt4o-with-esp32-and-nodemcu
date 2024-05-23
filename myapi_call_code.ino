#include <ESP8266WiFi.h> 
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "AP";
const char* password = "";

const char* apikey = "";
void setup(){
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid,password);
  Serial.print("connecting .....");
  while(WiFi.status() != WL_CONNECTED){
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
}


