#include "botoes.h"
#include "sirene.h"

botoes::botoes(int porta){
  _porta = porta;
  pinMode(_porta, INPUT_PULLUP);
  
}

int botoes::status(void){
  if(estado_botao==2){
    estado_botao=0;
    return pressionado;
  }else{
    return nada;
  }
}

void botoes::tick(void){

  switch(estado_botao){
    case 0:
        if(!digitalRead(_porta)){
          count++;
          if(count>50){
            estado_botao = 1;
          }
          
        }else{
          count = 0;
        }
      break;
    case 1:
        if(digitalRead(_porta)){
          count++;
          if(count>50){
            //buzzer.liga(ligar_bip);
            estado_botao = 2;
          }
        }else{
          count = 0;
        }
      break;
    case 2:

      break;
  }

}

