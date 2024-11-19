
#include "pitches.h"
//#include "sample.h"
#include "sample2.h"
#include "Espresso.h"

// Change this depending on where you put your piezo buzzer
const int TONE_OUTPUT_PIN = 12;

// The ESP32 has 16 channels which can generate 16 independent waveforms
// We'll just choose PWM channel 0 here
const int TONE_PWM_CHANNEL = 0;

// sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
// there are two values per note (pitch and duration), so for each note there are four bytes
int notes = sizeof(melody) / sizeof(melody[0]) / 2;

// this calculates the duration of a whole note in ms
int wholenote = (60000 * 4) / tempo;

int divider = 0, octave = 0, noteDuration = 0;

void loop() { //Plays melody once.
  ledcAttachPin(TONE_OUTPUT_PIN, TONE_PWM_CHANNEL);

  // iterate over the notes of the melody.
  // Remember, the array is twice the number of notes (notes + durations)
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

    // calculates the duration of each note
    divider = melody[thisNote + 1];
    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }

    ledcWriteTone(TONE_PWM_CHANNEL, melody[thisNote]);

    //    delay(noteDuration);
    //    we only play the note for 90% of the duration, leaving 10% as a pause
    //    tone(buzzer, melody[thisNote], noteDuration*0.9);

    // Wait for the specific duration before playing the next note.
    delay(noteDuration);

    // stop the waveform generation before the next note.
    ledcWriteTone(TONE_PWM_CHANNEL, 0);
  }
  ledcDetachPin(TONE_OUTPUT_PIN);

  updateEyes();
}

void setup() {
    init();
}
