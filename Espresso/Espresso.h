#include "Eyes.h"

#define TFT_1_ROT 1        // TFT 1 rotation
#define TFT_2_ROT 3        // TFT 2 rotation
#define EYE_1_XPOSITION  128 // x shift for eye 1 image on display
#define EYE_2_XPOSITION  128 // x shift for eye 2 image on display

// A simple state machine is used to control eye blinks/winks:
#define NOBLINK 0       // Not currently engaged in a blink
#define ENBLINK 1       // Eyelid is currently closing
#define DEBLINK 2       // Eyelid is currently opening
#define AUTOBLINK

// EYE LIST ----------------------------------------------------------------
#define NUM_EYES 2 // Number of eyes to display (1 or 2)

#define RXp2 16 //Serial port 2 RX pin
#define TXp2 17 //Serial port 2 TX pin

  //Espresso routines
  void initEyes(void);
  void updateEyes(void);
