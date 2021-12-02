#include "WiFiConnection.h"
#include "WebServer.h"
#include <ESP8266WebServer.h>
#include <EEPROM.h>

WiFiConnection wiFiConnection  = WiFiConnection();
WebServer webServer = WebServer();
ESP8266WebServer serv(80);

void setup(){
  Serial.begin(115200);
  EEPROM.begin(512);
  String esid;
  String epass = "";
  for (int i = 0; i < 32; ++i){
      esid += char(EEPROM.read(i));
  }
  for (int i = 32; i < 96; ++i){
    epass += char(EEPROM.read(i));
  }
  if(esid.length() > 1){
    wiFiConnection.connectTo(esid.c_str(), epass.c_str());
  }
  else{
    wiFiConnection.startAP();
  }
  
  webServer.setup(&serv);
  
 
  Serial.print("SSID: ");
  Serial.println(esid);
  
}
void loop(){
  serv.handleClient();
}
