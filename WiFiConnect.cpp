#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WebServer.h>
#include "Eeprom.cpp"

Eeprom eeprom = Eeprom();
bool testWifi(void){
  int c = 0;
  while ( c < 20 ) {
    if (WiFi.status() == WL_CONNECTED){
          return true;
    }
    delay(500);
    c++;
  }
      return false;
};

void launchWeb(){
  createWebServer();
  // Start the server
  server.begin();
}

void setupColdBoot(){
  WiFi.disconnect();
  delay(10);
  pinMode(LED_BUILTIN, OUTPUT);
  eeprom.readSettings();
      WiFi.begin(eeprom.esid.c_str(), eeprom.epass.c_str());

       if (testWifi()){
          return;
        }
        else
        {
          Serial.println("Turning the HotSpot On");
          launchWeb();
          setupAP();// Setup HotSpot
        } 
         while ((WiFi.status() != WL_CONNECTED)){
          delay(100);
          server.handleClient();
        }
    };


class Coldboot {
  private:  
    int i = 0;
    int statusCode;
    const char* ssid = "text";
    const char* passphrase = "text";
    String st;
    String content;
    ESP8266WebServer server;

   

  public:
    Coldboot() : server(80){};    
   
   
   
 

    void setupAP(void){
      WiFi.mode(WIFI_STA);
      WiFi.disconnect();
      delay(100);
      int n = WiFi.scanNetworks();
    
      this->st = "<ol>";
      for (int i = 0; i < n; ++i)
      {
        // Print SSID and RSSI for each network found
        this->st += "<li>";
        this->st += WiFi.SSID(i);
        this->st += " (";
        this->st += WiFi.RSSI(i);
     
        this->st += ")";
        this->st += (WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "*";
        this->st += "</li>";
      }
      this->st += "</ol>";
      delay(100);
      WiFi.softAP("how2electronics", "");
      launchWeb();
    };
  void onServerRoot(){
      IPAddress ip = WiFi.softAPIP();
      String ipStr = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);
      this->content = "<!DOCTYPE html>\r\n<html><head><meta charset='UTF-8'><meta http-equiv='X-UA-Compatible' content='IE=edge'><meta name='viewport' content='width=device-width, initial-scale=1.0'><title>Настройка подключения</title></head>";
      this->content +=  "<style>.container{max-width: 600px;margin:0 auto;}</style>";
      this->content += "<body><div class='container'>";
      this->content += "<h1 align='center'>Настройка подключения контроллера к wi-fi</h1>";
      this->content += "<form action=\"/scan\" method=\"POST\"><input type=\"submit\" value=\"Сканировать\"></form>";
      this->content += ipStr;
      this->content += "<p>";
      this->content += this->st;
      this->content += "</p><form method='get' action='setting'><label>SSID: </label><input name='ssid' length=32><input name='pass' length=64><input type='submit'></form>";
      this->content += "</div></body>";
      this->content += "</html>";
      this->server.send(200, "text/html", this->content);
    };
    void createWebServer(){
      this->server.on("/",[](){
          IPAddress ip = WiFi.softAPIP();
          String ipStr = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);
          String content = "<!DOCTYPE html>\r\n<html><head><meta charset='UTF-8'><meta http-equiv='X-UA-Compatible' content='IE=edge'><meta name='viewport' content='width=device-width, initial-scale=1.0'><title>Настройка подключения</title></head>";
          content +=  "<style>.container{max-width: 600px;margin:0 auto;}</style>";
          content += "<body><div class='container'>";
          content += "<h1 align='center'>Настройка подключения контроллера к wi-fi</h1>";
          content += "<form action=\"/scan\" method=\"POST\"><input type=\"submit\" value=\"Сканировать\"></form>";
          content += ipStr;
          content += "<p>";
          content += this->st;
          content += "</p><form method='get' action='setting'><label>SSID: </label><input name='ssid' length=32><input name='pass' length=64><input type='submit'></form>";
          content += "</div></body>";
          content += "</html>";
          server.send(200, "text/html", content);
        });
    };
   
};
 
