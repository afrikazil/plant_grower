#include "WiFiConnection.h"
#include <ESP8266WiFi.h>
#include <Arduino.h>
void WiFiConnection::startAP(){
  WiFi.softAP("PlantGrowerAP","");   
}

void WiFiConnection::connectTo(String esid, String epass){
  WiFi.begin(esid, epass);
}
