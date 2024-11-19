
#include "pitches.h"
#include "sample2.h"
#include "Espresso.h"


TaskHandle_t Task1;
TaskHandle_t Task2;

// Define pin numbers for the Piezo Buzzer and the two DC motors
const int TONE_OUTPUT_PIN = 12;
const int LEFT_MOTOR_IN1_PIN = 25;
const int LEFT_MOTOR_IN2_PIN = 26;
const int RIGHT_MOTOR_IN3_PIN = 33;
const int RIGHT_MOTOR_IN4_PIN = 32;

void setup() {
  // Set pin modes
  pinMode(TONE_OUTPUT_PIN, OUTPUT);
  pinMode(LEFT_MOTOR_IN1_PIN, OUTPUT);
  pinMode(LEFT_MOTOR_IN2_PIN, OUTPUT);
  pinMode(RIGHT_MOTOR_IN3_PIN, OUTPUT);
  pinMode(RIGHT_MOTOR_IN4_PIN, OUTPUT);
  init();


  //create a task that will be executed in the Task1code() function, with priority 1 and executed on core 0
  xTaskCreatePinnedToCore(
                    Task1code,   /* Task function. */
                    "Task1",     /* name of task. */
                    10000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    1,           /* priority of the task */
                    &Task1,      /* Task handle to keep track of created task */
                    0);          /* pin task to core 0 */                  
  delay(500); 

  //create a task that will be executed in the Task2code() function, with priority 1 and executed on core 1
  xTaskCreatePinnedToCore(
                    Task2code,   /* Task function. */
                    "Task2",     /* name of task. */
                    10000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    1,           /* priority of the task */
                    &Task2,      /* Task handle to keep track of created task */
                    1);          /* pin task to core 1 */
   delay(500); 
}

//Task1code: Allows Buzzer to play music
void Task1code( void * pvParameters ){
// The ESP32 has 16 channels which can generate 16 independent waveforms
// We'll just choose PWM channel 0 here
const int TONE_PWM_CHANNEL = 0;

// sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
// there are two values per note (pitch and duration), so for each note there are four bytes
int notes = sizeof(melody) / sizeof(melody[0]) / 2;

// this calculates the duration of a whole note in ms
int wholenote = (60000 * 4) / tempo;

int divider = 0, octave = 0, noteDuration = 0;
   
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
    // we only play the note for 90% of the duration, leaving 10% as a pause
    //    tone(buzzer, melody[thisNote], noteDuration*0.9);

    // Wait for the specific duration before playing the next note.
    delay(noteDuration);

    // stop the waveform generation before the next note.
    ledcWriteTone(TONE_PWM_CHANNEL, 0);
  }
  ledcDetachPin(TONE_OUTPUT_PIN);
}

//Task2code: Allow Robot to Dance by controlling motors
void Task2code( void * pvParameters ){
// Run the two DC motors forward for 1 second
  digitalWrite(LEFT_MOTOR_IN1_PIN, HIGH);
  digitalWrite(LEFT_MOTOR_IN2_PIN, LOW);
  digitalWrite(RIGHT_MOTOR_IN3_PIN, HIGH);
  digitalWrite(RIGHT_MOTOR_IN4_PIN, LOW);
  delay(1000);
  
  // Stop the two DC motors for 1 second
  digitalWrite(LEFT_MOTOR_IN1_PIN, LOW);
  digitalWrite(LEFT_MOTOR_IN2_PIN, LOW);
  digitalWrite(RIGHT_MOTOR_IN3_PIN, LOW);
  digitalWrite(RIGHT_MOTOR_IN4_PIN, LOW);
  delay(1000);
  
  // Turns Left for 1 second
  digitalWrite(LEFT_MOTOR_IN1_PIN, LOW);
  digitalWrite(LEFT_MOTOR_IN2_PIN, HIGH);
  digitalWrite(RIGHT_MOTOR_IN3_PIN, HIGH);
  digitalWrite(RIGHT_MOTOR_IN4_PIN, LOW);
  delay(2000);


  // Run the two DC motors backward for 1 second
  digitalWrite(LEFT_MOTOR_IN1_PIN, LOW);
  digitalWrite(LEFT_MOTOR_IN2_PIN, HIGH);
  digitalWrite(RIGHT_MOTOR_IN3_PIN, LOW);
  digitalWrite(RIGHT_MOTOR_IN4_PIN, HIGH);
  delay(1000);
  
  // Stop the two DC motors for 1 second
  digitalWrite(LEFT_MOTOR_IN1_PIN, LOW);
  digitalWrite(LEFT_MOTOR_IN2_PIN, LOW);
  digitalWrite(RIGHT_MOTOR_IN3_PIN, LOW);
  digitalWrite(RIGHT_MOTOR_IN4_PIN, LOW);
  delay(1000);

  // Turns Right for 2 seconds
  digitalWrite(LEFT_MOTOR_IN1_PIN, HIGH);
  digitalWrite(LEFT_MOTOR_IN2_PIN, LOW);
  digitalWrite(RIGHT_MOTOR_IN3_PIN, LOW);
  digitalWrite(RIGHT_MOTOR_IN4_PIN, HIGH);
  delay(4000);

}
void loop() {
  updateEyes();
}
