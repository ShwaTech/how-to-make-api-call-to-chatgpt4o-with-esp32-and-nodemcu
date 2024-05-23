#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>
#include <ArduinoJson.h>

const char* ssid = "AP";
const char* password = "";

const char* apiEndpoint = "https://shwatech.onrender.com/marcapi";

void setup() {
  Serial.begin(115200);
  delay(10);


  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

 
  if (WiFi.status() == WL_CONNECTED) { 
    std::unique_ptr<BearSSL::WiFiClientSecure> client(new BearSSL::WiFiClientSecure);
    client->setInsecure();

    HTTPClient http;  

    http.begin(*client, apiEndpoint);  
    http.addHeader("Content-Type", "application/json");
    

    
    String payload = R"(
    {
    'phosphorus':4.6,
    'calicium':5.6,
    'potassium': 7.8,
    'ph':5.4,
    'result':'rice'
    }
    )";

    int httpCode = http.POST(payload);  

    if (httpCode > 0) { 
      String response = http.getString(); 
      Serial.println(httpCode); 
      Serial.println(response);  
      StaticJsonDocument<1024> doc;
      DeserializationError error = deserializeJson(doc, response);

      if (!error) {
        const char* answer = doc["calicium"];
        Serial.println("Answer:");
        Serial.println(answer); // Print the extracted answer
      } else {
        Serial.print("JSON deserialization failed: ");
        Serial.println(error.c_str());
      }

    } else {
      Serial.println("Error on HTTP request");
    }

    http.end();  
  }
}

void loop() {
 
}
