#include "WiFiConnection.h"
#include <ESP8266WiFi.h>
#include <Arduino.h>
void WiFiConnection::startAP(){
  WiFi.softAP("PlantGrowerAP","");   
}

void WiFiConnection::connectTo(String esid, String epass){
  WiFi.begin(esid, epass);
}

bool WiFiConnection::testWiFi(){
  int c = 0;
  while ( c < 20 ) {
    if (WiFi.status() == WL_CONNECTED) { return true; } 
    delay(500);
    c++;
  }
  return false;
}
