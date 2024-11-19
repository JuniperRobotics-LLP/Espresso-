// Load the Espresso library
#include "Espresso.h"

// INITIALIZATION -- runs once at startup ----------------------------------
void setup(void) {
// Initialise the eyes
  init();
}

// MAIN LOOP -- runs continuously after setup() ----------------------------
void loop() {
updateEyes();
facetracking();
}
