#include "WiFiConnection.h"

WiFiConnection wiFiConnection;

void setup(){
  wiFiConnection = WiFiConnection();
  wiFiConnection.startAP();
}
void loop(){

}
