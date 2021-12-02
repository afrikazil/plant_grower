#include "Coldboot.cpp"

Coldboot coldboot;

void setup(){
  Coldboot coldboot  = Coldboot();
}
void loop(){
  coldboot.createWebServer();
}
