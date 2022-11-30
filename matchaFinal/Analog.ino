// Analog Watch Functions
TFT_eSprite sTime = TFT_eSprite(&tft);
TFT_eSprite mTime = TFT_eSprite(&tft);
TFT_eSprite hTime = TFT_eSprite(&tft);

int lastSec = 0;

void initAnalog() {
  modeStates[3] = false; // Uninitialize Game
  modeStates[0] = true;  // Initialize Analog
  clearScreen();         // Clear the Screen
}

void analog() {
    if (!modeStates[0]) {
    initAnalog(); // Initialize Analog Time
  }
  if (!timeSet) {
    initTime();
  }
  //screenText("Analog Time", 10, 100, 4);
  if (lastSec != rtc.getSecond()) {
    TJpgDec.drawJpg(0, 0, analogBG, sizeof(analogBG));
    lastSec = rtc.getSecond();
  }
  drawSecond();
  drawMinute();
  drawHour();
}

void drawSecond() {
  int w = 2;                     // second hand width in pixels
  int h = 70;                    // second hand height in pixels
  int nowSec = rtc.getSecond();
  int sAngle = (360 / 60) * nowSec;

  tft.setPivot(120, 120);
  sTime.createSprite(w, h);
  sTime.fillSprite(0xf61e);
  sTime.setPivot(w / 2, h);
  sTime.pushRotated(sAngle);
}

void drawMinute() {
  int w = 4;                     // minute hand width in pixels
  int h = 70;                    // minute hand height in pixels
  int nowMin = rtc.getMinute();
  int mAngle = (360 / 60) * nowMin;

  tft.setPivot(120, 120);
  mTime.createSprite(w, h);
  mTime.fillSprite(0xbe1e);
  mTime.setPivot(w / 2, h);
  mTime.pushRotated(mAngle);
}

void drawHour() {
  int w = 6;                     // hour hand width in pixels
  int h = 55;                    // hour hand height in pixels
  int nowHour = rtc.getHour();
  int hAngle = (360 / 12) * nowHour;

  tft.setPivot(120, 120);
  hTime.createSprite(w, h);
  hTime.fillSprite(0xe55c);
  hTime.setPivot(w / 2, h);
  hTime.pushRotated(hAngle);
}
