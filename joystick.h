#include "Arduino.h"
#define pressionado 11
#define nada 22
#define alto 33
#define baixo 44

class joystick{
  int _porta;
  int _nivel;
  int count;
  int estado_botao=0;
  public:
    joystick(int, int);
    void tick(void);
    int status(void);
};