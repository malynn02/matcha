// Sleep Functions

boolean isAwake = true;   // Is Watch Awake or Asleep

void sleepToggle(){isAwake = !isAwake;} // Toggles watch between sleep and awake
boolean sleepAwake(){return isAwake;}   // Returns value of isAwake
void sleepSleep(){clearScreen();}       // Puts the watch to sleep (clears screen)
