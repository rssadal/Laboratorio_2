#include "Arduino.h"
#define Numtimers 20
class timer{
  //const int Numtimers = 20;      //quantidade de timers alocados 
                                //para a aplicação
  typedef struct  {
    unsigned long value;    //Armazenará o valor à ser decrementado
    byte livre;             //flag que sinaliza se a
                            //posição no vetor está sendo utilizada  
  } type_timer_pool;
  type_timer_pool timer_pool[Numtimers];
  public:
    timer();
    byte get_timer(void);
    void free_timer(byte);
    void init_timer(byte, unsigned long);
    void timer_pool_init(void);
    unsigned long check_timer(byte);
    void decrement_timers(void);
};
