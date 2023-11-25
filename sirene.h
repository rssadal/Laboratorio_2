#include "Arduino.h"
#include "timer.h"
#define ligar_sirene 22
#define ligar_bip 33
#define desligar_sirene 44

class Sirene {

  int estado_sirene;
  byte tempo;
  int _porta;
  timer timer_sirene;

  public:
    Sirene(int);
    void base_tempo(void);
    void tick(void);
    void liga(int);

};
