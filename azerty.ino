#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <ArduinoJson.h>

const char *SSID = "TP-LINK_5982";
const char *PWD = "eunice22";
#define RED_LED 25 
#define POT 34
 
WebServer server(80);
 
void connectToWiFi() {
  Serial.print("Connecting to ...");
  Serial.println(SSID);
  
  WiFi.begin(SSID, PWD);
  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
    // we can even make the ESP32 to sleep
  }
 
  Serial.print("Connected. IP: ");
  Serial.println(WiFi.localIP());
}

void getPOT() {
 
  int power=analogRead(POT);
  
  server.send(200, "text", String(power));
  
}
 
void getRED_LED(){
  Serial.println("Get RED_LED");
  if(digitalRead(RED_LED)==LOW){
    digitalWrite(RED_LED, HIGH);
  }
  else{
    digitalWrite(RED_LED, LOW);
  }
}

// setup API resources
void setup_routing() {
  
 
  server.on("/POT", getPOT);
  server.on("/RED_LED", getRED_LED);
 
  // start server
  server.begin();
}

void setup() {	 	 
  Serial.begin(9600);	 	 
 	Serial.println("Begining...");	 
 	 
  
  connectToWiFi();	 	 
  pinMode(RED_LED, OUTPUT);
  digitalWrite(RED_LED, LOW);
 
  setup_routing(); 	 	 
  	 	 
   
}	 	 
  	 	 
void loop() {	 	 
  server.handleClient();	 
   
}