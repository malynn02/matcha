// Weather App Functions
#include <WiFi.h>         // WiFi Library
#include <HTTPClient.h>   // Server Library
#include <Arduino_JSON.h> // JSON Library

boolean weatherSet = false;

String setNowIcon;
int setNowTemp;
int setNowFeels;
int setNowMin;
int setNowMax;

unsigned long startTime = 60000;
int delayTime = 5000;

String testingPrint;

void initWeather() {
  modeStates[1] = false; // Uninitialize Digital
  modeStates[2] = true;  // Initialize Weather
  clearScreen();
}

void weather() {
  if (!weatherSet) {
    setWeather();
  }
  if (!modeStates[2]) {
    initWeather();
  }

  if (millis() - startTime >= delayTime) {

    if (setNowIcon.equals("01d")) {
      //draw clear day icon
      TJpgDec.drawJpg(0, 0, clearDay, sizeof(clearDay));
    }
    if (setNowIcon.equals("01n")) {
      //draw clear night icon
      TJpgDec.drawJpg(0, 0, clearNight, sizeof(clearNight));
    }
    if (setNowIcon.equals("02d") || setNowIcon.equals("03d") || setNowIcon.equals("04d")) {
      //draw cloudy day icon
      TJpgDec.drawJpg(0, 0, cloudyDay, sizeof(cloudyDay));
    }
    if (setNowIcon.equals("02n") || setNowIcon.equals("03n") || setNowIcon.equals("04n")) {
      //draw cloudy night icon
      TJpgDec.drawJpg(0, 0, cloudyNight, sizeof(cloudyNight));
    }
    if (setNowIcon.equals("09d") || setNowIcon.equals("10d")) {
      //draw rainy day icon
      TJpgDec.drawJpg(0, 0, rainyDay, sizeof(rainyDay));
    }
    if (setNowIcon.equals("09n") || setNowIcon.equals("10n")) {
      //draw rainy night icon
      TJpgDec.drawJpg(0, 0, rainyNight, sizeof(rainyNight));
    }
    if (setNowIcon.equals("11d") || setNowIcon.equals("11n")) {
      //draw thunderstorm icon
      TJpgDec.drawJpg(0, 0, thunderstorm, sizeof(thunderstorm));
    }
    if (setNowIcon.equals("13d") || setNowIcon.equals("13n")) {
      //draw snow icon
      TJpgDec.drawJpg(0, 0, snow, sizeof(snow));
    }
    if (setNowIcon.equals("50d") || setNowIcon.equals("50n")) {
      //draw misty icon
      TJpgDec.drawJpg(0, 0, mist, sizeof(mist));
    }

    startTime = millis();
  }

  tft.setTextColor(TFT_BLACK);
  //draw out temp, feels like, min, and max
  tft.drawCentreString(String(setNowTemp), 50, 50, 4);
  tft.drawCentreString("temp", 50, 70, 1);
  tft.drawCentreString(String(setNowFeels), 190, 50, 4);
  tft.drawCentreString("feels like", 190, 70, 1);
  tft.drawCentreString(String(setNowMin), 50, 170, 4);
  tft.drawCentreString("min", 50, 160, 1);
  tft.drawCentreString(String(setNowMax), 190, 170, 4);
  tft.drawCentreString("max", 190, 160, 1);
  tft.setTextColor(TFT_WHITE);
}

void setWeather() {

  String jsonBuffer;

  openWiFi();
  if ( WiFi.status() == WL_CONNECTED) {
    String serverPath = "http://api.openweathermap.org/data/2.5/weather?id=4219762&appid=90ad0c42c5ac9c15db7ae62ba8e78ed1";
    jsonBuffer = httpGETRequest(serverPath.c_str());
    JSONVar myObject = JSON.parse(jsonBuffer);

    String iconNow = JSON.stringify(myObject["weather"][0]["icon"]); iconNow.replace("\"", 0);
    String nowIcon = iconNow.substring(0, 4);
    String tempNow = JSON.stringify(myObject["main"]["temp"]);
    String nowTemp = tempNow.substring(0, 7);
    String feelsNow = JSON.stringify(myObject["main"]["feels_like"]);
    String nowFeels = feelsNow.substring(0, 7);
    String minNow = JSON.stringify(myObject["main"]["temp_min"]);
    String nowMin = minNow.substring(0, 7);
    String maxNow = JSON.stringify(myObject["main"]["temp_max"]);
    String nowMax = maxNow.substring(0, 7);

    setNowIcon = nowIcon;
    setNowTemp = ktof(nowTemp);
    setNowFeels = ktof(nowFeels);
    setNowMin = ktof(nowMin);
    setNowMax = ktof(nowMax);

    weatherSet = true;

    testingPrint = setNowIcon;
  }
  closeWiFi();
}

// Converts Kelvin (as String) to Farenheit (as float)
int ktof(String k) {
  float degreesK = k.toFloat();
  float degreesF = ((degreesK - 273.15) * 1.8) + 32;
  int intF = degreesF;
  return intF;
}

//notes
/*

  //90ad0c42c5ac9c15db7ae62ba8e78ed1
  //https://openweathermap.org/city/4219762
  
*/
