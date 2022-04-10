/* 
* AUTOR: ARLAND MICHELENA VILLEGAS
* GITHUB: https://github.com/ArlandMv/
* FECHA: 07/04/2022
* DESCRIPCION:
*   Este equipo tiene como funcion analizar la mayor cantidad   
*   de sensores en ubicaciones donde la conectividad WiFi o 
*   Ethernet no este disponible. 
*   Al detectar agua, alarma a seguridad mediante cables de
*   energia comun.
*/
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h> //me-no-dev/ESPAsyncTCP@1.2.2
#include <ESPAsyncWebServer.h> //ottowinter/ESPAsyncWebServer-esphome@2.1.0
#include <AsyncElegantOTA.h> //ayushsharma82/AsyncElegantOTA@2.2.6

// Replace with your network credentials
const char* ssid = "FMV24";
const char* password = "owl6357790";

AsyncWebServer server(80);

unsigned long last_time;
const long delay_time = 5000; // 60 seconds

//pins mas seguros para relays
const int relay1 = 5; //D1
const int relay2 = 4; //D2
const int relay3 = 14;//D5
const int relay4 = 12;//D6
//pins digitales de sensores
//PROBLEMATIC GPIO/PINS => 0-D3 
const int sensor1 = 0; //D3   unplug to FLASH!  
const int sensor2 = 2; //D4 fails if wet on flash
const int sensor3 = 13; //D7  OK 
const int sensor4 = 15; //D8  unplog to start
//check pins switching sensor 1 to analogic!  


/* FUNCTIONS DECLARATIONS */

void turnOnRelay(int relay);
void turnOffRelay(int relay);
void signalWithRelay(int relay);
void analizeSensor(int sensorPin, int relay);

//shows board is active
void blink(int time){
  digitalWrite(LED_BUILTIN, HIGH);
  delay(time);
  digitalWrite(LED_BUILTIN, LOW);
  delay(time);
}

void setup() {
  last_time = millis();
  //pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200); 
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);
  //PINS START WITH LOW STATUS
  turnOffRelay(relay1);
  turnOffRelay(relay2);
  turnOffRelay(relay3);
  turnOffRelay(relay4);
  //other devices
  //declaring pinMode for sensors
  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
  pinMode(sensor3, INPUT);
  pinMode(sensor4, INPUT); 

  //OTA Updates  (Over The Air) 
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(5000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", "Hi! I am ESP8266.");
  });

  AsyncElegantOTA.begin(&server);    // Start ElegantOTA
  server.begin();
  Serial.println("HTTP server started");
  
}

void loop() {
  Serial.println("START LOOP");
  long time = millis() - last_time;
  Serial.print("TIME: " + String(time/1000));
  Serial.print(" >? "+String(delay_time/1000));

  if (time > delay_time) {
    last_time = millis();
    Serial.println("\nSENSOR1 --> D3");
    analizeSensor(sensor1, relay1);
    Serial.println("\nSENSOR2 --> D4");
    analizeSensor(sensor2, relay2);
    Serial.println("\nSENSOR3 --> D7");
    analizeSensor(sensor3, relay3);
    Serial.println("\nSENSOR4 --> D8");
    analizeSensor(sensor4, relay4); 
  }
  Serial.println("\nEND LOOP\n");
  delay(5000);
}

/* FUNCTIONS DEFINITIONS */
/* 
*RELAY: Normally Open configuration, send LOW signal to let current flow 
*/

void turnOnRelay(int relay){
  digitalWrite(relay, LOW);
  //Serial.println("Current Flowing on relay connected to GPIO:" + String(relay));
}
void turnOffRelay(int relay){
  digitalWrite(relay, HIGH);
  //Serial.println("Current NOT Flowing on relay connected to GPIO: " + String(relay));
}
void signalWithRelay(int relay){
    turnOnRelay(relay);
    delay(2000);
    turnOffRelay(relay);
    Serial.println("signalWithRelay on GPIO: " + String(relay));
}
void toggleRelay(int relay){
  if(digitalRead(relay) == HIGH){
    turnOnRelay(relay);
  }else{
    turnOffRelay(relay);
  }
}

void analizeSensor(int sensorPin, int relay){
  if (digitalRead(sensorPin) == LOW) {
    signalWithRelay(relay);
    Serial.println("water DETECTED on pin: " + String(sensorPin));
  }
  else {
      Serial.println("water NOT detected on pin: " + String(sensorPin));
  }
}