/***************************************************
  Arduino TFT graphics library targeted at 32 bit
  processors such as ESP32, ESP8266 and STM32.

  This is a stand-alone library that contains the
  hardware driver, the graphics functions and the
  proportional fonts.

  The larger fonts are Run Length Encoded to reduce their
  size.

  Created by Bodmer 2/12/16
  Last update by Bodmer 20/03/20
 ****************************************************/

#include "Espresso.h"

TFT_eSPI tft;           // A single instance is used for 1 or 2 displays

#ifdef AUTOBLINK
uint32_t timeOfLastBlink = 0L, timeToNextBlink = 0L;
#endif

typedef struct {        // Struct is defined before including config.h --
  int8_t  select;       // pin numbers for each eye's screen select line
  uint8_t rotation;     // also display rotation and the x offset
  int16_t xposition;    // position of eye on the screen
} eyeInfo_t;

typedef struct {
  uint8_t  state;       // NOBLINK/ENBLINK/DEBLINK
  uint32_t duration;    // Duration of blink state (micros)
  uint32_t startTime;   // Time (micros) of last state change
} eyeBlink;

struct {                // One-per-eye structure
  int16_t   tft_cs;     // Chip select pin for each display
  eyeBlink  blink;      // Current blink/wink state
  int16_t   xposition;  // x position of eye image
} eye[NUM_EYES];

eyeInfo_t eyeInfo[] = {
  { TFT1_CS, TFT_1_ROT, EYE_1_XPOSITION }, // LEFT EYE chip select and wink pins, rotation and offset
  { TFT2_CS, TFT_2_ROT, EYE_2_XPOSITION }, // RIGHT EYE chip select and wink pins, rotation and offset
};

int16_t eyePosX = 128;

// EYE-RENDERING FUNCTION --------------------------------------------------
void drawEye( // Renders one eye.  Inputs must be pre-clipped & valid.
  // Use native 32 bit variables where possible as this is 10% faster!
  uint8_t  e,       // Eye array index; 0 or 1 for left/right
  uint32_t iScale,  // Scale factor for iris
  uint32_t  irisX, // First pixel X offset into sclera image
  uint32_t  irisY // First pixel Y offset into sclera image
) {

  digitalWrite(eye[e].tft_cs, LOW);
  tft.fillScreen(TFT_BLACK);
  tft.fillCircle(irisX, irisY, iScale, TFT_BLUE);
  digitalWrite(eye[e].tft_cs, HIGH);
}

// EYE-BLINK FUNCTION --------------------------------------------------
void drawBlink( // Renders one eye.  Inputs must be pre-clipped & valid.
  // Use native 32 bit variables where possible as this is 10% faster!
  uint8_t  e,       // Eye array index; 0 or 1 for left/right
  uint8_t w,  // Width of iris
  uint8_t h,  // Height of iris
  uint8_t  irisX, // First pixel X offset into sclera image
  uint8_t  irisY // First pixel Y offset into sclera image
) {

  digitalWrite(eye[e].tft_cs, LOW);
  tft.fillScreen(TFT_BLACK);
  tft.fillRect((irisX - (w / 2)), (irisY - (h / 2)), w, h, TFT_BLUE); //x,y,w,h,color
  digitalWrite(eye[e].tft_cs, HIGH);
}

// Initialise eyes ---------------------------------------------------------
void initEyes(void)
{
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, RXp2, TXp2);
  delay(2000);
  
  // Initialise eye objects based on eyeInfo list in config.h:
  for (uint8_t e = 0; e < NUM_EYES; e++) {
    //Serial.print("Create display #"); Serial.println(e);

    eye[e].tft_cs      = eyeInfo[e].select;
    eye[e].blink.state = NOBLINK;
    eye[e].xposition   = eyeInfo[e].xposition;

    pinMode(eye[e].tft_cs, OUTPUT);
    digitalWrite(eye[e].tft_cs, LOW);
  }
  tft.init();
  // Raise chip select(s) so that displays can be individually configured
  digitalWrite(eye[0].tft_cs, HIGH);
  if (NUM_EYES > 1) digitalWrite(eye[1].tft_cs, HIGH);
  for (uint8_t e = 0; e < NUM_EYES; e++) {
    digitalWrite(eye[e].tft_cs, LOW);
    tft.setRotation(eyeInfo[e].rotation);
    tft.fillScreen(TFT_BLACK);
    digitalWrite(eye[e].tft_cs, HIGH);
  }
  Serial.println("Good morning!");

  drawEye(0, 80, 128, 128);
  drawEye(1, 80, 128, 128);
  delay(2000);
  drawBlink(0, 100, 5, 128, 128);
  drawBlink(1, 100, 5, 128, 128);
  delay(200);
  drawEye(0, 80, 128, 128);
  drawEye(1, 80, 128, 128);
  delay(500);
  drawBlink(0, 100, 5, 128, 128);
  drawBlink(1, 100, 5, 128, 128);

  drawEye(0, 80, 128, 128);
  drawEye(1, 80, 128, 128);
  delay(500);

}
void updateEyes(void)
{
  uint32_t t = micros();
  
  if (Serial2.available() > 0) {
    int eyeBuffer = Serial2.parseInt();
    if (eyeBuffer > 0) {
      eyePosX = eyeBuffer;
    }
    Serial.println(eyePosX);
    drawEye(0, 80, eyePosX, 128);
    drawEye(1, 80, eyePosX, 128);
  }

  if (Serial.available() > 0) {
    eyePosX = Serial.parseInt();
    Serial.println(eyePosX);
    drawEye(0, 80, eyePosX, 128);
    drawEye(1, 80, eyePosX, 128);
  }
  
  // Blinking
#ifdef AUTOBLINK
  // Similar to the autonomous eye movement above -- blink start times
  // and durations are random (within ranges).
  if ((t - timeOfLastBlink) >= timeToNextBlink) { // Start new blink?
    timeOfLastBlink = t;
    uint32_t blinkDuration = random(75000, 100000); // ~1/28 - ~1/14 sec
    // Set up durations for both eyes (if not already winking)
    for (uint8_t e = 0; e < NUM_EYES; e++) {
      if (eye[e].blink.state == NOBLINK) {
        eye[e].blink.state     = ENBLINK;
        eye[e].blink.startTime = t;
        eye[e].blink.duration  = blinkDuration;
        drawBlink(e, 100, 5, 128, 128);
      }
    }
    timeToNextBlink = blinkDuration * 3 + random(10000000);
  }
  for (uint8_t eyeIndex = 0; eyeIndex < NUM_EYES; eyeIndex++) {
    if (eye[eyeIndex].blink.state) { // Eye currently blinking?
      uint32_t s = (t - eye[eyeIndex].blink.startTime);
      if (s >= eye[eyeIndex].blink.duration) {
        eye[eyeIndex].blink.state = NOBLINK;      // No longer blinking
        drawEye(eyeIndex, 80, 128, 128);
      }
    }
  }
#endif
}



