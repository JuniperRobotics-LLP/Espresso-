
#include "Espresso.h"

TaskHandle_t Task1;
TaskHandle_t Task2;

// IR pins
const int IR1 = 14; //Left IR sesnor
const int IR2 = 27; //Right IR sesnor

void setup() {
  Serial.begin(115200); 
  pinMode(IR1, OUTPUT);
  pinMode(IR2, OUTPUT);
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

//Task1code: IR sensor blinks every 1000 ms (1 seconds)
void Task1code( void * pvParameters ){
  Serial.print("Task1 running on core ");
  Serial.println(xPortGetCoreID());

  for(;;){
    digitalWrite(IR1, HIGH);
    delay(1000);
    digitalWrite(IR1, LOW);
    delay(1000);
  } 
}

//Task2code: IR sensor blinks every 600 ms (0.6 seconds)
void Task2code( void * pvParameters ){
  Serial.print("Task2 running on core ");
  Serial.println(xPortGetCoreID());

  for(;;){
    digitalWrite(IR2, HIGH);
    delay(600);
    digitalWrite(IR2, LOW);
    delay(600);
  }
}

void loop() {
  updateEyes();
}
