#ifndef Rele_H
#define Rele_H

class Rele {
  private:
    int IN1;
    int IN2;
    int IN3;
    int IN4;
    void releTurn(int chan, int type);

  public:
    int ON=0;
    int OFF=1;
    void on(int chan);
    void off(int chan);
    Rele(int chan1,int chan2,int chan3,int chan4);
};

#endif
