// Game App Functions

int zeroVal;
int prevVal = 1000;

float ballX = 0;
float ballY = 120;
float prevBallX = 0;
float prevBallY = 120;
int ballD = 3;
float ballXSpeed = .1;
float ballYSpeed = .1;

int targetX = 175;
int targetY = 100;
int targetW = 10;
int targetH = 30;

int thresh = 50000;
int score = 0;
boolean isJumping = false;

void initGame() {
  modeStates[2] = false; // Unitialize Weather
  modeStates[3] = true;  // Initiallize Game
  clearScreen();
}

void game() {
  if (!modeStates[3]) {
    initGame();
  }
  initAccel();

  //read the accelerometer value
  zeroVal = readAccel(0);

  //draw the ball and target
  tft.fillCircle(int(prevBallX), int(prevBallY), ballD + 3, TFT_BLACK);
  tft.fillCircle(int(ballX), int(ballY), ballD, TFT_WHITE);
  prevBallX = ballX;
  prevBallY = ballY;
  tft.fillRect(targetX, targetY, targetW, targetH, TFT_WHITE);

  //move the ball down across the screen
  ballX += ballXSpeed;
  ballY += ballYSpeed;

  //tell the ball to jump if the sensor is reading a value above the threshold, the ball is low enough on the screen, and the sensor's last reading was low
  if (zeroVal >= thresh) {
    if (ballY <= 235) {
      if (prevVal < 5000) {
        isJumping = true;
      }
    }
  }

  //make the ball jump and tell the program it is no longer jumping
  if (isJumping == true) {
    ballY -= 5;
    isJumping = false;
  }

  //store the previous value read by the sensor
  prevVal = zeroVal;

  //keep the ball inside the boundaries of the watch face
  if (ballY >= 240) {ballY = 240;}
  if (ballY <= -1) {ballY = 0;}
  if (ballX >= 240) {ballX = 0;}
  if (ballX <= -1) {ballX = 0;}

  //if the ball hits the target, increase the score, reset the ball, and move the target
  if (ballX + ballD / 2 >= targetX) {
    if (ballX - ballD / 2 <= targetX + targetW) {
      if (ballY + ballD / 2 >= targetY) {
        if (ballY - ballD / 2 <= targetY + targetH) {
          score ++; ballX = 5; ballY = 120;
          targetY = random(0, 240 - targetH);
          tft.fillScreen(TFT_BLACK);
        }
      }
    }
  }

  // if the ball goes out of bounds and/or doesn't hit the target, reset the ball and score
  if (ballX + ballD / 2 >= 240 || ballY + ballD / 2 > 240 || ballY - ballD / 2 <= 0) {
    score = 0; ballX = 5; ballY = 120;
    targetY = random(0, 240 - targetH);
    tft.fillScreen(TFT_BLACK);
  }

  // draw the score on the screen
  tft.setTextColor(TFT_WHITE);
  tft.drawCentreString(String(score), 120, 10, 4);
}
