#include <Arduino.h>
#ifndef WiFiConnection_H
#define WiFiConnection_H


//#include <ESP8266WebServer.h>
//#include "JsonConfig.h"

class WiFiConnection
{
  public:
    void startAP();
    void connectTo(String esid, String epass);
    bool testWiFi();
};

#endif
