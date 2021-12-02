#include "WiFiConnection.h"
#include "WebServer.h"
#include <ESP8266WebServer.h>
#include <EEPROM.h>
#include "time.h"

WiFiConnection wiFiConnection  = WiFiConnection();
WebServer webServer = WebServer();
ESP8266WebServer serv(80);


void setupClock(){
  const char* ntpServer = "pool.ntp.org";
  const long  gmtOffset_sec = 10800;   //Replace with your GMT offset (seconds)
  const int   daylightOffset_sec = 0; //Replace with your daylight offset (seconds)
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer); 
}


void startSetupMode(){
  wiFiConnection.startAP();
  webServer.setup(&serv,0);
}

void startWorkMode(){
  webServer.setup(&serv,1);
  setupClock();
}

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
    if(!wiFiConnection.testWiFi()){
       startSetupMode();
    }
    else{
      startWorkMode();
    }
  }
  else{
    startSetupMode();   
  }
  
}
void loop(){
  serv.handleClient();
}
