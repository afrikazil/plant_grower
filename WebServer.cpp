#include "WebServer.h"

void WebServer::webRoot()
{
 

    webServer->send(200, "text/html", "345345345345");    

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
