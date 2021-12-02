#include "WiFiConnection.h"
#include <ESP8266WiFi.h>

void WiFiConnection::startAP(){
  WiFi.softAP("PlantGrowerAP","");   
}
