#include <WiFi.h>
#include <WebServer.h>
#include "Espresso.h"

// Set your access point network credentials
const char* ssid = "LED_Excerise"; //change "LED_Excerise" to your name.

#define LEFT_IR_SENSOR_PIN 14 
#define RIGHT_IR_SENSOR_PIN 27

WebServer server(80);

unsigned long currentMillis;
unsigned long prevMillis;
unsigned int interval = 1000; 
uint8_t LEDstatus = 0;
bool ledState = false;

void setup() {
  init();
  Serial.begin(115200);
  pinMode(LEFT_IR_SENSOR_PIN, OUTPUT);    
  pinMode(RIGHT_IR_SENSOR_PIN, OUTPUT);  

// Wi-Fi connection
  Serial.print("Creating WiFi AP for ");
  Serial.println(ssid);
  WiFi.softAP(ssid);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  Serial.println("");
  Serial.println("WiFi connected");

  
  server.on("/", handle_OnConnect); //Fill in this section
  //ledBlink
  //ledAlternate
  //ledOff
  server.onNotFound(handle_NotFound);
  
  server.begin();
  Serial.println("HTTP server started");
  prevMillis = millis();
}

void loop() {
  updateEyes();
  server.handleClient();
  if(LEDstatus == 1)
    ledBlink();
  else if(LEDstatus == 2)
    ledAlternate();
  else
    ledOff();
}

void ledBlink(){
  currentMillis = millis();
  if(currentMillis - prevMillis >= interval){
    prevMillis = currentMillis;
    ledState = !ledState;
    digitalWrite(LEFT_IR_SENSOR_PIN,  ledState);
    digitalWrite(RIGHT_IR_SENSOR_PIN, ledState);
  }
}

void ledAlternate(){
//CTRL+C & CTRL+V 
  }
}

void ledOff(){
    digitalWrite(LEFT_IR_SENSOR_PIN, HIGH);
    digitalWrite(RIGHT_IR_SENSOR_PIN, HIGH);
}

void handle_OnConnect() { //Fillin this section
  LEDstatus = 0;  
  Serial.println("LED Status: OFF");
  server.send(200, "text/html", getHTML()); 
}

void handle_ledBlink() {
  LEDstatus = 1;
//LED Status: Blinking
}

void handle_ledAlternate() {
  LEDstatus = 2;
//LED Status: Alternating
}

void handle_ledOff() {
  LEDstatus = 0;
//LED Status: OFF
}

void handle_NotFound(){
// Not Found
}

String getHTML(){
  String htmlcode = "<!DOCTYPE html> <html>\n";
  htmlcode +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  htmlcode +="<title>LED Control</title>\n";
  
  htmlcode +="<style>html { font-family: Open Sans; display: inline-block; margin: 0px auto; text-align: center;}\n";
  htmlcode +="body{margin-top: 50px;} h1 {color: #154c79;margin: 30px auto 30px;} h3 {color: #1e81b0;margin-bottom: 50px;}\n";
  htmlcode +=".button {display: block;width: 150px;background-color: #3498db;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  htmlcode +=".button-on {background-color: #1e81b0;}\n";
  htmlcode +=".button-on:active {background-color: #15767b;}\n";
  htmlcode +=".button-off {background-color: #7a8081;}\n";
  htmlcode +=".button-off:active {background-color: #626667;}\n";
  htmlcode +="p {font-size: 18px;color: #888;margin-bottom: 10px;}\n";
  htmlcode +="</style>\n";
  
  htmlcode +="</head>\n";
  htmlcode +="<body>\n";
  htmlcode +="<h1>ESP32 Web Server Excerise</h1>\n";
  htmlcode +="<h3>LED Control Sequence using Access Point(AP) Mode</h3>\n";
  
  if (LEDstatus == 1){
    htmlcode +="<p>LED Status: Blinking</p><a class=\"button button-on\" href=\"/blink\">Blink</a>\n";
    htmlcode +="<a class=\"button button-off\" href=\"/alternate\">Alternate</a>\n";
    htmlcode +="<a class=\"button button-off\" href=\"/ledoff\">OFF</a>\n";
  } 
  else if (LEDstatus == 2){
    htmlcode +="<p>LED Status: Alternating</p><a class=\"button button-off\" href=\"/blink\">Blink</a>\n";
    htmlcode +="<a class=\"button button-on\" href=\"/alternate\">Alternate</a>\n";
    htmlcode +="<a class=\"button button-off\" href=\"/ledoff\">OFF</a>\n";
  } 
  else{
    htmlcode +="<p>LED Status: OFF</p><a class=\"button button-off\" href=\"/blink\">Blink</a>\n";
    htmlcode +="<a class=\"button button-off\" href=\"/alternate\">Alternate</a>\n";
    htmlcode +="<a class=\"button button-off\" href=\"/ledoff\">OFF</a>\n";
  }
  
  htmlcode +="</body>\n";
  htmlcode +="</html>\n";
  return htmlcode;
}
