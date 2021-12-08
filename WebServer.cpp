#include "WebServer.h"
#include <ESP8266WiFi.h>
#include <EEPROM.h>
#include "time.h"
#include "Rele.h"


String printLocalTime()
{
  time_t rawtime;
  struct tm * timeinfo;
  time (&rawtime);
  timeinfo = localtime (&rawtime);
  return asctime(timeinfo);
}

String WebServer::getPoints(){
  String points = "";
  WiFi.mode(WIFI_AP_STA);
      delay(100);
      int n = WiFi.scanNetworks();
      for (int i = 0; i < n; ++i)
      {
        String netName=WiFi.SSID(i);

        points += "<input type='radio' id='id_"+netName+"' name='ssid' value='"+netName+"'>\
                <label for='id_"+netName+"'>"+netName+"</label><br>";       
      }
     
      delay(100);
  return points;
}

void WebServer::setupRoot()
{
    String content = "\
      <!DOCTYPE html>\r\n<html><head><meta charset='UTF-8'><meta http-equiv='X-UA-Compatible' content='IE=edge'><meta name='viewport' content='width=device-width, initial-scale=1.0'><title>Настройка подключения</title></head>\
      <style>.container{max-width: 600px;margin:0 auto;}</style>\
      <body><div class='container'>\
      <h1 align='center'>Настройка подключения контроллера к wi-fi</h1>\
      <form method='get' action='setting'>\
      "+getPoints()+"<br>\
      <input name='pass' length=64><input type='submit'></form>\
      </body></html>\
    ";

    webServer->send(200, "text/html", content);    
}


void WebServer::workRoot()
{
    String content = "\
      <!DOCTYPE html>\r\n<html><head><meta charset='UTF-8'><meta http-equiv='X-UA-Compatible' content='IE=edge'><meta name='viewport' content='width=device-width, initial-scale=1.0'><title>Ох бля, оно работает!</title></head>\
      <style>.container{max-width: 600px;margin:0 auto;}</style>\
      <body><div class='container'>\
      <h1 align='center'>"+printLocalTime()+"</h1>\
      </body></html>\
    ";

    webServer->send(200, "text/html", content);    
}

void WebServer::workRele()
{
    int chanNum =  webServer->arg("channel").toInt() || -1;
    String content = "";
    if(chanNum >-1){
      String type = webServer->arg("type");
      Rele rele = Rele(D1,D2,D3,D4);
      
      int ntype = rele.OFF;
  
      if(type=="on") rele.on(chanNum);
      else rele.off(chanNum); 

      content += "{'ssss':'"+String(chanNum)+" - " + type + "'}"; 
    }
    if(content.length()==0) content += "{'ssss':'ошибка'}";
      webServer->send(200, "text/html", content);    
}


void WebServer::webSetup()
{
    String qsid =  webServer->arg("ssid");
    String qpass = webServer->arg("pass");

    for (int i = 0; i < 96; ++i) { EEPROM.write(i, 0); }


    for (int i = 0; i < qsid.length(); ++i){
        EEPROM.write(i, qsid[i]);
    }

    for (int i = 0; i < qpass.length(); ++i)
    {
      EEPROM.write(32+i, qpass[i]);
    }
    EEPROM.commit();    
    String content = "{\"Success\":\"saved to eeprom... reset to boot into new wifi\"}";
    webServer->send(200, "application/json", content);
    delay(500);
    ESP.restart();
}

void WebServer::clearEeprom()
{
      String content = "<!DOCTYPE HTML>\r\n<html>";
      content += "<p>Clearing the EEPROM</p></html>";
      webServer->send(200, "text/html", content);
      for (int i = 0; i < 96; ++i) { EEPROM.write(i, 0); }
      EEPROM.commit();
      delay(500);
      ESP.restart();
}

void WebServer::setup(ESP8266WebServer* webServer, int initType)
{
  if(initType==0){
     webServer->on("/", [this](){ setupRoot(); });
     webServer->on("/setting", [this](){ webSetup(); });
  }
  else if(initType==1){
    webServer->on("/", [this](){ workRoot(); });
  }
   
    
    webServer->on("/cleareeprom", [this](){ clearEeprom(); });
     webServer->on("/workrele", [this](){ workRele(); });
    webServer->begin();

    this->webServer = webServer;
}
