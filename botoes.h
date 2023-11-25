#include "Arduino.h"
#define pressionado 11
#define nada 22

class botoes{
  int _porta;
  int count;
  int estado_botao=0;
  public:
    botoes(int);
    void tick(void);
    int status(void);
};