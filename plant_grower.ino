#include "WiFiConnection.h"
#include "WebServer.h"
#include <ESP8266WebServer.h>


WiFiConnection wiFiConnection  = WiFiConnection();
WebServer webServer = WebServer();
ESP8266WebServer serv(80);

void setup(){
  webServer.setup(&serv);
  wiFiConnection.startAP();
}
void loop(){
  serv.handleClient();
}
