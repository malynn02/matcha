// Functions for Buttons
#include <Bounce2.h>                  // Include Debounce Library

int buttonPins[] = {25, 26, 27};      // Set Button Pins
int numButtons = 3;                   // Declare Number of Buttons
Bounce * buttons = new Bounce[3];     // Declare Button Object Array

// Initialize All Buttons
void initButtons() {
  for (int i = 0; i < numButtons; i++) {
    buttons[i].attach( buttonPins[i], INPUT);
    buttons[i].interval(25);
  }
}

// Read All Buttons
void readButtons() {
  for (int i = 0; i < 3; i++) {
    buttons[i].update();
    if (buttons[i].rose()) {
      if (i == 0) {
        sleepToggle();
      }
      else if (i == 1) {
        curMode++;
        curMode = curMode % numModes;
      }
      else if (i == 2) {
        curMode = 3;
      }
    }
  }
}
