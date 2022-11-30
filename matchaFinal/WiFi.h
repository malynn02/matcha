//WiFi Functions
#include <WiFi.h>         // WiFi Library
#include <HTTPClient.h>   // Server Library
#include <Arduino_JSON.h> // JSON Library

const char* ssid = "possum mobile";              // Network Name (e.g. EZConnect)
const char* password =  "111602102";             // Password

int wiFiAttemptCounter = 0;                  // Current Number of Attempts to Connect to WiFi
int wiFiAttemptTotal = 5;                    // Max Attempts to Connect to WiFi

// Connect to WiFi Network
void openWiFi(){
  WiFi.begin(ssid, password); 
  while (WiFi.status() != WL_CONNECTED && wiFiAttemptCounter < wiFiAttemptTotal){
    delay(1000);
    Serial.println("Attempting to Connect to WiFi...");
    wiFiAttemptCounter++;
  } 
  if(wiFiAttemptCounter >= wiFiAttemptTotal){Serial.println("WiFi could not connect!"); wiFiAttemptCounter = 0;}
  else{Serial.println("WiFi connected!");}
}

// Disconnect from WiFi Network
void closeWiFi(){WiFi.disconnect(); Serial.println("WiFi Disconnected");}

// Fetch New Data from WiFi Network
void wifiRefresh(){};

// Send Server Request
String httpGETRequest(const char* serverName) {
  WiFiClient client;
  HTTPClient http;

  http.begin(client, serverName);

  int httpResponseCode;
  int httpTryCounter = 0;
  int httpTryLimit = 5;

  while(http.GET() <= 0 && httpTryCounter < httpTryLimit){
    httpResponseCode = http.GET();
    httpTryCounter++;
    Serial.print("Connect Attempt #"); Serial.println(httpTryCounter);
    delay(1000);
  }
  String payload = "{}"; 

  if (httpTryLimit > 0) {Serial.println("Connected"); payload = http.getString(); Serial.println(payload);}
  else {Serial.println("Not Connected");}
  http.end();
  httpTryCounter = 0;

  return payload;
}
