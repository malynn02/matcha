// Time Functions

#include <ESP32Time.h>

ESP32Time rtc;                      // Clock
boolean timeSet = false;            // Has Time Been Set?

void initTime() {
  String jsonBuffer;
  openWiFi();
  if ( WiFi.status() == WL_CONNECTED) {
    String serverPath = "http://worldtimeapi.org/api/timezone/america/new_york";
    jsonBuffer = httpGETRequest(serverPath.c_str());
    JSONVar myObject = JSON.parse(jsonBuffer);

    String nowTime = JSON.stringify(myObject["datetime"]);
    String nowYear = nowTime.substring(1, 5);
    String nowMonth = nowTime.substring(6, 8);
    String nowDay = nowTime.substring(9, 11);
    String nowHour = nowTime.substring(12, 14);
    String nowMin = nowTime.substring(15, 17);
    String nowSec = nowTime.substring(18, 20);

    rtc.setTime(nowSec.toInt(), nowMin.toInt(), nowHour.toInt(), nowDay.toInt(), nowMonth.toInt(), nowYear.toInt());
    timeSet = true;
  }
  closeWiFi();
}
