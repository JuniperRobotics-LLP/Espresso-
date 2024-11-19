#include <WiFi.h>
#include <WebServer.h>
#include "Espresso.h"

// Set your access point network credentials
const char* ssid = "LED_ON/OFF_EXAMPLE "; //change "LED_ON/OFF_YOURNAME" to your name.

#define LEFT_IR_SENSOR_PIN 14 
#define RIGHT_IR_SENSOR_PIN 27

WebServer server(80);

bool LEDstatus = LOW;

void setup() {
  init();
  Serial.begin(115200);
  pinMode(LEFT_IR_SENSOR_PIN, OUTPUT);    
  pinMode(RIGHT_IR_SENSOR_PIN, OUTPUT);  

// Wi-Fi connection
  Serial.print("Creating WiFi AP for ");
  Serial.println(ssid);
  // Remove the password parameter, if you want the AP (Access Point) to be open
  //  WiFi.softAP(ssid, password);
  WiFi.softAP(ssid);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  Serial.println("");
  Serial.println("WiFi connected");
  
  server.on("/", handle_OnConnect);
  server.on("/ledon", handle_ledon);
  server.on("/ledoff", handle_ledoff);
  server.onNotFound(handle_NotFound);
  
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  updateEyes();
  server.handleClient();
  if (LEDstatus) {
    digitalWrite(RIGHT_IR_SENSOR_PIN, LOW);
  } else {
    digitalWrite(RIGHT_IR_SENSOR_PIN, HIGH);
  }

  if (LEDstatus) {
    digitalWrite(LEFT_IR_SENSOR_PIN, LOW);
  } else {
    digitalWrite(LEFT_IR_SENSOR_PIN, HIGH);
  }
}

void handle_OnConnect() {
  LEDstatus = LOW;  
  Serial.println("LED Status: OFF");
  server.send(200, "text/html", getHTML()); 
}

void handle_ledon() {
  LEDstatus = HIGH;  
  Serial.println("LED Status: ON");
  server.send(200, "text/html", getHTML()); 
}

void handle_ledoff() {
  LEDstatus = LOW;  
  Serial.println("LED Status: OFF");
  server.send(200, "text/html", getHTML()); 
}

void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}

String getHTML(){
  String htmlcode = "<!DOCTYPE html> <html>\n";
  htmlcode +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  htmlcode +="<title>LED Control</title>\n";
  
  htmlcode +="<style>html { font-family: Open Sans; display: inline-block; margin: 0px auto; text-align: center;}\n";
  htmlcode +="body{margin-top: 50px;} h1 {color: #154c79;margin: 30px auto 30px;} h3 {color: #1e81b0;margin-bottom: 50px;}\n";
  htmlcode +=".button {display: block;width: 150px;background-color: #3498db;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  htmlcode +=".button-on {background-color: #22d60b;}\n";
  htmlcode +=".button-on:active {background-color: #1e7b15;}\n";
  htmlcode +=".button-off {background-color: #7a8081;}\n";
  htmlcode +=".button-off:active {background-color: #b50d0d;}\n";
  htmlcode +="p {font-size: 18px;color: #888;margin-bottom: 10px;}\n";
  htmlcode +="</style>\n";
  
  htmlcode +="</head>\n";
  htmlcode +="<body>\n";
  htmlcode +="<h1>ESP32 Web Server ON/OFF</h1>\n";
  htmlcode +="<h3>LED Control using Access Point(AP) Mode</h3>\n";
  
  if (LEDstatus){
    htmlcode +="<p>IR Sensor LED Light Status: ON</p><a class=\"button button-off\" href=\"/ledoff\">OFF</a>\n";
  }
  else{
    htmlcode +="<p>IR Sensor LED Light Status: OFF</p><a class=\"button button-on\" href=\"/ledon\">ON</a>\n";
  }

  htmlcode +="</body>\n";
  htmlcode +="</html>\n";
  return htmlcode;
}
