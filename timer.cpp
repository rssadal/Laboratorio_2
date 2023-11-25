#include "timer.h"

timer::timer(){
  
}

byte timer::get_timer(void){
  for(byte i=0; i<Numtimers; i++){
    if(timer_pool[i].livre){
      timer_pool[i].livre = false;
      return i;
    }
  }
}

void timer::free_timer(byte i){
  timer_pool[i].livre = true;
}

void timer::init_timer(byte i, unsigned long valor){
 timer_pool[i].value = valor;
}

void timer::timer_pool_init(void){
   for(byte i=0; i<Numtimers; i++){
    timer_pool[i].value = 0;
    timer_pool[i].livre = true;
  }
}

unsigned long timer::check_timer(byte i){
  return timer_pool[i].value;
}

void timer::decrement_timers(void){
  for(byte i=0; i<Numtimers; i++){
    if(timer_pool[i].livre == false){
      if(timer_pool[i].value > 0){
        timer_pool[i].value--;
      }
    }
  }
}
