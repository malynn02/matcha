// Digital Watch Functions

void initDigital() {
  modeStates[0] = false;  // Uninitialize Analog
  modeStates[1] = true;   // Initialize Digital
  clearScreen();
  TJpgDec.drawJpg(0, 0, digitalBG, sizeof(digitalBG));
}

void digital() {
  if (!modeStates[1]) {
    initDigital();
  }
  if (!timeSet) {
    initTime();
  }

  int nowSec = rtc.getSecond();
  int nowMin = rtc.getMinute();
  int nowHour = rtc.getHour(true);
  int nowDay = rtc.getDay();
  int nowMonth = rtc.getMonth();
  int nowYear = rtc.getYear();
  String nowTime = rtc.getTime();
  String nowDate = rtc.getDate();

#define TONGUECOLOR 0xF551

  if (nowSec == 0) {
    TJpgDec.drawJpg(0, 0, digitalBG, sizeof(digitalBG));
  }

  tft.setTextColor(TFT_WHITE);
  tft.drawCentreString(String(nowHour), 100, 60, 4);
  tft.drawCentreString(":", 120, 60, 4);
  if (nowMin < 10) {
    tft.drawCentreString("0", 140, 60, 4);
    tft.drawCentreString(String(nowMin), 155, 60, 4);
  }
  else {
    tft.drawCentreString(String(nowMin), 140, 60, 4);
  }
  tft.drawCentreString(nowDate, 120, 160, 4);

  if (nowSec > 10) {
    tft.fillRect(91, 119, 17, 4, TONGUECOLOR);
  }
  if (nowSec > 20) {
    tft.fillRect(108, 119, 17, 4, TONGUECOLOR);
  }
  if (nowSec > 30) {
    tft.fillRect(125, 119, 17, 4, TONGUECOLOR);
  }
  if (nowSec > 40) {
    tft.fillRect(142, 119, 17, 4, TONGUECOLOR);
  }
  if (nowSec > 50) {
    tft.fillRect(159, 119, 17, 4, TONGUECOLOR);
  }
}
