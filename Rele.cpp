#include "Rele.h"
#include <Arduino.h>
#define ON   0
#define OFF  1

Rele::Rele(int chan1,int chan2,int chan3,int chan4){
    if(chan1){
      this->IN1 = chan1;
      pinMode(this->IN1,ON);
    }
    if(chan2){
      this->IN2 = chan2;
      pinMode(this->IN2,ON);
    }
     if(chan3){
      this->IN3 = chan3;
      pinMode(this->IN3,ON);
    }
      if(chan4){
      this->IN4 = chan4;
      pinMode(this->IN4,ON);
    }
   
}

void Rele::releOnOff(int chan,int type){
  if(chan==1) pinMode(this->IN1,type);
   if(chan==2) pinMode(this->IN2,type);
   if(chan==3) pinMode(this->IN3,type);
   if(chan==4) pinMode(this->IN4,type);
}
