#ifndef Rele_H
#define Rele_H

class Rele {
  private:
    int IN1;
    int IN2;
    int IN3;
    int IN4;


  public:
    void releOnOff(int chan,int type);
    Rele(int chan1,int chan2,int chan3,int chan4);
};

#endif
