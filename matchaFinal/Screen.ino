// Functions for LCD Display

// Screen is 240x240

void initScreen(){
  TJpgDec.setSwapBytes(true);
  TJpgDec.setCallback(tft_output);
  
  //tft.init();
  tft.begin();
  tft.setRotation(0);                     //modded to 0-3 to rotate screen
  tft.fillScreen(TFT_BLACK);
}

bool tft_output(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t* bitmap){
  if ( y >= tft.height() ) return 0;
  tft.pushImage(x, y, w, h, bitmap);
  return 1;
}

void clearScreen(){tft.fillScreen(TFT_BLACK);}

// Prints text (s) on screen at location x/y with font size f
void screenText(String s, int x, int y, int f){
  tft.setCursor(x, y, f);
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.println(s);
}

void debugText(String s, int y){tft.drawCentreString(s, 120, y, 1);}

float angleX(float offset, float degree){
  float r = (degree * 71.0) / 4068.0;
  float a = sin(r) * offset;
  float aOff = a + 120;
  return aOff;
}

float angleY(float offset, float degree){
  float r = (degree * 71.0) / 4068.0;
  float a = cos(r) * offset;
  float aOff = a + 120;
  return aOff;
}
