#include "WebServer.h"
#include <ESP8266WiFi.h>

String WebServer::getPoints(){
  String points = "";
  WiFi.mode(WIFI_AP_STA);
      delay(100);
      int n = WiFi.scanNetworks();
      for (int i = 0; i < n; ++i)
      {
        String netName=WiFi.SSID(i);

        points += "<input type='radio' name='accessPoints' value='"+netName+"'>\
                <label for='html'>"+netName+"</label><br>";       
      }
     
      delay(100);
  return points;
}

void WebServer::webRoot()
{
    String content = "\
      <!DOCTYPE html>\r\n<html><head><meta charset='UTF-8'><meta http-equiv='X-UA-Compatible' content='IE=edge'><meta name='viewport' content='width=device-width, initial-scale=1.0'><title>Настройка подключения</title></head>\
      <style>.container{max-width: 600px;margin:0 auto;}</style>\
      <body><div class='container'>\
      <h1 align='center'>Настройка подключения контроллера к wi-fi</h1>\
      <form method='get' action='setting'>\
      "+getPoints()+"<br>\
      <input name='pass' length=64><input type='submit'></form>\
    ";

    webServer->send(200, "text/html", content);    

}

void WebServer::setup(ESP8266WebServer* webServer)
{
    webServer->on("/", [this](){ webRoot(); });
//    webServer->on("/setup", [this](){ webSetup(); });
//    webServer->on("/reboot", [this](){ webReboot(); });
//    webServer->on("/styles.css", [this](){ webStyles(); });
//    webServer->onNotFound([this](){ handleNotFound(); });
    webServer->begin();

    this->webServer = webServer;
//    this->config = config;
//    this->rebootFunction = rebootFunction;
}
