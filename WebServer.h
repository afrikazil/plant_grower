#ifndef WebServer_H
#define WebServer_H

#include <ESP8266WebServer.h>
//#include "JsonConfig.h"

class WebServer
{
  private:
    ESP8266WebServer* webServer;
    
    void webRoot();
    void webSetup();
    void webReboot();
    void webStyles();
    String getPoints();
    
  public:
   void setup(ESP8266WebServer* webServer);
};

#endif
