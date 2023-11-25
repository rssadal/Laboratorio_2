#include "sirene.h"
#include "cancao.h"

Sirene::Sirene(int porta){
  _porta=porta;
  pinMode(porta, OUTPUT);
  timer_sirene.timer_pool_init();
  
}

void Sirene::base_tempo(void){
  timer_sirene.decrement_timers();
}

void Sirene::liga(int acao){
  if(estado_sirene == 5){
    if(acao == ligar_sirene){
      estado_sirene = 1;
    }else if(acao == ligar_bip){
      estado_sirene = 3;
    }
  }
  if(acao == desligar_sirene && (estado_sirene == 1 || estado_sirene == 2)){
    estado_sirene = 4;
    
  }
}


void Sirene::tick(void){

  switch(estado_sirene){
    case 0:
      tempo=timer_sirene.get_timer();
      estado_sirene = 5;
      break;
    case 1:
      if(!timer_sirene.check_timer(tempo)){
        sound();
        timer_sirene.init_timer(tempo,1000);
        Serial.println("led ligado");
        estado_sirene = 2;
      }
      break;
    case 2:
      if(!timer_sirene.check_timer(tempo)){
        noTone(_porta);
        timer_sirene.init_timer(tempo,1000);
        Serial.println("led desligado");
        estado_sirene = 1;
      }
      break;
    case 3:
      timer_sirene.init_timer(tempo, 100);
      tone(_porta, 440);
      estado_sirene=4;
      break;
    case 4:
       if(!timer_sirene.check_timer(tempo)){
        noTone(_porta);
        estado_sirene = 5;
      break;
    case 5:
      
      break;
  }

}
}
