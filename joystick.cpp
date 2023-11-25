#include "joystick.h"
#include "sirene.h"

joystick::joystick(int porta, int nivel) {
  _porta = porta;
  _nivel = nivel;
  if (nivel == alto) {
    estado_botao = 0;
  } else {
    estado_botao = 3;
  }
  pinMode(_porta, INPUT);
}

int joystick::status(void) {
  if (estado_botao == 2) {
    estado_botao = 0;
    return pressionado;
  } else if (estado_botao == 5) {
    estado_botao = 3;
    return pressionado;
  } else {
    return nada;
  }
}

void joystick::tick(void) {
  switch (estado_botao) {
    case 0:
      if (analogRead(_porta) > 750) {
        count++;
        if (count > 50) {
          estado_botao = 1;
        }

      } else {
        count = 0;
      }
      break;
    case 1:
      if (analogRead(_porta) <= 750) {
        count++;
        if (count > 50) {
          estado_botao = 2;
        }
      } else {
        count = 0;
      }
      break;
    case 2:
      break;
    case 3:
      if (analogRead(_porta) < 250) {
        count++;
        if (count > 50) {
          estado_botao = 4;
        }
      } else {
        count = 0;
      }
      break;
    case 4:
      if (analogRead(_porta) >= 250) {
        count++;
        if (count > 50) {
          estado_botao = 5;
        }
      } else {
        count = 0;
      }
      break;
    case 5:
      break;
  }
}
